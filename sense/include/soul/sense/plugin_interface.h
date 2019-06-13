/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_PLUGIN_INTERFACE_H_
#define SOUL_SENSE_PLUGIN_INTERFACE_H_

/**
 * Soul Sense plugin interface.
 * Specialises the generic plugin interface for Soul platform to the perception system.
 * This iteration of the interface will be similar to
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

/** Perception error messages. */
struct SenseError
{
  std::string message;  ///< Error message string.
};

/** Error callback function signature. */
using ErrorCbFuncSig = void(const SenseError);

/** std::function wrapper for the error callback. */
using ErrorCbFunc = std::function<ErrorCbFuncSig>;

/** Section name for Soul Sense plugins. */
constexpr char plugin_section_name_[] = "Sense";

/** Default directory name of the SoulSense plugins. */
constexpr char default_plugin_directory_[] = "sense/plugins";

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

class SensePluginInterface : public soul::PluginInterface
{
public:
  /** Add virtual destructor to stop dtor issues. */
  virtual ~SensePluginInterface() = default;

  /**
   * @brief Sets the ErrorCbFunc, so that SensePluginInterface can inform
   * another class about errors that occur.
   * @param errorCbFunc the error callback function to supply to the
   * SensePluginInterface.
   */
  virtual void setErrorCb(ErrorCbFunc errorCbFunc) = 0;

  /**
   * @brief Initialize the perception algorithm, creating or connecting to
   * services that are necessary for running the algorithm.
   * @param params The perceptor's parameters as string name and value.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool configure(std::unordered_map<std::string, std::string>& params) = 0;

  /**
   * @brief Activate the perception algorithm: start processing data.
   * @return Returns whether the function call was successful or not.
   */
  virtual bool activate(void) = 0;

  /**
   * @brief Deactivate the perception algorithm: stop processing data.
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

#endif  // SOUL_SENSE_PLUGIN_INTERFACE_H_
