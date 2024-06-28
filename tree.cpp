/*
 * Title: Tree implementation
 * Purpose: Implementation of an expression tree that helps with building, traversing and evaluating expression
 * Author: Shadman Shahzahan
 * Date: May27, 2024
 */

#include <stack>
#include <complex>
#include <iomanip>
#include "tree.h"
#include "tree_node.h"

Tree::Tree(){ // Default Constructor the root points to nullptr
    _root = nullptr;
}
Tree::~Tree(){ // Destructor deletes the entire tree
    delete (_root);
}
bool Tree:: BuildTree(const string& postfixExpression){ // Builds the expression tree from a postfix expression
    std::stack<TreeNode*> stack;
    std::stringstream ss(postfixExpression);
    string element;
    // Process each element in the postfix expression
    while (getline(ss, element, ' ')){
        if(isOperator(element)){
            if(stack.size() < 2){
                return false; // Not enough operands for the operator
            }
            TreeNode* nodeSecond = stack.top(); stack.pop();
            TreeNode* nodeFirst = stack.top(); stack.pop();
            TreeNode* node = new TreeNode(element, nodeFirst, nodeSecond);
            stack.push(node);
        }
        else{
            stack.push(new TreeNode(element));
        }
    }
    if (stack.size() != 1){
        return false; // Invalid expression
    }
    _root = stack.top();
    return true;
}
// Traverses the tree in the specified order
string Tree::Traverse(TraversalType traversalType)const{
    string result;
    if (traversalType == PREORDER){
        PreorderTraverse(_root, result);
        // Removes the trailing space if present
        if (!result.empty() && result.back() == ' '){
            result.pop_back();
        }
    }
    else if (traversalType == INORDER){
        InorderTraverse(_root, result);
        // Removes the trailing space if present
        if (!result.empty() && result.back() == ' '){
            result.pop_back();
        }
    }
    else if (traversalType == POSTORDER){
        PostorderTraverse(_root, result);
        // Removes the trailing space if present
        if (!result.empty() && result.back() == ' '){
            result.pop_back();
        }
    }
    else {
        return "invalid traversal type";
    }
return result;
}
// Evaluate the expression represented by the tree
double Tree::Evaluate()const{
    // Evaluate the expression in PostOrder
   string str = this->Traverse(POSTORDER);
   std::stack<double> stack;
   string op;

   for (size_t i = 0; i < str.size(); i++){
       char t = str[i];
       if (isspace(t)) {
           if (!op.empty()) {
               stack.push(std::stod(op));
               op.clear();
           }
       }
       else if (isalpha(t)){
               return 0; // Invalid character in the expression
       }
       else if (isalnum(t) || t == '.'){
           op += t;
       }
       else{
           if (!op.empty()){
               stack.push(std::stod(op));
               op.clear();
           }
           double b = stack.top(); stack.pop();
           double a = stack.top(); stack.pop();
           switch (t){
               case '+':
                   stack.push(a + b);
                   break;
               case '-':
                   stack.push(a - b);
                   break;
               case '*':
                   stack.push(a * b);
                   break;
               case '/':
                   if (b == 0){
                       throw std::invalid_argument("Division by zero");
                   }
                   stack.push(a / b);
                   break;
               case '^':
                   stack.push(pow(a, b));
                   break;
               default:
                   throw std::invalid_argument("Invalid operator");
           }
       }
   }
   if (!op.empty()) {
       stack.push(std::stod(op));
   }
   if (stack.size() != 1){
       return 0; // Invalid expression
   }
   return stack.top();
}
// Outputs step-by-step evaluation of the expression tree
void Tree::StepByStepEvaluation(ostream& output, bool useLevel)const{
    if (_root == nullptr){
        return;
    }
    int level = 0;
    int idCount = 0;
    int parentId = -1;
    StepByStepEvaluation(output, _root, useLevel, level, idCount,parentId);
}
// Helper function to delete nodes recursively
void Tree::deleteNode(TreeNode *node) {
    if (node != nullptr){
        deleteNode(node->GetLeftChild());
        deleteNode(node->GetRightChild());
        delete node;
    }
}
// Checks if a string is an operator
bool Tree::isOperator(const std::string &element) const {
    if (element == "+" || element == "-" || element == "*" || element == "/" || element == "^"){
        return true;
    }
    return false;
}
// Helper for preorder traversal
void Tree::PreorderTraverse(TreeNode *node, std::string &result) const {
    if (node == nullptr){
        return;
    }
    result += node->GetData() + " ";
    PreorderTraverse(node->GetLeftChild(), result);
    PreorderTraverse(node->GetRightChild(), result);
}
// Helper for inorder traversal
void Tree::InorderTraverse(TreeNode *node, std::string &result) const {
    if (node == nullptr){
        return;
    }
    InorderTraverse(node->GetLeftChild(), result);
    result += node->GetData() + " ";
    InorderTraverse(node->GetRightChild(), result);
}
// Helper for postorder traversal
void Tree::PostorderTraverse(TreeNode *node, std::string &result) const {
    if (node == nullptr){
        return;
    }
    PostorderTraverse(node->GetLeftChild(), result);
    PostorderTraverse(node->GetRightChild(), result);
    result += node->GetData() + " ";
}
// Helper function for step-by-step evaluation
void Tree::StepByStepEvaluation(std::ostream& output, TreeNode* node, bool useLevel, int level, int& idCount, int parentId)const{
    if (node == nullptr){
        return;
    }
    string operatorSym;
    if (isOperator(node->GetData())){
        operatorSym = node->GetData();
    }
    else{
        operatorSym = "#";
    }
    if (useLevel){
        for (int i = 0; i < level; i++){
            output << "\t";
        }
    }
    int currentId = idCount++;

    output << "{\"value\":";
    if (operatorSym == "#"){
        output << std::stod(node->GetData());
    }
    else{
        double value = node->Evaluate();
        output << std::fixed << std::setprecision(2) << value;
    }
    output << ", \"operator\":\"" << operatorSym << "\"";
    output << ", \"operand\":";
    if (operatorSym == "#"){
        output << "true";
    }
    else{
        output << "false";
    }
    output << ", \"id\":" << currentId;
    output << ", \"parent\":" << parentId;
    output << "}\n";

    StepByStepEvaluation(output, node->GetLeftChild(), useLevel, level + 1, idCount, currentId);
    StepByStepEvaluation(output, node->GetRightChild(), useLevel, level + 1, idCount, currentId);
}