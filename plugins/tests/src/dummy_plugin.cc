/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy plugin. For illustration purposes and useful for testing.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/plugins/interface.h>
#include "dummy_plugin_type.h"

#include <boost/dll/alias.hpp>

#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CLASSES                                                                   //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Dummy plugin to illustrate how to implement a plugin.
 */
class DummyPlugin final : public DummyPluginType
{
  PluginProfile profile_;

public:
  /**
   * @brief Provides the name of the plugin.
   * @return Name of the plugin.
   */
  std::string name() const override
  {
    return "Dummy,dummy_plugin";
  };

  /**
   * @brief Return the dummy profile.
   * @return Plugin profile.
   */
  const PluginProfile* getProfile() const override
  {
    return &profile_;
  };

  /**
   * @brief Required part of the interface but not enforced by the DummyPluginType. This is used as a factory to
   * instantiate the plugin object by the plugin manager.
   * @return Pointer to a newly created plugin object.
   */
  static std::unique_ptr<DummyPlugin> create()
  {
    return std::make_unique<DummyPlugin>();
  }
};

/* Export the symbols so that they can be loaded by the plugin manager. */
BOOST_DLL_ALIAS_SECTIONED(soul::DummyPlugin::create,  // Exporting this object
                          create,                     // Export symbol (alias)
                          Dummy                       // Section name. At most 8 bytes.
)

}  // namespace soul