/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirrorHelper(root);
}
template <typename T>
void BinaryTree<T>::mirrorHelper(Node* rootNode){
    Node* temp = rootNode->left;
    rootNode->left = rootNode->right;
    rootNode->right = temp;
    if(rootNode->left != NULL){
        mirrorHelper(rootNode->left);
    }
    if(rootNode->right != NULL){
        mirrorHelper(rootNode->right);
    }
    return;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    return isOrderedIterativeHelper(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedIterativeHelper(Node* rootNode) const
{
    // your code here
    if(rootNode == NULL){
        return true;
    }
    
    std::stack<Node*> nodeStack;
    Node* curr = rootNode;
    Node* prev = NULL;
    while(curr != NULL || !nodeStack.empty()){
        while(curr != NULL){
            nodeStack.push(curr);
            curr = curr->left;
        }
        curr = nodeStack.top();
        nodeStack.pop();
        if(prev != NULL && prev->elem >= curr->elem){
            return false;
        }
        prev = curr;
        curr = curr->right;
    }
    return true;
}


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursiveHelper(root, -100000, 100000);
}
template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelper(Node* rootNode, T min, T max) const
{
    if(rootNode == NULL){
        return true;
    }
    if(rootNode->elem > max || rootNode->elem < min){
        return false;
    }

    return isOrderedRecursiveHelper(rootNode->left, min, rootNode->elem) && isOrderedRecursiveHelper(rootNode->right, rootNode->elem, max);
}


