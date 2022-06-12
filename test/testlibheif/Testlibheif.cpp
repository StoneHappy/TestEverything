#include <gtest/gtest.h>

#include <libheif/ReadHeif.h>
TEST(libheifTest, ReadHeicTest)
{
	EXPECT_TRUE(ReadHeif("./resources/libheif/example.heic"));
}