/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_FACE_ENCODING_H_
#define SOUL_SENSE_FACE_ENCODING_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/msg/header.h>
#include <soul/sense/msg/sense_msg.h>
#include <soul/messaging/list.h>

#include <vector>

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
 * @brief SoulSense face encodings message type, which contains a face encoding for a detected face.
 */

class FaceEncoding final : public SenseMessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data; it should be set with the
   * image timestamp obtained from the camera driver firmware.
   * @param encodings The face encoding for a detected face.
   */
  explicit FaceEncoding(const Header header, const std::vector<float> encoding)
    : SenseMessageInterface(header), encoding_(encoding)
  {
  }

  /**
   * @brief Get the face encoding for a detected face.
   * @return the encodings.
   */
  std::vector<float> getEncoding() const
  {
    return encoding_;
  }

#ifndef HR_DEBUG
private:
#endif
  std::vector<float> encoding_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Enables a list of face encodings to be sent as a single message.
 */
using FaceEncodingList = soul::ListMessage<FaceEncoding>;

}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_FACE_ENCODING_H_