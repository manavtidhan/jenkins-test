/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_FACE_DETECTION_H_
#define SOUL_SENSE_FACE_DETECTION_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/msg/image.h>
#include <soul/sense/msg/sense_msg.h>
#include <soul/sense/msg/header.h>
#include <soul/sense/math/bounding_box.h>
#include <soul/messaging/list.h>

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
 * @brief SoulSense face detection message type.
 */

class FaceDetection final : public SenseMessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data; it should be set with the
   * image timestamp obtained from the camera driver firmware.
   * @param face_image The cropped images of the person's faces.
   * @param bbox The bounding box indicating the location of the detected face in the source image.
   */
  explicit FaceDetection(const Header header, const Image face_image, const soul::sense::math::BoundingBox bbox)
    : SenseMessageInterface(header), face_image_(face_image), bbox_(bbox)
  {
  }

  /**
   * @brief Get the cropped images of the person's face.
   * @return the cropped face image.
   */
  Image getFaceImage(void) const
  {
    return face_image_;
  }

  /**
   * @brief Get bounding boxes indicating the location of the detected face in the source image.
   * @return the bounding boxes.
   */
  soul::sense::math::BoundingBox getBoundingBox(void) const
  {
    return bbox_;
  }

#ifndef HR_DEBUG
private:
#endif
  Image face_image_;                     ///< the cropped images of the person's face.
  soul::sense::math::BoundingBox bbox_;  ///< the bounding boxes indicating the location of the detected
                                         ///< face in the source image.
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Enables a list of face detections to be sent as a single message.
 */
using FaceDetectionList = soul::ListMessage<FaceDetection>;

}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_FACE_DETECTION_H_