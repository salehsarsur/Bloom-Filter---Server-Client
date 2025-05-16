#include <gtest/gtest.h>
#include "StdHashFunction.h"
#include "DoubleStdHashFunction.h"

TEST(StdHashFunctionTest, ConsistentHashing) {
    StdHashFunction hasher;
    std::string url = "www.test.com";
    int hash1 = hasher.hash_f(url);
    int hash2 = hasher.hash_f(url);

    EXPECT_EQ(hash1, hash2);  // Should be deterministic
}

TEST(StdHashFunctionTest, DifferentStringsProduceDifferentHashes) {
    StdHashFunction hasher;
    int hash1 = hasher.hash_f("www.one.com");
    int hash2 = hasher.hash_f("www.two.com");

    EXPECT_NE(hash1, hash2);  // Usually different (not guaranteed, but likely)
}

TEST(DoubleStdHashFunctionTest, ConsistentDoubleHash) {
    DoubleStdHashFunction doubleHasher;
    std::string url = "www.double.com";
    int hash1 = doubleHasher.hash_f(url);
    int hash2 = doubleHasher.hash_f(url);

    EXPECT_EQ(hash1, hash2);  // Should also be deterministic
}

TEST(DoubleStdHashFunctionTest, DiffersFromStdHash) {
    StdHashFunction hasher1;
    DoubleStdHashFunction hasher2;
    std::string url = "www.different.com";

    int stdHash = hasher1.hash_f(url);
    int doubleHash = hasher2.hash_f(url);

    EXPECT_NE(stdHash, doubleHash);  // Different strategies
}
