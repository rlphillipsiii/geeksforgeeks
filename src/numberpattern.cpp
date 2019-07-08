/*******************************************************************************                                                                     
https://practice.geeksforgeeks.org/problems/number-following-a-pattern/0

Given a pattern containing only I's and D's. I for increasing and D for decreasing.
Devise an algorithm to print the minimum number following that pattern.  Digits 
from 1-9 and digits can't repeat.

Input:
The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is a string, which contains only I's and D's in 
capital letter.

Output:
Print the minimum number following that pattern. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <list>

using std::ifstream;
using std::string;
using std::istream;
using std::list;

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
        list<char> numbers = { '2', '3', '4', '5', '6', '7', '8', '9' };

        string pattern;
        std::getline(file, pattern);

        int extra = numbers.size() - pattern.size();
        while (extra--) { numbers.pop_back(); }

        list<char> output = { '1' };

        auto forward  = output.end();
        auto backward = output.rend();

        char last = 0;
        for (char c : pattern) {
            if ('D' == c) {
                if ('I' == last) {
                    backward = ++std::reverse_iterator<list<char>::iterator>(forward);                    
                }

                auto temp = output.insert(backward.base(), numbers.front());
                backward = std::reverse_iterator<list<char>::iterator>(temp);
            } else {
                forward = ++output.insert(forward, numbers.front());
            }

            last = c;
            numbers.pop_front();
        }
        
        for (char c : output) { std::cout << c; }
        std::cout << std::endl;
    }

    return 0;
}
