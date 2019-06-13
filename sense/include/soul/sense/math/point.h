/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MATH_POINT_H_
#define SOUL_SENSE_MATH_POINT_H_

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
 * @brief 2D point template
 */

template <typename T>
class Point2
{
public:
  /**
   * @brief Constructor.
   * @param x The x coordinate.
   * @param y The y coordinate.
   */
  explicit Point2(const T x, const T y) : x_(x), y_(y)
  {
  }

  /**
   * @brief Get the x coordinate.
   * @return x.
   */
  T getX() const
  {
    return x_;
  }

  /**
   * @brief Get the y coordinate.
   * @return y.
   */
  T getY() const
  {
    return y_;
  }

#ifndef HR_DEBUG
private:
#endif
  T x_;
  T y_;
};

/**
 * @brief 3D point template
 */

template <typename T>
class Point3
{
public:
  /**
   * @brief Constructor.
   * @param x The x coordinate.
   * @param y The y coordinate.
   * @param z The z coordinate.
   */
  Point3(const T x, const T y, const T z) : x_(x), y_(y), z_(z)
  {
  }

  /**
   * @brief Get the x coordinate.
   * @return x.
   */
  T getX() const
  {
    return x_;
  }

  /**
   * @brief Get the y coordinate.
   * @return y.
   */
  T getY() const
  {
    return y_;
  }

  /**
   * @brief Get the z coordinate.
   * @return z.
   */
  T getZ() const
  {
    return z_;
  }

#ifndef HR_DEBUG
private:
#endif
  T x_;
  T y_;
  T z_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

using Point2i = Point2<int>;
using Point2f = Point2<float>;
using Point2d = Point2<double>;
using Point3i = Point3<int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

}  // namespace math
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_MATH_POINT_H_