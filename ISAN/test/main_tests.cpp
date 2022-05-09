#include <gtest/gtest.h>
#include "../src/main.cpp"

// VALIDATE_KEY_TESTS
TEST(ValidatePathTest, Test1)
{
    EXPECT_EQ(0, ValidatePath("4.0.0.0v"));
}

TEST(ValidatePathTest, Test2)
{
    EXPECT_EQ(0, ValidatePath("4.0.0.0t"));
}

TEST(ValidatePathTest, Test3)
{
    EXPECT_EQ(-3, ValidatePath("4.0.0.0f"));
}

TEST(ValidatePathTest, Test4)
{
    EXPECT_EQ(-3, ValidatePath(".0.0.0f"));
}

TEST(ValidatePathTest, Test5)
{
    EXPECT_EQ(-3, ValidatePath("4.0.0."));
}

TEST(ValidatePathTest, Test6)
{
    EXPECT_EQ(-3, ValidatePath("4.0.0.0"));
}

TEST(ValidatePathTest, Test7)
{
    EXPECT_EQ(-3, ValidatePath("4..0.0t"));
}

TEST(ValidatePathTest, Test8)
{
    EXPECT_EQ(-3, ValidatePath("4.00.0.0t"));
}

//VALIDATE_ISAN_TESTS
TEST(ValidateIsanTest, Test1)
{
    EXPECT_EQ(0, ValidateIsan("[[[[]]]]"));
}

TEST(ValidateIsanTest, Test2)
{

    EXPECT_EQ(0, ValidateIsan("[1, 2, ”three”, [4, [5], [“six”]], [[[“seven”]]]]"));
}

TEST(ValidateIsanTest, Test3)
{

    EXPECT_EQ(-2, ValidateIsan("[[[[]]]"));
}

TEST(ValidateIsanTest, Test4)
{

    EXPECT_EQ(-2, ValidateIsan("0[[[]]0"));
}

TEST(ValidateIsanTest, Test5)
{
    EXPECT_EQ(-2, ValidateIsan("[1, 2, ”three”, [4, [5], [“six”]], [[[“seven”]"));
}

//PARSE_TESTS
TEST(ParseIsanTest, Test1)
{
    EXPECT_EQ(0, ParseIsan("[]", std::string()));
    PrintResult();
    elements.clear();
}

TEST(ParseIsanTest, Test2)
{
    EXPECT_EQ(0, ParseIsan("[[[[]]]]", std::string()));
    PrintResult();
    elements.clear();
}

TEST(ParseIsanTest, Test3)
{
    EXPECT_EQ(0, ParseIsan("[-1]", std::string()));
    PrintResult();
    elements.clear();
}

TEST(ParseIsanTest, Test4)
{
    EXPECT_EQ(0, ParseIsan("[“”]", std::string()));
    PrintResult();
    elements.clear();
}

TEST(ParseIsanTest, Test5)
{
    EXPECT_EQ(0, ParseIsan("[0, 0, 0, 3456, 0]", std::string()));
    PrintResult();
    elements.clear();
}

TEST(ParseIsanTest, Test6)
{
    EXPECT_EQ(0, ParseIsan("[1, 2, ”three”, [4, [5], [“six”]], [[[“seven”]]]]", std::string()));
    PrintResult();
    elements.clear();
}

//MAIN_TEST
TEST(MainTest, Test1)
{
    int code = CODE::SUCCESS;
    string isan, path;
    
    cout << "Enter ISAN: " << endl;
    getline(cin, isan, '\n');

    if(ValidateIsan(isan) == CODE::ISAN_SYNTAX_ERROR)
    {
        std::terminate();
        code = CODE::ISAN_SYNTAX_ERROR;
    }
    
    ParseIsan(isan, string());
    PrintResult();

    cout << "Enter KEY to get element: " << endl;
    getline(cin, path, '\n');

    if(ValidatePath(path) == CODE::ISAN_PATH_ERROR)
    {
        std::terminate();
        code = CODE::ISAN_PATH_ERROR;
    }

    GetElement(path);
    sleep(1); // pause to view the result in the console
    
    elements.clear();
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
