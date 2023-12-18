#include <cassert>
#include <vector>
#include <unordered_map>
template<typename Node>
class NodeIndexer
{
public:
    NodeIndexer(const std::vector<std::vector<Node>>& adj, const int num_nodes):
        __num_nodes(num_nodes), __tour_len(0)
    {
        __dfs(adj, 1, 0);
    }
    int get_node_start(const Node node)
    {
        assert(1 <= node && node <= __num_nodes);
        return node_start[node];
    }
    int get_node_end(const Node node)
    {
        assert(1 <= node && node <= __num_nodes);
        return node_end[node];
    }
private:
    int __num_nodes;
    int __tour_len;
    std::unordered_map<Node, int> node_start;
    std::unordered_map<Node, int> node_end;
    void __dfs(const std::vector<std::vector<Node>>& adj, int curr_node, int prev_node)
    {
        __tour_len++;
        node_start[curr_node] = __tour_len - 1;
        for(Node next : adj[curr_node])
        {
            if(next == prev_node)
            {
                continue;
            }
            __dfs(adj, next, curr_node);
        }
        node_end[curr_node] = __tour_len - 1;
    }
};
