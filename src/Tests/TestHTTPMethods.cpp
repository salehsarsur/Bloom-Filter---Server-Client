#include "gtest/gtest.h"
#include "../BloomFilter/BloomFilter.h"
#include "../HTTP_Methods/PostMethod.h"
#include "../HTTP_Methods/GetMethod.h"
#include "../HTTP_Methods/DeleteMethod.h"
#include "../Hash/StdHashFunction.h"
#include "../Hash/DoubleStdHashFunction.h"

#include <fstream>
#include <vector>
#include <string>

using namespace std;

class PostMethodTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Init hash functions and bloom filter
        vector<IHashFunction*> hashFunctions = {
            new StdHashFunction(),
            new DoubleStdHashFunction()
        };
        BloomFilter::initBloomFilter(100, hashFunctions);

        // Clear the blacklist before test
        ofstream clearFile("data/blacklist.txt", ios::trunc);
        clearFile.close();
    }
};

TEST_F(PostMethodTest, Execute_AddUrl) {
    PostMethod post;
    string response = post.execute("http://example.com");
    EXPECT_EQ(response, "201 Created\n");
    EXPECT_TRUE(BloomFilter::getInstance().possiblyContains("http://example.com"));
}

TEST(GetMethodTest, Execute_CheckExists) {
    GetMethod get;
    string url = "http://example.com";
    string response = get.execute(url);
    EXPECT_TRUE(response.find("200 Ok") != string::npos);
}

TEST(DeleteMethodTest, Execute_DeleteExists) {
    DeleteMethod del;
    string url = "http://example.com";
    string response = del.execute(url);
    EXPECT_EQ(response, "204 No Content\n");
}

TEST(DeleteMethodTest, Execute_DeleteNonExistent) {
    DeleteMethod del;
    string response = del.execute("http://nonexistent.com");
    EXPECT_EQ(response, "404 Not Found\n");
}
