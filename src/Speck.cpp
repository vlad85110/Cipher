//
// Created by vlad on 21.11.23.
//

#include "Speck.h"

Speck::Speck(const Key &key) : key(key) {}

uint64_t Speck::rotate_left(uint64_t value, int shift) {
    return (value << shift) | (value >> (64 - shift));
}

uint64_t Speck::rotate_right(uint64_t value, int shift) {
    return (value >> shift) | (value << (64 - shift));
}

Block Speck::encrypt_block(const Block &block) const {
    uint64_t left = block[0];
    uint64_t right = block[1];

    for (int i = 0; i < NUM_ROUNDS; ++i) {
        left = (rotate_right(left, 8) + right) ^ key[i % 2];
        right = rotate_left(right, 3) ^ left;
    }

    return {left, right};
}

Block Speck::decrypt_block(const Block &block) const {
    uint64_t left = block[0];
    uint64_t right = block[1];

    for (int i = NUM_ROUNDS - 1; i >= 0; --i) {
        right = rotate_right(right ^ left, 3);
        left = rotate_left((left ^ key[i % 2]) - right, 8);
    }

    return {left, right};
}

void Speck::encryptFile(const std::string &inputFile, const std::string &outputFile) const {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    while (!input.eof()) {
        Block plaintext = {0, 0};
        input.read(reinterpret_cast<char *>(plaintext.data()), sizeof(Block));

        auto bytesRead = input.gcount();

        if (bytesRead > 0) {
            Block ciphertext = encrypt_block(plaintext);
            output.write(reinterpret_cast<char *>(ciphertext.data()), bytesRead);
        }
    }

    input.close();
    output.close();
}

void Speck::decryptFile(const std::string &inputFile, const std::string &outputFile) const {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    while (!input.eof()) {
        Block ciphertext = {0, 0};
        input.read(reinterpret_cast<char *>(ciphertext.data()), sizeof(Block));

        auto bytesRead = input.gcount();

        if (bytesRead > 0) {
            Block plaintext = decrypt_block(ciphertext);
            output.write(reinterpret_cast<char *>(plaintext.data()), bytesRead);
        }
    }
}


