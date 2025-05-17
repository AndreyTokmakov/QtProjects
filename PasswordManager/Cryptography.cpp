/**============================================================================
Name        : Cryptography.cpp
Created on  : 30.11.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Cryptography.cpp
============================================================================**/

#include "Cryptography.h"


#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/engine.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/dh.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/stack.h>
#include <openssl/pkcs12.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/evperr.h>
#include <openssl/aes.h>
#include <openssl/crypto.h>


#include <memory>
#include <iostream>

namespace Cryptography
{
    bool encrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output)
    {
        output.resize(message.size() * AES_BLOCK_SIZE);
        int outlen = 0;

        std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx {
                EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free
        };

        if (0 == EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), nullptr, key.data(), iv.data())) {
            std::cerr << "Error: EVP_EncryptInit() failed" << std::endl;
            return false;
        }
        if (0 == EVP_EncryptUpdate(ctx.get(), output.data(), &outlen, message.data(), message.size())) {
            std::cerr << "Error: EVP_EncryptUpdate() failed" << std::endl;
            return false;
        }
        size_t total_out = outlen;
        if (0 == EVP_EncryptFinal_ex(ctx.get(), output.data()+total_out, &outlen)) {
            std::cerr << "Error: EVP_EncryptUpdate() failed" << std::endl;
            return false;
        }

        total_out += outlen;
        output.resize(total_out);

        EVP_CIPHER_CTX_cleanup(ctx.get());

        return true;
    }

    bool decrypt(const std::vector<uint8_t>& key,
                 const std::vector<uint8_t>& message,
                 const std::vector<uint8_t>& iv,
                 std::vector<uint8_t>& output)
    {
        output.resize(message.size() * 3);
        std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx {
                EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free
        };

        int32_t decLen { 0 }, blockLen { 0 };
        if (0 == EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), nullptr, key.data(), iv.data())) {
            std::cerr << "Error: EVP_EncryptInit() failed" << std::endl;
            return false;
        }
        if (0 == EVP_DecryptUpdate(ctx.get(), output.data(), &blockLen, message.data(), message.size())) {
            std::cerr << "Error: EVP_DecryptUpdate() failed" << std::endl;
            return false;
        }
        decLen += blockLen;

        if (0 == EVP_DecryptFinal_ex(ctx.get(), output.data() + decLen, &blockLen)) {
            std::cerr << "Error: EVP_DecryptUpdate() failed" << std::endl;
            return false;
        }

        decLen += blockLen;
        output.resize(decLen);

        EVP_CIPHER_CTX_cleanup(ctx.get());
        return true;
    }
}