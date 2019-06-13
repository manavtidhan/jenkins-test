/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy sense hardware plugin for testing.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/hw_plugin_interface.h>
#include <soul/sense/hw_plugin_profile.h>

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

///////////////////////////////////////////////////////////////////////////////
// CLASSES                                                                   //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Dummy soul sense hardware plugin for testing and demonstration.
 */

class DummySenseHwPlugin final : public SenseHwPluginInterface
{
public:
  /** Constructor */
  explicit DummySenseHwPlugin();

  /**
   * @brief Get plugin name.
   * @return Plugin name.
   */
  std::string name() const override;

  /**
   * @brief Get a new plugin object. Factory pattern.
   * @return Unique pointer to a new plugin object.
   */
  static std::unique_ptr<DummySenseHwPlugin> create();

  /**
   * @brief Get the plugin profile.
   * @return Pointer to the plugin profile.
   */
  const PluginProfile* getProfile() const override;

  /**
   * @brief Set the error callback function allowing for errors to be communicated back.
   * @param cb Error callback function.
   */
  void setErrorCb(HwErrorCbFunc cb) override;

  /**
   * @brief Configure the plugin with string key/value parameters.
   * @param params Parameter map.
   * @return True on success, false on failure.
   */
  bool configure(std::unordered_map<std::string, std::string>& params) override;

  /**
   * @brief Activate the plugin. It's allowed to run.
   * @return True on success, false on failure.
   */
  bool activate(void) override;

  /**
   * @brief Deactivate the plugin. It must cease operation.
   * @return True on success, false on failure.
   */
  bool deactivate(void) override;

  /**
   * @brief Clean up resources, prepare to be unloaded from memory.
   * @return True on success, false on failure.
   */
  bool cleanup(void) override;

  /**
   * @brief Get the current plugin state.
   * @return Plugin state.
   */
  PluginState getState(void) const override;

  /**
   * @brief Set the message sender function handle that allows the plugin to send messages to messaging queue.
   * @param fn Message sending function.
   */
  void setMessageSender(MessageSenderFn fn) override;

#ifndef HR_DEBUG
private:
#endif

  /** Plugin name. */
  std::string name_;

  /** Plugin profile. */
  SenseHwPluginProfile profile_;

  /** Error callback. */
  HwErrorCbFunc cb_;

  /** Parameters. */
  std::unordered_map<std::string, std::string> params_;

  /** Plugin state. */
  PluginState state_;

  /** Message sender. */
  MessageSenderFn sender_;
};

}  // namespace sense
}  // namespace soul