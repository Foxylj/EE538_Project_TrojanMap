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




