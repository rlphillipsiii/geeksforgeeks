/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/find-all-four-sum-numbers/0

Given an array A of size N, find all combination of four elements in the array whose sum 
is equal to a given value K. For example, if the given array is {10, 2, 3, 4, 5, 9, 7, 8} 
and K = 23, one of the quadruple is “3 5 7 8” (3 + 5 + 7 + 8 = 23).

The output should contain only unique quadrples  For example, if input array is 
{1, 1, 1, 1, 1, 1} and K = 4, then output should be only one quadrple {1, 1, 1, 1}
 

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test 
cases follow. Each test case contains two lines. The first line of input contains two 
integers N and K. Then in the next line are N space separated values of the array.

Output:
For each test case in a new line print all the quadruples present in the array separated 
by space which sums up to value of K. Each quadruple is unique which are separated by a 
delimeter "$" and are in increasing order. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <list>
#include <map>
#include <set>
#include <array>

using std::ifstream;
using std::string;
using std::istream;
using std::vector;
using std::pair;
using std::list;
using std::map;
using std::set;
using std::array;

typedef array<int, 4> Quad;

void foursumnum(int target, const vector<int> & input)
{
    map<int, list<pair<int, int>>> pairs;

    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = i + 1; j < input.size(); j++) {
            int sum = input.at(i) + input.at(j);

            if (pairs.find(sum) == pairs.end()) {
                pairs[sum] = list<pair<int, int>>();
            }
            pairs[sum].push_back(pair<int, int>(i, j));
        }
    }

    set<Quad> quads;
    
    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = i + 1; j < input.size(); j++) {
            int sum = input.at(i) + input.at(j);

            auto iterator = pairs.find(target - sum);
            if (pairs.end() == iterator) {
                continue;
            }

            for (const pair<int, int> & entry : iterator->second) {
                if ((entry.first == j) || (entry.second == j)
                    || (entry.first == i) || (entry.second == i)) {
                    continue;
                }

                Quad quad = {
                    input.at(i), input.at(j),
                    input.at(entry.first), input.at(entry.second)
                };
                std::sort(quad.begin(), quad.end());

                quads.insert(quad);
            }
        }
    }

    if (quads.empty()) {
        std::cout << "-1";
    }
    
    for (const Quad & quad : quads) {
        for (int entry : quad) {
            std::cout << entry << " ";
        }
        std::cout << "$";
    }
    std::cout << std::endl;
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

    int n = std::atoi(temp.c_str());
    while (n--) {
        int target, count;

        file >> count;
        file >> target;

        std::getline(file, temp);

        vector<int> input(count);
        for (int & entry : input) {
            file >> entry;
        }

        std::sort(input.begin(), input.end());
        foursumnum(target, input);
        
        std::getline(file, temp);
    }

    return 0;
}
