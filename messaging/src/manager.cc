/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Messaging manager.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/manager.h>

#include <future>
#include <iostream>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS                                                            //
///////////////////////////////////////////////////////////////////////////////

MessageManager::MessageManager() : num_msgs_(0), work_(true)
{
  using namespace std::chrono_literals;

  // Default maximum wait time before re-polling for data.
  wait_time_ = 10ms;
}

void MessageManager::clear(void)
{
  queue_.clear();
  publishers_.clear();
  subscribers_.clear();
}

std::vector<MessagePublisher> MessageManager::getPublishers(void)
{
  std::vector<MessagePublisher> publishers;

  for (const auto& pub : publishers_)
  {
    const auto& pubset = pub.second;
    for (const auto& entry : pubset)
      publishers.push_back(entry);
  }

  return publishers;
}

void MessageManager::notify(void)
{
  // In the future if we are extending it so some messages can be threaded off,
  // then we can add them as async tasks rather than directly calling the callback.
  // std::vector<std::future<void>> tasks;

  for (auto& entry : queue_)
  {
    const auto& msg_id = entry.first;
    auto& q = entry.second;

    auto&& messages = q.popAll();
    num_msgs_ -= messages.size();

    if (subscribers_.find(msg_id) == subscribers_.end())
      continue;

    auto& subscribers = subscribers_[msg_id];

    for (auto& msg : messages)
    {
      for (auto& sub : subscribers)
      {
        if (sub.cb != nullptr)
        {
          sub.cb(msg);
          // tasks.push_back(std::async(std::launch::async, sub.cb, msg));
        }
      }
    }

    // for (auto& task : tasks)
    //   task.get();
  }
}

void MessageManager::publish(const std::string msg_id, const MessagePublisher pub)
{
  std::lock_guard<std::mutex> lg(mlock_);

  publishers_[msg_id].insert(pub);
}

void MessageManager::subscribe(const std::string msg_id, const std::string plugin_name, MessageReceivedCb cb)
{
  std::lock_guard<std::mutex> lg(mlock_);

  MessageSubscriber sub;
  sub.name = plugin_name;
  sub.cb = cb;

  subscribers_[msg_id].insert(sub);
}

void MessageManager::send(const std::string msg_id, const std::string plugin_name,
                          std::shared_ptr<MessageInterface> msg)
{
  const std::string error = "Unauthorised publication request to " + msg_id + " from plugin " + plugin_name;

  {
    std::lock_guard<std::mutex> lg(qlock_);

    if (publishers_.find(msg_id) == publishers_.end())
    {
      std::cerr << error << std::endl;
      throw std::runtime_error(error);
    }

    auto& publishers = publishers_[msg_id];
    if (publishers.count(plugin_name) == 0)
    {
      std::cerr << error << std::endl;
      throw std::runtime_error(error);
    }

    queue_[msg_id].push(msg);

    ++num_msgs_;
  }

  q_cond_var_.notify_one();
}

bool MessageManager::waitForWork(void)
{
  if (!work_)
    return work_;

  auto ready = [&]() { return num_msgs_ != 0; };
  std::unique_lock<std::mutex> lock(qlock_);

  // Sleep and wait until there are things to process. If we want to restrict
  // the processing rate, add timing controls later. You can interrupt this
  // process by setting work_ to false.
  while (work_ && num_msgs_ == 0)
  {
    if (q_cond_var_.wait_for(lock, wait_time_, ready))
      break;
  }

  return work_;
}

void MessageManager::setWork(const bool flag)
{
  work_ = flag;
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS                                                           //
///////////////////////////////////////////////////////////////////////////////

}  // namespace soul