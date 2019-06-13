/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_PLUGINS_MANAGER_H_
#define SOUL_PLUGINS_MANAGER_H_

/*
 * Plugin manager for loading and unloading plugins.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/plugins/interface.h>

#include <boost/config.hpp>
#include <boost/dll/import.hpp>
#include <boost/dll/library_info.hpp>
#include <boost/dll/shared_library.hpp>

#include <algorithm>
#include <experimental/filesystem>  // If gcc > 7 this will become <filesystem>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/** Signature for plugin load callback function. */
using PluginLoadCallback =
    std::function<void(const std::string plugin_path, const std::string section_name, const std::string symbol_name)>;

/** Signature for plugin unload callback function. */
using PluginUnloadCallback = std::function<void(const std::string plugin_name)>;

///////////////////////////////////////////////////////////////////////////////
// CLASSES                                                                   //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Templated plugin manager that can be used by different systems for plugin management.
 * @tparam PluginType Plugin class type.
 */
template <typename PluginType>
class PluginManager
{
public:
  /**
   * @brief Destructor. Force destruction of plugins first to avoid crash on exit bugs.
   */
  ~PluginManager()
  {
    unloadAll();
  }

  /**
   * @brief Get a pointer to a loaded plugin.
   * @param plugin_name Name of the plugin.
   * @return Raw pointer to the plugin.
   * @throws std::runtime_error if there is a problem, e.g., the plugin is not loaded.
   */
  PluginType* getPlugin(const std::string plugin_name)
  {
    if (plugins_.find(plugin_name) == plugins_.end())
      throw std::runtime_error("Plugin not found.");

    return plugins_[plugin_name].get();
  }

  /**
   * @brief List all loaded plugins.
   * @return List of plugin names.
   */
  std::vector<std::string> listLoadedPlugins()
  {
    std::vector<std::string> plugins;

    for (auto& plugin : plugins_)
      plugins.push_back(plugin.first);

    return plugins;
  }

  /**
   * @brief Given a library path to search in, and a section name, attempt to load the plugin via the plugin factory.
   * @param library_path Directory containing the library.
   * @param library_name Name of the library. The suffix (e.g., .so) should
   * be omitted.
   * @param section_name Name of the section your plugin is exported under.
   * @return True on success, false otherwise.
   */
  bool load(const std::string library_dir, const std::string library_name, const std::string section_name)
  {
    const auto plugin_name = getPluginName(section_name, library_name);
    const auto plugin_path = getPluginPath(library_dir, library_name);

    if (plugins_.find(plugin_name) != plugins_.end())
    {
      std::cerr << "Plugin is already loaded. Skipping.\n";
      return false;
    }

    if (!containsSymbols(plugin_path, section_name, plugin_factory_method_name_))
    {
      std::cerr << "Library " << library_name << " does not contain " << plugin_factory_method_name_ << ". Skipping.\n";
      return true;
    }

    if (load_cb_ != nullptr)
      load_cb_(plugin_path, section_name, plugin_factory_method_name_);

    boost::dll::shared_library shlib(plugin_path);
    shared_libs_.insert_or_assign(plugin_name, std::move(shlib));
    auto creator =
        boost::dll::import_alias<std::unique_ptr<PluginType>()>(shared_libs_[plugin_name], plugin_factory_method_name_);

    auto plugin = creator();
    plugins_.insert_or_assign(plugin_name, std::move(plugin));

    return true;
  }

  /**
   * @brief Given a directory and a section name, attempts to load all objects contained in shared libraries in that
   * directory with the section name.
   * @param directory Directory path to search for plugin libraries.
   * @param section_name Name of the section your plugin is exported under.
   * @return True on success, or false if there was a failure.
   */
  bool loadAll(const std::string directory, const std::string section_name)
  {
    const auto&& shared_libs = getSharedLibs(directory);
    const auto&& plugin_names = getPluginNameFromFileName(shared_libs);

    for (const auto& library_name : plugin_names)
    {
      if (!load(directory, library_name, section_name))
      {
        std::cerr << "Error loading " << library_name << "\n";
        return false;
      }
    }

    return true;
  }

  /**
   * @brief Sets a callback to be called whenever it loads a plugin.
   * @param cb Callback function.
   */
  void setLoadCallback(PluginLoadCallback cb)
  {
    load_cb_ = cb;
  }

  /**
   * @brief Sets a callback to be called whenever it unloads a plugin.
   * @param cb Callback function.
   */
  void setUnloadCallback(PluginUnloadCallback cb)
  {
    unload_cb_ = cb;
  }

  /**
   * @brief Unloads a specified plugin.
   * @param plugin_name Name of the plugin to try unload.
   * @return True if succeeded.
   */
  bool unload(const std::string plugin_name)
  {
    if (unload_cb_ != nullptr)
      unload_cb_(plugin_name);

    if (plugins_.find(plugin_name) == plugins_.end())
    {
      std::cerr << "Unable to unload " << plugin_name << ". Not found.\n";
      return false;
    }

    plugins_.erase(plugin_name);
    shared_libs_.erase(plugin_name);

    return true;
  }

  /**
   * @brief Tries to unload all plugins. If it fails it will leave it in a partially unloaded state.
   * @return True if succeeded.
   */
  bool unloadAll()
  {
    std::vector<std::string> plugins;

    for (auto& entry : plugins_)
      plugins.push_back(entry.first);

    for (auto& plugin : plugins)
    {
      if (!unload(plugin))
        return false;
    }

    return true;
  }

#ifndef HR_DEBUG
private:
#endif
  /** Callback to invoke when loading a plugin. */
  PluginLoadCallback load_cb_;

  /** Callback to invoke when unloading a plugin. */
  PluginUnloadCallback unload_cb_;

  /** Loaded shared libraries. */
  std::unordered_map<std::string, boost::dll::shared_library> shared_libs_;

  /** Contains all the plugins that have been loaded. */
  std::unordered_map<std::string, std::unique_ptr<PluginType>> plugins_;

  /**
   * @brief Checks whether a library contains a symbol under a particular section name.
   * @param plugin_path File path for the plugin shared library.
   * @param section_name Section name for the symbol.
   * @param symbol Symbol name.
   * @return True if symbol found, false otherwise.
   */
  bool containsSymbols(const std::string plugin_path, const std::string section_name, const std::string symbol)
  {
    boost::dll::library_info info(plugin_path);
    std::vector<std::string> exports = info.symbols(section_name);

    const auto sym = std::find(exports.begin(), exports.end(), symbol);

    if (sym == exports.end())
    {
      std::cerr << "Cannot find symbol " << symbol << " in plugin " << plugin_path << "\n";
      return false;
    }

    return true;
  }

  /**
   * @brief Get the plugin name string.
   * @param section_name Section name the plugin symbol is exported under.
   * @param library_name Shared object library name.
   * @return Plugin name string.
   */
  std::string getPluginName(const std::string section_name, const std::string library_name)
  {
    return section_name + "," + library_name;
  }

  /**
   * @brief Get the plugin path
   * @param library_dir Plugin directory.
   * @param library_name Shared object library name.
   * @return Plugin path string.
   */
  std::string getPluginPath(const std::string library_dir, const std::string library_name)
  {
    return library_dir + "/lib" + library_name + ".so";
  }

  /**
   * @brief Get the shared library file names as candidates.
   * @param directory Directory name to scan for shared library objects.
   * @return List of shared library files.
   */
  std::vector<std::string> getSharedLibs(const std::string directory)
  {
    std::vector<std::string> shared_libs;
    for (auto& p : std::experimental::filesystem::directory_iterator(directory))
    {
      const auto path = p.path();
      const std::string filename = path.filename();

      const size_t fsize = filename.size();

      if (fsize < 3)
        continue;

      const std::string suffix = filename.substr(fsize - 3, 3);
      if (suffix != ".so")  // Linux specific. Worry about portability later.
        continue;

      shared_libs.push_back(filename.substr(0, fsize - 3));
    }

    return shared_libs;
  }

  /**
   * @brief Parse the shared library name and remove the prefix (lib) and suffix (.so) from the filename.
   * @param shared_libs List of shared library file names.
   * @return List of plugin names.
   */
  std::vector<std::string> getPluginNameFromFileName(const std::vector<std::string>& shared_libs)
  {
    std::vector<std::string> names;

    for (auto& lib : shared_libs)
    {
      const size_t str_size = lib.size();
      if (str_size < 4)
        continue;

      const auto libindex = lib.find_first_of("lib") + 3;
      if (str_size < libindex)
        continue;

      const auto remaining_size = str_size - libindex;
      const auto pname = lib.substr(libindex, remaining_size);
      names.push_back(pname);
    }

    return names;
  }
};

}  // namespace soul
#endif  // SOUL_PLUGINS_MANAGER_H_