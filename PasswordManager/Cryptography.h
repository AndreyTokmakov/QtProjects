/**============================================================================
Name        : Cryptography.h
Created on  : 30.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Cryptography.h
============================================================================**/

#ifndef QTPROJECTS_CRYPTOGRAPHY_H
#define QTPROJECTS_CRYPTOGRAPHY_H

#include <vector>
#include <cstdint>

namespace Cryptography
{
    bool encrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output);

    bool decrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output);
};

#endif //QTPROJECTS_CRYPTOGRAPHY_H
