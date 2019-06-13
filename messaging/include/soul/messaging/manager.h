/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_MANAGER_H_
#define SOUL_MESSAGING_MANAGER_H_

/*
 * Messaging manager
 *
 * Defines a generic messaging manager that manages pub and sub queues of
 * MessageInterface messages. Needs to be concurrency safe and memory
 * safe.  It will be designed around shared pointers to data structures
 * for now for efficiency in message passing within a system.
 *
 * Whoever designs the RPC part to expose public access to messages needs
 * to design a format to use for that layer, and conversions between the
 * data types.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>
#include <soul/messaging/message_publisher.h>
#include <soul/messaging/message_subscriber.h>
#include <soul/messaging/queue.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION                                                          //
///////////////////////////////////////////////////////////////////////////////

class MessageManager
{
public:
  /** Constructor */
  explicit MessageManager();

  /**
   * @brief Clear all queues, publishers, and subscribers.  This helps with
   * controlling cleanup. We need to destruct any objects that might have been
   * allocated in dangerous memory regions before those regions get deallocated.
   */
  void clear(void);

  /**
   * @brief Get a list of publishers.
   * @return List of publishers.
   */
  std::vector<MessagePublisher> getPublishers(void);

  /**
   * @brief Notify all subscribers.
   */
  void notify(void);

  /**
   * @brief Announce publication of messages to a msg_id. This will create the
   * message queue if it doesn't already exist.
   * @param msg_id Name of the messaging queue.
   * @param pub Publishing information.
   */
  void publish(const std::string msg_id, const MessagePublisher pub);

  /**
   * @brief Announce subscription to a msg_id.
   * @param msg_id Name of the messaging queue.
   * @param plugin_name Name of the subscribing plugin.
   * @param cb Callback from subscriber for when a new message is received.
   */
  void subscribe(const std::string msg_id, const std::string plugin_name, MessageReceivedCb cb);

  /**
   * @brief Put a message on the relevant message queue. This does not notify the subscribers.
   * @param msg_id Name of the messaging queue.
   * @param plugin_name Name of the publishing plugin.
   * @param msg Shared pointer to the message.
   */
  void send(const std::string msg_id, const std::string plugin_name, std::shared_ptr<MessageInterface> msg);

  /**
   * @brief Blocks until there is work in the queue to process or if the work flag is set to false.
   * @return Always Return true so you can use it to condition a loop, except when the work flag has been set to false.
   */
  bool waitForWork(void);

  /**
   * @brief Set the status that waitForWork will return when it unblocks.
   * @param flag Flag to set work flag to.
   */
  void setWork(const bool flag);

#ifndef HR_DEBUG
private:
#endif

  /** Default wait time for conditional variable release. */
  std::chrono::milliseconds wait_time_;

  /** Publisher list. Map from msg_id to set of publishers names. */
  std::unordered_map<std::string, std::unordered_set<MessagePublisher, MessagePublisherHash>> publishers_;

  /** Subscriber list. Map from msg_id to a set of subscribers. */
  std::unordered_map<std::string, std::unordered_set<MessageSubscriber, MessageSubscriberHash>> subscribers_;

  /** Map from a msg_id to a message queue. */
  std::unordered_map<std::string, MessageQueue> queue_;

  /** Map lock */
  std::mutex mlock_;

  /** Lock for controlling queue access. */
  std::mutex qlock_;

  /** Queue condition variable for notifying emptiness. */
  std::condition_variable q_cond_var_;

  /** Number of messages in the queues. */
  std::atomic<std::int32_t> num_msgs_;

  /** Flag that will be returned by waitForWork. */
  bool work_;
};

}  // namespace soul

#endif  // SOUL_MESSAGING_MANAGER_H_