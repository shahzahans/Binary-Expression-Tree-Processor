/*
 * Title: Tree_node implementation
 * Purpose: Tree_node class represent a node in a binary expression tree, holding an operand or operator and providing methods for construction,
 * deep copying, evaluation and memory management.
 * Author: Shadman Shahzahan
 * Date: May27, 2024
 */

#include <stdexcept>
#include "tree_node.h"

TreeNode::TreeNode(){  // Default constructor initializes the left and right children to nullptr
    left = nullptr;
    right = nullptr;
}
// Constructor initializes the data, left, and right children
TreeNode::TreeNode(const string& data, TreeNode* leftNode, TreeNode* rightNode): data(data), left(leftNode), right(rightNode){}

TreeNode::TreeNode(const TreeNode& other): data(other.data){ // Copy constructor performs a deep copy of the given TreeNode
    if (other.left != nullptr){
        this->left = new TreeNode(*other.left);
    }
    else{
        this->left = nullptr;
    }
    if (other.right != nullptr){
        this->right = new TreeNode(*other.right);
    }
    else{
        this->right = nullptr;
    }
}
// Destructor recursively deletes the left and right children
TreeNode::~TreeNode(){
    delete left;
    delete right;
}
// Assignment operator performs a deep copy of the given TreeNode
TreeNode &TreeNode::operator=(const TreeNode& other){
    if (this != &other){
        delete left;
        delete right;

        data = other.data;
        if (other.left){
            left = new TreeNode(*other.left);
        }
        else{
            left = nullptr;
        }
        if (other.right){
            right = new TreeNode(*other.right);
        }
        else{
            right = nullptr;
        }
    }
    return *this;
}
// Function to get the data stored in the node
string TreeNode::GetData() const{
    return data;
}
// Function to get the right child of the node
TreeNode *TreeNode::GetRightChild() const {
    return right;
}
// Function to get the left child of the node
TreeNode *TreeNode::GetLeftChild() const {
    return left;
}
// Function to evaluate the expression represented by the tree rooted at this node
double TreeNode::Evaluate() const {
    if (!isOperator(data)){
        return std::stod(data);
    }
    double leftVal = 0;
    double rightVal = 0;

    if (left){
        leftVal = left->Evaluate();
    }
    if (right){
        rightVal = right->Evaluate();
    }
    switch (data[0]) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal == 0){
                throw std::invalid_argument("Division by zero");
            }
            return leftVal / rightVal;
        case '^':
            return pow(leftVal, rightVal);
        default:
            throw std::invalid_argument("Invalid operator");
    }
}
// Helper function to check if string is an operator
bool TreeNode::isOperator(const std::string &element) {
    if (element == "+" || element == "-" || element == "*" || element == "/" || element == "^"){
        return true;
    }
    return false;
}