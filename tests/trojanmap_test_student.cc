#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
//-------------------------------------------------------
// Test case 1: GetNeighborIDs with valid id
TEST(TrojanMapTest, GetNeighborIDsTest1) {
  TrojanMap m;
  std::string id = "8530063146"; // Normandie & 24th
  std::vector<std::string> expected_output = {"122817171"};
  std::vector<std::string> result = m.GetNeighborIDs(id);
  EXPECT_EQ(result, expected_output);
}

// Test case 2: GetNeighborIDs with another valid id
TEST(TrojanMapTest, GetNeighborIDsTest2) {
  TrojanMap m;
  std::string id = "8530535251"; // Jefferson & Denker
  std::vector<std::string> expected_output = {"123289542"};
  std::vector<std::string> result = m.GetNeighborIDs(id);
  EXPECT_EQ(result, expected_output);
}

// Test case 3: GetNeighborIDs with invalid id
TEST(TrojanMapTest, GetNeighborIDsTest3) {
  TrojanMap m;
  std::string id = "invalid_id";
  std::vector<std::string> expected_output = {};
  std::vector<std::string> result = m.GetNeighborIDs(id);
  EXPECT_EQ(result, expected_output);
}
//-------------------------------------------------------
// Test case 1: CalculateEditDistance with identical strings
TEST(TrojanMapTest, CalculateEditDistanceTest1) {
  TrojanMap m;
  std::string a = "Normandie & 24th";
  std::string b = "Normandie & 24th";
  int expected_output = 0;
  int result = m.CalculateEditDistance(a, b);
  EXPECT_EQ(result, expected_output);
}

// Test case 2: CalculateEditDistance with completely different strings
TEST(TrojanMapTest, CalculateEditDistanceTest2) {
  TrojanMap m;
  std::string a = "Normandie & 24th";
  std::string b = "Exposition & Vermont";
  int expected_output = 16; // Assuming the edit distance between the two strings is 16
  int result = m.CalculateEditDistance(a, b);
  EXPECT_EQ(result, expected_output);
}

// Test case 3: CalculateEditDistance with strings having a small difference
TEST(TrojanMapTest, CalculateEditDistanceTest3) {
  TrojanMap m;
  std::string a = "Normandie & 24th";
  std::string b = "Normandie & 25th";
  int expected_output = 1;
  int result = m.CalculateEditDistance(a, b);
  EXPECT_EQ(result, expected_output);
}
//-------------------------------------------------------
// Test case 1: FindClosestName exact match
TEST(TrojanMapTest, FindClosestNameTest1) {
  TrojanMap m;
  std::string input_name = "Normandie & 24th";
  std::string expected_output = "Normandie & 24th";
  std::string result = m.FindClosestName(input_name);
  EXPECT_EQ(result, expected_output);
}

// Test case 2: FindClosestName with small edit distance
TEST(TrojanMapTest, FindClosestNameTest2) {
  TrojanMap m;
  std::string input_name = "Normandie & 24t";
  std::string expected_output = "Normandie & 24th";
  std::string result = m.FindClosestName(input_name);
  EXPECT_EQ(result, expected_output);
}

// Test case 3: FindClosestName with larger edit distance
TEST(TrojanMapTest, FindClosestNameTest3) {
  TrojanMap m;
  std::string input_name = "Adms & Vermnt";
  std::string expected_output = "Adams & Vermont";
  std::string result = m.FindClosestName(input_name);
  EXPECT_EQ(result, expected_output);
}
//--------------------------------------------------------
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

// Test case 1: GetPosition with an existing location name
TEST(TrojanMapTest, GetPositionTest1) {
  TrojanMap m;
  std::string input_name = "Normandie & 24th";
  std::pair<double, double> expected_output = {34.0346733, -118.3004000};
  std::pair<double, double> result = m.GetPosition(input_name);
  EXPECT_NEAR(result.first, expected_output.first, 1e-7);
  EXPECT_NEAR(result.second, expected_output.second, 1e-7);
}

// Test case 2: GetPosition with a non-existing location name
TEST(TrojanMapTest, GetPositionTest2) {
  TrojanMap m;
  std::string input_name = "NonExistingLocation";
  std::pair<double, double> expected_output = {-1, -1};
  std::pair<double, double> result = m.GetPosition(input_name);
  EXPECT_NEAR(result.first, expected_output.first, 1e-7);
  EXPECT_NEAR(result.second, expected_output.second, 1e-7);
}

// Test case 3: GetPosition with a location name containing a small typo
TEST(TrojanMapTest, GetPositionTest3) {
  TrojanMap m;
  std::string input_name = "Normandie & 24t";
  std::pair<double, double> expected_output = {-1, -1}; // Assuming the function doesn't correct typos
  std::pair<double, double> result = m.GetPosition(input_name);
  EXPECT_NEAR(result.first, expected_output.first, 1e-7);
  EXPECT_NEAR(result.second, expected_output.second, 1e-7);
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
//-----------------------------------------------
// Test case 1: GetID with an existing location name
TEST(TrojanMapTest, GetIDTest1) {
  TrojanMap m;
  std::string input_name = "Normandie & 24th";
  std::string expected_output = "8530063146";
  std::string result = m.GetID(input_name);
  EXPECT_EQ(result, expected_output);
}

// Test case 2: GetID with an non-existing location name
TEST(TrojanMapTest, GetIDTest2) {
  TrojanMap m;
  std::string input_name = "NonExistingLocation";
  std::string expected_output = "";
  std::string result = m.GetID(input_name);
  EXPECT_EQ(result, expected_output);
}

// Test case 3: GetID with a location name containing small typo
TEST(TrojanMapTest, GetIDTest3) {
  TrojanMap m;
  std::string input_name = "Normandie & 24t";
  std::string expected_output = ""; // Assuming the function doesn't correct typos
  std::string result = m.GetID(input_name);
  EXPECT_EQ(result, expected_output);
}
//------------------------------------------------
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
//---------------------------------------------------------------------------
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

TEST(CalculateShortestPath_Dijkstra, UNKNOW_LOCATION) {
  TrojanMap m;
  std::set<std::string> result = {""};
  auto output=m.CalculateShortestPath_Dijkstra("Chase","Ralph");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(CalculateShortestPath_Dijkstra, CLOSE_LOCATION) {
  TrojanMap m;
  std::set<std::string> result = { "1378231760", "1732340075", "1732340077", "1732340096", "4011837234", 
  "4060116191", "4400460712", "4400460714", "4400460720", "4400460721", "4400460722", "4400460725", 
  "4400460728", "4835549608", "6208583968", "6225907126", "6225907131", "63785522", "63785537", 
  "8501336171", "8501336173" };
  auto output=m.CalculateShortestPath_Dijkstra("Flower Street & Adams Boulevard","Flower Street & 23rd Street");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}
//--------------------------------------------------------------------------
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

TEST(CalculateShortestPath_Bellman_Ford, UNKNOW_LOCATION) {
  TrojanMap m;
  std::set<std::string> result = {""};
  auto output=m.CalculateShortestPath_Bellman_Ford("Chase","Ralph");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}

TEST(CalculateShortestPath_Bellman_Ford, CLOSE_LOCATION) {
  TrojanMap m;
  std::set<std::string> result = { "1378231760", "1732340075", "1732340077", "1732340096", "4011837234", 
  "4060116191", "4400460712", "4400460714", "4400460720", "4400460721", "4400460722", "4400460725", 
  "4400460728", "4835549608", "6208583968", "6225907126", "6225907131", "63785522", "63785537", 
  "8501336171", "8501336173" };
  auto output=m.CalculateShortestPath_Bellman_Ford("Flower Street & Adams Boulevard","Flower Street & 23rd Street");
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, result);
}
//---------------------------------------------------------------------

TEST(TravelingTrojan_Brute_force, TEST1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","122702233","6820935923"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "122702233", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TravelingTrojan_Brute_force, TEST2) {
  TrojanMap m;
  
  std::vector<std::string> input{"12345678"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"12345678"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TravelingTrojan_Brute_force, TEST3) {
  TrojanMap m;
  
  std::vector<std::string> input{"8501336171","8523122305","8501336176","8530063153","8530063148"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8501336171","8501336176","8523122305","8530063148","8530063153","8501336171"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

//---------------------------------------------------------------------

TEST(TravelingTrojan_Backtracking, TEST1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","122702233","6820935923"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "122702233", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TravelingTrojan_Backtracking, TEST2) {
  TrojanMap m;
  
  std::vector<std::string> input{"12345678"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"12345678"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TravelingTrojan_Backtracking, TEST3) {
  TrojanMap m;
  
  std::vector<std::string> input{"8501336171","8523122305","8501336176","8530063153","8530063148"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8501336171", "8530063153", "8530063148", "8523122305", "8501336176", "8501336171" }; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
//---------------------------------------------------------------------------------

TEST(OPT2, TEST1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","122702233","6820935923"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "122702233", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x <<" ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(OPT2, TEST2) {
  TrojanMap m;
  
  std::vector<std::string> input{"12345678"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"12345678"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(OPT2, TEST3) {
  TrojanMap m;
  
  std::vector<std::string> input{"8501336171","8523122305","8501336176","8530063153","8530063148"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8501336171", "8530063153", "8530063148", "8523122305", "8501336176", "8501336171" }; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x <<" ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
//----------------------------------------------------------------------------------
TEST(OPT3, TEST1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","122702233","6820935923"}; // Input location ids 
  auto result = m.TravelingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976", "122702233", "6820935923", "6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x <<" ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(OPT3, TEST2) {
  TrojanMap m;
  
  std::vector<std::string> input{"12345678"}; // Input location ids 
  auto result = m.TravelingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"12345678"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x << " ";
  }
  std::cout<<" "<<std::endl;
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(OPT3, TEST3) {
  TrojanMap m;
  
  std::vector<std::string> input{"8501336171","8523122305","8501336176","8530063153","8530063148"}; // Input location ids 
  auto result = m.TravelingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8501336171", "8530063153", "8530063148", "8523122305", "8501336176", "8501336171" }; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  std::cout<< "result" << std::endl;
  for(auto x:result.second.back()){
    std::cout << x <<" ";
  }
  std::cout<<" "<<std::endl;
  if (!result.second.empty() && gt == result.second.back()) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}
//----------------------------------------------------------------------------------
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
TEST(TrojanMapTest, inSquareTest1) {
  TrojanMap m;

  std::string id = "8501336167"; // Figueroa Street & 23rd Street
  std::vector<double> square = { -118.2747100, -118.2718526, 34.0346898, 34.0285582,};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, true);
}

// Test case 2: Outside the square
TEST(TrojanMapTest, inSquareTest2) {
  TrojanMap m;

  std::string id = "8501336178"; // Flower Street & Pico Boulevard
  std::vector<double> square = {-118.2747100,-118.2718526, 34.0346898, 34.0285582};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, false);
}

// Test case 3: On the edge of the square
TEST(TrojanMapTest, inSquareTest3) {
  TrojanMap m;

  std::string id = "8530063156"; // Normandie & Exposition
  std::vector<double> square = {-118.3010,-118.3000, 34.0190,34.0180};
  bool result = m.inSquare(id, square);
  EXPECT_EQ(result, true);
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

TEST(Queries, Stay_At_Starting_Point) {
  TrojanMap m;
  std::vector<std::pair<double, std::vector<std::string>>> input {
                                                                  {999, {"Target", "Target"}}};
  auto actual = m.Queries(input);
  std::vector<bool> expected {true};
  EXPECT_EQ(expected, actual);
}

TEST(Queries, MutipleDirections) {
  TrojanMap m;
  std::vector<std::pair<double, std::vector<std::string>>> input {
                                                                  {0.5, {"Normandie & Exposition 1", "Washington & Westmoreland"}},
                                                                  {0.1,{"Flower Street & Washington Boulevard","Normandie & Exposition 1"}},
                                                                  {999,{"Normandie & Exposition 1","Vermont & Jefferson"}}
                                                                  };
  auto actual = m.Queries(input);
  std::vector<bool> expected {true,true,true};
  EXPECT_EQ(expected, actual);
}

TEST(Queries, UNKNOW_DESTINATIONS) {
  TrojanMap m;
  std::vector<std::pair<double, std::vector<std::string>>> input {{0.05, {"Target", "Ralphs"}},
                                                                  {0.01, {"Ralphs", "Target"}},
                                                                  {999, {"KFC", "Ralphs"}},
                                                                  {999, {"Target", "Targ"}}};
  auto actual = m.Queries(input);
  std::vector<bool> expected {true, false, true, false};
  EXPECT_EQ(expected, actual);
}
