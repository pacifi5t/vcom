#pragma once

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
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parentNode;

public:
    TreeNode(int id, TreeNode *left, TreeNode *right);
    TreeNode(int id, char s);

    int getWeight();
    void setWeight(int w);
    int getNodeId();
    void setNodeId(int id);
    char getSymbol();
    void setSymbol(char s);
    TreeNode *getLeftChild();
    void setLeftChild(TreeNode *child);
    TreeNode *getRightChild();
    void setRightChild(TreeNode *child);
    TreeNode *getParent();
    void setParent(TreeNode *parent);

    void incWeight();
};

TreeNode::TreeNode(int id, TreeNode *left, TreeNode *right)
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

TreeNode *TreeNode::getLeftChild()
{
    return leftChild;
}

void TreeNode::setLeftChild(TreeNode *child)
{
    leftChild = child;
}

TreeNode *TreeNode::getRightChild()
{
    return rightChild;
}

void TreeNode::setRightChild(TreeNode *child)
{
    rightChild = child;
}

TreeNode *TreeNode::getParent()
{
    return parentNode;
}

void TreeNode::setParent(TreeNode *parent)
{
    parentNode = parent;
}

void TreeNode::incWeight()
{
    weight++;
}
