/*******************************************************************************
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
using std::list;
using std::string;
using std::unordered_set;
using std::vector;

/*This is a function problem.You only need to complete the function given below*/
//User function Template for C++
/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string alphabetize(
    const unordered_map<char, unordered_set<char>> & graph,    
    vector<char> str,
    char current,
    int k,
    unordered_set<char> visited)
{
    str.push_back(current);
    if (int(str.size()) == k) {
        return string(str.begin(), str.end());
    }

    visited.insert(current);
    
    const auto & iterator = graph.find(current);
    if (graph.end() == iterator) {
        return "";
    }
    
    for (char c : iterator->second) {
        if (visited.find(c) != visited.end()) {
            continue;
        }

        string order = alphabetize(graph, str, c, k, visited);
        if (!order.empty()) {
            return order;
        }
    }

    return "";
}

typedef vector<list<const string *>> BucketList;

string printOrder(string dict[], int N, int k)
{
    unordered_map<char, unordered_set<char>> graph;

    BucketList buckets(1);
    for (int i = 0; i < N; i++) { buckets[0].push_back(&dict[i]); }

    queue<pair<int, BucketList>> next;
    next.push({ 0, buckets });

    unordered_set<char> alphabet;
    
    while (!next.empty()) {
        auto entry = next.front();
        next.pop();

        int index = entry.first;
        for (const auto & bucket : entry.second) {
            BucketList sub;

            char last = 0;

            list<char> sorted;

            unordered_map<char, list<const string*>> temp;
            for (auto j = bucket.begin(); j != bucket.end(); j++) {
                const string *word = *j;
                
                if (index >= int(word->size())) { continue; }

                if ((0 != last) && (word->at(index) != last)) {
                    graph[last].insert(word->at(index));

                    alphabet.insert(last);
                }
                last = word->at(index);

                temp[word->at(index)].push_back(word);
                sorted.push_back(word->at(index));
            }

            for (char c : sorted) {
                auto iterator = temp.find(c);
                if (temp.end() == iterator) {
                    continue;
                }

                if (iterator->second.size() > 1) {
                    sub.push_back(iterator->second);
                }
                temp.erase(iterator);
            }
            
            if (!sub.empty()) { next.push({ index + 1, sub }); }
        }
    }

    for (const auto & connections : graph) {
        for (char c : connections.second) {
            auto iterator = alphabet.find(c);
            if (alphabet.end() == iterator) {
                continue;
            }
            alphabet.erase(iterator);
        }
    }

    for (const auto & connections : graph) {
        std::cout << connections.first << ": ";
        for (char c : connections.second) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    for (char start : alphabet) {
        vector<char> str;
        for (char c : alphabet) {
            if (c == start) { continue; }

            str.push_back(c);
        }

        string order = alphabetize(graph, str, start, k, {});
        if (!order.empty()) {
            std::cout << order << std::endl;
            return order;
        }
    }
    return "";
}
