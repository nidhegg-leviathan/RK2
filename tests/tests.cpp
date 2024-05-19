#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "proxy.h"
#include "database.h"

class ProxyMock : public Proxy{
    public:
    ProxyMock(std::string name) : Proxy(name){}
    MOCK_METHOD0(read, void());
    MOCK_METHOD1(write, std::string());
    MOCK_CONST_METHOD2(login, void(std::string, std::string));
};

Test(Proxy, Mock){
  DataBase database("myDB.db");
  ProxyMock prox("myDB.db");
  //First Test
  prox.login("Me", "MyPassword1234");
  EXPECT_EQ(prox.read(), "");
  //Second Test
  prox.login("admin", "admin");
  EXPECT_EQ(prox.read(), database.read());
  //Third Test
  EXPECT_EQ(prox.write("randomstring"), database.write("randomstring"));
}
