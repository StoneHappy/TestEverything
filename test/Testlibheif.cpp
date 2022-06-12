#include <gtest/gtest.h>

#include <libheif/ReadHeif.h>
TEST(ExampleTest, SimpleFirstTest)
{
	EXPECT_TRUE(ReadHeif());
}