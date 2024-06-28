//
// Created by Carlos R. Arias on 5/2/23.
//

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
#include <cmath>
using std::string;

class TreeNode {
    string data; // Data stored in the node
    // Pointers to the left and right of the node
    TreeNode* left;
    TreeNode* right;

    // Helper function to check if a string is an operator
    static bool isOperator(const string& element);
public:
    TreeNode(); // Default constructor
    TreeNode(const string& data, TreeNode* leftNode = nullptr, TreeNode* rightNode = nullptr); // Constructor
    TreeNode(const TreeNode& other); // Copy Constructor
    TreeNode& operator=(const TreeNode& other); // Assignment operator
    ~TreeNode(); // Destructor
    string GetData() const; // GetData function to get data
    TreeNode* GetLeftChild() const; // Get-left-child function to get left child
    TreeNode* GetRightChild() const; // Get-right-child function to get right child
    double Evaluate() const; // Evaluation function
};


#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_NODE_H
