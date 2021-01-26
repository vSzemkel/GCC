
#include <iostream>
#include <memory>
#include <vector>

class tree_t {
  public:
    explicit tree_t(int label, tree_t* parent = nullptr) : _label(label), _parent(parent) {}
    tree_t* add_left(int label) { _left = std::make_unique<tree_t>(label, this); return const_cast<tree_t*>(_left.get()); }
    tree_t* add_right(int label) { _right = std::make_unique<tree_t>(label, this); return const_cast<tree_t*>(_right.get()); }
    tree_t* find_lca(int lbl1, int lbl2) const;
    tree_t* find(int label) const;
    int label() const {return _label; }
    int count_paths_to(int label);
    int count_size();

    int root_paths_sum() const;
    int subtrees_paths_sum() const;
  private:
    const tree_t* find_path(int label, std::vector<const tree_t*>& path) const;
    std::unique_ptr<tree_t> _left;
    std::unique_ptr<tree_t> _right;
    int _label;
    int _size{1};
    tree_t* _parent{nullptr};
};

tree_t* tree_t::find_lca(const int lbl1, const int lbl2) const
{
    std::vector<const tree_t*> path1, path2;
    const auto node1 = find_path(lbl1, path1);
    const auto node2 = find_path(lbl2, path2);
    if (node1 == nullptr || node2 == nullptr)
        return nullptr;
    int i, max = std::min(path1.size(), path2.size());
    for (i = 0; i < max && path1[i] == path2[i]; ++i)
        ;
    return const_cast<tree_t*>(path1[--i]);
}

const tree_t* tree_t::find_path(const int label, std::vector<const tree_t*>& path) const
{
    path.push_back(this);
    if (_label == label) return this;

    if (_left) {
        auto ret = _left->find_path(label, path);
        if (ret != nullptr) return ret;
    }
    if (_right) {
        auto ret = _right->find_path(label, path);
        if (ret != nullptr) return ret;
    }

    path.pop_back();
    return nullptr;
}

tree_t* tree_t::find(const int label) const
{
    if (label == _label) 
        return const_cast<tree_t*>(this);
    tree_t* ret{nullptr};
    if (_left) ret = _left.get()->find(label);
    if (ret != nullptr) return ret;
    if (_right) ret = _right.get()->find(label);
    return ret;
}

int tree_t::count_size()
{
    _size = 1;
    if (_left) _size += _left.get()->count_size();
    if (_right) _size += _right.get()->count_size();
    return _size;
}

int tree_t::root_paths_sum() const
{
    int ret{_size - 1};
    if (_left) ret += _left.get()->root_paths_sum();
    if (_right) ret += _right.get()->root_paths_sum();

    return ret;
}

int tree_t::subtrees_paths_sum() const
{
    int ret = root_paths_sum();
    if (_left) ret += _left.get()->subtrees_paths_sum();
    if (_right) ret += _right.get()->subtrees_paths_sum();

    return ret;
}

int tree_t::count_paths_to(const int label)
{
    auto n = find(label);
    if (n->_parent == nullptr)
        return n->root_paths_sum();

    return n->_parent->root_paths_sum() + this->_size - 2 * n->_size;
}

tree_t g_tree{1};

void init()
{
    auto n = g_tree.add_left(2);
    auto m = n->add_left(4);
    m->add_left(7);
    n = m->add_right(8);
    n->add_left(10);
    n = g_tree.add_right(3);
    n->add_left(5);
    n = n->add_right(6);
    n->add_right(9);
}

int main(int argc, char* argv[])
{
    init();

    std::cout << "Nodes count: " << g_tree.count_size() << "\n";
    std::cout << "Root paths sum: " << g_tree.root_paths_sum() << "\n";
    std::cout << "Subtrees paths sum: " << g_tree.subtrees_paths_sum() << "\n";
    std::cout << "Sum of paths to 3: " << g_tree.count_paths_to(3) << "\n";
    std::cout << "Lowest common ancestor of 7 and 10: " << g_tree.find_lca(7, 10)->label() << "\n";
}

/*
clang++.exe -Wall -ggdb3 -O0 -std=c++17 tree.cpp -o tree.exe
*/
