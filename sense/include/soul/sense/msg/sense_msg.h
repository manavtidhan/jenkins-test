/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_SENSE_MESSAGE_INTERFACE_H_
#define SOUL_SENSE_SENSE_MESSAGE_INTERFACE_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>
#include <soul/sense/msg/header.h>

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

/**
 * @brief SoulSense message interface for sensory data, which has a header for
 * indicating the time and coordinate frame of the originating sensor data.
 */

class SenseMessageInterface : MessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data. The image timestamp obtained
   * from the sensor firmware should be used to set the header's timestamp.
   */
  explicit SenseMessageInterface(const Header header) : header_(header)
  {
  }

  /**
   * @brief Get the header that indicates the time and originating location of source data.
   * @return the header.
   */
  Header getHeader(void) const
  {
    return header_;
  }

#ifndef HR_DEBUG
private:
#endif
  Header header_;  ///< indicates the time and originating location of source data.
};

}  // namespace msg
}  // namespace sense
}  // namespace soul

#endif  // SOUL_SENSE_SENSE_MESSAGE_INTERFACE_H_