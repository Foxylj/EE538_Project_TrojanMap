#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(Autocomplete, Autocomplete_Test1) {
  TrojanMap m;
  std::unordered_set<std::string> expect={"Chase", "Chase Plaza Heliport"};
  for (auto& i:m.Autocomplete("Chas")) {
    EXPECT_EQ(expect.count(i) > 0, true);
    }
}

TEST(Autocomplete, Autocomplete_Test2) {
  TrojanMap m;
  std::unordered_set<std::string> expect={"KFC"};
  for (auto& i:m.Autocomplete("Kf")) {
    EXPECT_EQ(expect.count(i) > 0, true);
    }
}

TEST(Autocomplete, Autocomplete_Test3) {
  TrojanMap m;
  std::unordered_set<std::string> expect={};
  for (auto& i:m.Autocomplete("")) {
    EXPECT_EQ(expect.count(i) > 0, true);
    }
}

TEST(GetPosition, Test1) {
  TrojanMap m;
  std::pair<double, double> results1(34.0385316, -118.2814667);
  EXPECT_EQ(m.GetPosition("Washington & Union 1"), results1);
  std::pair<double, double> results2(-1, -1);
  EXPECT_EQ(m.GetPosition("washington"), results2);
}
TEST(GetPosition, Test2) {
  TrojanMap m;
  std::pair<double, double> results1(34.0257016, -118.2843512);
  EXPECT_EQ(m.GetPosition("Target"), results1);
  std::pair<double, double> results2(-1, -1);
  EXPECT_EQ(m.GetPosition("12345"), results2);
}
TEST(GetPosition, Test3) {
  TrojanMap m;
  std::pair<double, double> results1(34.023, -118.266);
  std::pair<double, double> input = m.GetPosition("");
  EXPECT_EQ(input, results1);
}
TEST(GetLat, TEST1){
  TrojanMap m;
  std::string input = "9561513962";
  EXPECT_EQ(m.GetLat(input), 34.0281557);
}
TEST(GetLat, TEST2){
  TrojanMap m;
  std::string input = "";
  EXPECT_EQ(m.GetLat(input), -1);
}
TEST(GetLat, TEST3){
  TrojanMap m;
  std::string input = "9601938171";
  EXPECT_EQ(m.GetLat(input), 34.0388531);
}

TEST(GetLon, TEST1){
  TrojanMap m;
  std::string input = "17680180";
  EXPECT_EQ(m.GetLon(input), -118.2682809);
}
TEST(GetLon, TEST2){
  TrojanMap m;
  std::string input = "";
  EXPECT_EQ(m.GetLon(input), -1);
}
TEST(GetLon, TEST3){
  TrojanMap m;
  std::string input = "9596558260";
  EXPECT_EQ(m.GetLon(input), -118.2680639);
}
TEST(GetName, TEST1){
  TrojanMap m;
  std::string input = "9597108858";
  EXPECT_EQ(m.GetName(input), "J&J Auto Center");
}
TEST(GetName, TEST2){
  TrojanMap m;
  std::string input = "0";
  EXPECT_EQ(m.GetName(input), "NULL");
}
TEST(GetName, TEST3){
  TrojanMap m;
  std::string input = "";
  EXPECT_EQ(m.GetName(input), "NULL");
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

TEST(TrojanMapTest, GetLocationRegex4) {
  TrojanMap m;
  std::set<std::string> expected_set = {"1376467705"};
  auto actual = m.GetLocationRegex(std::regex("Pico"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}

TEST(TrojanMapTest, GetLocationRegex5) {
  TrojanMap m;
  std::set<std::string> expected_set ;
  auto actual = m.GetLocationRegex(std::regex("USC Village.*Market"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}

TEST(TrojanMapTest, GetLocationRegex7) {
  TrojanMap m;
  std::set<std::string> expected_set;
  auto actual = m.GetLocationRegex(std::regex(".*building.*"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}
//-----
// Test case 1: ReadDependenciesFromCSVFileTest1
TEST(TrojanMapTest, ReadDependenciesFromCSVFileTest1) {
  TrojanMap m;

  // Prepare data.csv with the following content:
  // Source,Destination
  // 8523122298,8523122299
  // 8523122299,8523122301
  // 8523122301,8523122303

  std::string dependencies_filename = "data.csv";
  auto result = m.ReadDependenciesFromCSVFile(dependencies_filename);
  std::vector<std::vector<std::string>> gt = {{"8523122298", "8523122299"}, {"8523122299", "8523122301"}, {"8523122301", "8523122303"}};
  EXPECT_EQ(result, gt);
}

// Test case 2: ReadDependenciesFromCSVFileTest2
TEST(TrojanMapTest, ReadDependenciesFromCSVFileTest2) {
  TrojanMap m;

  // Prepare data.csv with the following content:
  // Source,Destination
  // 8530063146,8530063147
  // 8530063148,8530063149
  // 8530063149,8530063150

  std::string dependencies_filename = "data.csv";
  auto result = m.ReadDependenciesFromCSVFile(dependencies_filename);
  std::vector<std::vector<std::string>> gt = {{"8530063146", "8530063147"}, {"8530063148", "8530063149"}, {"8530063149", "8530063150"}};
  EXPECT_EQ(result, gt);
}

// Test case 3: ReadDependenciesFromCSVFileTest3
TEST(TrojanMapTest, ReadDependenciesFromCSVFileTest3) {
  TrojanMap m;

  // Prepare data.csv with the following content:
  // Source,Destination
  // 8530535232,8530535233
  // 8530535234,8530535235
  // 8530535236,8530535237

  std::string dependencies_filename = "data.csv";
  auto result = m.ReadDependenciesFromCSVFile(dependencies_filename);
  std::vector<std::vector<std::string>> gt = {{"8530535232", "8530535233"}, {"8530535234", "8530535235"}, {"8530535236", "8530535237"}};
  EXPECT_EQ(result, gt);
}


//-----
// Test case 1: Valid topological sorting
TEST(TrojanMapTest, DeliveringTrojanTest1) {
  TrojanMap m;

  std::vector<std::string> locations = {"A", "B", "C", "D", "E"};
  std::vector<std::vector<std::string>> dependencies = {{"A", "B"}, {"A", "C"}, {"B", "D"}, {"C", "D"}, {"D", "E"}};
  auto result = m.DeliveringTrojan(locations, dependencies);
  std::vector<std::string> gt = {"A", "B", "C", "D", "E"};
  EXPECT_EQ(result, gt);
}

// Test case 2:
TEST(TrojanMapTest, DeliveringTrojanTest2) {
  TrojanMap m;

  std::vector<std::string> locations = {"A", "B", "C", "D", "E"};
  std::vector<std::vector<std::string>> dependencies = {{"A", "B"}, {"B", "C"}, {"C", "D"}, {"D", "E"}, {"E", "A"}};
  auto result = m.DeliveringTrojan(locations, dependencies);
  std::vector<std::string> gt = { "E", "B", "C", "D", "A" };
  EXPECT_EQ(result, gt);
}

// Test case 3: Valid topological sorting with multiple possible solutions
TEST(TrojanMapTest, DeliveringTrojanTest3) {
  TrojanMap m;

  std::vector<std::string> locations = {"A", "B", "C", "D", "E"};
  std::vector<std::vector<std::string>> dependencies = {{"A", "D"}, {"B", "D"}, {"C", "E"}};
  auto result = m.DeliveringTrojan(locations, dependencies);
  // There are multiple valid topological orderings, such as {"A", "B", "C", "D", "E"} or {"B", "A", "C", "D", "E"}.
  bool valid_ordering = (result == std::vector<std::string>{"A", "B", "C", "D", "E"}) || (result == std::vector<std::string>{"B", "A", "C", "D", "E"});
  EXPECT_TRUE(valid_ordering);
}

//-----
// Test case 1: Inside the square
TEST(TrojanMapTest, inSquareTest1) {
  TrojanMap m;

  std::string id = "8523122301"; // Washington & Normandie
  std::vector<double> square = {34.0400, -118.3010, 34.0390, -118.3000};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, false);
}

// Test case 2: Outside the square
TEST(TrojanMapTest, inSquareTest2) {
  TrojanMap m;

  std::string id = "8530063149"; 
  std::vector<double> square = {34.0220249, -118.3003424, 34.0397098, -118.2916872};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, false);
}

// Test case 3: On the edge of the square
TEST(TrojanMapTest, inSquareTest3) {
  TrojanMap m;

  std::string id = "8530063156"; // Normandie & Exposition
  std::vector<double> square = {34.0190, -118.3010, 34.0180, -118.3000};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, false);
}
//-----
TEST(TrojanMapTest, GetSubgraph1) {
  TrojanMap m;
  std::vector<double> square = { -118.3004000, 34.0346733, -118.3001573, 34.0346733, -118.3001573, 34.0331084, -118.3004000, 34.0331084 };
  std::vector<std::string> actual_output = m.GetSubgraph(square);
  std::vector<std::string> expected_output = {};
  EXPECT_EQ(actual_output, expected_output);
}

TEST(TrojanMapTest, GetSubgraph2) {
  TrojanMap m;
  std::vector<double> square = { -118.2919733, 34.0328589, -118.2914187, 34.0261425 };
  std::vector<std::string> actual_output = m.GetSubgraph(square);
  std::vector<std::string> expected_output = {};
  EXPECT_EQ(actual_output, expected_output);
}

TEST(TrojanMapTest, GetSubgraph3) {
  TrojanMap m;
  std::vector<double> square = { -118.2999583, 34.0326422, -118.2957901, 34.0328389};
  std::vector<std::string> actual_output = m.GetSubgraph(square);
  std::vector<std::string> expected_output = {};
  EXPECT_EQ(actual_output, expected_output);
}

//-----
TEST(TrojanMapTest, CycleDetection1) {
  TrojanMap m;
  std::vector<std::string> subgraph = { "8530063148", "8530063149", "8530063150", "8530063151" };
  std::vector<double> square = { -118.3004000, 34.0346733, -118.3001573, 34.0346733, -118.3001573, 34.0331084, -118.3004000, 34.0331084 };
  bool actual_output = m.CycleDetection(subgraph, square);
  EXPECT_EQ(actual_output,true);
}

TEST(TrojanMapTest, CycleDetection2) {
  TrojanMap m;
  std::vector<std::string> subgraph = { "8530063148", "8530063149" };
  std::vector<double> square = { -118.3005000, 34.0346733, -118.3001573, 34.0346733, -118.3001573, 34.0331084, -118.3004000, 34.0331084 };
  bool actual_output = m.CycleDetection(subgraph, square);
  EXPECT_EQ(actual_output,false);
}

TEST(TrojanMapTest, CycleDetection3) {
  TrojanMap m;
  std::vector<std::string> subgraph = { "8530063148", "8530063149", "8530063150", "8530063151" };
  std::vector<double> square = { -118.3004000, 34.0350000, -118.3001573, 34.0350000, -118.3001573, 34.0331084, -118.3004000, 34.0331084 };
  bool actual_output = m.CycleDetection(subgraph, square);
  EXPECT_EQ(actual_output,true);
}


//-------
TEST(TrojanMapTest, FindNearby1) {
  TrojanMap m;
  std::vector<std::string> expected_output = { "591042107" };
  auto actual_output = m.FindNearby("fuel", "Chevron 2", 1, 1);
  EXPECT_EQ(expected_output, actual_output);
}

TEST(TrojanMapTest, FindNearby2) {
  TrojanMap m;
  std::vector<std::string> expected_output = {"5237417651", "9591449465"};
  auto actual_output = m.FindNearby("bank", "Chase", 1, 2);
  EXPECT_EQ(expected_output, actual_output);
}


TEST(TrojanMapTest, FindNearby3) {
  TrojanMap m;
  std::vector<std::string> expected_output = {};
  auto actual_output = m.FindNearby("amenity", "Nonexistent Place", 0.5, 5);
  EXPECT_EQ(expected_output, actual_output);
}

//--------
TEST(TrojanMapTest, ShortestPath1) {
  TrojanMap m;
  std::vector<std::string> input = { "Jefferson & Flower", "Jefferson & Hope22", "Grand & Jefferson" };
  std::vector<std::string> expected_output = {""};
  auto actual_output = m.TrojanPath(input);
  EXPECT_EQ(expected_output, actual_output);
}
TEST(TrojanMapTest, ShortestPath2) {
  TrojanMap m;
  std::vector<std::string> input = { "Dueling Dinosaurs", "Crosswalk 12", "Moreton Fig"};
  std::vector<std::string> expected_output = {""};
  auto actual_output = m.TrojanPath(input);
  EXPECT_EQ(expected_output, actual_output);
}
TEST(TrojanMapTest, ShortestPath3) {
  TrojanMap m;
  std::vector<std::string> input = { "Grand & 30th", "Grand & 23rd" };
  std::vector<std::string> expected_output = { "9596483797", "3402814840", "3402814839", "3663661792", "3402814836", "3402814835", "3663661791", "3396349768", 
  "6805477812", "3403046686", "3403046687", "3663661789", "3402810303", "6788584353", "3402810299", "3663661788", "3402810300", "4147530482", "544348521", 
  "6813513568", "6813513567", "6817197853", "6817197847", "6788102185", "4012864452", "1732340070", "9596483792" };
  auto actual_output = m.TrojanPath(input);
  EXPECT_EQ(expected_output, actual_output);
}

// TEST(TrojanMapTest, OPT3_TEST) {
//   TrojanMap m;
  
//   std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//   auto result = m.TravelingTrojan_3opt(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//   bool flag = false;
//   if (!result.second.empty() && gt == result.second.back()) // clockwise
//     flag = true;
//   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
//   if (!result.second.empty() && gt == result.second.back())
//     flag = true;
  
//   EXPECT_EQ(flag, true);
// }