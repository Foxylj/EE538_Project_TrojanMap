# EE538 Final Project - Spring 2023 - TrojanMap

The project is **optional**: you can select one of the following options:

1. Work on the project and submit the reports.
2. Submit homework assignments (HW4, 5, 6).

If you choose to work on the project, you don't have to submit the remaining homework assignments. Similarly, if you choose to work on the homework assignment, you do not have to submit the project. 

You should inform us of your choice by the first due date (Sunday, April 9).

#### Who should work on the project?
If you plan to become a software engineer, we recommend working on the project as it will give you more experience coding a real-life project. Otherwise, you can take the homework assignments.

Not everything in the project is covered in the class. The idea is for you to do some quick research and figure them out. For example, you should read about handling regular expressions in C++.

#### Which one is harder?
We expect both options to take a similar amount of time. The project, however, might require extra effort from you during the environment setup and installation prerequisites.

#### How many students in each team?
Each team should consist of one or two students. You can find a teammate who is in other sections of the course. You should select your teammates by the first due date (April 9).

#### What should I submit?
The project is submitted in different phases. You are required to submit the following:

1. Phase 1, 2, and 3: these should be submitted on GitHub.
2. Video presentation: you and your teammate will create a 3-4 minute video, post it as an unlisted video on Youtube and submit the link. The video should include:
   - Teammates introduction
   - Demo of the executable
   - Quick overview of the algorithm and code architecture
   - Tables, plots and comparisons
   - No coding details in the video

   Here is a [sample video from the previous semester.](https://www.youtube.com/watch?v=_KDML4Ck3SU&t=4s) 

3. A final report in the README file of your GitHub submission. The final report should include the questions that are asked in this README file, your tables and plots for the runtime results, and any other detail of your code.

## Due Dates

- Phase 1: Sunday, April 9, 23:59 pm
- Phase 2: Friday, April 14, 23:59 pm
- Phase 3: Friday, April 28, 23:59 pm
- Video Presentation: Friday, April 28, 23:59 pm
- Report: Friday, May 5, 23:59 pm

## TrojanMap

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- Please clone the repository, read through [README.md](README.md), and implement the functions of the project.
- Please make sure that your code can run `bazel run` and `bazel test`.
- You need to fill in [trojanmap.cc](src/lib/trojanmap.cc), [mapui.cc](src/lib/mapui.cc) and maybe [mapui.h](src/lib/mapui.h), and add unit tests in the `tests` directory.
- We will use the autograder to grade some of the questions
- We will compare the code similarity between submissions and the previous semester's submissions. Please complete the project within your group.
---

## The Data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
// A Node is the location of one point in the map.
class Node {
 public:
  Node(){};
  Node(const Node &n) {
    id = n.id;
    lat = n.lat;
    lon = n.lon;
    name = n.name;
    neighbors = n.neighbors;
    attributes = n.attributes;
  };
  std::string id;    // A unique id assigned to each point.
  double lat;        // Latitude
  double lon;        // Longitude
  std::string name;  // Name of the location. E.g. "Bank of America".
  std::vector<std::string>
      neighbors;  // List of the ids of all neighbor points.
  std::unordered_set<std::string>
      attributes;  // List of the attributes of the location.
};
```

---

## Prerequisites
The details of the environment setup will be reviewed in the discussion session. Please do not miss that class!

### External Libraries Installation

For visualization, we use `OpenCV` library. You will use this library as a black box and don't need to worry about the graphic details. Use the following commands to install OpenCV and other libraries.

#### For macOS Users

Step 1. Type the following three lines in your terminal.
```shell
$ brew install cmake
$ brew install opencv
$ brew install ncurses
```

Step 2. Check the installation paths of opencv and ncurses by

```shell
$ brew info opencv
```

and

```shell
$ brew info ncurses
```

respectively, and update their paths in the `WORKSPACE` file of your project root directory with the actual installation paths.



#### For Ubuntu users
Step 1. Type the following lines in your terminal.

```shell
$ cd **your project folder**
$ git clone https://github.com/opencv/opencv.git
$ sudo apt update
$ sudo apt install cmake libgtk2.0-dev pkg-config
$ sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
$ sudo apt install libncurses5-dev libncursesw5-dev
$ cp ubuntu/* ./
```

Step 2. Make sure you set the **path_to_install_folder** to be the absolute path to the **install** folder under opencv when running the following commands.

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=**path_to_install_folder** -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio ..
$ make install
```

For example, if cloned this repo under `"/Users/ari/github/TrojanMap"`, you should type:

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=/Users/ari/github/TrojanMap/opencv/install -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio ..
$ make install
```

## Run the program

For macOS users, run

```shell
$ bazel run src/main:main
```

For Ubuntu users, run
               
```shell
$ bazel run --cxxopt='-std=c++17' src/main:main
```

If everything is correct, a menu similar to this will show up.

```shell
TrojanMap Menu
**************************************************************
* Enter the function number (1-11) to start:                  
* 1. Autocomplete                                             
* 2. Find the location                                        
* 3. Find all location categories                             
* 4. Get all locations of a category                          
* 5. Get location matching regular expression                 
* 6. CalculateShortestPath                                    
* 7. Cycle Detection                                          
* 8. Topological Sort                                         
* 9. Traveling salesman problem                              
* 10. Find Nearby                                              
* 11. Find Path to Visit All Places
* 12. Check Exist of Path with Constrain
* 13. Exit                                                     
**************************************************************
```

## Test The Program

We created some tests for you to test your program, please run
```shell
$ bazel test tests:trojanmap_test
```

> You may also need to add the `--cxxopt='-std=c++17'` flag if you are using Linux.

Please add you test in the [trojanmap_test_student.cc](tests/trojanmap_test_student.cc) and run

```shell
$ bazel test tests:trojanmap_test_student
```
---------
--------
## Item 1: Autocomplete The Location Name (Phase 1)

```c++
std::vector<std::string> Autocomplete(std::string name);
```
### **Time Complexity: O(n^2)**
---
**In this function, we traversal the data nodes, for each node, we make the node's location name into lower case and find if there are same location name with input name in lower case.**

**We consider the names of nodes as the locations. Implement a method to type the partial name of the location and return a list of possible locations with the partial name as the prefix. Please treat uppercase and lowercase as the same character. Please return an empty output if the input string is empty.**

---
Example:

Input: "Chi" \
Output: ["Chick-fil-A", "Chipotle", "Chinese Street Food"]

Example 1:

```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:ch
*************************Results******************************
Chinese Street Food
Cheebos Burger
Chick-fil-A
Chase
Chevron 1
Chipotle
Chase Plaza Heliport
Chevron 2
Church of Christ
Chucks Chicken & Waffles
Chevron
**************************************************************
Time taken by function: 2 ms
```

Example 2:
```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:Bank of A
*************************Results******************************
Bank of America
**************************************************************
Time taken by function: 21 ms
```

Example 3:
```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:The
*************************Results******************************
The Hoxton
The Mirage
The Peoples Independent Church of Christ
The Coffee Bean & Tea Leaf
The Barber Shop
The Caribbean Apartments
The Sonshine Shop Thrift Store
The Pearl
The Row House
**************************************************************
Time taken by function: 30 ms
```
- What is the runtime of your algorithm? O(n^2)
- (Optional) Can you do it faster than `O(n)`?
---
---
## Item 2-1: Find the place's coordinates in the Map (Phase 1)

```c++
std::pair<double, double> GetPosition(std::string name);
```
### **Time Complexity: O(n)**
---
**Given a location name, return the latitude and longitude. There are no duplicated location names. You should mark the given locations on the map. If the location does not exist, return (-1, -1). The algorithm is case-sensitive.**

---
Example 1:

Input: "Target" \
Output: (34.0257016, -118.2843512)

```shell
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Target
*************************Results******************************
Latitude: 34.0257 Longitude: -118.284
**************************************************************
Time taken by function: 20 ms
```
<p align="center"><img src="img/Target.png" alt="Target" width="500"/></p>

Example 2:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:The Row House
*************************Results******************************
Latitude: 34.0264 Longitude: -118.279
**************************************************************
Time taken by function: 31 ms
```
<p align="center"><img src="img/The Row House.png" alt="The Row House" width="500"/></p>

Example 3:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Trojan Grounds (Starbucks)
*************************Results******************************
Latitude: 34.0213 Longitude: -118.282
**************************************************************
Time taken by function: 34 ms
```
<p align="center"><img src="img/Starbucks.png" alt="Starbucks" width="500"/></p>

-----
-----

## Item 2-2: Check Edit Distance Between Two Location Names (Phase 2)


```c++
int CalculateEditDistance(std::string name1, std::string name2);
```
### **Time Complexity:O(mn) m:length of name1, n:length of name2**
_____________________________________________
**In CalculateEditDistance, we use dynamic programming to get the edit distance between two strings.**

**Hear is a 2D vector ed used to store the distance of subsets of two strings.**
|   | A | B | C |
|---|---|---|---|
| B | 0 | 0 | 0 |
| D | 0 | 0 | 0 |
| E | 0 | 0 | 0 |

**ed [i] [0] represents the distance between the first i characters of string1 and an empty string, so its value is equal to i.
We use dynamic programing to find if the string1[i-1] is equal with sring2[j-1].
If they are different, then we do insert(ed[i][j] = ed[i][j-1]+1) or delete(ed[i][j] = ed[i-1][j]+1) or repalce(ed[i][j] = ed[i-1][j-1]+1), it depends on which one could get the min value.**
______________________________________________________________

When entering a location name that does not exist in the map, your program should determine whether the input can be replaced with a "similar name" or not. By "similar names" we mean the names that exist in the map with a *smallest distance* from the original input. 

The distance between two names A and B is the minimum number of operations required to convert A to B. There are 3 operations:
+ Insert a character
+ Delete a character
+ Replace a character

If the exact match is found, it will be shown on the map. Otherwise, the map will show the most similar name by using FindClosestName and print a warning. 

For example, if I type *Rolphs*, I should get a warning like "Did you mean *Ralphs* instead of *Rolphs*?". 

Write a dynamic programming solution to calculate edit distance. 
Time Complexity:O(Nmn)
```c++
std::string FindClosestName(std::string name);
```

Notes:
- Space can be treated like other characters.
- Spell checking part should be case insensitive.

Example:

Input: "Rolphs", "Ralphs" \
Output: 1


In the user interface of your program, you should show the names that have the minimum edit distance to the name that the user entered.

Example 1:

Input: "Rolphs"\
Output: "Ralphs"

```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Rolphs
*************************Results******************************
No matched locations.
Did you mean Ralphs instead of Rolphs? [y/n]y
Latitude: 34.0318 Longitude: -118.291
**************************************************************
Time taken by function: 20 ms
```

Example 2:

```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Hand
*************************Results******************************
No matched locations.
Did you mean Honda instead of Hand? [y/n]y
Latitude: 34.0377 Longitude: -118.269
**************************************************************
Time taken by function: 19 ms
```

Example 3:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Hon
*************************Results******************************
No matched locations.
Did you mean Honda instead of Hon? [y/n]y
Latitude: 34.0377 Longitude: -118.269
**************************************************************
Time taken by function: 17 ms
```
-----
-----
## Item 3: Get All Categories (Phase 2)

```c++
std::vector<std::string> GetAllCategories();
```
### **Time Complexity:O(mn) m=data.size, n=number of attributes**
____________________________________________________________________________

**In GetAllCategories function, we use for loop to traversal the data set and use another for loop to traversal the all attributes.**
___________________________________________________________________________
Some of the locations have category types (`attributes` field in `data.csv` file). 

In this section, your program should print all available categories among all existing categories in the map. There should be no duplicates in the output.

## Item 4: Get All Locations In A Category (Phase 2)
Example 1:
```shell
**************************************************************
* 3. Find all location categories                             
**************************************************************

"bank", "beauty", "restaurant", "clothes", "fast_food", "car", "parking_entrance", "fuel", "car_repair", "hotel", "optician", "post_box", "place_of_worship", "cafe", "theatre", "attraction", "social_facility", "library", "pharmacy", "convenience", "museum", "tobacco", "bicycle_rental", "school", "copyshop", "supermarket", "artwork", "mobile_phone", "post_office", "shoes", "department_store", "driving_school", "hairdresser", "music", "confectionery", "bar", "police", "beverages", "parking", "food_court", "fountain", "childcare", "car_wash", "shoe_repair", "clinic", "yoga", "bicycle", "yes", "gallery", "bus_station", "parcel_locker", "dentist", "marketplace", "bakery", "charging_station", "hospital", "fabric", "skate", TrojanMap Menu
**************************************************************
```
```c++
std::vector<std::string> GetAllLocationsFromCategory(std::string category);
```

In this section if the user entries a category, the program prints all locations that match that category. For example, if there is a category called "bank", your program should print all location ids that match the "bank" category. 

---
---
## Item 5: Get Locations Using A Regular Expression (Phase 2)
### **Time Complexity:O(n)**
```c++
std::vector<std::string> GetLocationRegex(std::regex location);
```

---
**The GetLocationRegex function iterates through all the nodes in the data and applies the regex_match() function to the name of each node, comparing it with the input Regular Expression. If a match is found, the function stores the corresponding node ID in the result vector. Finally, the function returns the result vector containing all the node IDs that matched the Regular Expression.**

---

In this section if the user enters a [regular expression](https://en.wikipedia.org/wiki/Regular_expression), they should see all location ids that match that regular expression.

Your program should also verify if the input regular expression was correct. Return an empty vector if the regex is not valid or matches no items.

Example 1:
``` shell
**************************************************************
* 5. Get locations using a regular expression                 
**************************************************************

Please input a regular expression for a location:Ra.?ph.+
*************************Results******************************
2578244375
**************************************************************
Time taken by function: 41 ms
```
Example 2:
``` shell
**************************************************************
* 5. Get locations using a regular expression                 
**************************************************************

Please input a regular expression for a location:R[A-Za-z]l[A-Za-z]hs
*************************Results******************************
2578244375
**************************************************************
Time taken by function: 37 ms
```
Example 3:
``` shell
**************************************************************
* 5. Get locations using a regular expression                 
**************************************************************

Please input a regular expression for a location:Tar[A-Za-z]et
*************************Results******************************
5237417650
**************************************************************
Time taken by function: 39 ms
```
---
---

## Item 6: CalculateShortestPath between two places (Phase 2)

```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,
                                               std::string &location2_name);
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
```
**Time Complexity:**

Dijkstra: O(n^2)

Bellman_Ford: O(n^2)
_____________________________________________________________________________________
Here, we use two algrothims to calculate the shortest path between two place.

**DijKstra** 

First one is DijKstra, we use a priority_queue to store the nodes which are waiting to process. Its elements are the pairs that include distance and ID, sort by distance from smallest to largest. When the operation is empty, we do following operations:

1.Pop the top element of queue and pass its value into "loc_id".

2.Check if loc_id is equal to the target location's ID. If so, break out of the loop. Otherwise, continue with the following steps.

3.Traversal the neighboring nodes of the current node in loc_id. Calculate the distance from the current node to the neighbor node plus the distance of the current node and input it in the "update_dist". 

4.Check if the "update_dist" is less than current distance of neighbor node "i", if it dose, we update the current distance of neighbor node(node_dist[i]) with "update_dist", and set the current node with prev node of neighbor node(P[i] = loc_id). Then, we add the neighbor node into the queue.

After these operations, we add the target location's ID into the vector path.

Starting from the target location, backtrack the shortest path using the P hashmap. Add the ID of each node passed along the way to the path vector until the starting location is reached.
Reverse the path vector to display it in the correct order from the starting location to the target location.

**Bellman_Ford**

In Bellman_Ford function, we traversal map data to find the start location and set the it with distance 0, then add it into the vector "current node".

When "current node" is not empty and loop variable "round" is less than 5, we do following operations:

1.Traversal every nodes "curr_id" in the "curr_node"

2.Traversal "curr_id"'s neighbor nodes "next_id". Process every "next_id", calculate the distance between "next_id" and "curr_id", and plus with the current distance("node_dist[curr_id] + CalculateDistance(curr_id, next_id)"). This is named as "update_dist".

3.if "update_dist" is less than the distance from "next_id"("node_dist[next_id]"), we will update the neighbor node's distance as "update_dist", and set current node with the prev node of neighbor node. Then we add the neighbor node into the vector "next_node". If u is equal with next_id, then we set "dest_curr" with "update_dist".

If "dest_curr" is not equal with Infinity, then we check if "dest_curr" is equal with "dest_prev", if it is equal, we do more five loops to check if there is any other better results.
If not, we set round with 0, and set "dest_prev" with "dest_curr".

We set the "current _node" with "next_node", and then clear "next_node".

The we add the target location's ID into the path vector. Tracing back the shortest path from the target node by using the P hash map. While P[u] is not empty, set P[u] to u and add it to the path vector.

Since the order of nodes in path is from the target location to the starting location. We need do reverse operation to the path elements.

Finally, we get the shortest path from result.
____________________________________________________________________________________
Given 2 locations A and B, find the best route from A to B. The distance between 2 points is the euclidean distance using latitude and longitude. You should use both Dijkstra algorithm and Bellman-Ford algorithm. Compare the time for the different methods. Show the routes on the map. If there is no path, please return empty vector.

Please report and compare the time spent by these algorithms.

**You should create a table like below, which includes the runtime of the algorithm for several examples.**

| Point A to Point B      | Dijkstra | Bellman Ford| Bellman Ford optimized|
| -------------------- | ----------- |-------|-----|
|                      |  t1         | t2    |   t3  |
|Chase->KFC             |   52ms      | 68ms     |68ms
|Chase->Bank of America             | 66ms        |68ms  |68ms
|KFC->Bank of America             | 72ms        |83ms  |83ms
|Honda->KFC             | 74ms        |304ms  |304ms
|Holbox->Target             |85ms        |358ms  |358ms
|Honda->Ralphs             | 100ms        |301ms  |301ms
|Honda->Target             | 111ms        |410ms  |410ms
|Honda->Bank of America             | 120ms        |473ms  |473ms
|Target->Shell             | 134ms        |524ms  |524ms
|Honda->Shell             | 145ms        |823ms  |823ms
|Chase->Ralphs    |    129ms       |  501ms   |501ms
|  Target->Ralphs           |    103ms      |  130ms   |130ms
|  KFC->Shell           |      157ms    |   595ms  |595ms
|  Chase->Shell           |    159ms      | 415ms    |415ms
|  Chase->Honda           |   135ms       |  718ms   |718ms

Your table should show have at least 15 rows.

Example
```
**************************************************************
* 6. CalculateShortestPath                                    
**************************************************************

Please input the start location:Ralphs
Please input the destination:Target
*************************Dijkstra*****************************
*************************Results******************************
"2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131","7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705","6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011","6816193692","6816193693","6816193694","4015377691","544693739","6816193696","6804883323","6807937309","6807937306","6816193698","4015377690","4015377689","122814447","6813416159","6813405266","4015372488","4015372487","6813405229","122719216","6813405232","4015372486","7071032399","4015372485","6813379479","6813379584","6814769289","5237417650",
The distance of the path is:0.927969 miles
**************************************************************
Time taken by function: 39 ms

*************************Bellman_Ford*************************
*************************Results******************************
"2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131","7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705","6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011","6816193692","6816193693","6816193694","4015377691","544693739","6816193696","6804883323","6807937309","6807937306","6816193698","4015377690","4015377689","122814447","6813416159","6813405266","4015372488","4015372487","6813405229","122719216","6813405232","4015372486","7071032399","4015372485","6813379479","6813379584","6814769289","5237417650",
The distance of the path is:0.927969 miles
**************************************************************
Time taken by function: 7084 ms
```

<p align="center"><img src="img/Routing.png" alt="Routing" width="500"/></p>

---
---
## Item 7: Cycle Detection (Phase 2)

```c++
bool CycleDetection(std::vector<double> &square);
```
### **Time Complexity:O(mn) m:subgraph.size n:data.size**
____________

**In CycleDection function, we traversal the subgraph, checking if each node is a named location in data. If we find more than 2 named locations, we judge that there is cycle in subgraph.**
____________
In this section, we use a square-shaped subgraph of the original graph by using four coordinates stored in ```std::vector<double> square```, which follows the order of left, right, upper, and lower bounds. 

Then try to determine if there is a cycle path in the that subgraph.
If it does, return true and report the path of the cycle on the map. Otherwise return false.

**Your report should include at least five examples.**

Example 1:
```shell
Input: square = {-118.299, -118.264, 34.032, 34.011}
Output: true

**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.299
Please input the right bound longitude(between -118.320 and -118.250):-118.264
Please input the upper bound latitude(between 34.000 and 34.040):34.032
Please input the lower bound latitude(between 34.000 and 34.040):34.011
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 2759 ms
```
Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle1.png" alt="TSP" width="500"/></p>

Example 2:
```shell
Input: square = {-118.290, -118.289, 34.030, 34.020}
Output: false
```
Here we use a square area inside USC campus as our subgraph
<p align="center"><img src="img/cycle2.png" alt="TSP" width="500"/></p>

```shell
**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.290
Please input the right bound longitude(between -118.320 and -118.250):-118.289
Please input the upper bound latitude(between 34.000 and 34.040):34.03
Please input the lower bound latitude(between 34.000 and 34.040):34.02
*************************Results******************************
there exist no cycle in the subgraph 
**************************************************************
Time taken by function: 23 ms
```

Example 3:
```shell
Input: square = {-118.3004, -118.3001573, 34.03456733, 34.0}
Output: true
```
Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle3.png" alt="TSP" width="500"/></p>

```shell
**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.3004000
Please input the right bound longitude(between -118.320 and -118.250):-118.3001573
Please input the upper bound latitude(between 34.000 and 34.040):34.0346733
Please input the lower bound latitude(between 34.000 and 34.040):34.0
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 37 ms
```

Example 4:

```shell
Input: square = {-118.290, -118.285, 34.038, 34.01}
Output: true
```

Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle4.png" alt="TSP" width="500"/></p>

```shell
**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.290
Please input the right bound longitude(between -118.320 and -118.250):-118.285
Please input the upper bound latitude(between 34.000 and 34.040):34.038
Please input the lower bound latitude(between 34.000 and 34.040):34.01
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 525 ms
```

Example 5:
```shell
Input: square = {-118.299, -118.27, 34.03, 34.02}
Output: true
```

Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle5.png" alt="TSP" width="500"/></p>

```shell
**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.299
Please input the right bound longitude(between -118.320 and -118.250):-118.27
Please input the upper bound latitude(between 34.000 and 34.040):34.03
Please input the lower bound latitude(between 34.000 and 34.040):34.02
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 1020 ms
```

Example 6:

```shell
Input: square = {-118.300, -118.288, 34.02, 34.03}
Output: false
```

Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle6.png" alt="TSP" width="500"/></p>

```shell
**************************************************************
* 7. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.300
Please input the right bound longitude(between -118.320 and -118.250):-118.288
Please input the upper bound latitude(between 34.000 and 34.040):34.02
Please input the lower bound latitude(between 34.000 and 34.040):34.03
*************************Results******************************
there exist no cycle in the subgraph 
**************************************************************
Time taken by function: 0 ms
```
----
----
## Item 8: Topological Sort (Phase 2)

```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```
### **Time Complexity:O(n^2)**

_____________________
**In Topological Sort function, we traversal "dependencies" to find the indices d_1 and d_2 of the two locations in the result vector. If the index d_1 is greater than d_2, we can get that the current order of locations are not satisfy the dependencies, for this situation, we will switch the locaiton in the vector "result" and setting "finish" to false to indicate there is at least one location's place in order do not satisfy the dependencies. After the loop, we could get the locations in expected order.**
_____________________
In this section, we assume that we are using a UAV which means we can fly directly from 1 point to another point. Tommy Trojan got a part-time job from TrojanEats, for which he needs to pick up and deliver food from local restaurants to various location near the campus. Tommy needs to visit a few different location near the campus with certain order, since there are some constraints. For example, he must first get the food from the restaurant before arriving at the delivery point. 

The TrojanEats app will have some instructions about these constraints. So, Tommy asks you to help him figure out the feasible route!

Here we will give you a vector of location names that Tommy needs to visit, and also some dependencies between those locations.


For example, s
Input: 
location_names = {"Ralphs", "Chick-fil-A", "KFC"}
dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"Chick-fil-A", "KFC"}}
```

Here, ```{"Ralphs","KFC"}``` means
that Tommy must go to `Ralphs` prior to `KFC`.

Your output should be:
```shell
Output: Ralphs  -> Chick-fil-A -> KFC
```
Also, we provide ```PlotPointsOrder``` function that can visualize the results on the map. It will plot each location name and also some arrowed lines to demonstrate a feasible route.

If no feasible route exists, you could simply return an empty vector.

Hint:
- You also need to finish ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions, so you could read and parse data from you own CSV files. We also give two sample CSV files under ```input``` folder, which could be a reference. 
- When it asks you filenames, you need to give the absolute path.
- If you do not have ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions ready yet, you can just press enter when it asks you filenames. It will call the default locations and dependencies.
- The locations are actually nodes, and the dependencies could be directed edges. You may want to first construct a DAG and then implement topological sort algorithm to get the route.

Note
- **Your report should show several examples of topological sort with at least 5 to 10 nodes.**


Below is an example output of 3 nodes
```shell
*************************Results******************************
Topological Sorting Results:
Ralphs
Chick-fil-A
KFC
**************************************************************
Time taken by function: 2 ms
```
<p align="center"><img src="img/TopologicalSort.png" alt="TSP" width="500"/></p>

In the user interface, we read the locations and dependencies from `topologicalsort_dependencies.csv` and `topologicalsort_locations.csv` to modify your input there.

Example1:
```shell
*************************Results******************************
Topological Sorting Results:
Ralphs
Bank of America
KFC
Chick-fil-A
**************************************************************
Time taken by function: 0 ms
```
<p align="center"><img src="img/TopologicalSort1.png" alt="TSP" width="500"/></p>

Example2:
```shell
*************************Results******************************
Topological Sorting Results:
Ralphs
Bank of America
Target
Chick-fil-A
KFC
**************************************************************
Time taken by function: 0 ms
```
<p align="center"><img src="img/TopologicalSort2.png" alt="TSP" width="500"/></p>

Example3:
```shell
*************************Results******************************
Topological Sorting Results:
Honda
Bank of America
Target
Chick-fil-A
KFC
Ralphs
**************************************************************
Time taken by function: 0 ms
```
<p align="center"><img src="img/TopologicalSort3.png" alt="TSP" width="500"/></p>

---
---

## Item 9: The Traveling Trojan Problem (AKA Traveling Salesman!) (Phase 3)

In this section, we assume that we are using a UAV which means we can fly directly from 1 point to another point. Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph).
Find the shortest route that covers all the locations exactly once and goes back to the start point. 

You will need to return the progress to get the shortest route which will then be converted to an animation.  

We will use the following algorithms:

- Brute-force (i.e. generating all permutations, and returning the minimum)
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Brute_force(
      std::vector<std::string> location_ids);
```
Time Complexity: O(n)

- Brute-force enhanced with early backtracking
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_Backtracking(
      std::vector<std::string> location_ids);
```
Time Complexity:O(n)

- [2-opt Heuristic](https://en.wikipedia.org/wiki/2-opt). Also see [this paper](http://cs.indstate.edu/~zeeshan/aman.pdf)
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravelingTrojan_2opt(
      std::vector<std::string> location_ids);
```
Time Complexity:O(1)

We use early backtracking when the current cost is higher than current minimum.

Please report and compare the time spent by these 3 algorithms. 2-opt algorithm may not get the optimal solution. Please show how far your solution is from the optimal solution.

Show the routes on the map. For each intermediate solution, create a new plot. Your final video presentation should include the changes to your solution.

We will randomly select N points in the map and run your program.

```shell
**************************************************************
* 9. Traveling salesman problem                              
**************************************************************

In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.

Please input the number of the places:8
"6807927343","1614922716","6790236614","304903656","3659478911","2873934661","7811845041","703503312",
Calculating ...
*************************Results******************************
TravelingTrojan_Brute_force
"6807927343","304903656","6790236614","703503312","2873934661","7811845041","1614922716","3659478911","6807927343",
The distance of the path is:10.2329 miles
**************************************************************
You could find your animation at src/lib/output0.avi.          
Time taken by function: 215 ms

Calculating ...
*************************Results******************************
TravelingTrojan_Backtracking
"6807927343","304903656","3659478911","1614922716","7811845041","2873934661","703503312","6790236614","6807927343",
The distance of the path is:10.6679 miles
**************************************************************
You could find your animation at src/lib/output0_backtracking.avi.
Time taken by function: 736 ms

Calculating ...
*************************Results******************************
TravelingTrojan_2opt
"6807927343","3659478911","304903656","6790236614","703503312","2873934661","7811845041","1614922716","6807927343",
The distance of the path is:11.3332 miles
**************************************************************
You could find your animation at src/lib/output0_2opt.avi.     
Time taken by function: 2 ms
```

<p align="center"><img src="img/TSP.png" alt="TSP" width="500"/></p>

<p align="center"><img src="img/output.gif" alt="TSP videos" width="500"/></p>

| nums of nodes     | Brute_force | Backtracking| 2opt|
| -------------------- | ----------- |-------|-----|
|10             |14629ms|79056ms|2ms
|9             |1582ms|7325ms|1ms
|8             |   215ms      | 736ms     |2ms
|7             | 50ms        |85ms  |1ms
|6             | 5ms        |13ms  |1ms
|5             | 0ms        |0ms  |1ms

---
---

## Item 10: Find Nearby (Phase 3)

Given an attribute name `C`, a location name `L` and a number `r` and `k`, find at most `k` locations in attribute `C` on the map near `L`(do not include `L`) with the range of `r` and return a vector of string ids. 

The order of locations should be from
nearest to farthest, and you should not include the current location. 

```c++
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k);
```

### **Time Complexity:O(n^2) n: size of data**

_________________________________

**In this function, we traversal the data nodes, for each node, we check if there exists the location with same attributeName with input, and check if the location is inside the circle with the input search radius "r" based on origin "input location". Then we input all location we found into the set loc to order them in distance from close to far. Finally we pick k most close locations to output the result.**
________________________________

All attributes:
```
'artwork', 'attraction', 'bakery', 'bank', 'bar', 'beauty', 'beverages', 'bicycle', 'bicycle_rental', 'bus_station', 
'cafe', 'car', 'car_repair', 'car_wash', 'charging_station', 'childcare', 'clinic', 'clothes', 'confectionery', 
'convenience', 'copyshop', 'dentist', 'department_store', 'driving_school', 'fabric', 'fast_food', 'food_court', 
'fountain', 'fuel', 'gallery', 'hairdresser', 'hospital', 'hotel', 'library', 'marketplace', 'mobile_phone', 'museum', 
'music', 'optician', 'parcel_locker', 'parking', 'pharmacy', 'place_of_worship', 'police', 'post_office', 
'restaurant', 'school', 'shoe_repair', 'shoes', 
'skate', 'social_facility', 'supermarket', 'theatre', 
'tobacco', 'yes', 'yoga'
```


Please report and compare the time spent by this algorithm and show the points on the map.

Example1:
```shell
**************************************************************
* 10. Find Nearby                                              
**************************************************************

Please input the attribute:bank
Please input the locations:Ralphs
Please input radius r:10
Please input number k:10
*************************Results******************************
Find Nearby Results:
1 USC Credit Union
2 Bank of America
3 Chase
**************************************************************
Time taken by function: 60 ms
```
<p align="center"><img src="img/NearBby2.png" alt="Nearby2" width="500"/></p>


Example2:
```shell
**************************************************************
* 10. Find Nearby                                              
**************************************************************

Please input the attribute:bank
Please input the locations:Target
Please input radius r:10
Please input number k:10
*************************Results******************************
Find Nearby Results:
1 Bank of America
2 USC Credit Union
3 Chase
**************************************************************
Time taken by function: 78 ms
```
<p align="center"><img src="img/NearBby3.png" alt="Nearby3" width="500"/></p>

--------
--------
## Item 11: Find the Shortest Path to Visit All locations (Phase 3)

Given an vector of locations, you need to find the shortest path to visit all the locations.

```c++
std::vector<std::string> TrojanMap::TrojanPath(std::vector<std::string> &location_names)
```

<<<<<<< HEAD
### **Time Complexity:O(n!+R(SD+L)) R:the number of routes, S:the number of max number of nodes on route, D: the time complexity CalculateShortestPath_Dijkstra which is N^2, N: the number of nodes **

---
**In the TrojanPath function, we first use the FindAllRoute function to generate all possible route combinations. Then, we use CalculateShortestPath_Dijkstra to compute the distance of each combination and update the path with the shortest distance. Finally, we return the path with the shortest distance as a vector of node.**

---
=======
### **Time Complexity:O(n!+R(SD+1)) R:the number of routes, S:the number of max number of nodes on route D:N^2 the time complexity CalculateShortestPath_Dijkstra, N is the number of nodes **

>>>>>>> 7410abeceee621e9ee1bbe2be9e0c3262f27aa47

Please report and compare the time spent by this algorithm and show the points on the map.

Example1:

```shell
**************************************************************
* 11. Shortest Path to Visit all Nodes                        
**************************************************************

Please input the locations filename:
*************************Results******************************
"3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305","6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831","6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544","6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620","4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864","6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101","6814916516","6814916515","6820935910","4547476733","6820935910","6814916515","6814916516","1837212101","6813411588","4015372458","1837212100","6820935907","2753199985","1837212107","1837212104","4015405543","4015405542","1781230449","1781230450","6820935898","6813379556","6820935901","6820935900","6819179753","4540763379","3233702827","1862347583","5231967015","4399697302","4399697304","6807762271","122728406","6787673296","123209598","6814958391","4399697589","4872897515","602606656","3402887080","6814958394","3402887081","6813379483","6813379589","6352865690","4015203127","4015203129","3195897587","4015203132","6389467809","21098539","4015203133","4015203134","4015203136","123152294","6816193786","6816193785","6808069740","6813416155","6813416151","6813416152","6813416153","6813416154","6813416145","7232024780","6818427916","6818427917","6818427898","6818427892","6818427918","6818427919","6818427920","4380040148","4380040152","4380040153","4380040154","2578244375",
The distance of the path is:2.26759 miles
Time taken by function: 233 ms
```

<p align="center"><img src="img/all.png" alt="All" width="500"/></p>

Example2: Ralphs->KFC->Chick-fil-A->Bank of America->Target->Honda
```shell
**************************************************************
* 11. Shortest Path to Visit all Nodes                        
**************************************************************

Please input the locations filename:/home/root123/spring2023_trojanmap-WenzhePan/input/topologicalsort_locations.csv
*************************Results******************************
"5695174696","8898278793","4687981681","6788402762","5344542585","122665888","5344542584","7852039556","122665893","6816950650","6816950651","122665895","7863404959","7863404958","7863404960","7863404957","7863404956","7863404955","7863404954","7863404953","7863404952","7863404951","7863404950","7863404949","7863404948","7863404947","4012864457","7362236512","123241952","7362236521","123241955","123241958","6787830199","6787830192","123161907","4011837239","6817111153","8501336167","1832234141","4258846991","1832234142","6816193810","1832234144","122454252","6816959863","6816959869","5680944620","5680944619","6813565325","3398621871","6813565323","3403035498","6816193705","5556118325","5680945525","7693467754","3403035499","6813513563","4147565192","4835551080","3403034587","4835551089","8397480749","3403034588","6813565312","4835551101","4835551097","4835551100","3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305","6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831","6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544","6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620","4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864","6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101","6814916516","6814916515","6820935910","4547476733","6820935910","6814916515","6814916516","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280","348121864","348121996","6813405275","1732243544","6819179749","4015372463","4015372469","1732243620","6814916523","6813379550","4399697300","4399697301","4399697303","5580881629","122844997","2738332817","1673644724","2738332818","1673645147","123153544","5580883117","1472141961","2776870269","6814770345","5580882852","2776870272","6814770342","4536993735","3431300454","6814770351","3432332948","4536989636","3433701978","6818390136","6813379491","3443310465","4536989640","4536989637","6813379432","3402887075","6813379464","6813379465","6813379466","6813379467","6813360936","6813360951","6813379420","6813360952","6813360954","6814620882","6813360960","5237417651","6813360960","6813379480","6813360961","6813379584","6814769289","5237417650","6814769289","6813379584","6813379479","4015372485","7071032399","4015372486","6813405232","122719216","6813405229","4015372487","4015372488","6813405266","6813416159","122814447","4015377689","4015377690","6816193698","6807937306","6807937309","6804883323","6816193696","544693739","4015377691","6816193694","6816193693","6816193692","4015442011","6787470576","6816193770","123230412","452688931","452688933","6816193774","123408705","6816193777","452688940","123318563","6813416129","6813416130","7645318201","6813416131","8410938469","6805802087","4380040167","4380040158","4380040154","2578244375",
The distance of the path is:3.50572 miles
Time taken by function: 236335 ms
```

<p align="center"><img src="img/all2.png" alt="All" width="500"/></p>

Example3:Ralphs->KFC->Chick-fil-A->Bank of America->Target 
```shell
*************************Results******************************
"4547476733","6820935910","6814916515","6814916516","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280","348121864","348121996","6813405275","1732243544","6819179749","4015372463","4015372469","1732243620","6814916523","6814916522","6813379547","6813379546","6813379536","6813379545","6813379544","6813379495","6813379494","3398574883","6813565327","3402810298","6813379501","3402814831","6813379533","6813379403","4835551107","3402814832","6813565296","6813565295","6813565305","6813565306","6813565307","4835551098","4835551099","4835551100","3088547686","4835551100","4835551097","4835551101","4835551096","2613117890","2613117915","4835551105","6813565334","2613117867","6787803635","6807905595","6813379406","2613117879","3398578893","3398574892","6813565290","3398578898","6813379398","6813379505","6813379519","4399698005","6813379511","6813379513","6813379512","4399698004","3398582608","4399698007","3398582607","6813379481","6813379480","6813360960","5237417651","6813360960","6813379480","6813360961","6813379584","6814769289","5237417650","6814769289","6813379584","6813379479","4015372485","7071032399","4015372486","6813405232","122719216","6813405229","4015372487","4015372488","6813405266","6813416159","122814447","4015377689","4015377690","6816193698","6807937306","6807937309","6804883323","6816193696","544693739","4015377691","6816193694","6816193693","6816193692","4015442011","6787470576","6816193770","123230412","452688931","452688933","6816193774","123408705","6816193777","452688940","123318563","6813416129","6813416130","7645318201","6813416131","8410938469","6805802087","4380040167","4380040158","4380040154","2578244375",
The distance of the path is:2.288 miles
Time taken by function: 26272 ms
```
<p align="center"><img src="img/all3.png" alt="All" width="500"/></p>

---
---

## Item 12: Check the existence of the path with a constrained gas tank (Phase 3)

### **Time Complexity: O((V+E)N) N:size of list of queries V:number of nodes in pathbool, E:number of egdes in pathbool**

---
**The Queries formula utilizes a strategy similar to the Bellman-Ford algorithm. The approach is to traverse the nodes from the starting point, and explore each node that can be reached within the fuel tank's volume until the end point is reached. Unlike the Bellman-Ford algorithm, we use a recursive function to traverse each node and halt as soon as we locate the end point. This strategy leads to faster processing times compared to Bellman-Ford algorithm.**

---


Given a map of nodes, you need to determine if it is possible to travel from a given starting point to a destination point with a car that has a certain size of gas tank. You can refuel at any nodes. If the distance between any two nodes on the path is larger than the size of the gas tank, you cannot travel between those nodes. Assume 1 gallon of gas can travel 1 mile.

Your task is to implement a function that takes in multiple queries and specifies if travelling between the two points of each query with the given gas tank is possible. Each query is a pair, `std::pair<double, std::vector<std::string>>`,  consisting of the size of the gas tank and the starting and destination points as a vector of strings. The function should return a vector of bools indicating whether or not a path exists for each query. If a location specified in a query does not exist in the map, the function should return false.

- If you could implement by [Union Find](https://en.wikipedia.org/wiki/Disjoint-set_data_structure), you could get 10 points.
Otherwise, you get 8 points.
- **Hint:**: While you can calculate the result of each query separately, it might be more optimal to use the result of one query to decide about other queries.


```c++
// Takes in a vector of queries. Each query consists of a pair: <tank_capacity, [source, destination]>.
// Returns the result of each query in a vector.
std::vector<bool> Queries(const std::vector<std::pair<double, std::vector<std::string>>> &q);
```
### **Time Complexity: O((V+E)N) N:size of list of queries V:number of nodes in pathbool, E:number of egdes in pathbool**
Please report and compare the time spent by this algorithm and show the points on the map.

**Example:**
Suppose you have a map with the following nodes:

<p align="center"><img src="img/graph.png" alt="Graph" width="500"/></p>

```css
1 - 2 (distance = 2)
1 - 3 (distance = 3)
2 - 3 (distance = 1)
2 - 4 (distance = 4)
3 - 4 (distance = 1)
```

Suppose the queries are:
```arduino
(1.5, {"1", "4"})
(2.5, {"1", "4"})
(3.5, {"1", "4"})
(4.5, {"1", "4"})
(3.0, {"2", "3"})
(3.0, {"3", "1"})
(2.0, {"1", "5"})
```
For each query, you need to determine whether or not it is possible to travel from the starting point to the destination point using a car with the given gas tank size.

The expected output for this example is:

```cpp
{
 false,
 true,
 true,
 true,
 true,
 true,
 false
}
```

Note that for the first query, it is not possible to travel from 1 to 4 using a car with a gas tank size of 1.5. There are four paths from 1 to 4: 1-2-4, 1-3-4, 1-2-3-4, and 1-3-2-4. Since the gas tank size is 1.5, you can not travel from 1 to 3 or 1 to 2. Therefore, the function should return false.

For the second query, if we want to travel from 1 to 4 using a car with a gas tank size of 2.5, we can refuel at 2, 3. Since 1->2 = 2 <= 2.5,  2->3 = 1 <= 2.5, 3->4=1 <= 2.5, we should return true! The problem is to make sure that the maximum distance between any two nodes on the path should be smaller than or equal to the size of the gas tank!

For the thrid query, it is possible to travel from 1 to 4 using a car with a gas tank size of 3.5. The maximum distance between two nodes on the path 1-3-4 is 3, which is smaller than the gas tank size. For the last query, 5 does not exist in the map, so the function should return false.

Another example where the inputs are read from your program's UI:
We use the whole map near USC as the graph! For example, if we want to start from Target to Ralphs, there are a lot of nodes on the path. We want to make sure that the distance between any two nodes on the path is smaller than the size of the gas tank! For dummy, it means if the location does not exist, we should return false.
Example1:
```shell
**************************************************************
* 12. Check Exist of Path with Constrain                      
**************************************************************

Please input the start location:Target
Please input the destination:Ralphs
Please input the volumn of the gas tank:0.05
More Query? (y/n)y
Please input the start location:Ralphs
Please input the destination:Target 
Please input the volumn of the gas tank:0.01
More Query? (y/n)y
Please input the start location:KFC
Please input the destination:Target
Please input the volumn of the gas tank:0.02
More Query? (y/n)y
Please input the start location:dummy
Please input the destination:dummy
Please input the volumn of the gas tank:999
More Query? (y/n)n
*************************Results******************************
From Target to Ralphs with 0.05 gallons of gas tank: Yes
From Ralphs to Target with 0.01 gallons of gas tank: No
From KFC to Target with 0.02 gallons of gas tank: No
From dummy to dummy with 999 gallons of gas tank: No
**************************************************************
Time taken by function: 239 ms
```
Example2:
```shell
**************************************************************
* 12. Check Exist of Path with Constrain                      
**************************************************************

Please input the start location:Target
Please input the destination:Ralphs
Please input the volumn of the gas tank:0.1
More Query? (y/n)y
Please input the start location:Ralphs
Please input the destination:Target
Please input the volumn of the gas tank:0.01
More Query? (y/n)y
Please input the start location:Honda
Please input the destination:Target
Please input the volumn of the gas tank:0.6
More Query? (y/n)y
Please input the start location:Ralphs
Please input the destination:Honda 
Please input the volumn of the gas tank:0.5
More Query? (y/n)n
*************************Results******************************
From Target to Ralphs with 0.1 gallons of gas tank: Yes
From Ralphs to Target with 0.01 gallons of gas tank: No
From Honda to Target with 0.6 gallons of gas tank: Yes
From Ralphs to Honda with 0.5 gallons of gas tank: Yes
**************************************************************
Time taken by function: 518095 ms
```

## Reporting Runtime:
For each menu item, your program should show the time it took to finish each task.

Please make sure to provide various examples when you report the runtime. For example for topological sort, show an example with few nodes and another example with 10 or more nodes. The idea is to see how your runtime grows as input size grows.

## Runtime Comparison
For shortest path algorithms, you should compare solving the same problem with different algorithms (Dijkstra and Bellman-Ford). 
Please show the results on at least 3 different examples.

Similarly for the TSP problem, please provide various examples that show the runtime comparison. In particular, you should show at what point using the exhaustive search is not practical and compare the same input with the heuristic implementation.

**Please provide a table like below that compares the runtime of your algorithms for different number of nodes:**

| Number of nodes      | Time with algorithm 1 | Time wit6h algorithm 2|
| -------------------- | ----------- |----|
|Chase->KFC             |   370ms      | 55ms     |
|Chase->Ralphs    |    2851ms       |  559ms   |
|  Target->Ralphs           |    1783ms      |  129ms   |
|  KFC->Shell           |      5180ms    |   624ms  |
|  Chase->Shell           |    1913ms      | 478ms    |
|  Chase->Honda           |   3291ms       |  858ms   |

Your table should show have at least 15 rows.

## Report and Rubrics:

Your final project should be checked into Github. The [README.md](README.md) of your project is your report. 

### Report:

Your REPORT.md file should include four sections:
Please create a new REPORT.md file and write your report there.

1. High-level overview of your design (Use diagrams and pictures for your data structures).
2. Detailed description of each function and its time complexity.
3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.

### Rubrics:

Phase 1: 2 points
- Item 1 (AutoComplete): 1 point. (Phase 1)
- Item 2-1 (GetPosition): 1 point. (Phase 1)

Phase 2: 38 points
- Item 2-2 (EditDistance): 5 points. (Phase 2)
- Item 3 (GetAllCategories): 3 Points. (Phase 2)
- Item 4 (GetAllLocationsFromCategory): 2 Points. (Phase 2)
- Item 5 (GetLocationRegex): 3 Points. (Phase 2)
- Item 6 (Shortest path): 15 points. (Phase 2)
   - Bellman-Ford implementation
   - Dijkstra implementation
   - Table/Plot for comparison, and measure and report time spent by two algorithms.
- Item 7 (Cycle detection): 5 points. (Phase 2)
   - Boolean value and draw the cycle if there exists one.
- Item 8 (Topological Sort): 5 points (Phase 2)
   - Check whether there exist a topological sort or not
   - Return the correct order and plot those point on the map

Phase 3: 60 points
- Item 9 (Traveling Trojan) (Phase 3)
   - Brute-force: 5 points.
   - Brute-force enhanced with early backtracking: 5 points.
   - 2-opt: 5 points.
   - Animated plot in the report.
- Item 10 (Find Nearby): 5 points. (Phase 3)
   - Return the correct nearby results.
- Item 11 (TrojanPath): 10 points. (Phase 3)
   - Return the correct ids and draw the points.
- Item 12 (CheckPath): 10 points. (Phase 3)
   - Return the correct output.
- Video presentation and report: 10 points. (Phase 3)
https://youtu.be/_tnvSLdy9gY
- Creating reasonable unit tests: 10 points.
      - Three different unit tests for each function.
## Extra credit items: Maximum of 20 points:
   1. Implementation of [3-opt](http://cs.indstate.edu/~zeeshan/aman.pdf): 10 points.
   2. [Genetic algorithm](https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/) implementation for Traveling Trojan: 10 points
   3. Create dynamic and animated UI using [ncurses](https://en.wikipedia.org/wiki/Ncurses): 10 points
      - Uncomment #define NCURSES in main.cc and mapui.h
      - Create your menu in DynamicPrintMenu().
      - You could check https://github.com/ourarash/ncurses_bazel
      - Please develope your own UI.
      - Example
         <p align="center"><img src="img/ncurses example.gif" alt="example" width="500"/></p>
               
   4. Accurate measurement of your algorithm runtime using [Google Benchmark](https://www.youtube.com/watch?v=9VKR8u9odrA) while sweeping the input size and providing a diagram of how the runtime grows based on the input size: 10 points.

