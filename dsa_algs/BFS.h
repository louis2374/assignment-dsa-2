#pragma once
#include "Pathfinder.h"
#include <queue>
#include <iostream>

class BFS : public Pathfinder
{
	// Creates a path backwards from the target then reverses it
	bool make_path(std::unordered_map<Label, Label>& _parents, Label _to, Label _from, std::vector<Label>& _path);
public:
	BFS(Graph _graph);

	// Performs a breadth first search to find any path between the given nodes.
	bool find_route(Label _from, Label _to, std::vector<Label>& _path);
};

