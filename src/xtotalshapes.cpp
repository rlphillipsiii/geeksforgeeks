/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/x-total-shapes/0

Given N * M string array of O's and X's. The task is to find the number of 'X' total 
shapes. 'X' shape consists of one or more adjacent X's (diagonals not included).

Input: The first line of input takes the number of test cases T. Then T test cases 
follow. Each of the T test cases takes 2 input lines. The first line of each test 
case have two integers N and M.The second line of N space separated strings follow 
which indicate the elements in the array.

Output:
For each testcase, print number of shapes. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_set>

using std::ifstream;
using std::string;
using std::istream;
using std::istringstream;
using std::vector;
using std::list;
using std::pair;
using std::unordered_set;

typedef vector<list<int>> AdjacencyList;

class TotalShapes {
public:
    TotalShapes(istream & stream, int rows, int cols);

    int count();
    
private:
    int m_rows;
    int m_cols;

    vector<vector<pair<char, int>>> m_matrix;

    AdjacencyList m_graph;

    inline bool isValid(int row, int col) const
    {
        return ((row >= 0) && (row < m_rows) && (col >= 0) && (col < m_cols));
    }

    inline int index(int row, int col) const
    {
        return ((row * m_cols) + col);
    }

    inline pair<int, int> coordinates(int idx) const
    {
        int row = idx / m_cols;
        int col = idx % m_cols;

        return { row, col };
    }

    void mark(int flag, int idx);
};

TotalShapes::TotalShapes(istream & stream, int rows, int cols)
    : m_rows(rows),
      m_cols(cols),
      m_matrix(rows),
      m_graph(rows * cols)
{
    string temp;
    
    std::getline(stream, temp);
    istringstream str(temp);

    for (auto & row : m_matrix) {
        row.reserve(m_cols);

        std::getline(str, temp, ' ');
            
        for (char c : temp) {
            row.push_back({ c, 0 });
        }
    }

    for (int i = 0; i < int(m_graph.size()); i++) {
        list<int> & connections = m_graph[i];

        auto cell = coordinates(i);
        int row = cell.first;
        int col = cell.second;

        if (isValid(row + 1, col)) { connections.push_back(index(row + 1, col)); }
        if (isValid(row - 1, col)) { connections.push_back(index(row - 1, col)); }
        if (isValid(row, col + 1)) { connections.push_back(index(row, col + 1)); }
        if (isValid(row, col - 1)) { connections.push_back(index(row, col - 1)); }
    }
}

void TotalShapes::mark(int flag, int idx)
{
    auto cell = coordinates(idx);

    const auto & current = m_matrix.at(cell.first).at(cell.second);
    if (('O' == current.first) || (0 != current.second)) {
        return;
    }

    m_matrix[cell.first][cell.second].second = flag;
    for (int neighbor : m_graph.at(idx)) {
        mark(flag, neighbor);
    }
}

int TotalShapes::count()
{
    int shapes = 0;
    for (int row = 0; row < int(m_matrix.size()); row++) {
        const auto & entry = m_matrix.at(row);
        
        for (int col = 0; col < int(entry.size()); col++) {
            const auto & cell = entry.at(col);
            if (('O' == cell.first) || (0 != cell.second)) {
                continue;
            }

            mark(++shapes, index(row, col));
        }
    }

    return shapes;
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
        int rows, cols;
        file >> rows;
        file >> cols;

        std::getline(file, temp);


        TotalShapes counter(file, rows, cols);
        std::cout << counter.count() << std::endl;
    }
    
    return 0;
}
