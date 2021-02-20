#pragma once

#include <list>
#include <map>
#include <string>
#include <memory>
#include <algorithm>

#include "TreeNode.hpp"

using std::list;
using std::map;
using std::shared_ptr;
using std::string;

class AdaptiveTree
{
private:
    int nextNodeId;
    shared_ptr<TreeNode> root, NYTNode;
    map<char, shared_ptr<TreeNode>> nodeMap;
    map<int, list<shared_ptr<TreeNode>>> nodeWeightLists;

public:
    AdaptiveTree();
    ~AdaptiveTree();

    string getHuffmanCode(char symbol);
    void addSymbol(char symbol);
    shared_ptr<TreeNode> createNode(char symbol);
    shared_ptr<TreeNode> getNode(char symbol);
    void updateNode(shared_ptr<TreeNode> node, int weight);
    void addNodeToMap(shared_ptr<TreeNode> node, int weight);
    void editListPosition(shared_ptr<TreeNode> node, int index_from_end, int weight);
    void swapNodes(shared_ptr<TreeNode> first_node, shared_ptr<TreeNode> second_node);
    bool isRoot(shared_ptr<TreeNode> node);
    bool isHighestInWeightList(shared_ptr<TreeNode> node);
    bool isSecondHighestInWeightList(shared_ptr<TreeNode> node);
};

AdaptiveTree::AdaptiveTree()
{
    //TreeNode nyt(255, 0);
    shared_ptr<TreeNode> nyt = std::make_shared<TreeNode>(255, 0);
    root = nyt;
    NYTNode = nyt;
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
    shared_ptr<TreeNode> current_node, parent_node;

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
    shared_ptr<TreeNode> node_to_edit = getNode(symbol);
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

    shared_ptr<TreeNode> temp = node_to_edit;

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

shared_ptr<TreeNode> AdaptiveTree::createNode(char symbol)
{
    shared_ptr<TreeNode> new_node = std::make_shared<TreeNode>(nextNodeId, symbol);
    shared_ptr<TreeNode> new_parent_node = std::make_shared<TreeNode>(NYTNode->getNodeId(), NYTNode, new_node);
    nextNodeId -= 2;
    NYTNode->setNodeId(new_parent_node->getNodeId() - 2);
    new_node->setParent(new_parent_node);

    if (NYTNode->getParent() != nullptr)
    {
        if (NYTNode->getParent()->getLeftChild() == NYTNode)
        {
            NYTNode->getParent()->setLeftChild(new_parent_node);
            new_parent_node->setParent(NYTNode->getParent());
        }
        else if (NYTNode->getParent()->getRightChild() == NYTNode)
        {
            new_parent_node->setParent(NYTNode->getParent());
            NYTNode->getParent()->setRightChild(new_parent_node);
        }
    }
    else
    {
        root = new_parent_node;
    }

    NYTNode->setParent(new_parent_node);
    nodeMap[symbol] = new_node;
    return new_node;
}

void AdaptiveTree::updateNode(shared_ptr<TreeNode> node, int weight)
{
    list<shared_ptr<TreeNode>> list_to_edit;

    if(isRoot(node->getParent()))
    {
        if(!isHighestInWeightList(node))
        {
            editListPosition(node, 0, weight);
        }
        else
        {
            nodeWeightLists[node->getWeight()].pop_back();
            addNodeToMap(node, node->getWeight() + 1);
        }
    }
    else if(!isHighestInWeightList(node) && !isHighestInWeightList(node->getParent()))
    {
        editListPosition(node, 0, weight);
    }
    else if(isHighestInWeightList(node->getParent()) && !isSecondHighestInWeightList(node))
    {
        editListPosition(node, 1, weight);
    }
    else if(isHighestInWeightList(node->getParent()) && isSecondHighestInWeightList(node))
    {
        list_to_edit = nodeWeightLists[node->getWeight()];
        list_to_edit.erase(((list_to_edit.end()--)--));
        addNodeToMap(node, weight);
    }
    else
    {
        list<shared_ptr<TreeNode>> temp = nodeWeightLists[node->getWeight()];
        temp.erase(temp.end());
        addNodeToMap(node, weight);
    }
}

void AdaptiveTree::editListPosition(shared_ptr<TreeNode> node, int index_from_end, int weight)
{
    list<shared_ptr<TreeNode>> new_list = nodeWeightLists[node->getWeight()];
    auto highest_node_iter = new_list.end();

    int i = 0;
    while(i <= index_from_end)
    {
        highest_node_iter--;
        i++;
    }

    auto pos_iter = std::find(new_list.begin(), new_list.end(), node);
    shared_ptr<TreeNode> highest_node = *(new_list.erase(highest_node_iter));
    new_list.insert(pos_iter, highest_node);
    addNodeToMap(node, weight);
    swapNodes(node, highest_node);
}

void AdaptiveTree::addNodeToMap(shared_ptr<TreeNode> node, int weight)
{
    list<shared_ptr<TreeNode>> new_list = nodeWeightLists[weight];
    bool place_found = false;

    if(&new_list == nullptr)
    {
        new_list = list<shared_ptr<TreeNode>>();
        new_list.push_back(node);
        nodeWeightLists.insert({weight, new_list});
    }
    else
    {
        if(new_list.size() == 0)
        {
            new_list.push_back(node);
        }
        else
        {
            auto iter = new_list.begin();
            shared_ptr<TreeNode> current_node;
            while(!place_found)
            {
                current_node = *iter;

                if(current_node->getNodeId() > node->getNodeId())
                {
                    new_list.insert(iter, node);
                    place_found = true;
                }

                iter++;

                if(new_list.end() == iter)
                {
                    new_list.push_back(node);
                    place_found = true;
                }
            }
        }
    }
}