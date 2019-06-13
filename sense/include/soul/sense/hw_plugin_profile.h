/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Hardware plugin profile.
 *
 * Author: Tuan Chien
 */

#ifndef SOUL_SENSE_HW_PLUGIN_PROFILE_H_
#define SOUL_SENSE_HW_PLUGIN_PROFILE_H_

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/message_publisher.h>
#include <soul/plugins/interface.h>

#include <string>
#include <vector>

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
 * @brief Hardware device type.
 */
enum class DeviceType
{
  Unknown,  ///< Unknown type. Should indicate an error.
  Camera,   ///< Cameras.
};

/**
 * @brief Hardware device information.
 */
struct DeviceInfo
{
  DeviceType type;                      ///< Type of hardware device.
  std::string id;                       ///< Device ID (in case we have multiple). Implement specifics as need arises.
  std::string name;                     ///< Name of the device.
  std::vector<std::string> attributes;  ///< Device attributes.
};

/**
 * @brief Hardware plugin profile.
 */
struct SenseHwPluginProfile : public soul::PluginProfile
{
  DeviceInfo devinfo;                  ///< Device information.
  std::vector<MessagePublisher> pubs;  ///< List of things we want to publish to.
};

}  // namespace sense
}  // namespace soul

#endif  // SOUL_SENSE_HW_PLUGIN_PROFILE_H_