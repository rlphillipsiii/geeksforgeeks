/*******************************************************************************
https://practice.geeksforgeeks.org/problems/rotate-a-2d-array-without-using-extra-space/0

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

You need to do this in place.

Note that if you end up using an additional array, you will only receive partial score.

Example:

If the array is 

1 2 3 4 5 6 7 8 9

Then the rotated array becomes: 

7 4 1 8 5 2 9 6 3

Input:

The first line contains an integer 'T' denoting the total number of test cases.
In each test cases, the first line contains an integer 'N' denoting the size of the 2D square matrix.

And in the second line, the elements of the matrix A[][], each separated by a space in row major form.


Output:

For each test case, print the elements of the rotated array row wise, each element separated by a space. 
Print the output of each test case in a new line.
*******************************************************************************/

#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>

using std::string;
using std::vector;
using std::ifstream;
using std::istream;

void print(const vector<vector<int>> & data)
{
    for (const vector<int> & row : data) {
        for (int entry : row) {
            std::cout << entry << " ";
        }
    }
    std::cout << std::endl;
}

void rotate(vector<vector<int>> & data)
{
    for (const vector<int> & row : data) {
        assert(data.size() == row.size());
    }

    int last = static_cast<int>(data.size()) - 1;
    
    int offset = 0;
    int end = static_cast<int>(data.size()) / 2;

    while (offset < end) {
        for (int index = offset; index <= last - offset - 1; index++) {
            int temp1, temp2;

            int & top    = data[offset][index];
            int & right  = data[index][last - offset];
            int & bottom = data[last - offset][last - index];
            int & left   = data[last - index][offset];

            temp1 = right;  right = top;
            temp2 = bottom; bottom = temp1;
            temp1 = left;   left = temp2;
            top = temp1;
        }

        offset++;
    }

    print(data);
}

int main(int, char **)
{
#ifdef LOCAL
    ifstream file(INPUT_FILE);
#else
    istream & file = std::cin;
#endif
    
    vector<vector<int>> data;

    string temp;
    std::getline(file, temp);
    
    int iterations = std::atoi(temp.c_str());
    for (int i = 0; i < iterations; i++) {
        std::getline(file, temp);

        int n = std::atoi(temp.c_str());

        data.resize(n);
        for (vector<int> & row : data) {
            row.resize(n);
        }

        for (vector<int> & row : data) {
            for (int & entry : row) {
                file >> entry;
            }
        }

        rotate(data);
        std::getline(file, temp);
    }
    
    return 0;
}
