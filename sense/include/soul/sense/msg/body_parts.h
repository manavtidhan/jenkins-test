/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_BODY_PARTS_H_
#define SOUL_SENSE_BODY_PARTS_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/math/pose.h>
#include <soul/sense/msg/header.h>
#include <soul/sense/msg/sense_msg.h>
#include <soul/messaging/list.h>

#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
namespace msg
{
///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief SoulSense body pose message type. This is indented to be used to represent the poses of a person's body
 * parts, for instance the pose of their head, eyes limbs etc.
 */

class BodyParts final : public SenseMessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data; it should be set with the
   * image timestamp obtained from the camera driver firmware.
   * @param names The names that correspond to the detected body part poses; these will differ depeding on each type of
   * pose detector employed.
   * @param poses The poses of the detected body parts in world coordinates.
   */
  explicit BodyParts(const Header header, std::vector<std::string> names,
                     const std::vector<soul::sense::math::Pose3f> poses)
    : SenseMessageInterface(header), names_(names), poses_(poses)
  {
  }

  /**
   * @brief Get the names of the detected body parts.
   * @return body part names.
   */
  std::vector<std::string> getNames() const
  {
    return names_;
  }

  /**
   * @brief Get the poses of the detected body parts.
   * @return 3D poses.
   */
  std::vector<soul::sense::math::Pose3f> getPoses() const
  {
    return poses_;
  }

#ifndef HR_DEBUG
private:
#endif
  const std::vector<std::string> names_;
  const std::vector<soul::sense::math::Pose3f> poses_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Enables a list of body parts to be sent as a single message.
 */
using BodyPartsList = soul::ListMessage<BodyParts>;

}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_BODY_PARTS_H_