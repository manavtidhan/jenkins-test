/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_HEADER_H_
#define SOUL_SENSE_HEADER_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <chrono>
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
 * @brief SoulSense message header.
 *
 * This data structure provides information about the time and coordinate
 * frame of the originating sensor data that was used to create a detection.
 * The timestamp enables synchronisation of different sensor data instances
 * whilst the coordinate frame identifier enables processed detections to be
 * associated with their originating sensor and a physical location.
 */

class Header final
{
public:
  /**
   * @brief Constructor.
   * @param timestamp The \a time that source sensor data was captured.
   * @param frame_id The coordinate frame \a where source sensor data originated.
   */
  explicit Header(const std::chrono::system_clock::time_point timestamp, const std::string frame_id)
    : timestamp_(timestamp), frame_id_(frame_id)
  {
  }

  /**
   * @brief Get the \a time that source sensor data was captured.
   * @return the timestamp.
   */
  std::chrono::system_clock::time_point getTimestamp(void) const
  {
    return timestamp_;
  }

  /**
   * @brief Get the coordinate frame \a where source sensor data originated.
   * @return the frame id.
   */
  std::string getFrameId(void) const
  {
    return frame_id_;
  }

#ifndef HR_DEBUG
private:
#endif
  std::chrono::system_clock::time_point timestamp_;  ///< specifies the \a time that source sensor data was captured.
  std::string frame_id_;  ///< identifies the coordinate frame \a where source sensor data originated.
};
}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_HEADER_H_