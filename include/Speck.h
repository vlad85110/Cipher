//
// Created by vlad on 21.11.23.
//

#ifndef INFOBEZ_LAB2_SPECK_H
#define INFOBEZ_LAB2_SPECK_H

#include "Cipher.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using Block = std::array<uint64_t, 2>;
using Key = Block;

class Speck {
private:
    static constexpr int NUM_ROUNDS = 32;

    [[nodiscard]] static uint64_t rotate_left(uint64_t value, int shift);

    [[nodiscard]] static uint64_t rotate_right(uint64_t value, int shift);

    Key key;

public:
    explicit Speck(const Key &key);

    [[nodiscard]] Block encrypt_block(const Block &block) const;

    [[nodiscard]] Block decrypt_block(const Block &block) const;

    void encryptFile(const std::string &inputFile, const std::string &outputFile) const;

    void decryptFile(const std::string &inputFile, const std::string &outputFile) const;
};


#endif //INFOBEZ_LAB2_SPECK_H
