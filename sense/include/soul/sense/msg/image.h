/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_IMAGE_H_
#define SOUL_SENSE_IMAGE_H_

/*
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/msg/sense_msg.h>
#include <soul/sense/msg/header.h>
#include <opencv2/opencv.hpp>

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
 * @brief SoulSense image message type for representing both RGB and RGBD images.
 */

class Image final : public SenseMessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param header The header indicates the time and originating location of source data. The image timestamp obtained
   * from the camera driver firmware should be used to set the header's timestamp.
   * @param image The RGB image.
   * @param depth The depth image.
   */
  explicit Image(const Header header, const cv::Mat image, const cv::Mat depth = cv::Mat())
    : SenseMessageInterface(header), image_(image), depth_(depth)
  {
  }

  /**
   * @brief Get the RGB image.
   * @return the RGB image.
   */
  cv::Mat getImage(void) const
  {
    return image_;
  }

  /**
   * @brief Get the depth image.
   * @return the depth image.
   */
  cv::Mat getDepth(void) const
  {
    return depth_;
  }

#ifndef HR_DEBUG
private:
#endif
  cv::Mat image_;  ///< the RGB image.
  cv::Mat depth_;  ///< the depth image.
};
}  // namespace msg
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_IMAGE_MSG_H_