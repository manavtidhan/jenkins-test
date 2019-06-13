/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense hardware manager.
 *
 * Author: Tuan Chien
 */

#ifndef SOUL_SENSE_HW_MANAGER_H_
#define SOUL_SENSE_HW_MANAGER_H_

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/manager.h>
#include <soul/plugins/manager.h>
#include <soul/sense/hw_plugin_interface.h>
#include <soul/sense/plugin_state.h>

#include <string>

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
struct SoulSenseHwManagerParameters
{
  std::string plugin_dir;    ///< Plugin directory containing all the hardware plugins.
  std::string section_name;  ///< Section name.

  MessageSenderFn sender;  ///< Message sender function.
  MessageManager* msgman;  ///< Pointer to the perception message manager.

  /**
   * @brief Constructor to help with initialisation.
   * @param pd Plugin directory.
   * @param sn Section name.
   */
  SoulSenseHwManagerParameters(std::string pd = default_hw_plugin_directory_, std::string sn = hw_plugin_section_name_,
                               MessageManager* const mm = nullptr)
    : plugin_dir(pd), section_name(sn), msgman(mm)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
// CLASSES                                                                   //
///////////////////////////////////////////////////////////////////////////////

/** Perception hardware manager. */
class SoulSenseHwManager final
{
public:
  /**
   * @brief Constructor that takes configuration options.
   * RAII for now. It will load all plugins it finds and activate them.
   * @params Configuration options.
   */
  explicit SoulSenseHwManager(const SoulSenseHwManagerParameters& params);

  /**
   * @brief Start the plugins. Threaded plugins will be run here.
   */
  void activatePlugins(void);

#ifndef HR_DEBUG
private:
#endif

  /** Manager parameters. */
  SoulSenseHwManagerParameters params_;

  /** Plugin manager. */
  PluginManager<soul::sense::SenseHwPluginInterface> pluginman_;

  /**
   * @brief Load plugins.
   */
  void loadPlugins(void);

  /**
   * @brief Configure plugins.
   */
  void configurePlugins(void);

  /**
   * @brief Setup messaging for the plugin.
   * @param plugin Pointer to the plugin.
   */
  void setupMessaging(SenseHwPluginInterface* plugin);
};

}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_HW_MANAGER_H_