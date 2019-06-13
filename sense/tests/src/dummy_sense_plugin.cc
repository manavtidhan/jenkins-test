/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy sense plugin for testing.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include "dummy_sense_plugin.h"

#include <boost/dll/alias.hpp>

#include <iostream>

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

///////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS                                                            //
///////////////////////////////////////////////////////////////////////////////

DummySensePlugin::DummySensePlugin() : state_(PluginState::unconfigured)
{
  profile_.pubs.push_back(MessagePublisher("test1", "dummy_sense_plugin", MessageType::image));
  profile_.pubs.push_back(MessagePublisher("test2", "dummy_sense_plugin", MessageType::image));

  MessageSubscriber subber("msg_name", name());
  profile_.subs.push_back(subber);
}

void DummySensePlugin::setMessageSender(MessageSenderFn fn)
{
  msg_sender_ = fn;
}

void DummySensePlugin::setErrorCb(ErrorCbFunc cb)
{
  error_cb_ = cb;
}

bool DummySensePlugin::configure(std::unordered_map<std::string, std::string>& params)
{
  params_ = params;
  state_ = PluginState::inactive;

  return true;
}

bool DummySensePlugin::activate(void)
{
  state_ = PluginState::active;

  if (msg_sender_ != nullptr)
  {
    auto msg = std::make_shared<MessageInterface>();
    msg_sender_("test1", "dummy_sense_plugin", msg);
  }

  return true;
}

bool DummySensePlugin::deactivate(void)
{
  state_ = PluginState::inactive;
  return true;
}

bool DummySensePlugin::cleanup(void)
{
  state_ = PluginState::shutdown;
  return true;
}

std::string DummySensePlugin::name() const
{
  return std::string(plugin_section_name_) + "," + std::string("dummy_sense_plugin");
}

const PluginProfile* DummySensePlugin::getProfile() const
{
  return &profile_;
}

PluginState DummySensePlugin::getState(void) const
{
  return state_;
}

std::unique_ptr<DummySensePlugin> DummySensePlugin::create(void)
{
  return std::make_unique<DummySensePlugin>();
}

/* Export the symbols so that they can be loaded by the plugin manager. */
BOOST_DLL_ALIAS_SECTIONED(soul::sense::DummySensePlugin::create,  // Exporting this object
                          create,                                 // Export symbol (alias)
                          Sense                                   // Section name. At most 8 bytes.
)

}  // namespace sense
}  // namespace soul