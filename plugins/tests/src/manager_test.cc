/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Plugin manager test.
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/plugins/manager.h>
#include "dummy_plugin_type.h"

#include <gmock/gmock.h>

#include <experimental/filesystem>
#include <functional>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACES                                                                //
///////////////////////////////////////////////////////////////////////////////

namespace soul
{
///////////////////////////////////////////////////////////////////////////////
// FIXTURE                                                                   //
///////////////////////////////////////////////////////////////////////////////

class LoaderFixture : public ::testing::Test
{
protected:
  PluginManager<DummyPluginType> pluginman;

  std::string plugpath;
  std::string sectname;
  std::string symbname;

  std::string plugname;

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

public:
  void loadCallback(const std::string plugin_path, const std::string section_name, const std::string symbol_name)
  {
    plugpath = plugin_path;
    sectname = section_name;
    symbname = symbol_name;
  }

  void unloadCallback(const std::string plugin_name)
  {
    plugname = plugin_name;
  }
};

///////////////////////////////////////////////////////////////////////////////
// PRIVATE TESTS                                                             //
///////////////////////////////////////////////////////////////////////////////

#ifdef HR_DEBUG

// Make sure that the plugins get saved in the manager, and that the name() method is callable.
TEST_F(LoaderFixture, load_no_callback_name)
{
  EXPECT_TRUE(pluginman.load(".", "dummy_plugin", "Dummy"));

  EXPECT_EQ(pluginman.plugins_.size(), unsigned(1));

  EXPECT_TRUE(pluginman.plugins_.find("Dummy,dummy_plugin") != pluginman.plugins_.end());

  DummyPluginType* plugin = pluginman.plugins_["Dummy,dummy_plugin"].get();

  EXPECT_TRUE(plugin != nullptr);

  EXPECT_EQ(plugin->name(), "Dummy,dummy_plugin");
}

#endif

///////////////////////////////////////////////////////////////////////////////
// PUBLIC TESTS                                                              //
///////////////////////////////////////////////////////////////////////////////

// Simple plugin load. Make sure it doesn't try to load duplicates.
TEST_F(LoaderFixture, load_no_callback)
{
  EXPECT_TRUE(pluginman.load(".", "dummy_plugin", "Dummy"));
  EXPECT_FALSE(pluginman.load(".", "dummy_plugin", "Dummy"));
}

// Test the loading callback function.
TEST_F(LoaderFixture, load_callback)
{
  auto load_cb = std::bind(&LoaderFixture::loadCallback, this, std::placeholders::_1, std::placeholders::_2,
                           std::placeholders::_3);

  EXPECT_TRUE(plugpath.empty());
  EXPECT_TRUE(sectname.empty());
  EXPECT_TRUE(symbname.empty());
  EXPECT_TRUE(plugname.empty());

  pluginman.setLoadCallback(load_cb);
  pluginman.load(".", "dummy_plugin", "Dummy");

  EXPECT_EQ(plugpath, "./libdummy_plugin.so");
  EXPECT_EQ(sectname, "Dummy");
  EXPECT_EQ(symbname, "create");
  EXPECT_TRUE(plugname.empty());
}

TEST_F(LoaderFixture, loadAll_callback)
{
  auto load_cb = std::bind(&LoaderFixture::loadCallback, this, std::placeholders::_1, std::placeholders::_2,
                           std::placeholders::_3);

  EXPECT_TRUE(plugpath.empty());
  EXPECT_TRUE(sectname.empty());
  EXPECT_TRUE(symbname.empty());
  EXPECT_TRUE(plugname.empty());

  pluginman.setLoadCallback(load_cb);
  EXPECT_TRUE(pluginman.loadAll(".", "Dummy"));

  EXPECT_EQ(plugpath, "./libdummy_plugin.so");
  EXPECT_EQ(sectname, "Dummy");
  EXPECT_EQ(symbname, "create");
  EXPECT_TRUE(plugname.empty());
}

// Test the unload mechanism and callback function.
TEST_F(LoaderFixture, unload_callback)
{
  auto unload_cb = std::bind(&LoaderFixture::unloadCallback, this, std::placeholders::_1);
  pluginman.setUnloadCallback(unload_cb);

  EXPECT_TRUE(plugname.empty());
  EXPECT_TRUE(pluginman.load(".", "dummy_plugin", "Dummy"));
  EXPECT_TRUE(pluginman.unload("Dummy,dummy_plugin"));
  EXPECT_EQ(plugname, "Dummy,dummy_plugin");

  EXPECT_EQ(pluginman.listLoadedPlugins().size(), unsigned(0));
}

// Test retrieving list of plugins.
TEST_F(LoaderFixture, listLoadedPlugins)
{
  auto plugins = pluginman.listLoadedPlugins();
  EXPECT_EQ(plugins.size(), unsigned(0));
  EXPECT_TRUE(pluginman.load(".", "dummy_plugin", "Dummy"));
  plugins = pluginman.listLoadedPlugins();
  ASSERT_EQ(plugins.size(), unsigned(1));
  EXPECT_EQ(plugins.at(0), "Dummy,dummy_plugin");
}

// Test getting valid plugin pointer.
TEST_F(LoaderFixture, getPlugin_valid)
{
  EXPECT_TRUE(pluginman.load(".", "dummy_plugin", "Dummy"));
  EXPECT_NO_THROW(pluginman.getPlugin("Dummy,dummy_plugin"));
  auto plugin = pluginman.getPlugin("Dummy,dummy_plugin");
  EXPECT_TRUE(plugin != nullptr);
}

// Test getting invalid plugin.
TEST_F(LoaderFixture, getPlugin_invalid)
{
  EXPECT_THROW(pluginman.getPlugin("this name should not exist"), std::runtime_error);
}

}  // namespace soul