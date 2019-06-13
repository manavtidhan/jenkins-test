/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_MATH_BOUNDING_BOX_H_
#define SOUL_SENSE_MATH_BOUNDING_BOX_H_

/**
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/math/point.h>
#include <soul/sense/math/size.h>

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
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief BoundingBox data type for representing a 2D or 3D bounding box in an image.
 */

class BoundingBox final
{
public:
  /**
   * @brief Initalizes a 2D bounding box.
   * @param point The x and y image coordinates; these define the top-left corner of the 2D bounding box. The z
   * coordinate is set to zero.
   * @param size The width and height of the 3D bounding box, from the top-left corner. Depth is set to zero.
   */

  BoundingBox(const Point2i point, const Size2i size)
    : point_(point.getX(), point.getY(), default_z_), size_(size.getWidth(), size.getHeight(), default_depth_)
  {
  }

  /**
   * @brief Initalizes a 3D bounding box.
   * @param point The x, y and z image coordinates; these define the top-left-front corner of the 3D bounding box.
   * @param size The width, height and depth of the 3D bounding box, from the top-left-front corner.
   */
  BoundingBox(const Point3i point, const Size3i size) : point_(point), size_(size)
  {
  }

  /**
   * @brief Get the point that defines the top-left-front corner of the 3D bounding box.
   * @return the point.
   */
  Point3i getPoint(void) const
  {
    return point_;
  }

  /**
   * @brief Get the size of the bounding box.
   * @return the size.
   */
  Size3i getSize(void) const
  {
    return size_;
  }

#ifndef HR_DEBUG
private:
#endif
  const int default_z_ = 0;
  const int default_depth_ = 0;
  Point3i point_;  ///< x, y, z image coordinates.
  Size3i size_;    ///< width, height and depth of bounding box in image coordinates.
};
}  // namespace math
}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_MATH_BOUNDING_BOX_H_