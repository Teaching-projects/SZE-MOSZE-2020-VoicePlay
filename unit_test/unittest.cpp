#include "../unit.h"
#include "../jsonparser.h"

#include <string>
#include <map>
#include <gtest/gtest.h>

TEST(Multest, resAsExpected){
    unit expected("TestUnit", 64, 32);
    unit* result = unit::parseUnit("unit2test.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDmg(), result->getDmg());
    EXPECT_DOUBLE_EQ(expected.getHp(), result->getHp());
};
TEST(Multest, allElementsFilled){
    unit* result = unit::parseUnit("unit2test.json");

    EXPECT_NE("", result->getName());
    EXPECT_NE(NULL, result->getDmg());
    EXPECT_NE(NULL, result->getHp());
};
TEST(Multest, faultySyntax){
    unit expected("TestUnit", 64, 32);
    std::string fname = "faultyunit.json";
    EXPECT_DEATH( { 
        try {
            unit* result = unit::parseUnit(fname);
        } catch(const int& e) {
            EXPECT_EQ(e,-3);
        }
    }, "Invalid json syntax");

};
TEST(Multest, fileException){
    unit expected("TestUnit", 64, 32);
    std::string fname = "unit2test.jso";
    const std::string exp = fname+" file does not exist!" ;
    EXPECT_DEATH({
        try {
            unit* result = unit::parseUnit(fname);
        } catch(const std::string e) {
            EXPECT_STREQ(exp.c_str(), e.c_str());    //throw;
        }
    }, fname+" file does not exist!");
};


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
