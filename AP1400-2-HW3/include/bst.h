#ifndef BST_H
#define BST_H
#include <functional>
#include <ostream>
#include <iostream>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        friend std::ostream& operator<<(std::ostream& out, const Node& node);
        /*
         * node > 4是一个类对象与整数之间的比较，需要在类中重载运算符
         * const 修饰符修饰成员函数声明不会改变class中对象的状态
         */
        bool operator<(int val) const;
        bool operator>(int val) const;
        bool operator<=(int val) const;
        bool operator>=(int val) const;
        bool operator==(int val) const;

        int value;
        Node* left;
        Node* right;
    };
    /*
     * Type*& fun()是一个函数声明，表示该函数返回一个指向指针的引用
     * Type* 表示一个指向'Type'类型对象的指针
     * '&' 表示引用
     */
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    /*
     * The 'successor' node is the node which has the largest value in the left subtree.
     * This node will move to the position in where a node will be deleted.
     */
    Node** find_successor(int value);
    /*
     * There are 4 situtions during we delete a node.
     * 1. There is no subtree.
     * 2. There is only one left subtree.
     * 3. There is only one right subtree.
     * 4. There are both left and right subtrees.
     *
     * The way to deal with 1:
     * Just delete it.
     *
     * The ways to deal with 2 and 3 are the same:
     * We only need to connect the subtree with the parent node of the node which is deleted.
     *
     * The way to deal with 3:
     * We need to move the node which has largest value of the left tree to the position which contains the deleted node.
     */
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& out, const BST& bst);
    BST();
    BST(const BST& bst);
    // Move constructor should be declared "noexcept".
    BST(const BST&& bst) noexcept;
    BST& operator=(const BST& bst);
    BST(std::initializer_list<int> il);
    ~BST();

private:
    Node* root;
};

/*
 * 4 > node 是整数与类的比较， 需要使用非成员函数重载运算符
 * 且在非成员函数中不能使用const修饰符修饰
 */
bool operator<(int val, const BST::Node& node);
bool operator>(int val, const BST::Node& node);
bool operator<=(int val, const BST::Node& node);
bool operator>=(int val, const BST::Node& node);
bool operator==(int val, const BST::Node& node);

BST& operator++(BST& bst);
BST operator++(BST& bst, int);

#endif //BST_H