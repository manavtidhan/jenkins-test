/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense manager isolation tests for the message processing.
 *
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

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

class TestFixture : public ::testing::Test
{
public:
  const int expected_callback_calls = 250000;

  TestFixture() : cb_count(0), mgr(nullptr)
  {
  }

  void recv_cb(std::shared_ptr<MessageInterface> msg)
  {
    if (msg == nullptr)
      throw std::runtime_error("recvCb got a nullptr. somebody dun goofed.");

    ++cb_count;

    if (cb_count == expected_callback_calls)
      mgr->msgman_.setWork(false);
  }

  void sendMsgThread()
  {
    using namespace std::chrono_literals;

    for (int i = 0; i < expected_callback_calls; ++i)
    {
      auto msg = std::make_shared<MessageInterface>();
      mgr->msgman_.send("test", "plug1", msg);
    }
  }

  std::atomic<int> cb_count;

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

/*
 * Test the execution flow.
 * Thread will sleep, then send message, then sleep, then send message, then send work stop.
 * Manager is expected to handle the pauses etc until it's told to stop.
 */

TEST_F(TestFixture, run)
{
  using namespace std::chrono_literals;
  mgr->msgman_.publish("test", "plug1");
  mgr->msgman_.subscribe("test", "plug1", cb);

  std::thread t(&TestFixture::sendMsgThread, this);

  mgr->run();

  t.join();

  EXPECT_EQ(cb_count, expected_callback_calls);
}

#endif
///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS*//                                                           //
///////////////////////////////////////////////////////////////////////////////

}  // namespace sense
}  // namespace soul