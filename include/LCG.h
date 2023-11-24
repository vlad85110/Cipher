//
// Created by vlad on 21.11.23.
//

#ifndef INFOBEZ_LAB2_LCG_H
#define INFOBEZ_LAB2_LCG_H

#include "Cipher.h"
#include <vector>

using std::vector;

class LCG {
private:
    unsigned long long a;
    unsigned long long c;
    unsigned long long m;
    unsigned long long x_0;
public:
    LCG(unsigned long long a, unsigned long long c, unsigned long long m, unsigned long long x0);

    [[nodiscard]] String encrypt(const String &text) const;

    [[nodiscard]] String decrypt(const String &data) const;
};


#endif //INFOBEZ_LAB2_LCG_H
