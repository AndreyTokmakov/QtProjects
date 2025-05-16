/**============================================================================
Name        : Encryption.h
Created on  : 16.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Encryption.h
============================================================================**/

#ifndef CPPPROJECTS_ENCRYPTION_H
#define CPPPROJECTS_ENCRYPTION_H

#include <string>
#include <vector>
#include <filesystem>
#include <expected>

namespace Encryption
{
    [[nodiscard]]
    std::string encrypt(const std::string& input,
                        const std::vector<uint8_t>& key,
                        const std::vector<uint8_t>& iv);

    [[nodiscard]]
    std::string decrypt(const std::string& cipherText,
                        const std::vector<uint8_t>& key,
                        const std::vector<uint8_t>& iv);

    /** Test Functions **/

    [[nodiscard]]
    std::expected<std::string, std::string> decryptFile(const std::filesystem::path& filePath) noexcept;

    [[nodiscard]]
    std::expected<std::string, bool> encryptFile(const std::string& filePath) noexcept;

    [[nodiscard]]
    std::expected<std::string, bool> encrypt(const std::string& content) noexcept;
}

#endif //CPPPROJECTS_ENCRYPTION_H
