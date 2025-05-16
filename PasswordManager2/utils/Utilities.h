/**============================================================================
Name        : Utilities.h
Created on  : 16.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Utilities.h
============================================================================**/

#ifndef CPPPROJECTS_UTILITIES_H
#define CPPPROJECTS_UTILITIES_H

#include <filesystem>
#include <vector>

namespace Utilities
{
    [[nodiscard]]
    std::vector<uint8_t> str2Bytes(const std::string& message);

    [[nodiscard]]
    std::vector<uint8_t> str2Bytes(std::string_view message);

    [[nodiscard]]
    std::string bytes2Str(const std::vector<uint8_t>& bytes);
}

#endif //CPPPROJECTS_UTILITIES_H
