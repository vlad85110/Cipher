#include <iostream>
#include <limits>
#include <valarray>
#include "LCG.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {

    String input;

    cout << "Enter your string: ";
    std::cin >> input;

    auto size = std::numeric_limits<size_t>::digits;
    auto m = static_cast<int>(pow(2, size));
    auto a = 1664525;
    auto c = 1013904223;
    auto x0 = 42;
    LCG lcg(a, c, m, x0);

#ifdef ENCODING
    std::string ciphertext = lcg.encrypt(input);
    std::cout << "Result: " <<  ciphertext << std::endl;
#endif

#ifdef DECODING
    std::string decryptedText = lcg.decrypt(input);
    std::cout << "Result: " << decryptedText << std::endl;
#endif

    return 0;
}
