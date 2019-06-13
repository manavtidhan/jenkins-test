/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_KNOWLEDGE_PERSON_STATE_H_
#define SOUL_KNOWLEDGE_PERSON_STATE_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>
#include <soul/sense/msg/face_landmarks.h>
#include <soul/sense/msg/face_encoding.h>
#include <soul/sense/msg/face_detection.h>
#include <soul/sense/msg/body_parts.h>
#include <soul/messaging/list.h>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace knowledge
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
 * @brief Person state message type, which contains the details of a person who is currently tracked by the knowledge
 * systems world model.
 */

class PersonState final : public MessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param id The person's identifier. Set to 0 if the identity is unknown.
   * @param face_encoding The person's latest face encoding.
   * @param face_detection The person's latest face detection.
   * @param face_landmarks The person's latest face landmarks.
   * @param body_parts The person's latest body part pose state.
   */
  explicit PersonState(std::int64_t id, const soul::sense::msg::FaceEncoding face_encoding,
                       const soul::sense::msg::FaceDetection face_detection,
                       const soul::sense::msg::FaceLandmarks face_landmarks,
                       const soul::sense::msg::BodyParts body_parts)
    : id_(id)
    , face_encoding_(face_encoding)
    , face_detection_(face_detection)
    , face_landmarks_(face_landmarks)
    , body_parts_(body_parts)
  {
  }

  /**
   * @brief Get the person's identifier.
   * @return id.
   */
  std::uint64_t getId(void) const
  {
    return id_;
  }

  /**
   * @brief Get the person's latest face encoding.
   * @return face encoding.
   */
  soul::sense::msg::FaceEncoding getFaceEncoding(void) const
  {
    return face_encoding_;
  }

  /**
   * @brief Get the person's latest face detection.
   * @return face detection.
   */
  soul::sense::msg::FaceDetection getFaceDetection(void) const
  {
    return face_detection_;
  }

  /**
   * @brief Get the person's latest face landmarks.
   * @return face landmarks.
   */
  soul::sense::msg::FaceLandmarks getFaceLandmarks(void) const
  {
    return face_landmarks_;
  }

  /**
   * @brief Get the person's body parts.
   * @return the person's body parts.
   */
  soul::sense::msg::BodyParts getBodyParts(void) const
  {
    return body_parts_;
  }

#ifndef HR_DEBUG
private:
#endif
  std::uint64_t id_;                                ///< the person's identifier.
  soul::sense::msg::FaceEncoding face_encoding_;    ///< the person's latest face encoding.
  soul::sense::msg::FaceDetection face_detection_;  ///< the person's latest face detection.
  soul::sense::msg::FaceLandmarks face_landmarks_;  ///< the person's latest face landmarks.
  soul::sense::msg::BodyParts body_parts_;          ///< the person's latest body part poses.
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Enables a list of person states to be sent as a single message.
 */
using PersonStateList = soul::ListMessage<PersonState>;

}  // namespace msg
}  // namespace knowledge
}  // namespace soul
#endif  // SOUL_KNOWLEDGE_PERSON_STATE_H_