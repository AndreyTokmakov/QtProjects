/**============================================================================
Name        : Utilities.cpp
Created on  : 16.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Utilities.h
============================================================================**/


#include "Utilities.h"

namespace Utilities
{
    std::vector<uint8_t> str2Bytes(const std::string& message)
    {
        std::vector<uint8_t> out(message.size());
        for (size_t n = 0; n < message.size(); n++) {
            out[n] = message[n];
        }
        return out;
    }

    std::vector<uint8_t> str2Bytes(const std::string_view message)
    {
        std::vector<uint8_t> out(message.size());
        for (size_t n = 0; n < message.size(); n++) {
            out[n] = message[n];
        }
        return out;
    }

    std::string bytes2Str(const std::vector<uint8_t>& bytes)
    {
        return std::string(bytes.begin(), bytes.end());
    }
}

