/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MANAGER_H_
#define SOUL_SENSE_MANAGER_H_

/*
 * Soul sense manager. Responsible for the perception system.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/manager.h>
#include <soul/plugins/manager.h>
#include <soul/sense/hw_manager.h>
#include <soul/sense/plugin_interface.h>

#include <future>
#include <memory>
#include <string>
#include <thread>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * Parameters for the Soul sense manager.
 */
struct SoulSenseManagerParameters
{
  std::string plugin_dir;    ///< Plugin directory containing all the perception plugins.
  std::string section_name;  ///< Section name.

  /**
   * @brief Constructor to help with initialisation.
   * @param pd Plugin directory.
   * @param sn Section name.
   */
  SoulSenseManagerParameters(std::string pd = default_plugin_directory_, std::string sn = plugin_section_name_)
    : plugin_dir(pd), section_name(sn)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
// CLASSES                                                                   //
///////////////////////////////////////////////////////////////////////////////

class SoulSenseManager final
{
public:
  /**
   * @brief Constructor that takes configuration options.
   * @params Configuration options.
   * @param Hardware manager configuration.
   */
  explicit SoulSenseManager(const SoulSenseManagerParameters& params, const SoulSenseHwManagerParameters& hwparams);
  // explicit SoulSenseManager(const SoulSenseManagerParameters& params);

  /**
   * @brief Control the destruction sequence.
   */
  ~SoulSenseManager();

  /**
   * @brief Handle the interrupt signal. Useful for debugging.
   */
  void interrupt(void);

  /**
   * @brief Run the event loop.
   */
  void run(void);

#ifndef HR_DEBUG
private:
#endif
  /** Manager parameters. */
  SoulSenseManagerParameters params_;

  /** Plugin manager. */
  PluginManager<soul::sense::SensePluginInterface> pluginman_;

  /** Messaging manager. */
  MessageManager msgman_;

  /** Hardware manager parameters. */
  SoulSenseHwManagerParameters hw_params_;

  /** Hardware manager. */
  std::unique_ptr<SoulSenseHwManager> hwman_;

  /**
   * @brief Load perception plugins.
   */
  void loadPlugins(void);

  /**
   * @brief Configure plugins.
   */
  void configurePlugins(void);

  /**
   * @brief Start the plugins. Threaded plugins will be run here.
   */
  void activatePlugins(void);

  /**
   * @brief Setup messaging for the plugin.
   * @param plugin Pointer to the plugin.
   */
  void setupMessaging(SensePluginInterface* plugin);
};

}  // namespace sense
}  // namespace soul

#endif  // SOUL_SENSE_MANAGER_H_