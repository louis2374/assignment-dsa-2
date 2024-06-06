#include "BFS.h"

bool BFS::make_path(std::unordered_map<Label, Label>& _parents, Label _to, Label _from, std::vector<Label>& _path)
{
	// Incase this is not already empty
	_path.clear();

	// Starting at the target node
	Label current = _to;

	do
	{
		// Add the nodes to the path
		_path.push_back(current);

		// If this node has no parent, it failed to find a path
		if (!_parents.count(current)) return false;

		// Current node is set to the parent of itself
		current = _parents.at(current);
	} while (current != _from);
	
	// Add the starting point to the path
	_path.push_back(_from);

	// Path is backwards, so reverse it
	std::reverse(_path.begin(), _path.end());

	// Success
	return true;
}

BFS::BFS(Graph _graph) : Pathfinder(_graph)
{
}

bool BFS::find_route(Label _from, Label _to, std::vector<Label>& _path)
{
	// Stores each node to its parent node.
	std::unordered_map<Label, Label> parents;

	// The nodes which still need to be checked.
	std::queue<Label> queue;

	// Starting with the first item.
	queue.push(_from);

	// Parent node of the first node is unknown
	// []operator will create the element
	parents[_from] = -1;

	// Will check each node in the queue, untill it is empty
	while (!queue.empty())
	{
		// Get the first node in the queue and remove it from the queue
		Label current = queue.front();
		queue.pop();

		// If this new node is the target, create the path from the parents.
		// This will directly return success of construction of the path
		if (current == _to) return make_path(parents, _to, _from, _path);

		// Get all the available paths from the current node
		std::vector<Path> paths = graph.get_available_paths(current);

		// Check to see which paths have not been checked, and add them to the queue
		for (Path& p : paths)
		{
			// This node has not been checked yet, so add it to the queue
			if (!parents.count(p.target))
			{
				// Add it
				queue.push(p.target);

				// Set the parent to the current node of the outer
				parents[p.target] = current;
			}
		}
	}

	return false;
}
