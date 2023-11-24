#include <gtest/gtest.h>
#include "LCG.h"
#include <cmath>

auto size = std::numeric_limits<size_t>::digits;
auto m = static_cast<int>(pow(2, size));

TEST(LCG_test1, BasicAssertions) {
    auto a = 1664525;
    auto c = 1013904223;

    auto x0 = 42;
    LCG lcg(a, c, m, x0);
    auto text = "Hello_world";

    auto encrypt_data = lcg.encrypt(text);
    auto decrypt_data = lcg.decrypt(encrypt_data);

    ASSERT_EQ(text, decrypt_data);
}

TEST(LCG_DoubleEncrypt, BasicAssertions) {
    auto a = 1664525;
    auto c = 1013904223;

    auto x0 = 42;
    LCG lcg(a, c, m, x0);
    auto text = "Some text which will be encoded twice";

    auto encrypt_data = lcg.encrypt(lcg.encrypt(text));
    auto decrypt_data = lcg.decrypt(lcg.decrypt(encrypt_data));

    ASSERT_EQ(text, decrypt_data);
}

