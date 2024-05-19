#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "proxy.cpp"

class ProxyMock : public Proxy{
    public:
    ProxyMock(string databaseName) : Proxy(database){}
    MOCK_CONST_METHOD2(login, void(std::string userName, std::string password));
};


TEST(Proxy, Mock){
    DataBase* database = new DataBase();
    ProxyMock prox(database);

    //First Test

    EXPECT_CALL(prox, login()).Times(1);
    EXPECT_CALL(prox, read()).Times(1);
    prox.login("asdasd", "asdasd");
    EXPECT_THAT(prox.read(), ::testing::StartsWith("you"));

    //Second Test

    EXPECT_CALL(prox, login()).Times(1);
    EXPECT_CALL(prox, read()).Times(1);
    prox.login("admin", "admin");
    EXPECT_THAT(prox.read(), ::testing::StartsWith("Proxy"));

    //Third Test

    EXPECT_CALL(prox, login()).Times(1);
    EXPECT_CALL(prox, write()).Times(1);
    prox.login("asdasd", "asdasd");
    EXPECT_THAT(prox.write(), ::testing::StartsWith("you"));

    delete database;
}