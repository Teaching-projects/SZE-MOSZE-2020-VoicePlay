#include "../unit.h"
#include "../JSON.h"
#include "../Hero.h"
#include <string>
#include <map>
#include <iterator>
#include <cmath>
#include <gtest/gtest.h>


TEST(Multest, resAsExpected){
    unit expected("TestUnit", 64, 32, 3);
    unit* result = unit::parseUnit("unit2test.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
    EXPECT_DOUBLE_EQ(expected.getHealthPoints(), result->getHealthPoints());
};
TEST(Multest, allElementsFilled){
    unit* result = unit::parseUnit("unit2test.json");

    EXPECT_NE("", result->getName());
    EXPECT_NE(NULL, result->getDamage());
    EXPECT_NE(NULL, result->getHealthPoints());
};
TEST(Multest, faultySyntax){
    unit expected("TestUnit", 64, 32,3);
    std::string fname = "faultyunit.json";
    EXPECT_DEATH( { 
        try {
            unit* result = unit::parseUnit(fname);
        } catch(const int& e) {
            EXPECT_EQ(e,-3);
        }
    }, "Invalid json syntax\n");

};
TEST(Multest, fileException){
    unit expected("TestUnit", 64, 32, 3);
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

TEST(Multest, stringParsTest){
    std::string inp="{\n \"k3\" : \"Name\" \n}";
    JSON exp = JSON::parseFromFile("unit2test3.json");
    JSON res = JSON::parseFromString(inp);
    EXPECT_EQ(exp.get<std::string>("k3"),res.get<std::string>("k3"));
    EXPECT_EQ(exp.count("k3"),res.count("k3"));
};

TEST(Multest, uselessKeysinJson){
    unit expected("TestUnit", 64, 32, 3);
    unit* result = unit::parseUnit("uselessKeys.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
};
TEST(Multest, gainXp100DMG){
    Hero re("Name",1000,100,1,0,1,100,10,10,0.9);
    unit* u = (new unit("na",200,1,1));
    double expected = re.getDamage();
    double xp = 0;

    if (u->getHealthPoints() <= re.getDamage()) xp += u->getHealthPoints();
    else xp += re.getDamage();
    while (xp >= re.experience_per_level) {
        xp = xp - re.experience_per_level;
        expected = expected + re.damage_bonus_per_level;
    }

    
    re.dealDamage(u);
    EXPECT_EQ(re.getDamage(), expected);
};
TEST(Multest, gainXp0DMG){
    Hero re("Name",1000,0,1,0,1,100,10,10,0.9);
    unit* u = (new unit("na",200,1,1));
    double expected = re.getDamage();
    double xp = 0;

    if (u->getHealthPoints() <= re.getDamage()) xp += u->getHealthPoints();
    else xp += re.getDamage();
    while (xp >= re.experience_per_level) {
        xp = xp - re.experience_per_level;
        expected = expected + re.damage_bonus_per_level;
    }

    
    re.dealDamage(u);
    EXPECT_EQ(re.getDamage(), expected);
};
TEST(Multest, gainXp_BigDMG){
    Hero re("Name",1000,1000,1,0,1,100,10,10,0.9);
    unit* u = (new unit("na",20000,1,1));
    double expected = re.getDamage();
    double xp = 0;

    if (u->getHealthPoints() <= re.getDamage()) xp += u->getHealthPoints();
    else xp += re.getDamage();
    while (xp >= re.experience_per_level) {
        xp = xp - re.experience_per_level;
        expected = expected + re.damage_bonus_per_level;
    }
    
    re.dealDamage(u);
    EXPECT_EQ(re.getDamage(), expected);
};
TEST(Multest, gainXp_DmgGTHP){ //damage greather than unit hp
    Hero re("Name",1000,1000,1,0,1,100,10,10,0.9);
    unit* u = (new unit("na",200,1,1));
    double expected = re.getDamage();
    double xp = 0;

    if (u->getHealthPoints() <= re.getDamage()) xp += u->getHealthPoints();
    else xp += re.getDamage();
    while (xp >= re.experience_per_level) {
        xp = xp - re.experience_per_level;
        expected = expected + re.damage_bonus_per_level;
    }
    
    re.dealDamage(u);
    EXPECT_EQ(re.getDamage(), expected);
};
TEST(Multest, gainXp_healedAfter){
    Hero re("Name",1000,1000,1,0,1,100,10,10,0.9);
    unit* u = (new unit("na",200,1,1));

    re.dealDamage(u);
    EXPECT_EQ(re.getHealthPoints(), re.getMaxHealthPoints());
};
TEST(Multest, AtkOrDfnd){ //damage greather than unit hp
    unit re("Name",1000,1000,2);
    unit* u = (new unit("na",200,1,1));
    double actime= re.getAttackCoolDown();
    double deftime= u->getAttackCoolDown();
    EXPECT_EQ(re.attackOrDefend(u,actime,deftime), false);
};
TEST(Multest, whitespacetest1){ //damage greather than unit hp
    unit expected("TestUnit", 64, 32, 3);
    unit* result = unit::parseUnit("whitespaceunit1.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
    EXPECT_DOUBLE_EQ(expected.getHealthPoints(), result->getHealthPoints());
};
TEST(Multest, whitespacetest2){ //damage greather than unit hp
    unit expected("TestUnit", 64, 32, 3);
    unit* result = unit::parseUnit("whitespaceunit2.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
    EXPECT_DOUBLE_EQ(expected.getHealthPoints(), result->getHealthPoints());
};
TEST(Multest, multiVarsInOneLine){
    unit expected("TestUnit", 64, 32, 3);
    unit* result = unit::parseUnit("unit2test2.json");

    EXPECT_EQ(expected.getName(), result->getName());
    EXPECT_DOUBLE_EQ(expected.getDamage(), result->getDamage());
    EXPECT_DOUBLE_EQ(expected.getHealthPoints(), result->getHealthPoints());
};
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
