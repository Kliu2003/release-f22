/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
     if(find(root, key) != NULL){
        return find(root, key)->value;
     }
     return V();
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if(subtree == NULL){
        return subtree;
    }
    else if(subtree->key == key){
        return subtree;
    }
    else if(subtree->key < key){
        return find(subtree->right, key);
    }
    else if(subtree->key > key){
        return find(subtree->left, key);
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    return;
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
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
     }
     else if(subtree->key > key){
        insert(subtree->left, key ,value);
     }
     return;
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    K tempKey = first->key;
    V tempVal = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = tempKey;
    second->value = tempVal;
    return;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    Node*& deleteNode = find(root, key);
    remove(deleteNode, key);
    return;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::findInOrderPredecessor(Node*& subtree){
    if(subtree->right == NULL){
        return subtree;
    }
    return findInOrderPredecessor(subtree->right);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
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
        // std::cout<<subtree->key<<std::endl;
        // std::cout<<subtree->left->key<<std::endl;
        // std::cout<<subtree->right->key<<std::endl;
        Node*& inOrderPredecessor = findInOrderPredecessor(subtree->left);
        // std::cout<<subtree->key<<std::endl;
        // std::cout<<subtree->left->key<<std::endl;
        // std::cout<<subtree->right->key<<std::endl;
        swap(subtree, inOrderPredecessor);
        remove(inOrderPredecessor, inOrderPredecessor->key);
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> bstPerm = BST<K,V>();
    for(std::pair<K, V> currPair: inList){
        bstPerm.insert(currPair.first, currPair.second);
    }
    return bstPerm;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int>hist;
    hist.resize(inList.size());
    sort(inList.begin(), inList.end());
    do{
        BST<K, V> currPerm = listBuild(inList);
        hist[currPerm.height()]++;
    }while(std::next_permutation(inList.begin(), inList.end()));

    return hist;
}