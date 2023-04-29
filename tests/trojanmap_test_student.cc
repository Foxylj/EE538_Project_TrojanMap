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

TEST(GetAllCategories, Test1) {
  TrojanMap m;
  std::set<std::string> result = {
    "car_repair", "bakery", "restaurant", "clothes", "fast_food", "bank", "car", "fuel", 
    "parking_entrance", "cafe", "hotel", "hairdresser", "beverages", "fabric", "skate", 
    "convenience", "confectionery", "school", "marketplace", "tobacco", "bar", "place_of_worship", 
    "optician", "social_facility", "dentist", "copyshop", "food_court", "yes", "parking", "driving_school", 
    "pharmacy", "charging_station", "department_store", "supermarket", "artwork", "parcel_locker", "attraction", 
    "mobile_phone", "car_wash", "childcare", "museum", "bicycle_rental", "music", "bicycle", "bus_station", 
    "beauty", "post_office", "clinic", "theatre", "fountain", "police", "hospital", "gallery", "library", 
    "yoga", "post_box", "shoe_repair", "shoes"
  };
  auto output=m.GetAllCategories();
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(GetAllLocationsFromCategory, Test1) {
  TrojanMap m;
  std::set<std::string> result = {"9591449441", "9591449465", "5237417651"};
  auto output=m.GetAllLocationsFromCategory("bank");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(GetLocationRegex, Test1) {
  TrojanMap m;
  std::set<std::string> result = {"2578244375"};
  auto output=m.GetLocationRegex(std::regex("Ra.?ph.+"));
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(GetLocationRegex, Test2) {
  TrojanMap m;
  std::set<std::string> result = {"2578244375"};
  auto output=m.GetLocationRegex(std::regex("R[A-Za-z]l[A-Za-z]hs"));
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(CalculateShortestPath_Dijkstra, Test1) {
  TrojanMap m;
  std::set<std::string> result = {"9591449441","9559739232","3398574883","6045067409","9559739236","3402917919",
  "3402917921","3872400990","6818390146","6813379456","6807200381","9591449452","6813379408","2783295153","544671962",
  "6813379439","6813379467","6813360938","5237377002","5237400231","6047234445","6813360983","6813360984","6045054380",
  "6813379385","6813379474","6813379475","6818390144","6818390145","6813405201","6813405202","6813405203","6813405204",
  "6813405205","6813405206","123318572","5565967545","7811699597","6817230310","3642819026","6817230316","2613117861",
  "6818390170","6818390171","6818390172","6807374562","2613117885","6818390165","2613117882","6818390178","2613117902",
  "6813416153","6813416154","6813416145","7232024780","6818427916","6818427917","6818427898","6818427892","6818427918",
  "6818427919","6818427920","4380040148","4380040152","4380040153","4380040154","2578244375"};
  auto output=m.CalculateShortestPath_Dijkstra("Chase","Ralphs");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(CalculateShortestPath_Bellman_Ford, Test1) {
  TrojanMap m;
  std::set<std::string> result = {"9591449441","9559739232","3398574883","6045067409","9559739236","3402917919",
  "3402917921","3872400990","6818390146","6813379456","6807200381","9591449452","6813379408","2783295153","544671962",
  "6813379439","6813379467","6813360938","5237377002","5237400231","6047234445","6813360983","6813360984","6045054380",
  "6813379385","6813379474","6813379475","6818390144","6818390145","6813405201","6813405202","6813405203","6813405204",
  "6813405205","6813405206","123318572","5565967545","7811699597","6817230310","3642819026","6817230316","2613117861",
  "6818390170","6818390171","6818390172","6807374562","2613117885","6818390165","2613117882","6818390178","2613117902",
  "6813416153","6813416154","6813416145","7232024780","6818427916","6818427917","6818427898","6818427892","6818427918",
  "6818427919","6818427920","4380040148","4380040152","4380040153","4380040154","2578244375"};
  auto output=m.CalculateShortestPath_Bellman_Ford("Chase","Ralphs");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(DeliveringTrojan, Test1) {
  TrojanMap m;
  std::set<std::string> result = {"A","B","C","D","E","F"};
  std::vector<std::string> location={"C","F","A","B","D","E"};
  std::vector<std::vector<std::string>> dependencie={{"A","B"},{"B","C"},{"C","D"},{"A","C"},{"D","E"},{"E","F"},{"B","E"}};
  auto output=m.DeliveringTrojan(location,dependencie);
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(TrojanMapTest, Queries) {
  TrojanMap m;
  std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "Ralphs"}},
                                                                  {0.01, {"Ralphs", "Target"}},
                                                                  {0.02, {"KFC", "Target"}},
                                                                  {999, {"dummy", "dummy"}}};
  auto actual = m.Queries(input);
  std::vector<bool> expected {true, false, false, false};
  EXPECT_EQ(expected, actual);
}