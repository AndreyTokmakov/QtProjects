/**============================================================================
Name        : Encryption.cpp
Created on  : 16.05.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Encryption.h
============================================================================**/

#include "Encryption.h"
#include "Utilities.h"
#include "FileUtilities.h"

#include <expected>
#include <iostream>

#include "rsa.h"
#include "hex.h"
#include "crc.h"
#include "base64.h"
#include "osrng.h"
#include "modes.h"

namespace Encryption
{
    std::string encrypt(const std::string& input,
                        const std::vector<uint8_t>& key,
                        const std::vector<uint8_t>& iv)
    {
        CryptoPP::AES::Encryption aes { CryptoPP::AES::Encryption(key.data(), key.size()) };
        CryptoPP::CBC_Mode_ExternalCipher::Encryption aesCbc { CryptoPP::CBC_Mode_ExternalCipher::Encryption(aes, iv.data()) };

        /* std::unique_ptr<CryptoPP::Base64Encoder> encoder {
                std::make_unique<CryptoPP::Base64Encoder>(new CryptoPP::StringSink(cipher))
        };

        std::unique_ptr<CryptoPP::StreamTransformationFilter> transformFiler {
                std::make_unique<CryptoPP::StreamTransformationFilter>(aes_cbc, encoder.get())
        }; */

        std::string cipher;
        CryptoPP::Base64Encoder* encoder = new CryptoPP::Base64Encoder(new CryptoPP::StringSink(cipher));
        CryptoPP::StreamTransformationFilter* transformFiler = new CryptoPP::StreamTransformationFilter(aesCbc, encoder);
        CryptoPP::StringSource ss(input, true, transformFiler);

        // std::vector<uint8_t> data;
        // CryptoPP::VectorSource vs(data, true, transformFiler);

        return cipher;
    }

    std::string decrypt(const std::string& cipherText,
                        const std::vector<uint8_t>& key,
                        const std::vector<uint8_t>& iv)
    {
        std::string plain_text;

        CryptoPP::AES::Decryption aes = CryptoPP::AES::Decryption(key.data(), key.size());
        CryptoPP::CBC_Mode_ExternalCipher::Decryption aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Decryption(aes, iv.data());

        CryptoPP::StringSource ss(cipherText,
            true,
            new CryptoPP::Base64Decoder(new CryptoPP::StreamTransformationFilter(aes_cbc,new CryptoPP::StringSink(plain_text)))
        );

        return plain_text;
    }
}

namespace Encryption
{
    using namespace Utilities;
    using namespace FileUtilities;

    const std::vector<uint8_t> keyBytes {
        0x8c, 0xd7, 0x6f, 0xf1, 0x32, 0xaa, 0x44, 0xb5, 0x44,0x71, 0x90, 0xf3, 0x4f, 0x52, 0xfd, 0x88,
        0x3c, 0x4a,0xe3, 0x0, 0x42, 0xd9, 0x93, 0x40, 0xf5, 0x96, 0xa2, 0x30, 0x70, 0xf3, 0x3c, 0x78
    };

    const std::vector<uint8_t> ivBytes {
        0x9d, 0x85, 0xc7, 0x69, 0x7a, 0xec, 0xd4, 0x93, 0xa3, 0x4b, 0x1, 0x87, 0xb3, 0xf0, 0x46, 0x88
    };

    [[nodiscard]]
    std::expected<std::string, bool> encrypt(const std::string& content) noexcept
    {
        // FIXME: Handle error
        return encrypt(content, keyBytes, ivBytes);
    }

    [[nodiscard]]
    std::expected<std::string, std::string> decryptFile(const std::filesystem::path& filePath) noexcept
    {
        const std::string secretText = FileUtilities::ReadFile(filePath);
        std::string encryptedData = decrypt(secretText, keyBytes, ivBytes);

        // FIXME: Handle error
        return encryptedData;
    }

    [[nodiscard]]
    std::expected<std::string, bool> encryptFile(const std::string& filePath) noexcept
    {
        const std::string secretText = FileUtilities::ReadFile(filePath);

        // FIXME: Handle error
        return encrypt(secretText, keyBytes, ivBytes);
    }
}
