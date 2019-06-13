/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Dummy sense hardware plugin.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include "dummy_sense_hw_plugin.h"
#include <soul/sense/hw_plugin_interface.h>

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

DummySenseHwPlugin::DummySenseHwPlugin() : name_("dummy_sense_hw_plugin"), state_(PluginState::unconfigured)
{
  profile_.pubs.push_back(MessagePublisher("test3", name_, MessageType::image));

  profile_.devinfo.id = "2";
  profile_.devinfo.name = "dummydevice";
  profile_.devinfo.type = DeviceType::Camera;
  profile_.devinfo.attributes.push_back("RGBD");
}

void DummySenseHwPlugin::setErrorCb(HwErrorCbFunc cb)
{
  cb_ = cb;
}

bool DummySenseHwPlugin::configure(std::unordered_map<std::string, std::string>& params)
{
  params_ = params;

  return true;
}

bool DummySenseHwPlugin::activate(void)
{
  state_ = PluginState::active;

  if (sender_ != nullptr)
  {
    auto msg = std::make_shared<MessageInterface>();
    sender_("test3", name_, msg);
  }

  return true;
}

bool DummySenseHwPlugin::deactivate(void)
{
  state_ = PluginState::inactive;
  return true;
}

bool DummySenseHwPlugin::cleanup(void)
{
  state_ = PluginState::shutdown;
  return true;
}

PluginState DummySenseHwPlugin::getState(void) const
{
  return state_;
}

void DummySenseHwPlugin::setMessageSender(MessageSenderFn fn)
{
  sender_ = fn;
}

std::string DummySenseHwPlugin::name() const
{
  return name_;
}

const PluginProfile* DummySenseHwPlugin::getProfile() const
{
  return &profile_;
}

std::unique_ptr<DummySenseHwPlugin> DummySenseHwPlugin::create()
{
  return std::make_unique<DummySenseHwPlugin>();
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS                                                           //
///////////////////////////////////////////////////////////////////////////////

/* Export the symbols so that they can be loaded by the plugin manager. */
BOOST_DLL_ALIAS_SECTIONED(soul::sense::DummySenseHwPlugin::create,  // Exporting this object
                          create,                                   // Export symbol (alias)
                          SenseHw                                   // Section name. At most 8 bytes.
)

}  // namespace sense
}  // namespace soul