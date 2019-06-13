/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MATH_POSE_H_
#define SOUL_SENSE_MATH_POSE_H_

/**
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/math/point.h>
#include <soul/sense/math/quaternion.h>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
namespace math
{
///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 3D pose template, which represents the position and orientation of an
 * entity in world space.
 */
template <typename T>
class Pose
{
public:
  /**
   * @brief Constructor.
   * @param position The position of the entity.
   * @param orientation The orientation of the entity expressed as a quaternion.
   */
  explicit Pose(const Point3<T> position, const Quaternion<T> orientation)
    : position_(position), orientation_(orientation)
  {
  }

  /**
   * @brief Get the position.
   * @return position.
   */
  Point3<T> getPosition() const
  {
    return position_;
  }

  /**
   * @brief Get the orientation.
   * @return orientation.
   */
  Quaternion<T> getOrientation() const
  {
    return orientation_;
  }

#ifndef HR_DEBUG
private:
#endif
  Point3<T> position_;
  Quaternion<T> orientation_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

using Pose3f = Pose<float>;
using Pose3d = Pose<double>;

}  // namespace math
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_MATH_POSE_H_