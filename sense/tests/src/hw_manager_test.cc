/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense hardware manager test.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/hw_manager.h>
#include <soul/sense/hw_plugin_profile.h>

#include <gmock/gmock.h>

#include <memory>

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
  TestFixture() : hwman(nullptr)
  {
  }

protected:
  std::unique_ptr<SoulSenseHwManager> hwman;
  MessageManager msgman;

  void SetUp() override
  {
    SoulSenseHwManagerParameters params;
    params.plugin_dir = ".";
    params.section_name = hw_plugin_section_name_;
    params.msgman = &msgman;
    params.sender =
        std::bind(&MessageManager::send, &msgman, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    hwman = std::make_unique<SoulSenseHwManager>(params);
  }

  void TearDown() override
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

TEST_F(TestFixture, init_load)
{
  auto&& plugins = hwman->pluginman_.listLoadedPlugins();
  ASSERT_EQ(plugins.size(), static_cast<size_t>(1));

  auto* plugin = dynamic_cast<SenseHwPluginInterface*>(hwman->pluginman_.getPlugin(plugins.at(0)));

  EXPECT_EQ(plugin->name(), "dummy_sense_hw_plugin");

  EXPECT_EQ(plugin->getState(), PluginState::unconfigured);
}

TEST_F(TestFixture, msg_queue_setup)
{
  EXPECT_EQ(msgman.publishers_.size(), static_cast<size_t>(1));
}

TEST_F(TestFixture, msg_send_test)
{
  hwman->activatePlugins();
  EXPECT_EQ(msgman.num_msgs_, 1);
}

TEST_F(TestFixture, profileCheck)
{
  auto&& plugins = hwman->pluginman_.listLoadedPlugins();
  ASSERT_EQ(plugins.size(), static_cast<size_t>(1));

  auto* plugin = dynamic_cast<SenseHwPluginInterface*>(hwman->pluginman_.getPlugin(plugins.at(0)));

  auto* profile = dynamic_cast<const SenseHwPluginProfile*>(plugin->getProfile());
  EXPECT_EQ(profile->devinfo.id, "2");
  EXPECT_EQ(profile->devinfo.name, "dummydevice");
  EXPECT_EQ(profile->devinfo.type, DeviceType::Camera);
  ASSERT_EQ(profile->devinfo.attributes.size(), static_cast<size_t>(1));
  EXPECT_EQ(profile->devinfo.attributes.at(0), "RGBD");
}

#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

}  // namespace sense
}  // namespace soul