#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(Autocomplete, Test1) {
  TrojanMap m;
  std::unordered_set<std::string> expect={"Chase", "Chase Plaza Heliport"};
  for (auto& i:m.Autocomplete("Chas")) {
    EXPECT_EQ(expect.count(i) > 0, true);
    }
}

TEST(GetPosition, Test1) {
  TrojanMap m;
  std::pair<double, double> results1(34.0257016, -118.2843512);
  EXPECT_EQ(m.GetPosition("Target"), results1);
  std::pair<double, double> results2(-1, -1);
  EXPECT_EQ(m.GetPosition("12345"), results2);
}
