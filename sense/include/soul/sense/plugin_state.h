/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_PLUGIN_STATE_H_
#define SOUL_SENSE_PLUGIN_STATE_H_

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
 * @brief A standard state structure for the plugins.
 */
enum class PluginState
{
  unconfigured = 0,  ///< Plugin not configured yet.
  inactive = 1,      ///< Plugin configured but not activated.
  active = 2,        ///< Plugin activated.
  shutdown = 3       ///< Plugin has shutdown and done cleanup, ready for unloading.
};

}  // namespace sense
}  // namespace soul

#endif  // SOUL_SENSE_PLUGIN_STATE_H_