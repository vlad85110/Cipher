//
// Created by vlad on 24.11.23.
//

#include "Speck.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        return 0;
    }

    String input(argv[1]);
    String output(argv[2]);

    Key key = {0x0123456789ABCDEF, 0xFEDCBA9876543210};
    Speck speck(key);

#ifdef ENCODING
    speck.encryptFile(input, output);
#endif

#ifdef DECODING
    speck.decryptFile(input, output);
#endif

    return 0;
}