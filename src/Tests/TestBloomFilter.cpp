#include "BloomFilter.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>

class HashFunction : public IHashFunction {
public:
    size_t hash_f(const std::string input) override {
        return input.length();  // deterministic
    }
};

class BloomFilterFullTest : public ::testing::Test {
protected:
    std::string blacklistPath = "data/blacklist.txt";
    std::string bloomSavePath = "data/bloom.dat";

    void SetUp() override {
        // Clean slate for each test
        std::ofstream(blacklistPath, std::ios::trunc).close();
        std::ofstream(bloomSavePath, std::ios::trunc).close();

        std::vector<IHashFunction*> hashFuncs = { new HashFunction() };
        BloomFilter::initBloomFilter(100, hashFuncs);
    }

    void TearDown() override {
        // Cleanup
        std::remove(blacklistPath.c_str());
        std::remove(bloomSavePath.c_str());
    }
};

TEST_F(BloomFilterFullTest, AddAndCheckURL) {
    BloomFilter& bf = BloomFilter::getInstance();
    std::string url = "https://example.com";
    bf.add(url);

    EXPECT_TRUE(bf.possiblyContains(url));
}

TEST_F(BloomFilterFullTest, CheckUnaddedURLReturnsFalse) {
    BloomFilter& bf = BloomFilter::getInstance();
    EXPECT_FALSE(bf.possiblyContains("https://notadded.com"));
}

TEST_F(BloomFilterFullTest, SaveAndReloadBloomBits) {
    BloomFilter& bf = BloomFilter::getInstance();
    bf.add("https://google.com");

    bf.saveToFile(bloomSavePath);
    std::ifstream in(bloomSavePath);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);  // size
    EXPECT_EQ(std::stoi(line), 100);
    std::getline(in, line);  // bits
    EXPECT_EQ(line.length(), 100);
    in.close();
}

TEST_F(BloomFilterFullTest, LoadBlacklistFromFile) {
    std::ofstream out(blacklistPath);
    out << "https://a.com\n";
    out << "https://b.com\n";
    out.close();

    BloomFilter& bf = BloomFilter::getInstance();
    bf.loadBlacklistFromFile(blacklistPath);

    EXPECT_TRUE(bf.possiblyContains("https://a.com"));
    EXPECT_TRUE(bf.possiblyContains("https://b.com"));
}

TEST_F(BloomFilterFullTest, DeleteFromBlacklist) {
    std::ofstream out(blacklistPath);
    out << "https://remove.com\n";
    out << "https://keep.com\n";
    out.close();

    BloomFilter& bf = BloomFilter::getInstance();
    bool deleted = bf.deleteFromBlacklist("https://remove.com", blacklistPath);
    EXPECT_TRUE(deleted);

    std::ifstream in(blacklistPath);
    std::string line;
    bool found = false;
    while (getline(in, line)) {
        if (line == "https://remove.com") found = true;
    }
    in.close();

    EXPECT_FALSE(found);
}

TEST_F(BloomFilterFullTest, HandlesFalsePositive) {
    BloomFilter& bf = BloomFilter::getInstance();
    bf.add("https://added.com");

    EXPECT_TRUE(bf.isFalsePositive("https://added.com"));  // in realBlacklist
    EXPECT_FALSE(bf.isFalsePositive("https://other.com")); // not in realBlacklist
}
