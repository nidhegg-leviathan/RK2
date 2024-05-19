#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "proxy.h"
#include "database.h"

class MockDatabase : public DataBase {
public:
  MOCK_METHOD0(read, std::string());
  MOCK_METHOD1(write, void(std::string));
};

//First test

TEST(ProxyTest, Read_Authenticated) {
  MockDatabase* mockDb = new MockDatabase();

  EXPECT_CALL(*mockDb, read()).Times(1).WillOnce(Return("Data from DB"));

  Proxy proxy("test_db", mockDb); 
  proxy.login("admin", "admin"); 

  std::string result = proxy.read();

  ASSERT_EQ(result, "Data from DB");

  delete mockDb;
}

//Second test

TEST(ProxyTest, Read_NotAuthenticated) {
  MockDatabase* mockDb = new MockDatabase();

  Proxy proxy("test_db", mockDb); 
  
  std::string result = proxy.read();

  ASSERT_EQ(result, "");
}

//Third test

TEST(ProxyTest, Write_Authenticated) {
  MockDatabase* mockDb = new MockDatabase();

  EXPECT_CALL(*mockDb, write("Test data")).Times(1);

  Proxy proxy("test_db", mockDb); 
  proxy.login("admin", "admin");

  proxy.write("Test data");

  delete mockDb;
}