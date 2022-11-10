/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] != second[curDim]){
      return first[curDim] < second[curDim];
    }
    return first<second;

}


template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int sumSquareCurrent = 0;
    int sumSquarePotential = 0;
    for(int i = 0; i < Dim; i++){
      sumSquareCurrent+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
      sumSquarePotential+=(potential[i]-target[i])*(potential[i]-target[i]);
     }
    if(sumSquarePotential != sumSquareCurrent){
      return sumSquarePotential < sumSquareCurrent;
    }
    return potential < currentBest;
}



template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int low, int high, int pivotIndex, int currDim) {
    /**
     * @todo Implement this function!
     */
    Point<Dim> pivotPoint = newPoints[pivotIndex];
    std::swap(newPoints[pivotIndex], newPoints[high]);
    int storeIndex = low;
    for(int i = low; i < high; i++){
      if(smallerDimVal(newPoints[i], pivotPoint, currDim)){
        std::swap(newPoints[storeIndex], newPoints[i]);
        storeIndex++;
      }
    }
    std::swap(newPoints[high], newPoints[storeIndex]);
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& newPoints, int low, int high, int k, int currDim){
    /**
     * @todo Implement this function!
     */

     if(low == high){
      return newPoints[low];
     }
     int pivotIndex = (low+high)/2;
     pivotIndex = partition(newPoints, low, high, pivotIndex, currDim);

     if(k == pivotIndex){
      return newPoints[k];
     }
     else if(k < pivotIndex){
      return select(newPoints, low, pivotIndex-1, k, currDim);
     }
     else{
      return select(newPoints, pivotIndex+1, high, k, currDim);
     }
}

template <int Dim>
void KDTree<Dim>::generateKDTree(KDTreeNode*& root, vector<Point<Dim>>& newPoints, int low, int high, int currDim)
{
    /**
     * @todo Implement this function!
     */
     if(low > high){
      return;
     }
     int median = (low+high)/2;
     Point<Dim> medianPoint = select(newPoints, low, high, median, currDim);
     root = new KDTreeNode(medianPoint);
     generateKDTree(root->left, newPoints, low, median-1, (currDim+1)%Dim);
     generateKDTree(root->right, newPoints, median+1, high, (currDim+1)%Dim);
     return;
     
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>>points = newPoints;
    if(points.empty()){
      root = NULL;
    }
    else{
      generateKDTree(root, points, 0, points.size()-1, 0);
      std::cout<<"reached here"<<std::endl;
    }
}

template <int Dim>
void KDTree<Dim>::copy_(KDTreeNode*& thisNode, KDTreeNode*& otherNode){
  if(otherNode == NULL){
    return;
  }
  thisNode = new KDTreeNode(otherNode->point);
  copy_(thisNode->left, otherNode->left);
  copy_(thisNode->right, otherNode->right);
}

template <int Dim>
void KDTree<Dim>::delete_(KDTreeNode*& rootNode){
  if(rootNode == NULL){
    return;
  }
  if(rootNode->left == NULL && rootNode->right == NULL){
    delete rootNode;
    return;
  }
  delete_(rootNode->left);
  delete_(rootNode->right);
  delete rootNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy_(this->root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  delete_(this->root);
  copy_(this->root, rhs->root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete_(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //
    if(root == NULL){
      return Point<Dim>();
    }
    return findNearestNeighborHelper(root, query, root->point, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(KDTreeNode* currNode, const Point<Dim> query, Point<Dim> currBest, int currDim) const
{
  /**
    * @todo Implement this function!
    */

  bool checkLeft = true;

  if(currNode->left == NULL && currNode->right == NULL){
    return currNode->point;
  }

  if(smallerDimVal(query, currNode->point, currDim)){
    if(currNode->left != NULL){
      currBest = findNearestNeighborHelper(currNode->left, query, currBest, (currDim + 1) % Dim);
    }
    else{
      currBest = findNearestNeighborHelper(currNode->right, query, currBest, (currDim + 1) % Dim);
      checkLeft = false;
    }
  }
  else{
    if(currNode->right != NULL){
      currBest = findNearestNeighborHelper(currNode->right, query, currBest, (currDim + 1) % Dim);
      checkLeft = false;
    }
    else{
      currBest = findNearestNeighborHelper(currNode->left, query, currBest, (currDim + 1) % Dim);
    }
  }


  if(shouldReplace(query, currBest, currNode->point)){
    currBest = currNode->point;
  }

  double currBestDist = 0.0;
  for(int i = 0; i < Dim; i++){
    currBestDist += (currBest[i]-query[i])*(currBest[i]-query[i]);
  }

  double onedDist = (currNode->point[currDim]-query[currDim])*(currNode->point[currDim]-query[currDim]);

  if(currBestDist >= onedDist){
    if(checkLeft && currNode->right != NULL){
      Point<Dim> checkOther = findNearestNeighborHelper(currNode->right, query, currBest, (currDim + 1) % Dim);
      if(shouldReplace(query, currBest, checkOther)){
        currBest = checkOther;
      }
    }
    else if(!checkLeft && currNode->left != NULL){
      Point<Dim> checkOther = findNearestNeighborHelper(currNode->left, query, currBest, (currDim + 1) % Dim);
      if(shouldReplace(query, currBest, checkOther)){
        currBest = checkOther;
      }
    }
  }
  return currBest;
}

