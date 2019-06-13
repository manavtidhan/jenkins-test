/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_MESSAGING_LIST_MESSAGE_H_
#define SOUL_MESSAGING_LIST_MESSAGE_H_

/**
 * Author: Jamie Diprose
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/interface.h>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INTERFACE                                                                 //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief List message template which enables batches of items to be sent as a single message.
 * @tparam T Message type you want to turn into a list message.
 */
template <typename T>
class ListMessage : MessageInterface
{
public:
  /**
   * @brief Constructor.
   * @param items The items to send.
   */
  explicit ListMessage(const std::vector<T> items) : items_(items)
  {
  }

  /**
   * @brief Get the items.
   * @return the items.
   */
  std::vector<T> getItems() const
  {
    return items_;
  }

#ifndef HR_DEBUG
private:
#endif
  std::vector<T> items_;  ///< the items to send.
};

}  // namespace soul
#endif  // SOUL_MESSAGING_LIST_MESSAGE_H_