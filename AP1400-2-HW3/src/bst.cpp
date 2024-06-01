#include "bst.h"

#include <memory>
#include <queue>

BST::Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right){}

BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right){}

BST::Node::Node() : value(0), left(nullptr), right(nullptr){}

std::ostream& operator<<(std::ostream& out, const BST::Node& node)
{
    out << "Address: " << &node << "; "
    << "Value:  " << node.value << "; "
    << "Left child: " << node.left << "; "
    << "Right child: " << node.right << std::endl;

    return out;
}

bool BST::Node::operator<(int val) const
{
    return value < val;
}

bool BST::Node::operator>(int val) const
{
    return value > val;
}

bool BST::Node::operator<=(int val) const
{
    return value <= val;
}

bool BST::Node::operator>=(int val) const
{
    return value >= val;
}

bool BST::Node::operator==(int val) const
{
    return value == val;
}

bool operator<(int val, const BST::Node& node)
{
    return val < node.value;
}

bool operator>(int val, const BST::Node& node)
{
    return val > node.value;
}

bool operator<=(int val, const BST::Node& node)
{
    return val <= node.value;
}

bool operator>=(int val, const BST::Node& node)
{
    return val >= node.value;
}

bool operator==(int val, const BST::Node& node)
{
    return val == node.value;
}


BST::BST()
{
    root = nullptr;
}

static void copy_BST(BST::Node* src, BST::Node*& dst) {
    if (src) {
        dst = new BST::Node(src->value, 0, 0);
        copy_BST(src->left, dst->left);
        copy_BST(src->right, dst->right);
    }
}

BST::BST(const BST& bst) {
    this->root = new Node(bst.root->value, nullptr, nullptr);
    if (bst.root) {
        copy_BST(bst.root, root);
    }
}


BST::BST(const BST&& bst) noexcept
{
    root = bst.root;
}


BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    std::queue<Node*> que;
    que.push(root);
    while (!que.empty())
    {
        Node* node = que.front();
        que.pop();
        func(node);
        if (node->left != nullptr)
        {
            que.push(node->left);
        }
        if (node->right != nullptr)
        {
            que.push(node->right);
        }
    }
}

size_t BST::length() const
{
    size_t len = 0;
    auto getLength = [&len](BST::Node*& node){len++;};
    bfs(getLength);
    return len;
}

bool BST::add_node(int value)
{
    Node* newNode = new Node{value, nullptr, nullptr};
    auto tmp = get_root();
    Node* parent = nullptr;

    // Find the parent node. Add newNode to the back of newNdoe.
    while (tmp != nullptr)
    {
        parent = tmp;
        if (tmp->value == value)
        {
            delete newNode;
            return false;
        }
        else if (tmp->value > value)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
    }

    // If the tree is empty
    if (parent == nullptr)
    {
        root = newNode;
    }
    else
    {
        // If the children is empty
        if (parent->value > value)
        {
            parent->left = newNode;
        } else
        {
            parent->right = newNode;
        }
    }


    return true;
}


/*
 * 在这里我们动态分配内存res新建了一个指针
 * 这是因为在指针tmp为临时变量生命周期为这个函数完成时，所以在外界需要时会得到一个空指针。
 * 解决办法就是动态分配一个内存，生命周期不再仅限于这个周期了。
 * 之后的find_parent,find_successor函数也是如此
 */
BST::Node** BST::find_node(int value)
{
    auto tmp = get_root();
    Node** res = new Node*{nullptr};
    while (tmp != nullptr)
    {
        if (tmp->value == value)
        {
            *res = tmp;
            return res;
        }
        else if (tmp->value > value)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }

    }
    delete res;
    return nullptr;
}

BST::Node** BST::find_parrent(int value)
{
    auto tmp = get_root();
    Node** parent = new Node*{nullptr};
    while (tmp != nullptr)
    {
        if (tmp->value == value)
        {
            return parent;
        }
        else if (tmp->value > value)
        {
            *parent = tmp;
            tmp = tmp->left;
        }
        else
        {
            *parent = tmp;
            tmp = tmp->right;
        }
    }

    delete parent;
    return nullptr;
}


BST::Node** BST::find_successor(int value)
{
    auto node = find_node(value);
    if (node == nullptr) return nullptr;
    auto tmp = *node;
    tmp = tmp->left;
    while (tmp->right != nullptr)
    {
        tmp = tmp->right;
    }

    Node** res = new Node*{tmp};
    delete node;
    return res;
}


bool BST::delete_node(int value)
{
    auto node = find_node(value);
    // There is no such a node.
    if (node == nullptr) return false;
    auto deletedNode = *node;
    auto parent = *find_parrent(value);

    // There is no subtree.
    if (deletedNode->left == nullptr && deletedNode->right == nullptr)
    {
        if (parent->left != nullptr && parent->left->value == value)
        {
            parent->left = nullptr;
        }
        else if (parent->right != nullptr && parent->right->value == value)
        {
            parent->right = nullptr;
        }
        delete deletedNode;
        return true;
    }

    // There is only one left subtree.
    // or there is only one right subtree.
    Node* subtree = nullptr;
    if (deletedNode->left != nullptr && deletedNode->right == nullptr)
    {
        subtree = deletedNode->left;
    }
    if (deletedNode->left == nullptr && deletedNode->right != nullptr)
    {
        subtree = deletedNode->right;
    }
    if (subtree != nullptr)
    {
        if (parent->left != nullptr && parent->left->value == value)
        {
            parent->left = subtree;
        }
        else if (parent->right != nullptr && parent->right->value == value)
        {
            parent->right = subtree;
        }
        delete deletedNode;
        return true;
    }

    // There are both left subtree and right subtree.
    Node* successor = nullptr;
    if (deletedNode->left != nullptr && deletedNode->right != nullptr)
    {
        successor = *find_successor(value);
        auto successorParent = *find_parrent(successor->value);
        successorParent->right = nullptr;
        successor->left = deletedNode->left;
        successor->right = deletedNode->right;
        if (parent == nullptr)
        {
            root = successor;
            delete deletedNode;
            return true;
        }
        else if (parent->left != nullptr && parent->left->value == value)
        {
            parent->left = successor;
        }
        else if (parent->right != nullptr && parent->right->value == value)
        {
            parent->right = successor;
        }
        delete deletedNode;
        return true;
    }

}

std::ostream& operator<<(std::ostream& out, const BST& bst)
{
    out << "********************************************************************************" << std::endl;
    auto tmp = bst.root;
    auto output = [&out](BST::Node*& node)
    {
      out << node << "       => value: " << node->value << "       => left: " << node->left << "       => right: " <<
          node->right << std::endl;
    };

    bst.bfs(output);
    out << "binary search tree size: " << bst.length() << std::endl;
    out << "********************************************************************************" << std::endl;
}

BST& BST::operator=(const BST& bst)
{
    root = bst.root;
    return *this;
}

BST::BST(std::initializer_list<int> il) : root(nullptr)
{
    for (auto& value : il)
    {
        add_node(value);
    }
}

BST& operator++(BST& bst)
{
    auto add = [](BST::Node*& node){++node->value;};
    bst.bfs(add);
    return bst;
}

BST operator++(BST& bst, int)
{
    BST oldBst(bst);
    ++bst;
    return oldBst;
}

BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](Node*& node){nodes.push_back(node);});
    for (auto node : nodes)
    {
        delete node;
    }
}
