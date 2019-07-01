/*******************************************************************************                                                                     https://practice.geeksforgeeks.org/problems/word-boggle/0

Given a dictionary, a method to do lookup in dictionary and a M x N board where every 
cell has one character. Find all possible words that can be formed by a sequence of 
adjacent characters. Note that we can move to any of 8 adjacent characters, but a word 
should not have multiple instances of same cell.

Example:

Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
       boggle[][]   = {{'G','I','Z'},
                       {'U','E','K'},
                       {'Q','S','E'}};

Output:  Following words of dictionary are present
         GEEKS, QUIZ

Input:
The first line of input contains an integer T denoting the no of test cases . Then T test
cases follow. Each test case contains an integer x denoting the no of words in the 
dictionary. Then in the next line are x space separated strings denoting the contents of 
the dictinory. In the next line are two integers N and M denoting the size of the boggle. 
The last line of each test case contains NxM space separated values of the boggle.

Output:
For each test case in a new line print the space separated sorted distinct words of the 
dictionary which could be formed from the boggle. If no word can be formed print -1. 
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>

using std::unordered_set;
using std::ifstream;
using std::string;
using std::istream;
using std::vector;
using std::map;
using std::istringstream;
using std::set;

struct CharacterNode {
    bool word;

    map<char, CharacterNode> nodes;

    CharacterNode() : word(false) { }
};
typedef struct CharacterNode Dictionary;

void print(const Dictionary & dictionary, const string & word)
{
    if (dictionary.word) {
        std::cout << word << " ";
    }

    for (const auto & entry : dictionary.nodes) {
        string str = word + entry.first;
        
        print(entry.second, str);
    }
}

void add(Dictionary & dictionary, const string & word)
{
    if (word.size() == 0) {
        dictionary.word = true;
        return;
    }

    auto character = word[0];
    
    auto iterator = dictionary.nodes.find(character);
    if (iterator == dictionary.nodes.end()) {
        dictionary.nodes[character] = CharacterNode();

        iterator = dictionary.nodes.find(character);
    }

    add(iterator->second, word.substr(1));
}

void lookup(
    set<string> & words,
    const Dictionary & dictionary,
    const vector<char> & characters,
    string & word,
    unordered_set<int> indices)
{
    if (dictionary.word) {
        words.insert(word);
    }
    
    if ((indices.size() == characters.size()) || (dictionary.nodes.size() == 0)) {
        return;
    }

    unordered_set<char> traversed;
    
    for (size_t i = 0; i < characters.size(); i++) {
        if (indices.find(i) != indices.end()) {
            continue;
        }

        auto character = characters[i];
        
        auto iterator = dictionary.nodes.find(character);
        if (dictionary.nodes.end() == iterator) {
            continue;
        }

        if (traversed.end() != traversed.find(character)) {
            continue;
        }
        traversed.insert(character);
        
        unordered_set<int> copy = indices;
        indices.insert(i);

        string str = word + character;
        lookup(words, iterator->second, characters, str, indices);
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
    
    int iterations = std::atoi(temp.c_str());
    for (int i = 0; i < iterations; i++) {
        Dictionary dictionary;

        std::getline(file, temp);
        int size = std::atoi(temp.c_str());

        std::getline(file, temp);
        istringstream stream(temp);

        for (int i = 0; i < size; i++) {
            std::getline(stream, temp, ' ');
            add(dictionary, temp);
        }

        std::getline(file, temp);
        stream = istringstream(temp);

        std::getline(stream, temp, ' ');
        int n = std::atoi(temp.c_str());
        std::getline(stream, temp, ' ');
        int m = std::atoi(temp.c_str());

        std::getline(file, temp);
        stream = istringstream(temp);

        vector<char> letters(n * m);
        for (char & letter : letters) {
            std::getline(stream, temp, ' ');
            letter = temp[0];
        }
        
        unordered_set<int> indices;
        temp.clear();
        
        set<string> words;
        lookup(words, dictionary, letters, temp, indices);

        for (const string & str : words) {
            std::cout << str << " ";
        }
        if (words.size() == 0) {
            std::cout << "-1";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
