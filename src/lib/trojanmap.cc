#include "trojanmap.h"
#include "cmath"
#include <algorithm>

//-----------------------------------------------------
// TODO: Students should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id)
{
  double l = -1;
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (at_posi.id == id)
    {
      l = at_posi.lat;
    }
  }
  return l;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id)
{
  double l = -1;
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (at_posi.id == id)
    {
      l = at_posi.lon;
    }
  }
  return l;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id)
{
  std::string name = "";
  for (auto &i : data)
  {
    // Node at_posi=i.second;
    // if (at_posi.id==id){
    //   name=at_posi.name;
    // }
    if (i.second.id == id)
    {
      name = i.second.name;
      return name;
    }
  }
  return name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id)
{
  std::vector<std::string> n_id = {};
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (at_posi.id == id)
    {
      n_id = at_posi.neighbors;
    }
  }
  return n_id;
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 * The location name must be unique, which means there is only one node with the name.
 *
 * @param  {std::string} name          : location name
 * @return {std::string}               : id
 */
std::string TrojanMap::GetID(const std::string &name)
{
  std::string res = "";
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (at_posi.name == name)
    {
      res = at_posi.id;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name)
{
  std::pair<double, double> results(-1, -1);
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (at_posi.name == name)
    {
      results.first = at_posi.lat;
      results.second = at_posi.lon;
    }
  }
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * @param  {std::string} a          : first string
 * @param  {std::string} b          : second string
 * @return {int}                    : edit distance between two strings
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b)
{
  int row = a.size();
  int col = b.size();
  int de[row + 1][col + 1] = {0};
  for (int i = 0; i < row + 1; i++)
  {
    de[i][0] = i;
  }
  for (int j = 0; j < col + 1; j++)
  {
    de[0][j] = j;
  }
  for (int i = 1; i < row + 1; i++)
  {
    for (int j = 1; j < col + 1; j++)
    {
      if (a[i - 1] != b[j - 1])
      {
        de[i][j] = std::min({de[i - 1][j - 1], de[i - 1][j], de[i][j - 1]}) + 1;
      }
      else
      {
        de[i][j] = de[i - 1][j - 1];
      }
    }
  }
  return de[row][col];
}

/**
 * FindClosestName: Given a location name, return the name with the smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : the closest name
 */
std::string TrojanMap::FindClosestName(std::string name)
{
  int distance = -1;
  std::string id = "";
  std::string tmp = "";
  for (auto &x : data)
  {
    if (distance == -1)
    {
      distance = CalculateEditDistance(x.second.name, name);
    }
    if (!x.second.name.empty())
    {
      if (distance >= CalculateEditDistance(x.second.name, name))
      {
        distance = CalculateEditDistance(x.second.name, name);
        id = x.second.id;
      }
    }
  }
  tmp = GetName(id); // Start with a dummy word
  return tmp;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name)
{
  std::vector<std::string> results;
  if (name.length() == 0)
    return results;
  transform(name.begin(), name.end(), name.begin(), ::tolower); // Make input all lower case
  for (auto &i : data)
  {
    Node node = i.second;
    std::string loc = node.name;
    transform(loc.begin(), loc.end(), loc.begin(), ::tolower); // Make location all lower case
    std::size_t found = loc.find(name);
    if (found != std::string::npos && found == 0)
      results.push_back(node.name); // Check is input in location and at pos 0
  }
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories()
{
  std::vector<std::string> result = {};
  std::vector<std::string>::iterator it;
  for (auto &i : data)
  {
    Node at_posi = i.second;
    for (auto &j : at_posi.attributes)
    {
      it = find(result.begin(), result.end(), j);
      if (it == result.end())
      {
        result.push_back(j);
      }
    }
  }
  return result;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category         : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(std::string category)
{
  std::vector<std::string> res = {};
  std::vector<std::string>::iterator it;
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (find(at_posi.attributes.begin(), at_posi.attributes.end(), category) != at_posi.attributes.end())
    {
      res.push_back(at_posi.id);
      continue;
    }
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location)
{
  std::vector<std::string> result = {};
  for (auto &i : data)
  {
    Node at_posi = i.second;
    if (regex_match(at_posi.name, location))
    {
      result.push_back(at_posi.id);
    }
  }
  return result;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 * We have provided the code for you. Please do not need to change this function.
 * You can use this function to calculate the distance between 2 nodes.
 * The distance is in mile.
 * The distance is calculated using the Haversine formula.
 * https://en.wikipedia.org/wiki/Haversine_formula
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id)
{
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 * We have provided the code for you. Please do not need to change this function.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path)
{
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++)
  {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(std::string location1_name, std::string location2_name)
{
  std::vector<std::string> path;
  std::unordered_map<std::string, double> node_dist;
  std::unordered_map<std::string, std::string> P;
  std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> queue;

  for (auto &i : data)
  {
    std::string id = i.first;
    P[id] = "";
    node_dist[id] = std::numeric_limits<double>::infinity();
    if (i.second.name == location1_name)
    {
      node_dist[id] = 0;
      queue.push(std::make_pair(0, id));
    }
  }
  while (queue.empty() == false)
  {
    auto loc = queue.top();
    queue.pop();
    std::string loc_id = loc.second;

    if (GetName(loc_id) == location2_name)
      break;
    else
    {
      for (auto &i : data[loc_id].neighbors)
      {
        double update_dist = node_dist[loc_id] + CalculateDistance(loc_id, i);
        if (update_dist < node_dist[i])
        {
          node_dist[i] = update_dist;
          P[i] = loc_id;
          queue.push(std::make_pair(update_dist, i));
        }
      }
    }
  }
  std::string u = GetID(location2_name);
  path.push_back(u);
  while (P[u] != "")
  {
    u = P[u];
    path.push_back(u);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(std::string location1_name, std::string location2_name)
{
  std::vector<std::string> path;
  std::unordered_map<std::string, double> node_dist;
  std::unordered_map<std::string, std::string> P;
  std::vector<std::string> curr_node = {};
  std::vector<std::string> next_node = {};
  double dest_prev = std::numeric_limits<double>::infinity();
  double dest_curr = std::numeric_limits<double>::infinity();
  int round = 0;
  std::string u = GetID(location2_name);
  for (auto &i : data)
  {
    std::string id = i.first;
    P[id] = "";
    node_dist[id] = std::numeric_limits<double>::infinity();
    if (i.second.name == location1_name)
    {
      node_dist[id] = 0;
      curr_node.push_back(id);
    }
  }
  while (curr_node.empty() != true && round < 5)
  {
    for (auto &curr_id : curr_node)
    {
      // if (GetName(curr_id)==location2_name && indx==0) indx++;//indx++;
      for (auto &next_id : data[curr_id].neighbors)
      {
        double update_dist = node_dist[curr_id] + CalculateDistance(curr_id, next_id);
        if (update_dist < node_dist[next_id])
        {
          node_dist[next_id] = update_dist;
          P[next_id] = curr_id;
          next_node.push_back(next_id);
          if (u == next_id)
            dest_curr = update_dist;
        }
      }
    }
    if (dest_curr != std::numeric_limits<double>::infinity())
    {
      if (dest_curr == dest_prev)
        round++;
      else
      {
        round = 0;
        dest_prev = dest_curr;
      }
    }
    curr_node = next_node;
    next_node.clear();
  }

  path.push_back(u);
  while (P[u] != "")
  {
    u = P[u];
    path.push_back(u);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path,
 *                                                                      for example: {10.3, {{0, 1, 2, 3, 4, 0}, {0, 1, 2, 3, 4, 0}, {0, 4, 3, 2, 1, 0}}},
 *                                                                      where 10.3 is the total distance,
 *                                                                      and the first vector is the path from 0 and travse all the nodes and back to 0,
 *                                                                      and the second vector is the path shorter than the first one,
 *                                                                      and the last vector is the shortest path.
 */
// Please use brute force to implement this function, ie. find all the permutations.
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::sort(location_ids.begin()+1, location_ids.end());
  records.first = 99999999999999;
  std::vector<std::string> compute_locs;
  std::vector<std::string> test = {"6819019976", "6820935923", "7771782316", "6816180153", "8566227783", "122702233",
   "8566227656", "1873055993", "6819019976"};
  std::cout << CalculatePathLength(location_ids)<<std::endl;
  do{
    location_ids.push_back(location_ids[0]);
    std::vector<std::string> tmp_vec;
    double tmp = CalculatePathLength(location_ids);
    if(tmp<records.first){
      // records.second.push_back(location_ids);
      records.second = {location_ids};
      records.first = tmp;
    }
    location_ids.pop_back();
    // location_ids.pop_back();
  }while (std::next_permutation(location_ids.begin(), location_ids.end()));
  std::vector<std::string> tmp;
  tmp = records.second.back();
  for (std::string x : tmp) {
    std::cout << x << ' ';
  }
  return records;
 
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::BackTrackingHelper(std::set<std::string> chosenID, std::string begining,  
    double &totaldistance, std::vector<std::string> record_cities, std::vector<std::string> location_ids){
      // std::unordered_map<double, std::string> distance_map;
      // std::vector<double> dis_collection;
      std::string chooseID;
      std::pair<double, std::vector<std::vector<std::string>>> res;
      double dis = 999999;
      double d1 = CalculatePathLength({"6819019976","1873055993","8566227656","122702233"});
      double d2 = CalculatePathLength({"6819019976","1873055993","8566227656","8566227783"});
      for(int i=0;i<location_ids.size();i++){
        record_cities.push_back(location_ids[i]);
        record_cities.push_back(location_ids[location_ids.size()-1]);
        double tmp = CalculatePathLength(record_cities);
        record_cities.pop_back();
        record_cities.pop_back();
        if(tmp<dis && chosenID.count(location_ids[i])==0){
          dis = tmp;
          chooseID = location_ids[i];
        }
      }
      chosenID.insert(chosenID.end(),chooseID);//add the visited shortest path location.
      totaldistance += dis;
      record_cities.push_back(chooseID);
      if(chosenID.size()<location_ids.size()){
        return BackTrackingHelper(chosenID,chooseID,totaldistance,record_cities,location_ids);
      }
      res.first = totaldistance;
      record_cities.push_back(location_ids[0]);
      res.second.push_back(record_cities);
      return res;
}
double TrojanMap::BackTrackingHelper2(std::vector<std::string> location_ids, 
    std::string current, double distance, std::unordered_map<std::string,bool> &visited)
{
  std::pair<double, std::vector<std::vector<std::string>>> res;
  bool if_visited = false;
  for(const auto& x:visited){
    if(!x.second){
      if_visited = false;
      break;
    }
  }
  if (if_visited) {
    distance = distance + CalculateDistance(GetID(current),location_ids[0]);
    return distance;
  }
  double min_distance = 99999999;
  for(size_t i=0;i<location_ids.size();i++){
    std::string next_loc = location_ids[i];
    if(!visited[next_loc]){
      visited[next_loc] = true;
      double current_dis = distance + CalculateDistance(GetID(current),GetID(next_loc));
      double new_dis = BackTrackingHelper2(location_ids,next_loc, current_dis,visited);
      min_distance = std::min(min_distance,new_dis);
    }
  }
  return min_distance;  
}
// Please use backtracking to implement this function
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  double min_distance = 99999999;
  std::unordered_map<std::string,bool> visited;
  std::vector<std::string> path(location_ids.size());

  for(auto x:location_ids){
    visited[x] = false;
  }
  
  for(size_t i=0;i<location_ids.size();++i){
    visited[location_ids[i]] == true;
    double new_dis = BackTrackingHelper2(location_ids,location_ids[i],0,visited);
    if(new_dis < min_distance){
      min_distance = new_dis;
      path = location_ids;
    }
    visited[location_ids[i]] == true;
  }
  records.first = min_distance;
  records.second.push_back(path);
  return records;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  location_ids.push_back(location_ids[0]);
  double distance = CalculatePathLength(location_ids);
  int loop = 0;
  int index1 = 0;
  int index2 = 0;
  while (loop<50)
  {
    index1 = (rand() % (location_ids.size())); 
    index2 = (rand() % (location_ids.size()));
    if(index2 != 0 && index2<index1){
      loop++;
      continue;
    }
    if(index1 >= 1 && index2 <= location_ids.size()-2 && index2 >=1 && index1< index2){
      std::iter_swap(location_ids.begin()+index1,location_ids.begin()+index2);
    }
    else if(index1 <= 0 || index2 > location_ids.size()-1){
      loop++;
      continue;
    }
    double tmp = CalculatePathLength(location_ids);
    if(tmp <distance){
      distance = tmp;
      loop++;
    }
    records.second.push_back(location_ids);
  }
  records.first = distance;

  return records;
}

// This is optional
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_3opt(
    std::vector<std::string> location_ids)
{
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example:
 *   Input: "topologicalsort_locations.csv"
 *   File content:
 *    Name
 *    Ralphs
 *    KFC
 *    Chick-fil-A
 *   Output: ['Ralphs', 'KFC', 'Chick-fil-A']
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 * File dir: /Users/lijingyang/Desktop/Course/USC/EE/EE538/Project/spring2023_trojanmap-Foxylj/input/topologicalsort_locations.csv
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename)
{
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word))
  {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 * We have provided the code for you. Please do not need to change this function.
 * Example:
 *   Input: "topologicalsort_dependencies.csv"
 *   File content:
 *     Source,Destination
 *     Ralphs,Chick-fil-A
 *     Ralphs,KFC
 *     Chick-fil-A,KFC
 *   Output: [['Ralphs', 'Chick-fil-A'], ['Ralphs', 'KFC'], ['Chick-fil-A', 'KFC']]
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 * File dir: /Users/lijingyang/Desktop/Course/USC/EE/EE538/Project/spring2023_trojanmap-Foxylj/input/topologicalsort_dependencies.csv
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename)
{
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line))
  {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ','))
    {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations, std::vector<std::vector<std::string>> &dependencies)
{
  std::vector<std::string> result = locations;
  bool finish = false;
  std::string temp;

  while (!finish)
  {
    finish = true;
    for (auto &i : dependencies)
    {
      auto d_1 = std::find(result.begin(), result.end(), i[0]) - result.begin();
      auto d_2 = std::find(result.begin(), result.end(), i[1]) - result.begin();
      if (d_1 > d_2)
      {
        temp = result[d_2];
        result[d_2] = result[d_1];
        result[d_1] = temp;
      }
    }
  }
  return result;
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square)
{
  double lon = (GetPosition(GetName(id))).second;
  double lat = (GetPosition(GetName(id))).first;
  if (lon >= square.at(0) && lon <= square.at(1))
  {
    if (lat <= square.at(2) && lat >= square.at(3))
    {
      return true;
    }
  }
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square)
{
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  for (auto &x : data)
  {
    double lon = x.second.lon;
    double lat = x.second.lat;
    if (lon >= square.at(0) && lon <= square.at(1))
    {
      if (lat <= square.at(2) && lat >= square.at(3))
      {
        subgraph.push_back(x.second.id);
      }
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square)
{
  std::vector<std::pair<double, double>> pos;
  std::vector<std::string> path;
  std::vector<std::string> loc;
  for (int i = 0; i < subgraph.size(); i++)
  {
    if (!GetName(subgraph.at(i)).empty())
    {
      loc.push_back(subgraph.at(i));
    }
  }
  if (loc.size() > 2)
  {
    return true;
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {double} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k)
{
  auto comp = [](const std::pair<std::string, double> &lhs, const std::pair<std::string, double> &rhs)
  {
    return lhs.second < rhs.second;
  };
  std::vector<std::string> res;
  std::set<std::pair<std::string, double>, decltype(comp)> loc(comp);
  double lon = GetPosition(name).second;
  double lat = GetPosition(name).first;
  double distance;
  for (auto x : data)
  {
    if (x.second.lat <= lat + r && x.second.lon <= lon + r)
    {
      if (x.second.attributes.count(attributesName) && GetID(name) != x.second.id)
      {
        distance = (x.second.lat - lat) * (x.second.lat - lat) + (x.second.lon - lon) * (x.second.lon - lon);
        loc.insert(std::make_pair(x.second.id, distance));
      }
    }
    else if (x.second.lat <= lat + r && x.second.lon >= lon - r)
    {
      if (x.second.attributes.count(attributesName) && GetID(name) != x.second.id)
      {
        distance = (x.second.lat - lat) * (x.second.lat - lat) + (x.second.lon - lon) * (x.second.lon - lon);
        loc.insert(std::make_pair(x.second.id, distance));
      }
    }
    else if (x.second.lat >= lat - r && x.second.lon >= lon - r)
    {
      if (x.second.attributes.count(attributesName) && GetID(name) != x.second.id)
      {
        distance = (x.second.lat - lat) * (x.second.lat - lat) + (x.second.lon - lon) * (x.second.lon - lon);
        loc.insert(std::make_pair(x.second.id, distance));
      }
    }
    else if (x.second.lat >= lat - r && x.second.lon <= lon + r)
    {
      if (x.second.attributes.count(attributesName) && GetID(name) != x.second.id)
      {
        distance = (x.second.lat - lat) * (x.second.lat - lat) + (x.second.lon - lon) * (x.second.lon - lon);
        loc.insert(std::make_pair(x.second.id, distance));
      }
    }
  }
  if (loc.size() >= k)
  {
    int index = 0;
    for (auto it = loc.begin(); it != loc.end() && index < 10; ++it, ++index)
    {
      auto element = *it;
      res.push_back(element.first);
    }
  }
  else
  {
    for (auto y : loc)
    {
      // auto element = *it;
      std::pair<std::string, double> pair_tmp = y;
      res.push_back(y.first);
    }
  }
  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and no need to go back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::vector<std::string> }      : the shortest path
 */
std::vector<std::string> TrojanMap::TrojanPath(
    std::vector<std::string> &location_names)
{
  std::vector<std::string> res;
  std::unordered_map<std::string, int> inner_map;
  std::unordered_map<int, int> path;

  int start_end[1][1];
  int n = location_names.size();
  std::vector<std::vector<int>> dist(n,std::vector<int>(n,1e9));
  std::set<int> visited;
  int index = 1;
  for(int k=0;k<location_names.size();k++){
    std::pair<std::string,int> pair = {location_names[k],index};
    inner_map.insert(pair);
    index++;
  } 
  for(int i=1;i<n;i++){
    for(int j=2;j<n;j++){
      if(j>i){
        std::vector<std::string> road = CalculateShortestPath_Dijkstra(location_names[i],location_names[j]);
        dist[i][j] = road.size();
        std::pair<std::pair<int,int>,std::vector<std::string>> pair;
        pair.first = {i,j};
        pair.second = road; 
        if(dist[i][j]<dist[i-1][j-1]+dist[i-1][j]){
          dist[i-1][j] = dist[i][j];
          // path.insert(1,1);
          std::pair<int, int> map_pair;
          map_pair.first = j;
          map_pair.second = i;
          path.insert(map_pair);//put the shortest path to the map
        }
      }
    }
  }
  return res;
}

/**
 * Given a vector of queries, find whether there is a path between the two locations with the constraint of the gas tank.
 *
 * @param  {std::vector<std::pair<double, std::vector<std::string>>>} Q : a list of queries
 * @return {std::vector<bool> }      : existence of the path
 */
std::vector<bool> TrojanMap::Queries(const std::vector<std::pair<double, std::vector<std::string>>> &q)
{
  std::vector<bool> ans(q.size());
  
  return ans;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * We have provided the code for you. Please do not need to change this function.
 */
void TrojanMap::CreateGraphFromCSVFile()
{
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line))
  {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ','))
    {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else
      {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
