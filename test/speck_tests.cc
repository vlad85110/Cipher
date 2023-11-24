#include <gtest/gtest.h>
#include "Speck.h"

TEST(Block_test, BasicAssertions) {
    Speck speck({1918, 1110});

    Block block{11, 11};

    auto en_block = speck.encrypt_block(block);
    auto de_block = speck.decrypt_block(en_block);

    ASSERT_EQ(de_block[0], block[0]);
    ASSERT_EQ(de_block[1], block[1]);
}

TEST(DoubleEncodeBlockTest, BasicAssertions) {
    Speck speck({1918, 1110});

    Block block{11, 11};

    auto en_block = speck.encrypt_block(speck.encrypt_block(block));
    auto de_block = speck.decrypt_block(speck.decrypt_block(en_block));

    ASSERT_EQ(de_block[0], block[0]);
    ASSERT_EQ(de_block[1], block[1]);
}

