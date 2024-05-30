#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "proxy.h"
#include "databaseparent.h"

class ProxyMock : public Proxy{
    public:
    ProxyMock(std::string name) : Proxy(std::string name){}
    MOCK_METHOD0(read, std::string());
    MOCK_METHOD1(write, void(std::string));
    MOCK_CONST_METHOD2(login, void(std::string, std::string));
};

TEST(Proxy, firstTest){
  std::string name = "myDB.db";
  ProxyMock prox(name);
  //First Test
  prox.login("Me", "MyPassword1234");
  EXPECT_EQ(prox.read(), "");
}
TEST(Proxy, secondTest){
  std::string name = "myDB.db";
  ProxyMock prox(name);
  //Second Test
  prox.login("admin", "admin");
  EXPECT_EQ(prox.read(), "");
}
TEST(Proxy, thirdTest){
  std::string name = "myDB.db";
  ProxyMock prox(name);
  prox.login("admin", "admin");
  //Third Test
  EXPECT_CALL(prox, write("randomstring"));

  prox.write("randomstring");

  EXPECT_CALL(prox, read());
  
  EXPECT_EQ(prox.read(), "randomstring");
}
