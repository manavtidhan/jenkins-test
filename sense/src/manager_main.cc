/*
 * Copyright 2019 Hanson Robotics Limited. All Rights Reserved.
 */

/*
 * Main function stuff for the soul sense manager.
 *
 * Author: Tuan Chien.
 */

///////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                  //
///////////////////////////////////////////////////////////////////////////////

#include <soul/sense/hw_manager.h>
#include <soul/sense/manager.h>

#include <boost/program_options.hpp>

#include <signal.h>

#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// CUSTOM DEFINITIONS                                                        //
///////////////////////////////////////////////////////////////////////////////

/** Program return codes. */
enum ReturnCodes
{
  SUCCESS = 0,
  COMMAND_LINE_ARG_ERROR = 1
};

///////////////////////////////////////////////////////////////////////////////
// STATIC METHODS                                                            //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Convert boost program options to Soul sense manager's options.
 * @param vm Boost variable map.
 * @return Soul sense manager options.
 */
static soul::sense::SoulSenseManagerParameters getSoulSenseParameters(const boost::program_options::variables_map& vm)
{
  using namespace soul::sense;

  SoulSenseManagerParameters params;

  params.plugin_dir = vm["dir"].as<std::string>();
  params.section_name = vm["secname"].as<std::string>();

  return params;
}

/**
 * @brief Defines the command line arguments.
 * @return Boost command line arguments object.
 */
static boost::program_options::options_description getOptions()
{
  using namespace boost::program_options;
  options_description desc{ "Command line arguments" };

  desc.add_options()("help,h", "Help screen");

  // just to suppress unused-parameter errors. remove this later.
  // desc.add_options()("dir,d", value<std::string>()->default_value("plugins/sense"), "plugins directory");

  // For testing
  desc.add_options()("dir,d", value<std::string>()->default_value("."), "plugins directory");

  desc.add_options()("secname,s", value<std::string>()->default_value("Sense"), "plugin section name");

  return desc;
}

/**
 * @brief Parse the command line arguments.
 * @param argc Command line argument count.
 * @param argv Command line arguments.
 * @param vm Variables map of parsed arguments.
 * @param options Boost command line arguments object.
 * @return True on success, false on failure.
 */
bool parseCommandLine(int argc, char* argv[], boost::program_options::variables_map& vm,
                      boost::program_options::options_description& options) try
{
  using namespace boost::program_options;

  store(parse_command_line(argc, argv, options), vm);
  notify(vm);

  if (vm.count("help") > 0)
  {
    std::cout << options << '\n';
    return false;
  }

  return true;
}
catch (const boost::program_options::error& ex)
{
  std::cerr << ex.what() << "\n";
  std::cout << options << '\n';
  return false;
}

/** Pointer to the manager object. Used for signal handling. */
soul::sense::SoulSenseManager* g_sense_man_ptr = nullptr;

/**
 * @brief Interrupt signal handler (ctrl+c).
 * @param s Signal number.
 */
static void interruptHandler(int s)
{
  std::cerr << "\nInterrupt detected.\n";

  if (s != SIGINT)
    std::cerr << "interruptHandler called on non SIGINT signal.\n";

  if (g_sense_man_ptr != nullptr)
    g_sense_man_ptr->interrupt();
}

///////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION                                                             //
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  boost::program_options::variables_map vm;

  /* Extract command line arguments. */
  auto&& options = getOptions();

  if (!parseCommandLine(argc, argv, vm, options))
    return COMMAND_LINE_ARG_ERROR;

  /* Convert command line arguments to the manager parameters. */
  auto&& params = getSoulSenseParameters(vm);

  /* Hardware parameters. */
  soul::sense::SoulSenseHwManagerParameters hwparams;
  hwparams.plugin_dir = ".";
  hwparams.section_name = "SenseHw";

  /* Instantiate the manager. */
  // soul::sense::SoulSenseManager mgr(params);
  soul::sense::SoulSenseManager mgr(params, hwparams);

  g_sense_man_ptr = &mgr;

  // Register interrupt signal handler.
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = interruptHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, nullptr);

  /* Run the manager. */
  mgr.run();

  return SUCCESS;
}