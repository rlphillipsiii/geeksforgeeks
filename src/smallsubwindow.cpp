/*******************************************************************************                                                                      
*******************************************************************************/

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <list>

using std::ifstream;
using std::string;
using std::istream;
using std::unordered_map;
using std::unordered_set;
using std::list;

class Substring {
public:
    Substring(const string & str);
    ~Substring() = default;

    inline bool found()   const { return (m_target == m_size); }
    inline bool optimal() const { return (m_window.size() == m_chars.size()); }
    inline string value() const { return m_substring; }

    void push(char c);
    void pop();

    void save();
    
private:
    string m_substring;

    int m_size;
    int m_target;
    
    unordered_set<char> m_chars;
    unordered_map<char, int> m_found;

    list<char> m_window;
};

Substring::Substring(const string & str)
    : m_size(0),
      m_target(int(str.size()))
{
    for (const char & c : str) {
        m_chars.insert(c);

        m_found[c]++;
    }
}

void Substring::save()
{
    if (m_substring.empty() || (m_window.size() < m_substring.length())) {
        m_substring = string(m_window.begin(), m_window.end());
    }
}

void Substring::push(char c)
{
    if (m_chars.find(c) != m_chars.end()) {
        int & entry = m_found[c];
        if (entry > 0) { m_size++; }

        entry--;
    }

    m_window.push_back(c);
}

void Substring::pop()
{
    char c = m_window.front();
    
    auto found = m_found.find(c);
    if (m_found.end() != found) {
        int & entry = m_found[c];
        if (entry >= 0) { m_size--; }

        entry++;
    }

    m_window.pop_front();
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
        string str;
        std::getline(file, str);

        std::getline(file, temp);
        Substring substring(temp);
        
        int begin = 0, end = 0;

        substring.push(str.at(begin));
        while (true) {
            if (substring.found()) {
                substring.pop();
                begin++;
            } else {
                if (++end == int(str.size())) {
                    break;
                }
                substring.push(str.at(end));
            }
            
            if (substring.found()) { 
                substring.save();

                if (substring.optimal()) { break; }
            }
        }

        string output = substring.value();
        if (output.empty()) {
            output = "-1";
        }
        std::cout << output << std::endl;
    }
    
    return 0;
}
