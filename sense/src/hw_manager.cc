/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense hardware manager.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/hw_manager.h>
#include <soul/sense/hw_plugin_profile.h>

#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS                                                            //
///////////////////////////////////////////////////////////////////////////////

SoulSenseHwManager::SoulSenseHwManager(const SoulSenseHwManagerParameters& params) : params_(params)
{
  loadPlugins();
  configurePlugins();
}

void SoulSenseHwManager::activatePlugins(void)
{
  // For each loaded plugin, configure them.
  auto&& loaded_plugins = pluginman_.listLoadedPlugins();

  for (auto& p : loaded_plugins)
  {
    std::cerr << "Hardware manager loaded plugin: " << p << std::endl;
    auto* plugin = dynamic_cast<SenseHwPluginInterface*>(pluginman_.getPlugin(p));

    plugin->activate();
  }
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS                                                           //
///////////////////////////////////////////////////////////////////////////////

void SoulSenseHwManager::loadPlugins(void)
{
  if (params_.plugin_dir.empty())
  {
    std::string error = "SoulSenseHwManager: No plugin directory given!\n";
    std::cerr << error;
    throw std::runtime_error(error);
  }

  if (params_.section_name.empty())
  {
    std::string error = "SoulSenseHwManager: No section name given!\n";
    std::cerr << error;
    throw std::runtime_error(error);
  }

  pluginman_.loadAll(params_.plugin_dir, params_.section_name);
}

void SoulSenseHwManager::configurePlugins(void)
{
  auto&& loaded_plugins = pluginman_.listLoadedPlugins();

  for (auto& p : loaded_plugins)
  {
    auto* plugin = dynamic_cast<SenseHwPluginInterface*>(pluginman_.getPlugin(p));

    // TODO: parameter loading.
    std::unordered_map<std::string, std::string> params;
    plugin->configure(params);

    // Setup messaging system.
    setupMessaging(plugin);
  }
}

void SoulSenseHwManager::setupMessaging(SenseHwPluginInterface* plugin)
{
  auto* profile = reinterpret_cast<const SenseHwPluginProfile*>(plugin->getProfile());

  if (!params_.msgman)
  {
    std::cerr << "ERROR: SoulSenseHwManager: no message manager access provided!\n";
    return;
  }

  // Publish
  for (auto& pub : profile->pubs)
    params_.msgman->publish(pub.msg_id, pub);

  // Set messaging function
  plugin->setMessageSender(params_.sender);
}

}  // namespace sense
}  // namespace soul