/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Plugin manager test for Soul Sense.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/plugins/manager.h>
#include <soul/sense/plugin_interface.h>
#include "dummy_sense_plugin.h"

#include <gmock/gmock.h>

#include <experimental/filesystem>
#include <functional>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
namespace sense
{
///////////////////////////////////////////////////////////////////////////////
// FIXTURE                                                                   //
///////////////////////////////////////////////////////////////////////////////

class TestFixture : public ::testing::Test
{
public:
  void errorcb(const SenseError error)
  {
    error_ = error;
  }

protected:
  const std::string dummy_plugin_name = "dummy_sense_plugin";

  std::string plugin_name_;

  PluginManager<SensePluginInterface> pluginman_;
  SenseError error_;

  void SetUp() override
  {
    plugin_name_ = std::string(plugin_section_name_) + "," + dummy_plugin_name;
    pluginman_.load(".", dummy_plugin_name, plugin_section_name_);
  }

  void TearDown() override
  {
  }
};  // namespace sense

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

TEST_F(TestFixture, errorcb)
{
  auto* plugin_r = pluginman_.getPlugin(plugin_name_);
  DummySensePlugin* plugin = reinterpret_cast<DummySensePlugin*>(plugin_r);

  EXPECT_TRUE(plugin->error_cb_ == nullptr);
  auto cb = std::bind(&TestFixture::errorcb, this, std::placeholders::_1);
  plugin_r->setErrorCb(cb);
  EXPECT_TRUE(plugin->error_cb_ != nullptr);
}

#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

TEST_F(TestFixture, name)
{
  auto* plugin = pluginman_.getPlugin(plugin_name_);
  EXPECT_EQ(plugin->name(), plugin_name_);
}

TEST_F(TestFixture, profile)
{
  auto* plugin = pluginman_.getPlugin(plugin_name_);
  const auto* profile = dynamic_cast<const SensePluginProfile*>(plugin->getProfile());
  EXPECT_EQ(profile->thread, false);
  EXPECT_EQ(profile->subs.size(), unsigned(1));
  EXPECT_EQ(profile->pubs.size(), unsigned(2));
}

TEST_F(TestFixture, modeswitch)
{
  auto* plugin = pluginman_.getPlugin(plugin_name_);
  EXPECT_EQ(plugin->getState(), PluginState::unconfigured);
  EXPECT_TRUE(plugin->activate());
  EXPECT_EQ(plugin->getState(), PluginState::active);
  EXPECT_TRUE(plugin->deactivate());
  EXPECT_EQ(plugin->getState(), PluginState::inactive);
  EXPECT_TRUE(plugin->cleanup());
  EXPECT_EQ(plugin->getState(), PluginState::shutdown);
}

TEST_F(TestFixture, config)
{
  auto* plugin = pluginman_.getPlugin(plugin_name_);

  std::unordered_map<std::string, std::string> params;
  EXPECT_TRUE(plugin->configure(params));
}

}  // namespace sense
}  // namespace soul
