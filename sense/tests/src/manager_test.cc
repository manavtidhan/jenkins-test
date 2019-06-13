/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense manager test.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/manager.h>

#include <gmock/gmock.h>

#include <atomic>
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
  TestFixture() : mgr(nullptr)
  {
  }

  void recv_cb(std::shared_ptr<MessageInterface> msg)
  {
    if (msg == nullptr)
      throw std::runtime_error("recvCb got a nullptr. somebody dun goofed.");
  }

protected:
  void SetUp() override
  {
    SoulSenseManagerParameters params(".", "Sense");

    /* Hardware parameters. */
    soul::sense::SoulSenseHwManagerParameters hwparams;
    hwparams.plugin_dir = ".";
    hwparams.section_name = "SenseHw";

    mgr = std::make_unique<SoulSenseManager>(params, hwparams);

    cb = std::bind(&TestFixture::recv_cb, this, std::placeholders::_1);
  }

  void TearDown() override
  {
  }

  std::unique_ptr<SoulSenseManager> mgr;

  MessageReceivedCb cb;
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

TEST_F(TestFixture, init)
{
  auto&& plugins = mgr->pluginman_.listLoadedPlugins();
  ASSERT_EQ(plugins.size(), static_cast<size_t>(1));

  auto* plugin = dynamic_cast<SensePluginInterface*>(mgr->pluginman_.getPlugin(plugins.at(0)));

  EXPECT_EQ(plugin->getState(), PluginState::inactive);
}

TEST_F(TestFixture, msg_queue_setup)
{
  EXPECT_EQ(mgr->msgman_.publishers_.size(), static_cast<size_t>(3));
  EXPECT_EQ(mgr->msgman_.subscribers_.size(), static_cast<size_t>(1));
}

TEST_F(TestFixture, msg_send_test)
{
  auto&& plugins = mgr->pluginman_.listLoadedPlugins();
  ASSERT_EQ(plugins.size(), static_cast<size_t>(1));
  auto* plugin = dynamic_cast<SensePluginInterface*>(mgr->pluginman_.getPlugin(plugins.at(0)));
  plugin->activate();

  EXPECT_EQ(mgr->msgman_.num_msgs_, 1);
}

TEST_F(TestFixture, hwman_activate)
{
  EXPECT_EQ(mgr->msgman_.publishers_.size(), static_cast<size_t>(3));
  EXPECT_EQ(mgr->msgman_.num_msgs_, 0);
  mgr->hwman_->activatePlugins();
  EXPECT_EQ(mgr->msgman_.num_msgs_, 1);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

TEST_F(TestFixture, hello)
{
  EXPECT_TRUE(true);  // add a test
}

}  // namespace sense
}  // namespace soul