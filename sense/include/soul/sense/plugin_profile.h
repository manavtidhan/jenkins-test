/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

#ifndef SOUL_SENSE_PLUGIN_PROFILE_H_
#define SOUL_SENSE_PLUGIN_PROFILE_H_

/**
 * Soul Sense plugin profile.
 * Specialises the PluginProfile interface to Soul Sense plugins.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/message_publisher.h>
#include <soul/messaging/message_subscriber.h>
#include <soul/plugins/interface.h>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Soul sense plugin profile and settings.
 */
struct SensePluginProfile : public soul::PluginProfile
{
  bool thread;                          ///< Whether we should launch in an independent thread.
  std::vector<MessagePublisher> pubs;   ///< List of topics we want to request publication to.
  std::vector<MessageSubscriber> subs;  ///< List of topics (including callbacks) we want to subscribe to.

  /**
   * @brief Initialise everything to default values.
   */
  explicit SensePluginProfile() : thread(false)
  {
  }

  /**
   * @brief Full initialisation.
   * @param thread Whether to launch in an independent thread.
   * @param List of topics we want to request publication to.
   * @param List of topics (including callbacks) we want to subscribe to.
   */
  explicit SensePluginProfile(const bool t, const std::vector<MessagePublisher>& p,
                              const std::vector<MessageSubscriber>& s)
    : thread(t), pubs(p), subs(s)
  {
  }

  /** Add virtual destructor just in case. */
  virtual ~SensePluginProfile() = default;
};

}  // namespace sense
}  // namespace soul
#endif  // SOUL_SENSE_PLUGIN_PROFILE_H_