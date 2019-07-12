/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/overlapping-intervals/0

Given a collection of Intervals,merge all the overlapping Intervals.
For example:

Given [1,3], [2,6], [8,10], [15,18],

return [1,6], [8,10], [15,18].

Make sure the returned intervals are sorted.

Input:
The first line contains an integer T, depicting total number of test cases. 
Then following T lines contains an integer N depicting the number of Intervals and next 
line followed by the intervals starting and ending positions 'x' and 'y' respectively.


Output:
Print the intervals after overlapping in sorted manner.  There should be a newline at 
the end of output of every test case.
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <stack>
#include <memory>

using std::ifstream;
using std::string;
using std::istream;
using std::pair;
using std::vector;
using std::stack;
using std::shared_ptr;

typedef pair<int, int> Range;
typedef shared_ptr<Range> RangePtr;

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
        int count;
        file >> count;

        vector<RangePtr> pairs(count);
        for (RangePtr & entry : pairs) {
            entry = RangePtr(new pair<int, int>());
            
            file >> entry->first;
            file >> entry->second;
        }

        std::sort(pairs.begin(), pairs.end(),
            [](const RangePtr & a, const RangePtr & b) {
                return (a->first > b->first);
            }
        );

        stack<RangePtr> next;
        for (const RangePtr & ptr : pairs) { next.push(ptr); }

        RangePtr last = nullptr;
        while (!next.empty()) {
            auto entry = next.top();
            next.pop();

            if (last) {
                if (last->second >= entry->first) {
                    last = RangePtr(new Range(last->first, std::max(last->second, entry->second)));
                } else {
                    std::cout << last->first << " " << last->second << " ";

                    last = entry;
                }
            } else {
                last = entry;
            }

            
        }
        std::cout << last->first << " " << last->second << std::endl;
    }

    return 0;
}
