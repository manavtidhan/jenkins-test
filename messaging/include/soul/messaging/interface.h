/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_MESSAGE_INTERFACE_H_
#define SOUL_MESSAGING_MESSAGE_INTERFACE_H_

/*
 * Message interface
 *
 * Define the generic message type which can be passed around by the messaging
 * manager.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <functional>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

struct MessageInterface;

/** Callback function to invoke to notify subscribers of messages of new messages. */
using MessageReceivedCb = std::function<void(std::shared_ptr<MessageInterface>)>;

/** Function that can send Soul messages. */
using MessageSenderFn =
    std::function<void(const std::string msg_id, const std::string plugin_name, std::shared_ptr<MessageInterface>)>;

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Generic message interface. The messaging manager will manage these
 * message types. Architects need to specialise this to their particular
 * plugins.
 */
struct MessageInterface
{
  /**
   * @brief Virtual destructor for our interface to prevent funny dtor issues.
   */
  virtual ~MessageInterface() = default;

  /** Time stamp. */
  std::chrono::system_clock::time_point timestamp;
};

}  // namespace soul

#endif  // SOUL_MESSAGING_MESSAGE_INTERFACE_H_