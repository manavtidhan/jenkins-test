/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Messaging queue test.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/messaging/queue.h>
#include "dummy_msg.h"

#include <gmock/gmock.h>

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
  }

  void TearDown() override
  {
  }

  MessageQueue msg_q;
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

static void push_hi(MessageQueue& q)
{
  for (int i = 0; i < 500; ++i)
  {
    auto msg = std::make_shared<DummyMessage>("Hi");
    q.push(std::move(msg));
  }
}

static void push_sleep(MessageQueue& q)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  auto msg = std::make_shared<DummyMessage>("Hi");
  q.push(std::move(msg));
}

TEST_F(TestFixture, push_threaded)
{
  EXPECT_TRUE(msg_q.empty());
  auto t = std::thread(push_hi, std::ref(msg_q));

  for (int i = 0; i < 500; ++i)
  {
    auto msg = std::make_shared<DummyMessage>("Hi");
    msg_q.push(std::move(msg));
  }

  t.join();

  EXPECT_EQ(msg_q.size(), unsigned(1000));
  EXPECT_FALSE(msg_q.empty());
}

TEST_F(TestFixture, pop_empty_first)
{
  auto t = std::thread(push_sleep, std::ref(msg_q));
  msg_q.pop();

  t.join();
}

TEST_F(TestFixture, pop_normal)
{
  for (int i = 0; i < 500; ++i)
  {
    auto msg = std::make_shared<DummyMessage>("Hi");
    msg_q.push(std::move(msg));
  }

  for (int i = 0; i < 500; ++i)
  {
    auto msg = std::dynamic_pointer_cast<DummyMessage>(msg_q.pop());
    EXPECT_EQ(msg->str, "Hi");
  }
}

TEST_F(TestFixture, popAll)
{
  for (int i = 0; i < 500; ++i)
  {
    auto msg = std::make_shared<DummyMessage>("Hi");
    msg_q.push(std::move(msg));
  }

  auto msgs = msg_q.popAll();
  EXPECT_EQ(msgs.size(), unsigned(500));
}

}  // namespace soul