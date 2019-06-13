/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_TYPE_H_
#define SOUL_MESSAGING_TYPE_H_

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * Specify all the message types here.  All systems that want to use this messaging system need to add their to this
 * enum.
 */
enum class MessageType
{
  image,  ///< Image type. One OpenCV mat.
};

}  // namespace soul

#endif  // SOUL_MESSAGING_TYPE_H_