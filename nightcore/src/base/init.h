#pragma once

#ifndef __FAAS_SRC
#error base/init.h cannot be included outside
#endif

#include <vector>

namespace faas {
  namespace base {

    /**
     * @brief Initializes the main function for the application.
     *
     * This function sets up the necessary environment for the application to run,
     * including initializing the symbolizer, installing a failure signal handler,
     * parsing command line arguments, initializing logging, and registering the main thread.
     *
     * @param argc The number of command line arguments.
     * @param argv The array of command line arguments.
     * @param positional_args A pointer to a vector that will store positional arguments.
     *                        If nullptr, the function will check if there are any positional
     *                        arguments and log a fatal error if there are.
     */
    void InitMain(int argc, char* argv[], std::vector<char*>* positional_args = nullptr);

  }  // namespace base
}  // namespace faas
