/*******************************************************************************
https://practice.geeksforgeeks.org/problems/word-break-part-2/0

Given a string s and a dictionary of words dict, add spaces in s to construct a 
sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "snakesandladder",
dict = ["snake", "snakes", "and", "sand", "ladder"].

A solution is ["snakes and ladder",
           "snake sand ladder"].

Input:
The first line contains an integer T, denoting the number of test cases.
Every test case has 3 lines.
The first line contains an integer N, number of words in the dictionary.
The second line contains N strings denoting the words of the dictionary.
The third line contains a string s.

Output:
For each test case, print all possible strings in one line. Each string is enclosed in 
(). See Example.
If no string possible print "Empty" (without quotes).
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
#include <vector>

using std::ifstream;
using std::string;
using std::istream;
using std::unordered_map;
using std::istringstream;
using std::shared_ptr;
using std::unordered_set;
using std::vector;

struct Branch {
    Branch() : word(false) { }

    bool word;
    string str;
    
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
    root->str  = word;
}

void lookup(
    const Branch & dictionary,
    const string & letters,
    vector<vector<string>> & sentences,
    unordered_set<string> & cache,
    const vector<string> & sentence)
{
    if (cache.find(letters) != cache.end()) { return; }
    
    const Branch *node = &dictionary;

    for (int i = 0; i < int(letters.size()); i++) {        
        if (node->word) {
            vector<string> copy = sentence;
            copy.push_back(node->str);
            
            lookup(dictionary, letters.substr(i), sentences, cache, copy);
        }

        auto iterator = node->children.find(letters.at(i));
        if (node->children.end() == iterator) {
            return;
        }
        node = iterator->second.get();
    }

    if (node->word) {
        vector<string> copy = sentence;
        copy.push_back(node->str);

        sentences.push_back(copy);
    } else {
        cache.insert(letters);
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

        vector<vector<string>> sentences;
        
        unordered_set<string> cache;
        lookup(dictionary, temp, sentences, cache, {});

        if (sentences.empty()) {
            std::cout << "Empty" << std::endl;
            continue;
        }

        for (const vector<string> & sentence : sentences) {
            std::cout << "(";
            for (size_t i = 0; i < sentence.size(); i++) {
                if (0 != i) {
                    std::cout << " ";
                }
                std::cout << sentence[i];
            }
            std::cout << ")";
        }

        std::cout << std::endl;
    }
    
    return 0;
}
