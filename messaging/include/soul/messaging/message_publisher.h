/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/* Message publisher structure.
 * Author: Tuan Chien
 */

#ifndef SOUL_MESSAGING_MESSAGE_PUBLISHER_H_
#define SOUL_MESSAGING_MESSAGE_PUBLISHER_H_

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/type.h>

#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * Message publisher.
 */
struct MessagePublisher
{
  /** Default constructor. */
  MessagePublisher() = default;

  /**
   * @brief Constructor. Using this to allow for implicit construction to make hash lookups easier.
   * @param n Name of the publisher.
   */
  MessagePublisher(const char n[]) : name(n)
  {
  }

  /**
   * @brief Constructor. Using this to allow for implicit construction to make hash lookups easier.
   * @param n Name of the publisher.
   */
  MessagePublisher(const std::string n) : name(n)
  {
  }

  /**
   * @brief Constructor
   * @param id Message id.
   * @param n Publisher name.
   * @param t Message type.
   */
  MessagePublisher(const std::string id, const std::string n, const MessageType t) : msg_id(id), name(n), type(t)
  {
  }

  /** Message ID. */
  std::string msg_id;

  /** Name of the publisher. Likely to be the plugin name. */
  std::string name;

  /** Message type. */
  MessageType type;
};

/**
 * @brief Equality comparison for message publisher. Needed for unordered_set.
 * @param lhs Left hand side publisher.
 * @param rhs Right hand side publisher.
 */
inline bool operator==(const MessagePublisher lhs, const MessagePublisher rhs)
{
  return lhs.name == rhs.name;
}

/**
 * @brief Not equal comparison for message publisher.
 * @param lhs Left hand side publisher.
 * @param rhs Right hand side publisher.
 */
inline bool operator!=(const MessagePublisher lhs, const MessagePublisher rhs)
{
  return lhs.name != rhs.name;
}

/** Hash definition for MessagePublisher. */
struct MessagePublisherHash
{
  std::size_t operator()(const MessagePublisher& pub) const
  {
    return std::hash<std::string>{}(pub.name);
  }
};

}  // namespace soul

#endif  // SOUL_MESSAGING_MESSAGE_PUBLISHER_H_