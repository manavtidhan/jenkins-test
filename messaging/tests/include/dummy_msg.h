/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_DUMMY_MESSAGE_H_
#define SOUL_MESSAGING_DUMMY_MESSAGE_H_

/*
 * Dummy message that implements MessageInterface
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>

#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Dummy message implementation for testing.
 */
struct DummyMessage : public MessageInterface
{
  DummyMessage() = default;

  /**
   * @brief Constructor to help with initialising message string.
   * @param msg Message string.
   */
  DummyMessage(std::string msg)
  {
    str = msg;
  }

  std::string str;  ///< Message string.
};

}  // namespace soul
#endif  // SOUL_MESSAGING_DUMMY_MESSAGE_H_