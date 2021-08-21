// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// main.cpp
//
#include "backup-tool.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(const int argc, const char * const argv[])
{
    using namespace backup;

    const std::vector<std::string> args((argv + 1), (argv + static_cast<std::size_t>(argc)));

    try
    {
        BackupTool backupTool(args);
        backupTool.run();
        return EXIT_SUCCESS;
    }
    catch (const silent_runtime_error &)
    {
        // these exceptions are only thrown if the error has already been printed
        // so nothing to do here
        return EXIT_SUCCESS;
    }
    catch (const std::exception & ex)
    {
        std::cout << "fatal exception error: \"" << ex.what() << "\"" << std::endl;
    }
    catch (...)
    {
        std::cout << "fatal exception error: (unknown)" << std::endl;
    }

    return EXIT_FAILURE;
}
