/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/word-break/0

Given an input string and a dictionary of words, find out if the input string can be 
segmented into a space-separated sequence of dictionary words. See following examples 
for more details.

Consider the following dictionary
{ i, like, sam, sung, samsung, mobile, ice,
  cream, icecream, man, go, mango}

Input:  ilike
Output: Yes
The string can be segmented as "i like".

Input:  ilikesamsung
Output: Yes
The string can be segmented as "i like samsung" or "i like sam sung".

Input:
First line is integer T denoting number of test cases. 1<=T<=100.
Every test case has 3 lines.
First line is N number of words in dictionary. 1<=N<=12.
Second line contains N strings denoting the words of dictionary. Length of each word
is less than 15.
Third line contains a string S of length less than 1000.

Output:
Print 1 is possible to break words, else print 0. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <utility>
#include <memory>
#include <unordered_set>

using std::ifstream;
using std::string;
using std::istream;
using std::unordered_map;
using std::istringstream;
using std::shared_ptr;
using std::unordered_set;

struct Branch {
    Branch() : word(false) { }

    bool word;
    
    unordered_map<char, shared_ptr<Branch>> children;
};

void add(Branch & dictionary, const string & word)
{
    Branch *root = &dictionary;
    for (char c : word) {
        if (root->children.find(c) == root->children.end()) {
            root->children[c] = shared_ptr<Branch>(new Branch());
        }
        root = root->children[c].get();
    }

    root->word = true;
}

bool lookup(const Branch & dictionary, const string & letters, unordered_set<string> & cache)
{
    if (cache.find(letters) != cache.end()) { return false; }
    
    const Branch *node = &dictionary;

    for (int i = 0; i < int(letters.size()); i++) {
        if (node->word) {
            if (lookup(dictionary, letters.substr(i), cache)) {
                return true;
            }
        }

        auto iterator = node->children.find(letters.at(i));
        if (node->children.end() == iterator) {
            cache.insert(letters);

            return false;
        }

        node = iterator->second.get();
    }

    if (!node->word) { cache.insert(letters); }
    return node->word;
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
        std::getline(file, temp);
        int count = int(std::atoi(temp.c_str()));

        Branch dictionary;

        std::getline(file, temp);

        istringstream stream(temp);
        for (int i = 0; i < count; i++) {
            string word;
            std::getline(stream, word, ' ');
            
            add(dictionary, word);
        }

        std::getline(file, temp);

        unordered_set<string> cache;
        char output = (lookup(dictionary, temp, cache)) ? '1' : '0';
        
        std::cout << output<< std::endl;
    }
    
    return 0;
}
