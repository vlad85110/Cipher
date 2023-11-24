//
// Created by vlad on 21.11.23.
//

#include <ios>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "LCG.h"

using ull = unsigned long long;

LCG::LCG(ull a, ull c, ull m, ull x0) : a(a), c(c), m(m), x_0(x0) {}

std::string convertToHexString(uint64_t value) {
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << value;
    return oss.str();
}

std::string LCG::encrypt(const std::string& plaintext) const {
    std::string ciphertext;

    auto x_n = x_0;
    for (char ch : plaintext) {
        x_n = (a * x_n + c) % m;

        uint64_t encryptedValue = static_cast<uint64_t>(ch) ^ x_n;
        ciphertext += convertToHexString(encryptedValue);
    }

    return ciphertext;
}

std::string LCG::decrypt(const std::string& ciphertext) const {
    std::string decryptedText;
    auto x_n = x_0;

    for (size_t i = 0; i < ciphertext.length(); i += 16) {
        std::string hexValue = ciphertext.substr(i, 16);

        uint64_t encryptedValue;
        std::istringstream(hexValue) >> std::hex >> encryptedValue;

        x_n = (a * x_n + c) % m;
        char decryptedChar = static_cast<char>(encryptedValue ^ x_n);
        decryptedText += decryptedChar;
    }

    return decryptedText;
}

