class union_set 
{
public:
    union_set(int num_vals): parent(num_vals + 1), cmp_size(num_vals + 1)
    {
        for(int i = 1; i <= num_vals; i++)
        {
            parent[i] = i;
            cmp_size[i] = 1;
        }
    };
    int get_parent(int node)
    {
        if(parent[node] == node)
        {
            return node;
        }
        int compression = get_parent(parent[node]);
        parent[node] = compression;
        return compression;
    }
    bool join(int node1, int node2)
    {
        int node1_parent = get_parent(node1), node2_parent = get_parent(node2);
        if(node1_parent == node2_parent)
        {
            return false;
        }

        if(cmp_size[node1_parent] < cmp_size[node2_parent])
        {
            swap(node1_parent, node2_parent);
        }
        parent[node2_parent] = node1_parent;
        cmp_size[node2_parent] += cmp_size[node1_parent];
        return true;
    }
private:
    vector<int> parent;
    vector<int> cmp_size;
};
