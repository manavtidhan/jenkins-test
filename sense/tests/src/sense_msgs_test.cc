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

#include <soul/sense/msg/header.h>
#include <soul/sense/msg/image.h>
#include <soul/sense/math/bounding_box.h>
#include <soul/sense/msg/face_detection.h>
#include <soul/sense/msg/face_encoding.h>
#include <soul/sense/msg/face_landmarks.h>
#include <soul/sense/msg/body_parts.h>
#include <soul/knowledge/msg/person_state.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>
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
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

TEST(TestSenseMsgsInterfacesCompile, IfThisWorksSenseMsgsInterfacesCompiled)
{
  using namespace soul::sense::math;

  // Instantiate header and call methods.
  Header header(std::chrono::system_clock::now(), "test");
  header.getTimestamp();
  header.getFrameId();

  // Instantiate ImageMsg and call methods.
  Image image_msg(header, cv::Mat(), cv::Mat());
  image_msg.getHeader();
  image_msg.getImage();
  image_msg.getDepth();

  // Instantiate FaceDetection and call methods.
  Point3i bbox_position(1, 1, 1);  // 3D image coordinates
  Size3i bbox_size(1, 1, 1);       // in pixels
  BoundingBox bbox3d(bbox_position, bbox_size);

  FaceDetection face_detection_msg(header, image_msg, bbox3d);
  face_detection_msg.getHeader();
  face_detection_msg.getFaceImage();
  face_detection_msg.getBoundingBox();

  // Instantiate FaceEncoding and call methods
  int dlib_default_embedding_len = 128;
  std::vector<float> face_encoding(dlib_default_embedding_len, 0.);
  FaceEncoding face_encoding_msg(header, face_encoding);
  face_encoding_msg.getHeader();
  face_encoding_msg.getEncoding();

  // Instantiate FaceLandmarks and call methods
  std::vector<std::string> landmark_names = { "reye_rcorner", "reye_lcorner", "leye_rcorner", "leye_lcorner", "nose" };
  std::vector<Point3i> landmarks = { Point3i(10., 20., 0.), Point3i(20., 20., 0.), Point3i(50., 20., 0.),
                                     Point3i(60., 20., 0.), Point3i(35., 40., 0.) };
  FaceLandmarks face_landmarks_msg(header, landmark_names, landmarks);
  face_landmarks_msg.getHeader();
  face_landmarks_msg.getNames();
  face_landmarks_msg.getLandmarks();

  // Instantiate BodyPartPoses and call methods
  std::vector<std::string> body_part_names = { "head" };
  Point3f position(1, 1, 1);  // World coordinates
  Quaternionf orientation(0, 0, 0, 1);
  Pose3f head_pose(position, orientation);
  std::vector<Pose3f> poses = { head_pose };

  BodyParts body_parts_msg(header, body_part_names, poses);
  body_parts_msg.getHeader();
  body_parts_msg.getNames();
  body_parts_msg.getPoses();

  // Instantiate PersonState and call methods
  soul::knowledge::msg::PersonState person_state_msg(0, face_encoding_msg, face_detection_msg, face_landmarks_msg,
                                                     body_parts_msg);
  person_state_msg.getId();
  person_state_msg.getFaceEncoding();
  person_state_msg.getFaceDetection();
  person_state_msg.getFaceLandmarks();
  person_state_msg.getBodyParts();

  EXPECT_TRUE(true);
}
}  // namespace msg
}  // namespace sense
}  // namespace soul