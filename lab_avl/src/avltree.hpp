/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <math.h>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* currRight = t->right;
    t->right = t->right->left;
    currRight->left = t;
    t = currRight;
    t->height = 1+std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t->left->height = 1+std::max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* currLeft = t->left;
    t->left = t->left->right;
    currLeft->right = t;
    t = currLeft;
    t->height = 1+std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t->right->height = 1+std::max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL){
        return;
    }
    // your code here
    Node* leftChild = subtree->left;
    Node* rightChild = subtree->right;

    int balanceFactor = heightOrNeg1(leftChild) - heightOrNeg1(rightChild);

    if(balanceFactor > 1){
        int balanceFactorLeft = heightOrNeg1(leftChild->left) - heightOrNeg1(leftChild->right);
        if(balanceFactorLeft > 0){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    else if(balanceFactor < -1){
        int balanceFactorRight = heightOrNeg1(rightChild->left) - heightOrNeg1(rightChild->right);
        if(balanceFactorRight < 0){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    return;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(subtree == NULL){
        Node* newNode = new Node(key, value);
        subtree = newNode;
        return;
    }
    else if(subtree->key == key){
        return;
    }
    else if(subtree->key < key){
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
    else if(subtree->key > key){
        insert(subtree->left, key ,value);
        rebalance(subtree);
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
struct AVLTree<K, V>::Node* & AVLTree<K, V>::findInOrderPredecessor(Node*& subtree){
    if(subtree->right == NULL){
        return subtree;
    }
    return findInOrderPredecessor(subtree->right);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (key < subtree->key) {
        remove(subtree->left, key);    
    } 
    else if (key > subtree->key) {
        remove(subtree->right, key);
    } 
    else{
        if(subtree == NULL){
            return;
        }
        else if(subtree->left == NULL && subtree->right == NULL){
            delete subtree;
            subtree = NULL;
            return;
        }
        else if(subtree->left == NULL){
            Node* temp = subtree->right;
            delete subtree;
            subtree = temp;
            return;
        }
        else if(subtree->right == NULL){
            Node* temp = subtree->left;
            delete subtree;
            subtree = temp;
            return;
        }
        else{
            Node*& inOrderPredecessor = findInOrderPredecessor(subtree->left);
            swap(subtree, inOrderPredecessor);
            remove(inOrderPredecessor, inOrderPredecessor->key);
        }
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
