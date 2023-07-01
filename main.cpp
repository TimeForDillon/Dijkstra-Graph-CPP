/*******************************************************************************
* AUTHOR       : Dillon Welsh
* ASSIGNMENT 7 : DIJKSTRA
* CLASS        : CS 8
* SECTION      : 33776
* DUE DATE     : 05/05/2021
*******************************************************************************/

#include <iostream>
#include <list>
#include <set>
#include <vector>

#define infinity 999999

using namespace std;

/*******************************************************************************
* CLASS Graph
*_______________________________________________________________________________
* This class represents a graph of data
*******************************************************************************/

class Graph
{
private:
    int numberOfVerticies;      // IN - number of verticies in graph
    list<pair<int, int>> *adj;  // IN - list of verticies with weights

public:
    /******************************
     * CONSTRUCTORS & DESTRUCTORS *
     ******************************/
    Graph(int numberOfVertices);

    /************
     * MUTATORS *
     ************/
    void addEdge(int city1, int city2, int length);

    /*************
     * ACCESSORS *
     *************/
    void shortestPath(int city);
};

/*******************************************************************************
* CONSTRUCTOR Graph
*_______________________________________________________________________________
* This constructs a graph object with a specific number of verticies
*******************************************************************************/
Graph::Graph(int numberOfVerticies)
{
    this->numberOfVerticies = numberOfVerticies;
    this->adj = new list<pair<int, int>>[numberOfVerticies];
}

/*******************************************************************************
* MUTATOR addEdge
*_______________________________________________________________________________
* This adds an edge to the graph with the next vertex and weight
*******************************************************************************/
void Graph::addEdge(int city1, int city2, int length)
{
    adj[city1].push_back(make_pair(city2, length));
}

/*******************************************************************************
* ACCESSOR shortestPath
*_______________________________________________________________________________
* This uses dijkstra algorithm to find the shortest path
*******************************************************************************/
void Graph::shortestPath(int city)
{
    set<pair<int, int>> extract_set;
    vector<int> distances(numberOfVerticies, infinity);

    extract_set.insert(make_pair(0, city));
    distances[city] = 0;

    while(!extract_set.empty())
    {
        pair<int, int> temp = *extract_set.begin();
        extract_set.erase(extract_set.begin());

        int currentCity = temp.second;

        for(auto i = adj[city].begin(); i != adj[city].end(); i++)
        {
            int nextCity = (*i).first;
            int length = (*i).second;

            if(distances[nextCity] > distances[currentCity] + length)
            {
                if(distances[nextCity] != infinity)
                {
                    extract_set.erase(extract_set.find(make_pair(distances[nextCity], nextCity)));
                }

                distances[nextCity] = distances[city] + length;
                extract_set.insert(make_pair(distances[nextCity], nextCity));
            }
        }
    }

    cout << "minimum distance from vertex: " << city << endl;
    for(int i = 0; i < numberOfVerticies; i++)
    {
        cout << "Vertex: " << i << " Distance: " << distances[i] << endl;
    }
}

/*
Seattle = 0
San Francisco = 1
Los Angeles = 2
Denver = 3
Chicago = 4
Kansas City = 5
Dallas = 6
Houston = 7
Boston = 8
New York = 9
Atlanta = 10
Miami = 11
*/

int main()
{
    Graph cities(12);

    // From Seattle
    cities.addEdge(0, 1, 807);
    cities.addEdge(0, 3, 1331);
    cities.addEdge(0, 4, 2097);

    // From San Francisco
    cities.addEdge(1, 0, 807);
    cities.addEdge(1, 3, 1267);
    cities.addEdge(1, 2, 381);

    // From Los Angeles
    cities.addEdge(2, 1, 381);
    cities.addEdge(2, 3, 1015);
    cities.addEdge(2, 5, 1663);
    cities.addEdge(2, 6, 1435);

    // From Denver
    cities.addEdge(3, 0, 1331);
    cities.addEdge(3, 1, 1267);
    cities.addEdge(3, 2, 1015);
    cities.addEdge(3, 5, 599);
    cities.addEdge(3, 4, 1003);

    // From Chicago
    cities.addEdge(4, 0, 2097);
    cities.addEdge(4, 3, 1003);
    cities.addEdge(4, 5, 533);
    cities.addEdge(4, 8, 983);
    cities.addEdge(4, 9, 787);

    // From Kansas City
    cities.addEdge(5, 4, 533);
    cities.addEdge(5, 3, 599);
    cities.addEdge(5, 2, 1663);
    cities.addEdge(5, 6, 496);
    cities.addEdge(5, 10, 864);
    cities.addEdge(5, 9, 1260);

    // From Dallas
    cities.addEdge(6, 2, 1435);
    cities.addEdge(6, 5, 496);
    cities.addEdge(6, 10, 781);
    cities.addEdge(6, 7, 239);

    // From Houston
    cities.addEdge(7, 6, 239);
    cities.addEdge(7, 10, 810);
    cities.addEdge(7, 11, 1187);

    // From Boston
    cities.addEdge(8, 4, 983);
    cities.addEdge(8, 9, 214);

    // From New York
    cities.addEdge(9, 8, 214);
    cities.addEdge(9, 4, 787);
    cities.addEdge(9, 5, 1260);
    cities.addEdge(9, 10, 888);

    // From Atlanta
    cities.addEdge(10, 9, 888);
    cities.addEdge(10, 5, 864);
    cities.addEdge(10, 6, 781);
    cities.addEdge(10, 7, 810);
    cities.addEdge(10, 11, 661);

    // From Miami
    cities.addEdge(11, 10, 661);
    cities.addEdge(11, 7, 1187);

    cities.shortestPath(5);

    return 0;
}

/*
Seattle = 0
San Francisco = 1
Los Angeles = 2
Denver = 3
Chicago = 4
Kansas City = 5
Dallas = 6
Houston = 7
Boston = 8
New York = 9
Atlanta = 10
Miami = 11
*/
