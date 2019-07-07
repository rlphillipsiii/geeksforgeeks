/*******************************************************************************
https://practice.geeksforgeeks.org/problems/lru-cache/1

The task is to design and implement methods of an LRU cache. The class has two methods 
get() and set() which are defined as follows.
get(x)   : Returns the value of the key x if the key exists in the cache otherwise 
returns -1.
set(x,y) : inserts the value if the key x is not already present. If the cache reaches 
its capacity it should invalidate the least recently used item before inserting the 
new item.

In the constructor of the class the size of the cache should be intitialized.

Input Format:
The first line of input contain an integer T denoting the number of test cases. Then T 
test case follow. Each test case contains 3 lines. The first line of input contains an 
integer N denoting the capacity of the cache and then in the next line is an integer Q 
denoting the number of queries Then Q queries follow. A Query can be of two types
1. SET x y : sets the value of the key x with value y
2. GET x : gets the key of x if present else returns -1.

Output Format:
For each test case, in a new line, output will be space separated values of the query.

Your Task:
This is a function problem. You only need to complete the provided functions.
*******************************************************************************/

#include<bits/stdc++.h>
using namespace std;
class LRUCache
{
public:
    LRUCache(int );
 
    int get(int );
 
    void set(int , int );
};
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
        int n;
        file>>n;
        LRUCache *l  = new LRUCache(n);
        int q;
        file>>q;
        for(int i=0;i<q;i++)
        {
            string a;
            file>>a;
            if(a=="SET")
            {
                int aa,bb;
                file>>aa>>bb;
                l->set(aa,bb);
            }else if(a=="GET")
            {
                int aa;
                file>>aa;
                cout<<l->get(aa)<<" ";
            }
        }
        cout<<endl;
    }
}

/*This is a function problem.You only need to complete the function given below*/
/*The structure of the class is as follows 
class LRUCache
{
public:
    LRUCache(int );
    int get(int );
    void set(int , int );
    
private:
    
};*/

#include <map>
#include <list>
#include <utility>

using std::map;
using std::list;
using std::pair;

static int m_size;
    
static map<int, list<pair<int, int>>::iterator> m_table;
    
static list<pair<int, int>> m_cache;

/*You are required to complete below methods */
/*Inititalize an LRU cache with size N */
LRUCache::LRUCache(int N)
{
    m_cache.clear();
    m_table.clear();
    
    m_size = N;
}
/*Sets the key x with value y in the LRU cache */
void LRUCache::set(int x, int y) 
{
    auto iterator = m_table.find(x);
    if (m_table.end() == iterator) {
        if (int(m_cache.size()) == m_size) {
            auto oldest = m_cache.back();
            m_cache.pop_back();
        
            auto iterator = m_table.find(oldest.first);
            m_table.erase(iterator);
        }

        m_cache.push_front({ x, y });
        m_table[x] = m_cache.begin();    
    } else {
        m_cache.splice(m_cache.begin(), m_cache, iterator->second);
    }
    
    pair<int, int> & entry = *(m_table[x]);
    entry.second = y;
}

/*Returns the value of the key x if 
present else returns -1 */
int LRUCache::get(int x)
{
    auto iterator = m_table.find(x);
    if (m_table.end() == iterator) {
        return -1;
    }
    
    int value = (*(iterator->second)).second;
    m_cache.splice(m_cache.begin(), m_cache, iterator->second);
    
    return value;
}
