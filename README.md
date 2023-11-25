# Project "Cipher"

This project represents the implementation of various encryption and hashing algorithms in the C++ programming language.

## Contents

1. [LCG (Linear Congruential Generator)](src/LCG.cpp)
    - Implementation of a linear congruential generator.
    - Build file: [lcg_main.cpp](src/lcg_main.cpp)

2. [Speck Cipher](src/Speck.cpp)
    - Implementation of the Speck encryption algorithm.
    - Build file: [speck_main.cpp](src/speck_main.cpp)

3. [Jenkins Hash](src/JenkinsHash.cpp)
    - Implementation of the Jenkins hash function.
    - Build file: [hash_main.cpp](src/hash_main.cpp)

## How to Use

### LCG (Linear Congruential Generator)

To use LCG, create an LCG object with the necessary parameters (a, c, m, x0) and call the `encrypt` or `decrypt` methods. An example of usage is in the file [lcg_main.cpp](src/lcg_main.cpp). Enter a string from the keyboard for encryption or decryption.

```bash
./lcg_encode "your_input_string"
./lcg_decode "your_input_string"
```

### Speck Cipher

To use the Speck Cipher, create a Speck object by passing a key to the constructor. Then, call the `encryptFile` or `decryptFile` methods for encrypting or decrypting files, respectively. An example of usage is in the file [speck_main.cpp](src/speck_main.cpp). Pass the input and output file names as parameters.

```bash
./speck_encode input.txt output.txt
./speck_decode input.txt output.txt
```

### Jenkins Hash

To use Jenkins Hash, call the `calculate` method and pass the string you want to hash. An example of usage is in the file [hash_main.cpp](src/hash_main.cpp). Enter a string from the keyboard for hashing.

```bash
./jenkins_hash
```

## Building the Project

The project uses CMake for building. You can compile the necessary executable files with encoding or decoding support by setting the corresponding `ENCODING` and `DECODING` flags in the [CMakeLists.txt](CMakeLists.txt) file.

```bash
cmake .
make
```

## Testing

The project includes tests using Google Test. You can run them using the following commands:

```bash
cmake .
make
./cipher_tests
```

## Dependencies

The project uses the Google Test library for testing. All necessary dependencies will be downloaded automatically during the build process.
