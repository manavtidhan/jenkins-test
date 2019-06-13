/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_PLUGINS_INTERFACE_H_
#define SOUL_PLUGINS_INTERFACE_H_

/*
 * Plugin API.
 *
 * Plugins must have stable behaviour with default initialisation (no arguments
 * provided). Each system is responsible for defining configuration and runtime
 * behaviour of each plugin.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/** Symbol name for the factory method that instantiates a plugin object. */
constexpr char plugin_factory_method_name_[] = "create";

/**
 * @brief Abstract data type for the plugin profile. Each system should define
 * and implement their own specification for what they want to have in here.
 */
struct PluginProfile
{
  /** Add virtual destructor just in case. */
  virtual ~PluginProfile() = default;
};

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Abstract plugin interface for the Soul platform. Any Soul systems that use this should define specialised
 * interfaces that implement this abstract plugin interface.
 */
class PluginInterface
{
public:
  /** Adding virtual destructor to stop dtor problems. */
  virtual ~PluginInterface() = default;

  /**
   * @brief Returns the name of the plugin.
   * Naming convention: SectionName,PluginName
   * Example: Perception,FaceDetectionDlib
   */
  virtual std::string name() const = 0;

  /**
   * @brief Retrieve the plugin profile.
   * @return Plugin profile.
   */
  virtual const PluginProfile* getProfile() const = 0;

  /*
   * ATTENTION
   * Each plugin MUST implement a static create() method that returns a
   * unique_ptr to a new instance of that class. There is no nice way in C++
   * to force this through a virtual interface for the plugin infrastructure,
   * so it will be just have to be a specification requirement.
   * An example might look like:
   * static std::unique_ptr<my_plugin_class> create()
   * {
   *    return std::make_unique<my_plugin_class>();
   * }
   */
};

}  // namespace soul
#endif  // SOUL_PLUGINS_INTERFACE_H_