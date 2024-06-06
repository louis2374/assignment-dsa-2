#include "Dijkstra.h"

bool Dijkstra::path_from_weights(const std::unordered_map<Label, NodeData>& _weights, Label _to, Label _from, std::vector<Label>& _path)
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
        if (_weights.at(current).parent == NO_NODE) return false;

        // Current node is set to the parent of itself
        current = _weights.at(current).parent;
    } while (current != _from);

    // Add the starting point to the path
    _path.push_back(_from);

    // Path is backwards, so reverse it
    std::reverse(_path.begin(), _path.end());

    // Success
    return true;
}

Dijkstra::Dijkstra(Graph _graph) : Pathfinder(_graph)
{

}

bool Dijkstra::find_route(Label _from, Label _to, std::vector<Label>& _path)
{
    // Stores a node against its shortest known route from the source, and the parent node, and if its checked
    //std::unordered_map<Label, std::pair<Weight, Label>> weights;
    std::unordered_map<Label, NodeData> weights;

    // Initialise all weights to infinite.
    // Add all nodes to not checked.
    std::vector<Label> all = graph.get_all();
    for (Label l : all)
    {
        weights.insert({ l, NodeData{ NO_NODE, std::numeric_limits<Weight>::max(), false} });
    }

    // Starting at the source.
    Label current = _from;
    weights.at(current).cost = 0;

    // While current node is not the final node.
    while (current != _to)
    {
        // Get all available new paths
        std::vector<Path> new_paths = graph.get_available_paths(current);

        // No paths from this node
        if (new_paths.empty())
        {
            // The current node has no parent, only case if the source has no routes.
            if (weights.at(current).parent == NO_NODE) return false;
        }

        // The node has paths
        else
        {
            // If a shorter path is found for any path, update it to the new weight and parent.
            for (Path& p : new_paths)
            {
                // Dont update a node that has already been completed
                if (weights.at(p.target).checked) continue;

                if (weights.at(p.target).cost > weights.at(current).cost + p.weight)
                {
                    // Update the old parent and cost to the one just found.
                    weights.at(p.target) = NodeData{ current, (Weight)(weights.at(current).cost + p.weight), weights.at(p.target).checked };
                }
            }
        }

        // Node is checked
        weights.at(current).checked = true;

        // Finds the lowest cost unchceked node
        int lowest_weight = std::numeric_limits<int>::max();
        for (auto& entry : weights)
        {
            // Dont check nodes that have been completed already.
            if (weights.at(entry.first).checked) continue;

            // Find the lowest weight.
            if (entry.second.cost < lowest_weight)
            {
                lowest_weight = entry.second.cost;

                // Update the current
                // This may happen multiple times but that should not be an issue
                current = entry.first;
            }
        }

        // No unchecked nodes, so break out
        if (lowest_weight == std::numeric_limits<int>::max()) break;
        
    }

    // After dijkstra, make the path from the weights.

    // This modifies the path array, and i can directly return the success.
    return path_from_weights(weights, _to, _from, _path);
}