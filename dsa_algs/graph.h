#pragma once
#include <cstdint>
#include <unordered_map>
#include <vector>

// Makes reading the code easier, and allows me to quickly change the size if required
using Label = uint16_t;
using Weight = uint16_t;
#define NO_NODE 0

struct Path
{
	Weight weight;
	Label target;

	bool operator<(const Path& _other) const;
};

class Graph
{
	// Stores all paths, similar to "A -> B : 10"
	std::unordered_map<Label, std::vector<Path>> paths;

public:
	// Adds a path to a node
	void add_path(Label _from, Label _to, Weight _weight);

	// Gets all available paths from a given node
	std::vector<Path> get_available_paths(Label _from);

	// Gets all node labels.
	std::vector<Label> get_all() const;

	// Returns false if it failed to connect
	// Totals the weights into _weight
	// Some algs will do this when finding the route, some wont. So this is a kind of catchall
	bool find_cost_of_route(std::vector<Label> _route, Weight& _weight);
};

