/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/form-a-palindrome/0

Given a string, find the minimum number of characters to be inserted to convert it to a
palindrome.
For Example:
ab: Number of insertions required is 1. bab or aba
aa: Number of insertions required is 0. aa
abcd: Number of insertions required is 3. dcbabcd

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is S.

Output:
Print the minimum number of characters. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <unordered_map>
#include <list>

using std::ifstream;
using std::string;
using std::istream;
using std::unordered_map;
using std::list;

typedef unordered_map<int, unordered_map<int, list<char>>> Cache;

list<char> insertions(const string & input, Cache & cache, int a, int b)
{
    if ((b - a) == 0) { return { input.at(a) }; }

    if ((b - a) == 1) {
        list<char> val = { input.at(a), input.at(b) };
        if (input.at(a) != input.at(b)) {
            val.push_back(input.at(a));
        }
        return val;
    }

    auto iterator = cache.find(a);
    if (cache.end() != iterator) {
        if (iterator->second.find(b) != iterator->second.end()) {
            return cache[a][b];
        }
    }

    int next;
    
    list<char> value;
    if (input.at(a) == input.at(b)) {
        value = insertions(input, cache, a + 1, b - 1);

        next = a;
    } else {
        list<char> left  = insertions(input, cache, a, b - 1);
        list<char> right = insertions(input, cache, a + 1, b);

        if (left.size() < right.size()) {
            next = b;
            
            value = left;
        } else {
            next = a;

            value = right;
        }
    }

    value.push_front(input.at(next));
    value.push_back(input.at(next));
    
    cache[a][b] = value;
    return value;
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
        string input;
        std::getline(file, input);

        Cache cache;
        list<char> str = insertions(input, cache, 0, int(input.size()) - 1);

        std::cout << (str.size() - input.size()) << std::endl;
    }
    
    return 0;
}
