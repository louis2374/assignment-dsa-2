#include "graph.h"

void Graph::add_path(Label _from, Label _to, Weight _weight)
{
	// Adds the path to the node if it already exists, or creates a new node.
	paths.count(_from) ? paths.at(_from).push_back({ _weight, _to }) : paths[_from].push_back({ _weight, _to });
}

std::vector<Path> Graph::get_available_paths(Label _from)
{
	// This will create an empty entry in the map if the label does not exist, this is not really a problem.
	return paths[_from];
}

std::vector<Label> Graph::get_all() const
{
	std::vector<Label> all;
	for (auto& n : paths) all.push_back(n.first);
	return all;
}

bool Graph::find_cost_of_route(std::vector<Label> _route, Weight& _weight)
{
	// Set to 0 incase it is not
	_weight = 0;

	for (int i = 0; i < _route.size() - 1; i++)
	{
		// Get paths from current node
		std::vector<Path> paths = get_available_paths(_route[i]);

		bool found = false;
		// Find cost to get to the next node in the route
		for (Path& p : paths)
		{
			// If this path is the path to the node
			if (p.target == _route[i + 1])
			{
				// Add the weight to total.
				_weight += p.weight;

				// Found the route, break out.
				found = true;
				break;
			}
		}

		// If it never found the route, return false
		if (!found) return false;
	}

	return true;
}

bool Path::operator<(const Path& _other) const
{
	return target < _other.target;
}
