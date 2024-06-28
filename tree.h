//
// Created by Carlos R. Arias on 4/28/23.
//

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
using std::string;
using std::ostream;


#include "tree_node.h"


enum TraversalType {INORDER, PREORDER, POSTORDER};


class Tree {
private:
    TreeNode* _root; // Root node of the tree
    Tree(const Tree& other); // Private copy constructor to prevent copying
    const Tree& operator=(const Tree& rhs); // Private assignment operator to prevent copying
    void PreorderTraverse(TreeNode* node, string& result) const; // Helper function for preorder traversal
    void InorderTraverse(TreeNode* node, string& result) const; // Helper function for Inorder traversal
    void PostorderTraverse(TreeNode* node, string& result) const; // Helper function for Postorder traversal
    void deleteNode(TreeNode* node); // Helper function to delete nodes recursively
    bool isOperator(const string& element) const; // Checks if a string is an operator
    // Helper function for step-by-step evaluation
    void StepByStepEvaluation(ostream& output, TreeNode* node, bool useLevel, int level, int& idCount, int parentId)const;

public:
    Tree(); // Default constructor
    ~Tree(); // Destructor
    bool BuildTree(const string& postfixExpression); // Build function for Tree
    string Traverse(TraversalType traversalType)const; // Traverse function for tree
    double Evaluate()const; // Evaluation function to evaluate
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const; // Outputs step-by-step evaluation of the expression tree
};

#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_H
