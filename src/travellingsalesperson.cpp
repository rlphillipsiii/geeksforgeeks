/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/travelling-salesman-problem/0

Given a matrix M of size N where M[i][j] denotes the cost of moving from city i to city 
j. Your task is to complete a tour from the city 0 (0 based index) to all other cities 
such that you visit each city atmost once and then at the end come back to city 0 in 
min cost.

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test 
cases follow. Each test case contains an integer N denoting the size of the matrix then 
in the next line are N*N space separated values of the matrix M.
 
Output:
For each test case print the required result denoting the min cost of the tour in a new 
line. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>
#include <memory>

using std::ifstream;
using std::string;
using std::istream;
using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::function;
using std::shared_ptr;

struct Route {
    int city;
    int distance;

    unordered_set<int> visited;
    vector<int> cities;
    
    Route(int c, int d) : city(c), distance(d) { }
    Route(int c, int d, const unordered_set<int> & v)
        : city(c), distance(d), visited(v) { }
    ~Route() { }
};

typedef shared_ptr<Route> RoutePtr;

struct Compare {
    inline bool operator() (const RoutePtr & a, const RoutePtr & b)
    {
        return (a->distance == b->distance) ?
            (a->visited.size() < b->visited.size()) : (a->distance > b->distance);
    }
};

typedef priority_queue<RoutePtr, vector<RoutePtr>, Compare> RouteQueue;

int route(const vector<vector<int>> & matrix)
{
    RouteQueue routes;
    routes.push(RoutePtr(new Route(0, 0)));

    while (!routes.empty()) {
        RoutePtr route = routes.top();
        if (route->visited.size() == matrix.size()) {
            return route->distance;
        }
        routes.pop();

        int city = route->city;
        for (int i = 0; i < int(matrix[city].size()); i++) {
            int distance = matrix[city][i];
            
            if (0 == distance) { continue; }
            if ((0 == i) && (route->visited.size() != (matrix.size() - 1))) { continue; }
            if (route->visited.find(i) != route->visited.end()) { continue; }

            RoutePtr newRoute(new Route(i, route->distance + distance, route->visited));
            newRoute->visited.insert(i);

            newRoute->cities = route->cities;
            newRoute->cities.push_back(i);
            
            routes.push(newRoute);
        }
    }

    return -1;
}

int main(int, char **)
{
#ifdef LOCAL
    ifstream file(INPUT_FILE);
#else
    istream & file = std::cin;
#endif

    string temp;
    std::getline(file, temp);

    int n = int(std::atoi(temp.c_str()));
    while (n--) {
        std::getline(file, temp);
        int dimension = int(std::atoi(temp.c_str()));

        vector<vector<int>> matrix;
        matrix.reserve(dimension);
        
        for (int i = 0; i < dimension; i++) {
            matrix.push_back(vector<int>(dimension));
                             
            for (int j = 0; j < dimension; j++) {
                file >> matrix[i][j];
            }
        }

        std::cout << route(matrix) << std::endl;

        std::getline(file, temp);
    }
    
    return 0;
}
