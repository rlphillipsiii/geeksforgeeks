/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/knight-walk/0

Given a chess board of order N x M and source points (s1, s2) and destination points 
(d1, d2). The task to find minimum number of moves required by the Knight to go to the 
destination cell.

Input:
The first line of input contains an integer T denoting the number of testcases. Then T 
test cases follow. Each test case contains two lines. The first line of each testcase 
contains two space separated integers N and M. Then in the next line are four space 
separated values s1, s2 and d1, d2.

Output:
For each testcase in a new line print the minimum number of moves required by the knight 
to go to the destination from the source. If no such move is possible print -1. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <utility>
#include <vector>
#include <list>
#include <unordered_set>
#include <queue>

using std::ifstream;
using std::string;
using std::istream;
using std::pair;
using std::vector;
using std::list;
using std::unordered_set;
using std::queue;

typedef pair<int, int> Cell;

typedef vector<vector<list<Cell>>> AdjacencyList;

struct PHash {
    inline size_t operator()(const Cell & cell) const {
        return ((cell.first * 31) + cell.second);
    }
};

bool isValid(const Cell & cell, int rows, int cols)
{
    if ((cell.first < 0) || (cell.first >= rows))   { return false; }
    if ((cell.second < 0) || (cell.second >= cols)) { return false; }

    return true;
}

AdjacencyList buildGraph(int rows, int cols)
{
    AdjacencyList graph;
    graph.resize(rows);
    
    for (int i = 0; i < rows; i++) {
        graph[i].resize(cols);
        
        for (int j = 0; j < cols; j++) {
            graph[i][j] = {
                { i + 1, j + 2 }, { i + 1, j - 2 }, { i - 1, j + 2 }, { i - 1, j - 2 },
                { i + 2, j + 1 }, { i - 2, j + 1 }, { i + 2, j - 1 }, { i - 2, j - 1 },                
            };
        }
    }
    
    return graph;
}

int findMoves(
    const AdjacencyList & graph,
    const Cell & start,
    const Cell & end)
{
    int rows = graph.size();
    int cols = graph[0].size();

    unordered_set<Cell, PHash> visited;

    queue<pair<int, Cell>> next;
    next.push({ 0, start });

    while (!next.empty()) {
        const auto & entry = next.front();

        int depth    = entry.first;
        Cell current = entry.second;

        next.pop();

        if (!isValid(current, rows, cols) || (visited.find(current) != visited.end())) {
            continue;
        }

        if ((current.first == end.first) && (current.second == end.second)) {
            return depth;
        }
        
        for (const Cell & cell : graph[current.first][current.second]) {
            next.push({ depth + 1, cell });
        }
        visited.insert(current);
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
    
    int n = static_cast<int>(std::atoi(temp.c_str()));
    while (n--) {
        int rows, cols;

        file >> cols;
        file >> rows;

        std::getline(file, temp);

        Cell start, finish;

        file >> start.second;
        file >> start.first;

        file >> finish.second;
        file >> finish.first;

        std::getline(file, temp);

        AdjacencyList graph = buildGraph(rows, cols);

        start.first--; start.second--; finish.first--; finish.second--;
        
        std::cout << findMoves(graph, start, finish) << std::endl;
    }
    
    return 0;
}
