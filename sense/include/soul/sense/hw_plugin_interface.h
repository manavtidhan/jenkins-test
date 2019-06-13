/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_HW_PLUGIN_INTERFACE_H_
#define SOUL_SENSE_HW_PLUGIN_INTERFACE_H_

/**
 * Soul Sense hardware plugin interface.
 * Specialises the generic plugin interface for Soul platform hardware devices,
 * e.g., sensors.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/message_subscriber.h>
#include <soul/plugins/interface.h>
#include <soul/sense/plugin_state.h>

#include <functional>
#include <string>
#include <unordered_map>

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

/** Perception hardware error messages. */
struct HwError
{
  std::string message;  ///< Error message string.
};

/** Error callback function signature. */
using HwErrorCbFuncSig = void(const HwError);

/** std::function wrapper for the error callback. */
using HwErrorCbFunc = std::function<HwErrorCbFuncSig>;

/** Section name for Soul Sense plugins. */
constexpr char hw_plugin_section_name_[] = "SenseHw";

/** Default directory name of the SoulSense plugins. */
constexpr char default_hw_plugin_directory_[] = "sense/hardware";

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

class SenseHwPluginInterface : public soul::PluginInterface
{
public:
  /** Add virtual destructor to stop dtor issues. */
  virtual ~SenseHwPluginInterface() = default;

  /**
   * @brief Sets the error cb, so that we can report back on errors.
   * @param cb the error callback to invoke.
   */
  virtual void setErrorCb(HwErrorCbFunc cb) = 0;

  /**
   * @brief Initialize the hardware device.
   * @param params The device's parameters using string key/value map.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool configure(std::unordered_map<std::string, std::string>& params) = 0;

  /**
   * @brief Activate the device and start sending data.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool activate(void) = 0;

  /**
   * @brief Deactivate the device and stop sending data.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool deactivate(void) = 0;

  /**
   * @brief Destroy any objects before shutting down.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool cleanup(void) = 0;

  /**
   * @brief Get the plugin state.
   * @return The plugin state.
   */
  virtual PluginState getState(void) const = 0;

  /**
   * @brief Give access to a function to allow sending messages through the
   * messaging system.
   * @param fn Message sending function.
   */
  virtual void setMessageSender(MessageSenderFn fn) = 0;
};

}  // namespace sense
}  // namespace soul

#endif  // SOUL_SENSE_HW_PLUGIN_INTERFACE_H_
