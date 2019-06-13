/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy sense plugin for testing.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/plugin_interface.h>
#include <soul/sense/plugin_profile.h>

#include <memory>

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
 * @brief Dummy soul sense plugin for testing and for demonstrating how to implement one.
 * Note that you have to access any methods in this class through the SensePluginInterface
 * interface unless you explicitly export symbols for DummySensePlugin in the source file.
 * For example, setErrorCb can be called as a SensePluginInterface method but if you
 * reinterpreted the pointer as a DummySensePlugin it will complain about unresolved symbols
 * at runtime unless those symbols have been exported.
 */
class DummySensePlugin final : public SensePluginInterface
{
public:
  /**
   * @brief Default initialisation
   */
  explicit DummySensePlugin();

  /**
   * @brief Sets the ErrorCbFunc, so that SensePluginInterface can inform
   * another class about errors that occur.
   * @param errorCbFunc the error callback function to supply to the SensePluginInterface.
   */
  void setErrorCb(ErrorCbFunc cb) override;

  /**
   * @brief Initialize the perception algorithm, creating or connecting to
   * services that are necessary for running the algorithm.
   * @param params The perceptor's parameters as string name and value.
   * @return Returns whether the function call was successful or not.
   */
  bool configure(std::unordered_map<std::string, std::string>& params) override;

  /**
   * @brief Activate the perception algorithm: start processing data.
   * @return Returns whether the function call was successful or not.
   */
  bool activate(void) override;

  /**
   * @brief Deactivate the perception algorithm: stop processing data.
   * @return Returns whether the function call was successful or not.
   */
  bool deactivate(void) override;

  /**
   * @brief Destroy any objects before shutting down.
   * @return Returns whether the function call was successful or not.
   */
  bool cleanup(void) override;

  /**
   * @brief Get the name of the plugin.
   * Required by the PluginInterface.
   * @return Plugin name as a string.
   */
  std::string name() const override;

  /**
   * @brief Return the dummy plugin profile.
   * Required by the PluginInterface.
   * @return Plugin profile.
   */
  const PluginProfile* getProfile() const override;

  /**
   * @brief Get the plugin state.
   * @return The plugin state.
   */
  PluginState getState(void) const override;

  /**
   * @brief Set message sending function to use.
   * @param fn Message sending function.
   */
  void setMessageSender(MessageSenderFn fn) override;

  /**
   * @brief Factory method for creating a new instance of the plugin.
   * Required by the PluginInterface.
   * @return Unique pointer to the new instance of the plugin.
   */
  static std::unique_ptr<DummySensePlugin> create(void);

#ifndef HR_DEBUG
private:
#endif

  SensePluginProfile profile_;  ///< Plugin profile.

  MessageSenderFn msg_sender_;  ///< Message sender function.

  ErrorCbFunc error_cb_;  ///< Error callback function.

  PluginState state_;  ///< Sense plugin state.

  std::unordered_map<std::string, std::string> params_;  ///< Parameters
};

}  // namespace sense
}  // namespace soul