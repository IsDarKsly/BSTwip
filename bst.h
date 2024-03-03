#pragma once
#include "node.h"
#include <iostream>
#include <functional>

//ONLY SUPPORTS CLASS TYPES, PRIMITIVE TYPES WITHOUT MEMBERS WILL NOT WORK
//HAS AUTO SORTING IMPLIMENTATION

template <class nodeType, class sortType, sortType nodeType::* sortValue> // (class nodeType, class sortType, sortType nodeType::* sortValue) Needs the type of node this tree will hold, the type of data this tree will sort by, and the direct member reference to the data being sorted
class bst
{
public:
    node<nodeType>* root;

    bst(nodeType obj): root(new node<nodeType>(obj)){}; //constructor takes object being stored in node, creates root node with value as object

    bst(): root(nullptr){}; //default constructor

    void print() //prints out the value of sort if it exists, if not prints out the value of roots value
    {
        std::cout << root->value.*sortValue << std::endl;
    };

    bool add(nodeType obj)
    {
        node<nodeType>* n = new node<nodeType>(obj); //Creates a new node holding the object
        if (root == nullptr) //The tree is empty
        {
            root = n; //set the root of the tree to n
            n->updateHeight(); //updateHeight of root
            return true;
        }

        //Otherwise, we run a recursive function, moving either right or left to find the next empty space

        sortType value = n->value.*sortValue; //record what we are sorting by

        std::function<void(node<nodeType>* currentNode)> func = [&](node<nodeType>* currentNode)
        {
            //We check left and then check right
            if(value < currentNode->value.*sortValue) //We are less than the current node
            {
                if(currentNode->left==nullptr) //Left node is empty or we are greater than the left node sort value
                {
                    currentNode->left = n; //assign values
                    n->parent = currentNode; //asiign values
                }
                else
                {
                    func(currentNode->left); //traverse inwards
                }
            }
            else
            {
                if(currentNode->right==nullptr) //Left node is empty or we are greater than the left node sort value
                {
                    currentNode->right = n; //assign values
                    n->parent = currentNode; //asiign values
                }
                else
                {
                    func(currentNode->right); //traverse inwards
                }
            }
            //We have finished whatever task we set out to accomplish
            rebalance(currentNode);
        };
        func(root);

        return true;
    };

    void rebalance(node<nodeType>* n) //checks the balance of the node, and rebalances if necessary
    {
        node<nodeType>* parent = n->parent;
        int b = balanceFactor(n); //Checks balance of node
        if (b*b < 2) 
        {
            n->updateHeight(); 
            return;
        } //We arent that heavy (1*1=1, -1*-1=1, 0*0=0).

        if (b > 1) //right heavy
        {
            b = balanceFactor(n->right); //Check right child
            if (b < 0) //right child is left heavy, additional rotation needed
            {
                n->right = rotateRight(n->right);
                n->right->parent = n;
            }

            node<nodeType>* newRight = rotateLeft(n);

            if(parent != nullptr) //There was a parent object
            {
                parent->right = newRight;
            }
            else //With no parent node, we can safely assume the root is the newRight
            {
                root = newRight;
            }
            newRight->parent = parent;
        }
        else if(b < -1) //left heavy
        {
            b = balanceFactor(n->left); //Check left child
            if (b > 0) //left child is right heavy, additional rotation needed
            {
                n->left = rotateLeft(n->left);
                n->left->parent = n;
            } 
            node<nodeType>* newLeft = rotateRight(n);

            if(parent != nullptr)
            {
                parent->left = newLeft;
            }
            else //With no parent node, we can safely assume the root is the newLeft
            {
                root = newLeft;
            }
            newLeft->parent = parent;
        }
    };

    int getNodeHeight(node<nodeType>* n) //returns nodes own height, unless null
    {
        if (n == nullptr) return -1;

        return n->height;
    };

    int balanceFactor(node<nodeType>* node) //measures the balance of the current node
    {
        return (getNodeHeight(node->right) - getNodeHeight(node->left));
    };

    node<nodeType>* rotateRight(node<nodeType>* n) //Rotates the selected node to the right
    {
        node<nodeType>* l = n->left;
        n->left = l->right;
        if(n->left != nullptr)
        {
            n->left->parent = n;
        }
        l->right = n;
        n->parent = l;
        n->updateHeight();
        l->updateHeight();
        return l;
    };

    node<nodeType>* rotateLeft(node<nodeType>* n)
    {
        node<nodeType>* r = n->right;
        n->right = r->left;
        if(n->right != nullptr)
        {
            n->right->parent = n;
        }
        r->left = n;
        n->parent = r;
        n->updateHeight();
        r->updateHeight();
        return r;
    };
};