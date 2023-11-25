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

To use LCG, enter a string from the keyboard for encryption or decryption.

```bash
./lcg_encode
./lcg_decode
```

### Speck Cipher

To use the Speck Cipher, pass the input and output file names as parameters.

```bash
./speck_encode input.txt output.txt
./speck_decode input.txt output.txt
```

### Jenkins Hash

To use Jenkins Hash, enter a string from the keyboard for hashing.

```bash
./jenkins_hash
```

## Building the Project

The project uses CMake for building.

```bash
mkdir build
cd build
cmake <path_to_project_root>
make
```

## Testing

The project includes tests using Google Test. You can run them using the following commands:

```bash
make
./cipher_tests
```

Or you can run 

```bash
make
ctest
```
in your build directory

## Dependencies

The project uses the Google Test library for testing. All necessary dependencies will be downloaded automatically during the build process.
