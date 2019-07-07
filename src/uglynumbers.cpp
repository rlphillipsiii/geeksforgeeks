/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/ugly-numbers/0

Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence 1, 2, 
3, 4, 5, 6, 8, 9, 10, 12, 15, … shows the first 11 ugly numbers. By convention, 1 is 
included. Write a program to find Nth Ugly Number.

Input:
The first line of input contains an integer T denoting the number of test cases. T 
testcases follow. For each testcase there is one line of input that contains the 
number N.

Output:
Print the Nth Ugly Number. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdint>

using std::ifstream;
using std::string;
using std::istream;
using std::vector;

void generateUglies(vector<uint64_t> & uglies, vector<int> & indices, uint64_t count)
{
    while (uglies.size() < count) {
        uint64_t value2 = uglies[indices[0]] * 2;
        uint64_t value3 = uglies[indices[1]] * 3;
        uint64_t value5 = uglies[indices[2]] * 5;

        if (value2 == value3) { indices[0]++; continue; }
        if (value3 == value5) { indices[1]++; continue; }
        if (value2 == value5) { indices[2]++; continue; }
        
        if ((value2 < value3) && (value2 < value5)) {
            uglies.push_back(value2);

            indices[0]++;
        } else if ((value3 < value2) && (value3 < value5)) {
            uglies.push_back(value3);

            indices[1]++;
        } else {
            uglies.push_back(value5);

            indices[2]++;
        }
    }
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

    vector<uint64_t> uglies = { 1 };
    vector<int> indices(3, 0);
    
    int n = static_cast<int>(std::atoi(temp.c_str()));
    while (n--) {
        uint64_t count;
        file >> count;

        generateUglies(uglies, indices, count);
        
        std::cout << uglies[count - 1] << std::endl;
        std::getline(file, temp);
    }
    
    return 0;
}
