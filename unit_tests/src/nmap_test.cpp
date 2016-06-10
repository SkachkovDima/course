#include <gtest/gtest.h>
#include <nmap.cpp>

class nmap_fixture : public ::testing::Test {

protected:
  virtual void SetUp() {
    nmap_test = new nmap;
  }

  virtual void TearDown() {
    delete nmap_test;
  }

  nmap *nmap_test;
};


TEST_F(nmap_fixture, to_unsigned_POSITIVE_VALUE) {
  EXPECT_EQ(2, nmap_test->to_unsigned("2"));
}

TEST_F(nmap_fixture, to_unsigned_NEGATIVE_VALUE){
  EXPECT_ANY_THROW(nmap_test->to_unsigned("-1"));
}

TEST_F(nmap_fixture, to_unsigned_NOT_NUMBER) {
  EXPECT_ANY_THROW(nmap_test->to_unsigned("check"));
}

TEST_F(nmap_fixture, read_port_RIGHT_PATH) {
  EXPECT_NO_THROW(nmap_test->read_ports(PORT));
}

TEST_F(nmap_fixture, read_port_WRONG_PATH){
  EXPECT_ANY_THROW(nmap_test->read_ports("wrong path"));
}

TEST_F(nmap_fixture, read_report_RIGHT_PATH) {
  EXPECT_NO_THROW(nmap_test->read_report(REPORT));
}

TEST_F(nmap_fixture, read_report_WRONG_PATH) {
  EXPECT_ANY_THROW(nmap_test->read_report("wrong path"));
}

TEST_F(nmap_fixture, convert_ports_EMPTY_STRING) {
  EXPECT_ANY_THROW(nmap_test->convert_ports(""));
}

TEST_F(nmap_fixture, convert_ports_STRING_WITHOUT_SPACES){
  EXPECT_ANY_THROW(nmap_test->convert_ports("withoutSpaces"));
}

TEST_F(nmap_fixture, convert_ports_WRONG_STRING_WITH_SPACES) {
  EXPECT_ANY_THROW(nmap_test->convert_ports("it is 123 wrong string"));
}

TEST_F(nmap_fixture, convert_ports_RIGHT_STRING) {
  EXPECT_NO_FATAL_FAILURE(nmap_test->convert_ports("21 23 25"));
}