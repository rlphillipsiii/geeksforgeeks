#include<bits/stdc++.h>
#include <fstream>
using namespace std;
void dijkstra(vector<vector<int>> , int ,int );
int main()
{
    ifstream file(INPUT_FILE);

    int t;
    int V;
    file>>t;
    while(t--){
        file>>V;
        
        vector<vector<int>> g(V);
        
        for(int i = 0;i<V;i++){
            vector<int> temp(V);
            g[i] = temp;
        }
        
        for(int i=0;i<V;i++)
        {
      	    for(int j=0;j<V;j++)
      	    {
      		    file>>g[i][j];
      	    }
        }
        
        int s;
        file>>s;
        
        dijkstra(g, s, V);
        cout<<endl;
       }
        return 0;
}

/*This is a function problem.You only need to complete the function given below*/
/*  Function to implement Dijkstra
*   graph: vector of vectors which represents the graph
*   src: source vertex to start traversing graph with
*   V: number of vertices
*/

#include <queue>
#include <unordered_set>
#include <memory>
#include <map>

struct Route {
    int vertex;
    int distance;

    unordered_set<int> visited;

    Route() = default;
    Route(int v, int d) : vertex(v), distance(d) { }
    
    inline bool operator()(const shared_ptr<Route> & a, const shared_ptr<Route> & b)
    {
        return (a->distance > b->distance);
    }
};
typedef shared_ptr<Route> RoutePtr;

void dijkstra(vector<vector<int>> graph, int src, int V)
{
    priority_queue<RoutePtr, vector<RoutePtr>, Route> next;
    next.push(RoutePtr(new Route(src, 0)));

    unordered_map<int, int> distances;

    while (!next.empty()) {
        RoutePtr route = next.top();
        route->visited.insert(route->vertex);

        next.pop();

        if (distances.find(route->vertex) == distances.end()) {
            distances[route->vertex] = route->distance;
        }

        if (int(distances.size()) == V) {
            break;
        }

        vector<int> & connections = graph[route->vertex];
        for (int i = 0; i < int(connections.size()); i++) {
            if (route->visited.find(i) != route->visited.end()) {
                continue;
            }
            
            RoutePtr edge(new Route(i, route->distance + connections[i]));
            edge->visited = route->visited;

            next.push(edge);
        }
    }

    for (int i = 0; i < V; i++) {
        auto iterator = distances.find(i);
        if (distances.end() != iterator) {
            std::cout << iterator->second << " ";
        }
    }
}
