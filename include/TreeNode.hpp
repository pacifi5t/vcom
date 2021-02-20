#pragma once

#include <memory>

using std::shared_ptr;

class TreeNode
{
    /**
     * If leftChild & rightChild == nullptr --> this == Leaf
     * If this == Leaf & weight == 0 --> this == NYT
     */

private:
    int weight;
    int nodeId;
    char symbol;
    shared_ptr<TreeNode> leftChild;
    shared_ptr<TreeNode> rightChild;
    shared_ptr<TreeNode> parentNode;

public:
    TreeNode(int id, shared_ptr<TreeNode> left, shared_ptr<TreeNode> right);
    TreeNode(int id, char s);

    int getWeight();
    void setWeight(int w);
    int getNodeId();
    void setNodeId(int id);
    char getSymbol();
    void setSymbol(char s);
    shared_ptr<TreeNode> getLeftChild();
    void setLeftChild(shared_ptr<TreeNode> child);
    shared_ptr<TreeNode> getRightChild();
    void setRightChild(shared_ptr<TreeNode> child);
    shared_ptr<TreeNode> getParent();
    void setParent(shared_ptr<TreeNode> parent);

    void incWeight();
};

TreeNode::TreeNode(int id, shared_ptr<TreeNode> left, shared_ptr<TreeNode> right)
{
    nodeId = id;
    symbol = 0;
    leftChild = left;
    rightChild = right;
    weight = left->getWeight() + right->getWeight();
}

TreeNode::TreeNode(int id, char symb)
{
    nodeId = id;
    symbol = symb;
    leftChild = nullptr;
    rightChild = nullptr;
    weight = symb;
}

int TreeNode::getWeight()
{
    return weight;
}

void TreeNode::setWeight(int w)
{
    weight = w;
}

int TreeNode::getNodeId()
{
    return nodeId;
}

void TreeNode::setNodeId(int id)
{
    nodeId = id;
}

char TreeNode::getSymbol()
{
    return symbol;
}

void TreeNode::setSymbol(char s)
{
    symbol = s;
}

shared_ptr<TreeNode> TreeNode::getLeftChild()
{
    return leftChild;
}

void TreeNode::setLeftChild(shared_ptr<TreeNode> child)
{
    leftChild = child;
}

shared_ptr<TreeNode> TreeNode::getRightChild()
{
    return rightChild;
}

void TreeNode::setRightChild(shared_ptr<TreeNode> child)
{
    rightChild = child;
}

shared_ptr<TreeNode> TreeNode::getParent()
{
    return parentNode;
}

void TreeNode::setParent(shared_ptr<TreeNode> parent)
{
    parentNode = parent;
}

void TreeNode::incWeight()
{
    weight++;
}
