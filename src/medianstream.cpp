/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/find-median-in-a-stream/0

Given an input stream of N integers. The task is to insert these numbers into a new 
stream and find the median of the stream formed by each insertion of X to the new stream.

Input:
The first line of input contains an integer N denoting the number of elements in the 
stream. Then the next N lines contains integer x denoting the number to be inserted into 
the stream.

Output:
For each element added to the stream print the floor of the new median in a new line. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

using std::function;
using std::ifstream;
using std::string;
using std::istream;
using std::vector;

int init(vector<int> & left, vector<int> & right, int value)
{
    if (right.size() == 0) {
        right.push_back(value);
        return value;
    }

    if (right[0] < value) {
        left.push_back(right[0]);
        right[0] = value;
    } else {
        left.push_back(value);
    }

    return (left[0] + right[0]) / 2;
}

void insert(vector<int> & left, vector<int> & right, int value)
{
    function<bool(int,int)> gt = [](int a, int b) { return a > b; };
    
    if (value >= right[0]) {
        right.push_back(value);

        std::push_heap(right.begin(), right.end(), gt);
    } else if (value <= left[0]) {
        left.push_back(value);
        
        std::push_heap(left.begin(), left.end());
    } else if (right.size() > left.size()) {
        left.push_back(value);

        std::push_heap(left.begin(), left.end());
    } else {
        right.push_back(value);

        std::push_heap(right.begin(), right.end(), gt);
    }

    if (left.size() > right.size() + 1) {
        std::pop_heap(left.begin(), left.end());

        right.push_back(left.back());
        left.pop_back();
        
        std::push_heap(right.begin(), right.end(), gt);
    } else if (right.size() > left.size() + 1) {
        std::pop_heap(right.begin(), right.end(), gt);

        left.push_back(right.back());
        right.pop_back();
        
        std::push_heap(left.begin(), left.end());
    }
}

int median(vector<int> & left, vector<int> & right, int value)
{
    if (left.size() == 0) {
        return init(left, right, value);
    }

    insert(left, right, value);

    if (left.size() == right.size()) {
        return (left[0] + right[0]) / 2;
    }

    return (left.size() > right.size()) ? left[0] : right[0];
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

    vector<int> left, right;
    left.reserve(n/2 + 2);
    right.reserve(n/2 + 2);

    for (int i = 0; i < n; i++) {
        int entry;
        file >> entry;

        std::cout << median(left, right, entry) << std::endl;
        std::getline(file, temp);
    }


    return 0;
}
