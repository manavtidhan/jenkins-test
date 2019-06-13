/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/* Message subscriber structure.
 * Author: Tuan Chien
 */

#ifndef SOUL_MESSAGING_MESSAGE_SUBSCRIBER_H_
#define SOUL_MESSAGING_MESSAGE_SUBSCRIBER_H_

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
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * Message subscriber.
 */
struct MessageSubscriber
{
  /** Default constructor. */
  MessageSubscriber() = default;

  /**
   * @brief Constructor
   * @param id Message id
   * @param n Subscriber name.
   * @param fn Message received callback function.
   */
  MessageSubscriber(const std::string id, const std::string n, MessageReceivedCb fn) : msg_id(id), name(n), cb(fn)
  {
  }

  /**
   * @brief Constructor
   * @param id Message id
   * @param n Subscriber name.
   */
  MessageSubscriber(const std::string id, const std::string n) : msg_id(id), name(n)
  {
  }

  /** Message ID. */
  std::string msg_id;

  /** Name of the subscriber. Likely to be the plugin name. */
  std::string name;

  /** Callback function to invoke on a new message. */
  MessageReceivedCb cb;
};

/**
 * @brief Equality comparison for message subscribers. Needed for unordered_set.
 * @param lhs Left hand side subscriber.
 * @param rhs Right hand side subscriber.
 */
inline bool operator==(const MessageSubscriber lhs, const MessageSubscriber rhs)
{
  return lhs.name == rhs.name;
}

/**
 * @brief Not equal comparison for message subscribers.
 * @param lhs Left hand side subscriber.
 * @param rhs Right hand side subscriber.
 */
inline bool operator!=(const MessageSubscriber lhs, const MessageSubscriber rhs)
{
  return lhs.name != rhs.name;
}

/** Hash definition for MessageSubscriber. */
struct MessageSubscriberHash
{
  std::size_t operator()(const MessageSubscriber& sub) const
  {
    return std::hash<std::string>{}(sub.name);
  }
};

}  // namespace soul

#endif  // SOUL_MESSAGING_MESSAGE_SUBSCRIBER_H_