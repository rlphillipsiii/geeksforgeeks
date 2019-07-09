/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/maximum-index/0

Given an array A[] of N positive integers. The task is to find the maximum of j - i 
subjected to the constraint of A[i] <= A[j].

Input:
The first line contains an integer T, depicting total number of test cases.  Then T 
test case follows. First line of each test case contains an integer N denoting the 
size of the array. Next line contains N space separated integeres denoting the 
elements of the array.

Output:
Print the maximum difference of the indexes i and j in a separtate line. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::string;
using std::istream;
using std::vector;

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
        int size;
        file >> size;

        vector<int> left(size), right(size), input(size);
        for (int i = 0; i < size; i++) {
            file >> input[i];

            if (0 == i) {
                left[i] = input[i];
            } else {
                left[i] = std::min(left[i - 1], input[i]);
            }
        }

        right[size - 1] = input[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            right[i] = std::max(right[i + 1], input[i]);
        }

        int distance = 0;

        int lIndex = 0, rIndex = 0;
        while ((lIndex < size) && (rIndex < size)) {
            if (left[lIndex] <= right[rIndex]) {
                distance = std::max(rIndex - lIndex, distance);

                rIndex++; 
            } else {
                lIndex++;
            }
        }

        std::cout << distance << std::endl;

        std::getline(file, temp);
    }
    
    return 0;
}
