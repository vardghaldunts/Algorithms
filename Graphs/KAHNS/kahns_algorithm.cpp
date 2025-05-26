/**
	 * Tasks:
	 *
	 * Implement function 'isTopologicallySorted()'
	 *     >> check that it passes the tests.
	 *
	 * Look at how 'topologicalSort()' is implemented.
	 *     >> check that it orders the graph properly.
	 *
	 * Change the function 'topologicalSort()' in such a way, that it will
	 *         also keep incoming degrees for all vertices, as
	 *         "std::vector< int > degree( N )". Initialize the 'degrees'
	 *         array, and decrement its elements when removing a vertex.
	 *     >> make sure that the result is correct.
	 *
	 * Add one more case of a directed acyclic graph, and run the function
	 *         "topologicalSort()" on it.
	 *     >> check that it reports a proper order.
	 *
	 * Add one other example of a graph with cycle, and check that the function
	 *         "topologicalSort()" returns empty sequence.
	 *
	 * Change the function 'topologicalSort()' again, so it will have a
	 *         queue of vertices which have no incoming edges.
	 *         "std::queue< int > q". Place vertices with no in-degree there,
	 *         and obtain the next vertex in O(1) time, using it.
	 *     >> make sure that the result is correct.
	 *
	 * Implement alternative variant of Kahn's algorithm on such adjacency list,
	 *         which describes incoming edges, not outgoing ones.
	 *     >> for that, present the same graph alternatively also.
	 *     >> check that results of running the alternative version is proper.
	 *
	 * [*] Change 'topologicalSort()' in such a way that it will restore not one
	 *         but all possible topological orderings. For that, make it to return
	 *         "std::vector< std::vector< int > > orders" by a reference argument.
	 *
	 * Implement Kahn's algorithm over adjacency matrix.
	 */


#include <vector>
#include <string>
#include <iostream>

#include "AdjacencyList.hpp"


/// Given an unweighted graph 'g', checks if the order of
/// its vertices provided by the 'vertices' argument represents
/// a topological order.
/// In other words, for every "i < j", there should NOT be edge
/// "vertices[j] -> vertices[i]" in 'g'.
bool isTopologicallySorted(
	const AdjacencyList& g,
	const std::vector< int >& vertices )
{
	std::vector<int> pos(g.size(), -1);
	for (int i = 0; i < (int)vertices.size(); ++i)
		pos[vertices[i]] = i;

	for (int u = 0; u < g.size(); ++u)
		for (int v : g._adj[u])
			if (pos[u] > pos[v])
				return false;

	return true;
}


/// Same as previous function, but vertices now are presented
/// as uppercase letters.
bool isTopologicallySorted(
    const AdjacencyList &g,
    const std::string &vertices) {
    std::vector<int> vs;
    for (char v: vertices)
        vs.push_back(v - 'A'); // Convert char to int
    return isTopologicallySorted(g, vs);
}


/// Performs Kahn's algorithm on provided graph 'g', by sequentially
/// removing edges and vertices from it.
/// In case if there is a cycle, returns empty sequence.
std::vector<int> topologicalSort(AdjacencyList g) {
    const int N = g.size(); // Number of vertices
    std::vector<int> result;
    std::vector<bool> isRemoved(N, false); // If vertex 'i' was removed
    // Repeatedly find a vertex with no incoming edges
    while ((int) result.size() < N) {
        // Check which vertices have no incoming edges
        std::vector<bool> hasIncoming(N, false);
        for (int u = 0; u < N; ++u)
            for (int v: g._adj[u])
                hasIncoming[v] = true; // An edge (u,v) is considered
        // Find the first vertex with no incoming edge
        int u = -1;
        for (u = 0; u < N; ++u)
            if (!isRemoved[u] && !hasIncoming[u])
                break; // Found 'u'
        if (u == -1) // If no such vertex was found
            return std::vector<int>(); // Empty result means there is a cycle
        // Now the vertex 'u' has no incoming edges:
        //    ... place it into result,
        result.push_back(u);
        //    ... and remove it from the graph
        g._adj[u].clear(); // Removing all edges which start at 'u'.
        isRemoved[u] = true;
    }
    return result;
}
std::vector< int > topologicalSort_degree
( AdjacencyList g )
{
	const int N = g.size();
	std::vector<int> degree(N, 0);
	for (int u = 0; u < N; ++u)
		for (int v : g._adj[u])
			++degree[v];

	std::vector<int> result;
	std::vector<bool> removed(N, false);
	while ((int)result.size() < N) {
		int u = -1;
		for (int i = 0; i < N; ++i)
			if (!removed[i] && degree[i] == 0) {
				u = i;
				break;
			}
		if (u == -1)
			return std::vector<int>();
		result.push_back(u);
		for (int v : g._adj[u])
			--degree[v];
		removed[u] = true;
	}
	return result;
}
#include <queue>

std::vector< int > topologicalSort_queue( const AdjacencyList& g )
{
	const int N = g.size();
	std::vector<int> degree(N, 0);
	for (int u = 0; u < N; ++u)
		for (int v : g._adj[u])
			++degree[v];

	std::queue<int> q;
	for (int i = 0; i < N; ++i)
		if (degree[i] == 0)
			q.push(i);

	std::vector<int> result;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		result.push_back(u);
		for (int v : g._adj[u])
			if (--degree[v] == 0)
				q.push(v);
	}
	return (result.size() == N) ? result : std::vector<int>();
}
std::vector<int> topologicalSortIncoming(const AdjacencyList& incoming)
{
	int N = incoming.size();
	std::vector<int> degree(N, 0);
	for (int u = 0; u < N; ++u)
		degree[u] = incoming._adj[u].size();

	std::queue<int> q;
	for (int i = 0; i < N; ++i)
		if (degree[i] == 0)
			q.push(i);

	std::vector<int> result;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		result.push_back(u);
		for (int v = 0; v < N; ++v)
			for (int src : incoming._adj[v])
				if (src == u && --degree[v] == 0)
					q.push(v);
	}
	return (result.size() == N) ? result : std::vector<int>();
}


/// Prints provided order of vertices in a readable form.
void printOrder(const std::vector<int> &order) {
    std::cout << " [";
    for (int v: order)
        std::cout << ' ' << char(v + 'A');
    std::cout << " ]" << std::endl;
}


using std::cout;
using std::endl;

int main() {
    /**
     *   A--->C--->E<---H
     *   |         ^    ^
     *   v         |    |
     *   F--->D    G    I
     *   |    |
     *   v    v
     *   B--->J<---K
     */
    AdjacencyList g('K' - 'A' + 1); // Maximal vertex is 'K'
    g.addEdge('A', 'C');
    g.addEdge('C', 'E');
    g.addEdge('G', 'E');
    g.addEdge('H', 'E');
    g.addEdge('I', 'H');
    g.addEdge('A', 'F');
    g.addEdge('F', 'D');
    g.addEdge('D', 'J');
    g.addEdge('F', 'B');
    g.addEdge('B', 'J');
    g.addEdge('K', 'J');

    cout << "\t Testing 'isTopologicallySorted()' ..." << endl; {
        std::string order1 = "AFBJDKGEHIC";
        cout << "Is the order '" << order1 << "' topologically sorted: "
                << isTopologicallySorted(g, order1) << endl;

        std::string order2 = "ACEIHGKFDBJ";
        cout << "Is the order '" << order2 << "' topologically sorted: "
                << isTopologicallySorted(g, order2) << endl;
    }

    cout << "\t Testing 'topologicalSort()' ..." << endl; {
        std::vector<int> order;
        order = topologicalSort(g);
        cout << "A topological order of vertices is:";
        printOrder(order);
    }
	{
    	AdjacencyList dag(5);  // 0->1->2, 0->3, 3->4
    	dag.addEdge(0, 1);
    	dag.addEdge(1, 2);
    	dag.addEdge(0, 3);
    	dag.addEdge(3, 4);

    	auto ord = topologicalSort(dag);
    	cout << "DAG order:";
    	printOrder(ord);
    	cout << "Is valid: " << isTopologicallySorted(dag, ord) << endl;
	}
	{
    	AdjacencyList cycleGraph(3); // 0->1->2->0
    	cycleGraph.addEdge(0, 1);
    	cycleGraph.addEdge(1, 2);
    	cycleGraph.addEdge(2, 0);

    	auto ord = topologicalSort(cycleGraph);
    	cout << "Cycle graph order:";
    	printOrder(ord);
    	cout << "Should be empty: " << (ord.empty() ? "yes" : "no") << endl;
	}


    return 0;
}
