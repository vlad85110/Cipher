#include <sstream>
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

size_t file_size(std::istream& file) {
    auto pos = file.tellg();

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();

    file.seekg(pos);
    return fileSize;
}

void Speck::encryptFile(const std::string &inputFile, const std::string &outputFile) const {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    size_t fileSize = file_size(input);

    input.seekg(0, std::ios::beg);
    std::stringstream binaryStream(std::ios::in | std::ios::out | std::ios::binary);
    binaryStream << input.rdbuf();

    size_t blockSize = sizeof(Block);
    if (fileSize % blockSize != 0) {
        auto bytesToWrite = 16 - (fileSize % blockSize);

        std::cout << bytesToWrite;

        binaryStream.seekg(0, std::ios::end);
        for (int i = 0; i < bytesToWrite; ++i) {
            binaryStream.put(static_cast<char>(bytesToWrite));
        }
        binaryStream.seekg(0, std::ios::beg);
    }

    while (!binaryStream.eof()) {
        Block plaintext = {0, 0};
        binaryStream.read(reinterpret_cast<char *>(plaintext.data()), sizeof(Block));

        auto bytesRead = binaryStream.gcount();

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

    std::stringstream binaryStream(std::ios::in | std::ios::out | std::ios::binary);

    while (!input.eof()) {
        Block ciphertext = {0, 0};
        input.read(reinterpret_cast<char *>(ciphertext.data()), sizeof(Block));

        auto bytesRead = input.gcount();

        if (bytesRead > 0) {
            Block plaintext = decrypt_block(ciphertext);
            binaryStream.write(reinterpret_cast<char *>(plaintext.data()), bytesRead);
        }
    }
    
    binaryStream.seekg(-1, std::ios::end);
    char lastByte;
    binaryStream.get(lastByte);

    binaryStream.seekg(-lastByte, std::ios::end);
    auto del = true;
    for (int i = 0; i < lastByte; ++i) {
        auto s = binaryStream.get();

        if (s != lastByte) {
            del = false;
        }
    }

    auto str = binaryStream.str();
    if (del) {
        for (int i = 0; i < lastByte; ++i) {
            str.pop_back();
        }
    }

    output << str;
}
