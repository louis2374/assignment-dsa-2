#include "Pathfinder.h"
#include "Dijkstra.h"
#include <iostream>
#include "BFS.h"
#include <chrono>

int main()
{
	// True if the program should run time counts
	const bool RUN_TIME_COUNTER = true;

	// Create a graph
	Graph graph;

	// Add all the nodes to the graph and their paths

	// I put these in a block so i can minimise them
	{
		graph.add_path('A', 'B', 10);
		graph.add_path('A', 'D', 12);
		graph.add_path('A', 'G', 11);
		graph.add_path('A', 'H', 4);
		graph.add_path('B', 'A', 10);
		graph.add_path('B', 'D', 8);
		graph.add_path('B', 'H', 20);
		graph.add_path('C', 'D', 17);
		graph.add_path('C', 'E', 8);
		graph.add_path('C', 'G', 13);
		graph.add_path('C', 'H', 10);
		graph.add_path('D', 'A', 12);
		graph.add_path('D', 'B', 8);
		graph.add_path('D', 'C', 17);
		graph.add_path('D', 'F', 16);
		graph.add_path('D', 'G', 24);
		graph.add_path('D', 'H', 14);
		graph.add_path('E', 'C', 8);
		graph.add_path('E', 'F', 8);
		graph.add_path('E', 'G', 11);
		graph.add_path('E', 'H', 5);
		graph.add_path('F', 'D', 16);
		graph.add_path('F', 'E', 8);
		graph.add_path('F', 'G', 18);
		graph.add_path('F', 'H', 21);
		graph.add_path('G', 'A', 11);
		graph.add_path('G', 'C', 13);
		graph.add_path('G', 'D', 24);
		graph.add_path('G', 'E', 11);
		graph.add_path('G', 'F', 18);
		graph.add_path('G', 'H', 30);
		graph.add_path('H', 'A', 4);
		graph.add_path('H', 'B', 20);
		graph.add_path('H', 'C', 10);
		graph.add_path('H', 'D', 14);
		graph.add_path('H', 'E', 5);
		graph.add_path('H', 'F', 21);
		graph.add_path('H', 'G', 30);
	}


	// Instantiate a class of each
	// I only put them in classes to hide private functions
	// They dont need to be classes really
	Dijkstra dij(graph);
	BFS bfs(graph);

	// Create a path vector, the algs will mutate this
	std::vector<Label> path;

	// Similar to path, will be mutated by the find cost function
	Weight weight = 0;

	// Target and source for route
	Label to = 'F', from = 'A';

	// Find the route for Dijkstra
	if (!dij.find_route(from, to, path))
	{
		// Couldnt find route
		std::cout << "Failed to find path using Dijkstra from " << from << " to " << to << ".\n";
	}
	else
	{
		// Found the path, print it and its weight
		std::cout << "Dijkstra path: ";

		// Print each node
		for (int i = 0; i < path.size(); i++)
		{
			// If it is the last one, it prints cost instead of an arrow
			std::cout << (char)path[i] << (i == path.size() - 1 ? " Cost: " : " -> ");
		}

		// Find cost and print
		graph.find_cost_of_route(path, weight);
		std::cout << weight << '\n';
	}

	// Find the route for Breadth first search.
	if (!bfs.find_route(from, to, path))
	{
		// Couldnt find route
		std::cout << "Failed to find path using BFS from " << from << " to " << to << ".\n";
	}
	else
	{
		// Found the path, print it and its weight
		std::cout << "BFS path: ";

		// Print each node
		for (int i = 0; i < path.size(); i++)
		{
			// If it is the last one, it prints cost instead of an arrow
			std::cout << (char)path[i] << (i == path.size() - 1 ? " Cost: " : " -> ");
		}

		// Find cost and print
		graph.find_cost_of_route(path, weight);
		std::cout << weight << '\n';
	}
	
	// End early if no need to test time.
	if (!RUN_TIME_COUNTER) return 0;

	// These will have no output, but will run a basic speed test
	const int TEST_COUNT = 100000;

	int dijkstra_time, bfs_time;

	// Dijkstra
	{
		auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < TEST_COUNT; i++)
			{
				dij.find_route(from, to, path);
			}
		auto end = std::chrono::high_resolution_clock::now();

		dijkstra_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}

	// BFS
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < TEST_COUNT; i++)
		{
			bfs.find_route(from, to, path);
		}
		auto end = std::chrono::high_resolution_clock::now();

		bfs_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}

	std::cout << "Time taken for " << TEST_COUNT << " runs:\n"
		<< "Dijkstra: " << dijkstra_time << "ms\n"
		<< "BFS: " << bfs_time << "ms\n";

	// These are not the best way to time the function, as there will be discrepencies between cache hits
	// and compiler optimisations, however they are acceptable for demo purposes.
}