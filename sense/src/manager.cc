/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Soul sense manager. Responsible for the perception system.
 *
 * Author: Tuan Chien
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/manager.h>
#include <soul/sense/plugin_profile.h>

#include <functional>

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

SoulSenseManager::SoulSenseManager(const SoulSenseManagerParameters& params,
                                   const SoulSenseHwManagerParameters& hwparams)
  : params_(params), hw_params_(hwparams), hwman_(nullptr)
{
  // Initialise hardware manager
  hw_params_.msgman = &msgman_;
  hw_params_.sender =
      std::bind(&MessageManager::send, &msgman_, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  hwman_ = std::make_unique<SoulSenseHwManager>(hw_params_);

  /* Initialise the plugins. */
  loadPlugins();
  configurePlugins();
}

SoulSenseManager::~SoulSenseManager()
{
  msgman_.clear();
}

void SoulSenseManager::interrupt(void)
{
  std::cerr << "SoulSenseManager received an interrupt signal.\n"
            << "Stopping message queue processing.\n";

  msgman_.setWork(false);
}

void SoulSenseManager::run()
{
  activatePlugins();
  hwman_->activatePlugins();

  // Main event loop.
  // The current strategy is to tie execution to messaging callbacks.
  // If locking slowdown becomes a performance issue, we could replace this with
  // a wait and notify single function call with backend changes to messaging
  // manager.
  while (msgman_.waitForWork())
  {
    msgman_.notify();
  }
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS                                                           //
///////////////////////////////////////////////////////////////////////////////

void SoulSenseManager::loadPlugins()
{
  // For now, just load all plugins.
  pluginman_.loadAll(params_.plugin_dir, params_.section_name);
}

void SoulSenseManager::configurePlugins()
{
  // For each loaded plugin, configure them.
  auto&& loaded_plugins = pluginman_.listLoadedPlugins();

  for (auto& p : loaded_plugins)
  {
    auto* plugin = dynamic_cast<SensePluginInterface*>(pluginman_.getPlugin(p));

    // TODO: parameter loading.
    std::unordered_map<std::string, std::string> params;
    plugin->configure(params);

    // Setup messaging system.
    setupMessaging(plugin);
  }
}

void SoulSenseManager::activatePlugins()
{
  // For each loaded plugin, configure them.
  auto&& loaded_plugins = pluginman_.listLoadedPlugins();

  for (auto& p : loaded_plugins)
  {
    auto* plugin = dynamic_cast<SensePluginInterface*>(pluginman_.getPlugin(p));

    plugin->activate();
  }
}

void SoulSenseManager::setupMessaging(SensePluginInterface* plugin)
{
  auto* profile = reinterpret_cast<const SensePluginProfile*>(plugin->getProfile());

  // Subscribe
  for (auto& sub : profile->subs)
    msgman_.subscribe(sub.msg_id, sub.name, sub.cb);

  // Publish
  for (auto& pub : profile->pubs)
    msgman_.publish(pub.msg_id, pub);

  // Set messaging function
  auto sender = std::bind(&soul::MessageManager::send, &msgman_, std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3);

  plugin->setMessageSender(sender);
}

}  // namespace sense
}  // namespace soul