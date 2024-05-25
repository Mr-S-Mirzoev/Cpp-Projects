#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

const int INF = std::numeric_limits<int>::max();
const int NOT_A_PARENT = -1;

struct VertexTo {
    int distance;
    int v;

    bool operator>( const VertexTo& other ) const {
        return distance > other.distance || ( distance == other.distance && v > other.v );
    }
};

class AdjacencyList {
    std::vector<std::vector<VertexTo>> graph;

public:
    AdjacencyList( int n )
        : graph( n ) {}

    void addEdge( int u, int v, int distance ) {
        graph[u].push_back( { distance, v } );
        graph[v].push_back( { distance, u } );
    }

    const std::vector<VertexTo>& operator[]( int u ) const {
        return graph[u];
    }
};

void Dijkstra( const AdjacencyList& graph, std::vector<int>& distances,
               std::vector<std::vector<int>>& optimal_parents ) {
    std::priority_queue<VertexTo, std::vector<VertexTo>, std::greater<VertexTo>> pq;
    pq.push( { 0, 0 } );
    distances[0] = 0;

    while ( !pq.empty() ) {
        auto [d, u] = pq.top();
        pq.pop();

        if ( d > distances[u] ) {
            continue;
        }

        for ( const auto& [distance, v] : graph[u] ) {
            const int new_distance = distances[u] + distance;
            if ( distances[v] > new_distance ) {
                distances[v] = new_distance;
                optimal_parents[v] = { u };
                pq.push( { distances[v], v } );
            } else if ( distances[v] == new_distance ) {
                optimal_parents[v].push_back( u );
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    AdjacencyList graph( n );

    for ( int i = 0; i < m; ++i ) {
        int x, y, l;
        std::cin >> x >> y >> l;
        graph.addEdge( x - 1, y - 1, l );
    }

    std::vector<int> distances( n, INF );
    std::vector<std::vector<int>> parents( n, { NOT_A_PARENT } );
    Dijkstra( graph, distances, parents );

    const int optimal_single_parents
        = std::count_if( parents.begin(), parents.end(), []( const std::vector<int>& p ) {
              return p.size() == 1 && p[0] != NOT_A_PARENT;
          } );

    // The edge is critical only if it's the single optimal parent of the vertex
    std::cout << optimal_single_parents << std::endl;
}
