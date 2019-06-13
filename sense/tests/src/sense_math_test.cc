/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Tests to make sure that SoulSense data types compile.
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/math/point.h>
#include <soul/sense/math/size.h>
#include <soul/sense/math/quaternion.h>
#include <soul/sense/math/pose.h>
#include <soul/sense/math/bounding_box.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

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
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

TEST(TestSenseMathInterfacesCompile, IfThisWorksSenseMathInterfacesCompiled)
{
  // Create a pose
  Point3f position(1, 1, 1);  // World coordinates
  Quaternionf orientation(0, 0, 0, 1);
  Pose3f robot_pose(position, orientation);

  // Create a 3D bounding box
  Point3i bbox_pos(1, 1, 1);  // 3D image coordinates
  Size3i bbox_size(1, 1, 1);  // pixels
  BoundingBox bbox3d(bbox_pos, bbox_size);

  // Create a 2D bounding box
  Point2i bbox_pos_2d(1, 1);  // 2D image coordinates
  Size2i bbox_size_2d(1, 1);  // pixels
  BoundingBox bbox2d(bbox_pos_2d, bbox_size_2d);

  EXPECT_TRUE(true);
}
}  // namespace math
}  // namespace sense
}  // namespace soul