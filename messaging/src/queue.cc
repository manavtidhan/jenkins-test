/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/**
 * A thread safe message queue.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////
#include <soul/messaging/queue.h>

#include <condition_variable>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS                                                            //
///////////////////////////////////////////////////////////////////////////////

bool MessageQueue::empty(void)
{
  std::lock_guard<std::mutex> lock_guard(lock_);

  return queue_.empty();
}

void MessageQueue::push(std::shared_ptr<MessageInterface> msg)
{
  std::lock_guard<std::mutex> lock_guard(lock_);
  queue_.push(msg);
  cond_.notify_one();
}

std::shared_ptr<MessageInterface> MessageQueue::pop(void)
{
  std::unique_lock<std::mutex> unique_lock(lock_);
  while (queue_.empty())
    cond_.wait(unique_lock);

  auto msg = queue_.front();
  queue_.pop();

  return msg;
}

std::vector<std::shared_ptr<MessageInterface>> MessageQueue::popAll(void)
{
  std::unique_lock<std::mutex> unique_lock(lock_);
  std::vector<std::shared_ptr<MessageInterface>> result;

  if (queue_.empty())
    return result;

  while (!queue_.empty())
  {
    result.push_back(queue_.front());
    queue_.pop();
  }

  return result;
}

std::size_t MessageQueue::size(void)
{
  std::lock_guard<std::mutex> lock_guard(lock_);

  return queue_.size();
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS                                                           //
///////////////////////////////////////////////////////////////////////////////

}  // namespace soul