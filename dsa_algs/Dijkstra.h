#pragma once
#include "Pathfinder.h"
#include <set>
#include <algorithm>
#include <iostream>
#include <limits>

class Dijkstra : public Pathfinder
{

	struct NodeData
	{
		Label parent;
		Weight cost;
		bool checked;
	};

	// Builds a path from the output of dijkstras, (the weights), backwards then reverses it.
	bool path_from_weights(const std::unordered_map<Label,NodeData>& _weights, Label _to, Label _from, std::vector<Label>& _path);
public:
	Dijkstra(Graph _graph);

	bool find_route(Label _from, Label _to, std::vector<Label>& _path);
};

