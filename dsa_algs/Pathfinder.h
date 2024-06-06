#pragma once
#include "graph.h"

class Pathfinder
{
protected:
	Graph graph;

public:
	Pathfinder(Graph _graph);
	virtual bool find_route(Label _from, Label _to, std::vector<Label>& _path) = 0;
};

