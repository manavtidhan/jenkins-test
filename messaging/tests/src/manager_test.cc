/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Messaging manager test.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/list.h>
#include <soul/messaging/manager.h>
#include "dummy_msg.h"

#include <gmock/gmock.h>

#include <chrono>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// FIXTURE                                                                   //
///////////////////////////////////////////////////////////////////////////////

class TestFixture : public ::testing::Test
{
public:
protected:
  void SetUp() override
  {
    cb = std::bind(&TestFixture::recv_cb, this, std::placeholders::_1);
  }

  void TearDown() override
  {
  }

  void recv_cb(std::shared_ptr<MessageInterface> msg)
  {
    auto dmsg = std::dynamic_pointer_cast<DummyMessage>(msg);
    recv_msg = dmsg->str;
  }

  std::string recv_msg;

  MessageReceivedCb cb;

  MessageManager mgr;
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG
TEST_F(TestFixture, publish)
{
  mgr.publish("test", "plug1");
  mgr.publish("test", "plug2");

  EXPECT_EQ(mgr.publishers_["test"].size(), unsigned(2));
  EXPECT_EQ(mgr.publishers_["unknown"].size(), unsigned(0));
}

TEST_F(TestFixture, subscribe)
{
  mgr.subscribe("test", "plug1", nullptr);
  mgr.subscribe("test", "plug2", cb);

  auto& subs = mgr.subscribers_["test"];
  EXPECT_EQ(subs.size(), unsigned(2));
}

TEST_F(TestFixture, send_normal)
{
  mgr.publish("test", "plug1");
  mgr.subscribe("test", "plug1", cb);

  auto msg = std::make_shared<DummyMessage>("Hi");
  mgr.send("test", "plug1", msg);

  auto& q = mgr.queue_["test"];
  EXPECT_EQ(q.size(), unsigned(1));
}

TEST_F(TestFixture, send_no_subs)
{
  mgr.publish("test", "plug1");
  auto msg = std::make_shared<DummyMessage>("Hi");
  mgr.send("test", "plug1", msg);
  auto& q = mgr.queue_["test"];
  EXPECT_EQ(q.size(), unsigned(1));
}

TEST_F(TestFixture, send_no_pub)
{
  mgr.subscribe("test", "plug1", cb);
  auto msg = std::make_shared<DummyMessage>("Hi");
  EXPECT_THROW(mgr.send("test", "plug1", msg), std::runtime_error);
}

TEST_F(TestFixture, send_and_notify)
{
  mgr.publish("test", "plug1");
  mgr.subscribe("test", "plug1", cb);

  auto msg = std::make_shared<DummyMessage>("Hi");

  EXPECT_EQ(recv_msg, "");

  mgr.send("test", "plug1", msg);

  mgr.notify();

  EXPECT_EQ(recv_msg, "Hi");

  auto& q = mgr.queue_["test"];
  EXPECT_EQ(q.size(), unsigned(0));
}

TEST_F(TestFixture, send_and_notify_no_cb)
{
  mgr.publish("test", "plug1");
  mgr.subscribe("test", "plug1", nullptr);

  auto msg = std::make_shared<DummyMessage>("Hi");

  EXPECT_EQ(recv_msg, "");

  mgr.send("test", "plug1", msg);

  auto& q = mgr.queue_["test"];
  EXPECT_EQ(q.size(), unsigned(1));

  mgr.notify();

  EXPECT_EQ(recv_msg, "");

  auto& q2 = mgr.queue_["test"];
  EXPECT_EQ(q2.size(), unsigned(0));
}

TEST_F(TestFixture, setWork)
{
  EXPECT_TRUE(mgr.work_);
  mgr.setWork(false);
  EXPECT_FALSE(mgr.work_);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

TEST_F(TestFixture, getPublishers)
{
  mgr.publish("test", "plug1");
  mgr.publish("test", "plug2");

  auto pubs = mgr.getPublishers();
  ASSERT_EQ(pubs.size(), static_cast<size_t>(2));
  EXPECT_EQ(pubs.at(1).name, "plug1");
  EXPECT_EQ(pubs.at(0).name, "plug2");
}

TEST_F(TestFixture, waitForWork_non_empty)
{
  mgr.publish("test", "plug1");

  auto msg = std::make_shared<DummyMessage>("Hi");

  mgr.send("test", "plug1", msg);

  EXPECT_TRUE(mgr.waitForWork());
}

static void msgSender(MessageManager* mgr)
{
  using namespace std::chrono_literals;

  std::this_thread::sleep_for(20ms);

  auto msg = std::make_shared<DummyMessage>("Hi");

  mgr->send("test", "plug1", msg);
}

TEST_F(TestFixture, waitForWork_temp_empty)
{
  mgr.publish("test", "plug1");

  std::thread t(msgSender, &mgr);

  EXPECT_TRUE(mgr.waitForWork());

  t.join();
}

static void msgInterrupt(MessageManager* mgr)
{
  using namespace std::chrono_literals;

  std::this_thread::sleep_for(20ms);

  mgr->setWork(false);
}

TEST_F(TestFixture, waitForWork_interrupted)
{
  mgr.publish("test", "plug1");

  std::thread t(msgInterrupt, &mgr);

  EXPECT_FALSE(mgr.waitForWork());

  t.join();
}

TEST(TestListMessageCompiles, IfThisWorksListMessageCompiled)
{
  std::vector<int> items = { 4, 8, 15, 16, 23, 42 };
  ListMessage<int> test_list(items);
  test_list.getItems();

  EXPECT_TRUE(true);
}

}  // namespace soul