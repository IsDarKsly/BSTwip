#pragma once

template <class type>
class node
{ 
public:
    type value;
    int height;
    node* left;
    node* right;
    node* parent;

    node(type v) : value{v}, left(nullptr), right(nullptr), parent(nullptr) {height = 0;}; //Constructor assigns value to v

    void updateHeight() //Updates the height of the node based on its childrens values
    {
        height = ((left == nullptr ? 0 : left->height) >= (right == nullptr ? 0 : right->height) ? (left == nullptr ? 0 : left->height) : (right->height)) + 1; //Jesus help me if left isnt nullptr and its height is greater/equal to right(if it isnt nllptr) than return left.height (unless it was nullptr then return 0)
    };

};