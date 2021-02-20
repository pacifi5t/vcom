#pragma once

#include <list>
#include <map>
#include <string>

#include "TreeNode.hpp"

using std::list;
using std::map;
using std::string;

class AdaptiveTree
{
private:
    int nextNodeId;
    TreeNode *root, *NYTNode;
    map<char, TreeNode *> nodeMap;
    map<int, list<TreeNode *>> nodeWeightLists;

public:
    AdaptiveTree();
    ~AdaptiveTree();

    string getHuffmanCode(char symbol);
    void addSymbol(char symbol);
    TreeNode *createNode(char symbol);
    TreeNode *getNode(char symbol);
    void updateNode(TreeNode *node, int weight);
    void addNodeToMap(TreeNode *node, int weight);
    bool isRoot(TreeNode *node);
};

AdaptiveTree::AdaptiveTree()
{
    TreeNode nyt(255, 0);
    root = &nyt;
    NYTNode = &nyt;
    nextNodeId = 254;
}

AdaptiveTree::~AdaptiveTree()
{
    /**
     * TODO:clear tree?
     */
}

string AdaptiveTree::getHuffmanCode(char symbol)
{
    string result;
    bool root_node_found = false;
    TreeNode *current_node, *parent_node;

    if (!symbol)
    {
        current_node = NYTNode;

        if (isRoot(NYTNode))
        {
            return 0;
        }
    }
    else
    {
        current_node = nodeMap[symbol];
    }

    parent_node = current_node->getParent();

    while (!root_node_found)
    {
        result = parent_node->getRightChild() == current_node ? "1" + result : "0" + result;

        if (isRoot(parent_node))
        {
            root_node_found = true;
        }
        else
        {
            current_node = parent_node;
            parent_node = current_node->getParent();
        }
    }

    return result;
}

void AdaptiveTree::addSymbol(char symbol)
{
    TreeNode *node_to_edit = getNode(symbol);
    bool root_node_found = false;

    if (node_to_edit == nullptr)
    {
        node_to_edit = createNode(symbol);

        if (!isRoot(node_to_edit->getParent()))
        {
            addNodeToMap(node_to_edit->getParent(), 1);
        }

        addNodeToMap(node_to_edit, 1);
        node_to_edit = node_to_edit->getParent();
    }
    else
    {
        updateNode(node_to_edit, node_to_edit->getWeight() + 1);
        node_to_edit->incWeight();
    }

    if (isRoot(node_to_edit))
    {
        root_node_found = true;
    }

    TreeNode *temp = node_to_edit;

    while (!root_node_found)
    {
        temp = temp->getParent();

        if (isRoot(temp))
        {
            root_node_found = true;
        }
        else
        {
            updateNode(temp, temp->getWeight() + 1);
        }

        temp->incWeight();

        if (isRoot(temp))
        {
            root_node_found = true;
        }
    }
}

TreeNode *AdaptiveTree::createNode(char symbol)
{
    TreeNode new_node(nextNodeId, symbol);
    TreeNode new_parent_node(NYTNode->getNodeId(), NYTNode, &new_node);
    nextNodeId -= 2;
    NYTNode->setNodeId(new_parent_node.getNodeId() - 2);
    new_node.setParent(&new_parent_node);

    if (NYTNode->getParent() != nullptr)
    {
        if (NYTNode->getParent()->getLeftChild() == NYTNode)
        {
            NYTNode->getParent()->setLeftChild(&new_parent_node);
            new_parent_node.setParent(NYTNode->getParent());
        }
        else if (NYTNode->getParent()->getRightChild() == NYTNode)
        {
            new_parent_node.setParent(NYTNode->getParent());
            NYTNode->getParent()->setRightChild(&new_parent_node);
        }
    }
    else
    {
        root = &new_parent_node;
    }

    NYTNode->setParent(&new_parent_node);
    nodeMap[symbol] = &new_node;
    return &new_node;
}