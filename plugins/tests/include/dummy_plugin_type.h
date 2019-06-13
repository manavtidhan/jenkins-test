/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy specialised plugin interface to placehold the need for one.
 * Author: Tuan Chien
 */

#ifndef SOUL_PLUGINS_TEST_PLUGIN_TYPE_H_
#define SOUL_PLUGINS_TEST_PLUGIN_TYPE_H_

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/plugins/interface.h>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

struct DummyPluginProfile : public PluginProfile
{
  /** Add virtual destructor just in case. */
  virtual ~DummyPluginProfile() = default;
};

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Dummy plugin interface that inherits PluginInterface. If you are designing one of the systems in the Soul
 * platform, you should implement your own for that system which inherits the PluginInterface.
 */
class DummyPluginType : public PluginInterface
{
public:
  /** Add virtual destructor to stop dtor issues. */
  virtual ~DummyPluginType() = default;
};

}  // namespace soul

#endif  // SOUL_PLUGINS_TEST_PLUGIN_TYPE_H_