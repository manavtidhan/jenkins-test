/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_FACE_LANDMARKS_H_
#define SOUL_SENSE_FACE_LANDMARKS_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/math/point.h>
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
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief SoulSense face landmarks message type, which contains a vector of face landmarks for a person.
 */

class FaceLandmarks final : public SenseMessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data; it should be set with the
   * image timestamp obtained from the camera driver firmware.
   * @param names The names that correspond to each face landmark point; these will differ depeding on each type of
   * face landmark detector employed.
   * @param landmarks A vector of 3D image coordinates for the face landmarks for a detected face. If 2D image
   * coordinates (i.e. no depth) then for each point set z to zero.
   */
  explicit FaceLandmarks(const Header header, const std::vector<std::string> names,
                         const std::vector<soul::sense::math::Point3i> landmarks)
    : SenseMessageInterface(header), names_(names), landmarks_(landmarks)
  {
  }

  /**
   * @brief Get the names of the face landmarks.
   * @return landmark names.
   */
  std::vector<std::string> getNames() const
  {
    return names_;
  }

  /**
   * @brief Get the face landmark image coordinates.
   * @return landmarks.
   */
  std::vector<soul::sense::math::Point3i> getLandmarks() const
  {
    return landmarks_;
  }

#ifndef HR_DEBUG
private:
#endif
  const std::vector<std::string> names_;
  const std::vector<soul::sense::math::Point3i> landmarks_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Enables a list of face landmarks to be sent as a single message.
 */
using FaceLandmarksList = soul::ListMessage<FaceLandmarks>;

}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_FACE_LANDMARKS_H_