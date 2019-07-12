/*******************************************************************************
https://practice.geeksforgeeks.org/problems/alien-dictionary/1

Given a sorted dictionary of an alien language having N words and k starting alphabets 
of standard dictionary the task is to complete the function which returns a string 
denoting the order of characters in the language.
Note: Many orders may be possible for a particular test case, thus you may return any 
valid order.

Examples:
Input:  Dict[] = { "baa", "abcd", "abca", "cab", "cad" }, k = 4
Output: Function returns "bdac"
Here order of characters is 'b', 'd', 'a', 'c'
Note that words are sorted and in the given language "baa"
comes before "abcd", therefore 'b' is before 'a' in output.
Similarly we can find other orders.

Input: Dict[] = { "caa", "aaa", "aab" }, k = 3
Output: Function returns "cab"

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test 
cases follow. Each test case contains an integer N and k denoting the size of the dictionary. 
Then in the next line are sorted space separated values of the alien dictionary.

Output:
For each test case in a new line output will be 1 if the order of string returned by the 
function is correct else 0 denoting incorrect string returned.
*******************************************************************************/

//Initial Template for C++
/* script for test case http://code.geeksforgeeks.org/PetjYq */
#include<bits/stdc++.h>
#include <fstream>

using namespace std;
string printOrder(string [], int , int );
string order;
bool f(string a,string b)
{
    int p1=0;int p2=0;
    for(int i=0;i<min(int(a.size()),int(b.size())) and p1 ==p2;i++ )
    {
        p1 = order.find(a[i]);
        p2 = order.find(b[i]);
    }
        
    if(p1 == p2 and a.size()!=b.size())
        return a.size()<b.size();
        
    return p1<p2;
}
        
// Driver program to test above functions
int main()
{
#ifdef LOCAL
    ifstream file(INPUT_FILE);
#else
    istream & file = std::cin;
#endif
    int t;
    file>>t;
    while(t--)
    {
        int n,k;
        file>>n>>k;
        string s[n];
        for(int i=0;i<n;i++)file>>s[i];
    
        string ss = printOrder(s,n,k);
        order="";
        for(int i=0;i<int(ss.size());i++)
            order+=ss[i];
        
        string temp[n];
        std::copy(s, s + n, temp);
        sort(temp,temp+n,f);
        
        bool f= true;
        for(int i=0;i<n;i++)
            if(s[i]!=temp[i])f=false;
        
        cout<<f;
        cout<<endl;
        
    }
    return 0;
}

#include <unordered_map>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>
#include <utility>

using std::unordered_map;
using std::string;
using std::unordered_set;
using std::vector;
using std::pair;
using std::queue;

/*This is a function problem.You only need to complete the function given below*/
//User function Template for C++
/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
void build(
    unordered_map<char, unordered_set<char>> & graph,
    string dict[],
    int N)
{
    queue<pair<int, vector<string>>> bins;
    bins.push({ 0, vector<string>(&dict[0], (&dict[0]) + N) });

    while (!bins.empty()) {
        auto bin = bins.front();
        bins.pop();

        vector<string> subset;

        int index = bin.first;

        const string *last = nullptr;
        for (const string & str : bin.second) {
            if (index >= int(str.size())) { continue; }

            if (last) {
                if (last->at(index) != str.at(index)) {
                    graph[last->at(index)].insert(str.at(index));

                    if (subset.size() > 1) {
                        bins.push({ index + 1, subset });
                    }
                    subset.clear();
                }
            }

            subset.push_back(str);
            last = &str;
        }

        if (subset.size() > 1) { bins.push({ index + 1, subset }); }
    }
}
    
void alphabetize(
    const unordered_map<char, unordered_set<char>> & graph,    
    vector<char> & str,
    unordered_set<char> & visited,
    char current)
{
    visited.insert(current);
    
    const auto & iterator = graph.find(current);
    if (graph.end() != iterator) { 
        for (char c : iterator->second) {
            if (visited.find(c) != visited.end()) {
                continue;
            }

            alphabetize(graph, str, visited, c);
        }
    }

    str.push_back(current);
}

string printOrder(string dict[], int N, int k)
{
    unordered_map<char, unordered_set<char>> graph;
    build(graph, dict, N);

    vector<char> order;

    unordered_set<char> visited;
    for (const auto & connections : graph) {
        char letter = connections.first;
        
        if (visited.find(letter) == visited.end()) {
            alphabetize(graph, order, visited, letter);
        }
    }

    return string(order.rbegin(), order.rend());
}
