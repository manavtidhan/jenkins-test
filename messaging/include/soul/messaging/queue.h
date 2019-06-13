/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_QUEUE_H_
#define SOUL_MESSAGING_QUEUE_H_

/**
 * A thread safe message queue.
 * For now the queue sizes are unbounded.  In the future there might be queue size bounds.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION                                                          //
///////////////////////////////////////////////////////////////////////////////

/*
 * @brief A sequentially accessible message queue. Thread safe. Will block on
 * empty queue if you try to read from it.
 */
class MessageQueue
{
public:
  /**
   * @brief Add a new message to the queue.
   * @param msg Message to add to the queue.
   */
  void push(std::shared_ptr<MessageInterface> msg);

  /**
   * @brief Pop an element from the queue.
   * @return Shared pointer to the message.
   */
  std::shared_ptr<MessageInterface> pop(void);

  /**
   * @brief Pop all elements off the queue.
   * @return All elements in the queue.
   */
  std::vector<std::shared_ptr<MessageInterface>> popAll(void);

  /**
   * @brief Indicate whether the queue is empty.
   * @return True if queue is empty.
   */
  bool empty(void);

  /**
   * @brief Get size of the queue.
   * @return Size of the queue.
   */
  std::size_t size(void);

#ifndef HR_DEBUG
private:
#endif
  /** Mutex lock to control sequential access. */
  std::mutex lock_;

  /** Condition variable for maintaining the lock through signalling. */
  std::condition_variable cond_;

  /** Message queue. */
  std::queue<std::shared_ptr<MessageInterface>> queue_;
};

}  // namespace soul

#endif  // SOUL_MESSAGING_QUEUE_H_