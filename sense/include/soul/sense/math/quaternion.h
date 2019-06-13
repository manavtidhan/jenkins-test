/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MATH_QUATERNION_H_
#define SOUL_SENSE_MATH_QUATERNION_H_

/**
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

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
 * @brief Quaternion template for representing orientation.
 */
template <typename T>
class Quaternion
{
public:
  /**
   * @brief Constructor.
   * @param x .
   * @param y .
   * @param z .
   * @param w .
   */
  explicit Quaternion(const T x, const T y, const T z, const T w) : x_(x), y_(y), z_(z), w_(w)
  {
  }

  /**
   * @brief Get x.
   * @return x.
   */
  T getX() const
  {
    return x_;
  }

  /**
   * @brief Get y.
   * @return y.
   */
  T getY() const
  {
    return y_;
  }

  /**
   * @brief Get z.
   * @return z.
   */
  T getZ() const
  {
    return z_;
  }

  /**
   * @brief Get w.
   * @return w.
   */
  T getW() const
  {
    return w_;
  }

#ifndef HR_DEBUG
private:
#endif
  T x_;
  T y_;
  T z_;
  T w_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;

}  // namespace math
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_MATH_QUATERNION_H_