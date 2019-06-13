/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MATH_SIZE_H_
#define SOUL_SENSE_MATH_SIZE_H_

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
 * @brief 2D size template
 */

template <typename T>
class Size2
{
public:
  /**
   * @brief Constructor.
   * @param width The width of the entity.
   * @param height The height of the entity.
   */
  explicit Size2(const T width, const T height) : width_(width), height_(height)
  {
  }

  /**
   * @brief Get the width of the entity.
   * @return width.
   */
  T getWidth() const
  {
    return width_;
  }

  /**
   * @brief Get the height of the entity.
   * @return height.
   */
  T getHeight() const
  {
    return height_;
  }

#ifndef HR_DEBUG
private:
#endif
  T width_;
  T height_;
};

/**
 * @brief 3D size template
 */
template <typename T>
class Size3
{
public:
  /**
   * @brief Constructor.
   * @param width The width of the entity.
   * @param height The height of the entity.
   * @param depth The depth of the entity.
   */
  explicit Size3(const T width, const T height, const T depth) : width_(width), height_(height), depth_(depth)
  {
  }

  /**
   * @brief Get the width of the entity.
   * @return width.
   */
  T getWidth() const
  {
    return width_;
  }

  /**
   * @brief Get the height of the entity.
   * @return height.
   */
  T getHeight() const
  {
    return height_;
  }

  /**
   * @brief Get the depth of the entity.
   * @return depth.
   */
  T getDepth() const
  {
    return depth_;
  }

#ifndef HR_DEBUG
private:
#endif
  T width_;
  T height_;
  T depth_;
};

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

using Size2i = Size2<int>;
using Size2f = Size2<float>;
using Size2d = Size2<double>;
using Size3i = Size3<int>;
using Size3f = Size3<float>;
using Size3d = Size3<double>;

}  // namespace math
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_MATH_SIZE_H_