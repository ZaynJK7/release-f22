/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
  if (first[curDim] == second[curDim]) {
    return first < second;
  }
  return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    size_t currDist = 0;
    size_t potDist = 0;

    for (size_t i = 0; i < Dim; i++) {
      currDist += pow(target[i] - currentBest[i], 2);
      potDist += pow(target[i] - potential[i], 2);
    }
    if (currDist == potDist) {
      return potential < currentBest;
    }
    return potDist < currDist;
}
















template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     //handle the case that the vector has no Point in it.
     if(newPoints.empty()){
       root = NULL;
       size = 0;
     }
     else{
       //copying the input list of points into a points vector
       vector<Point<Dim>> points = newPoints;
       size = 0;
       constructKD(points, 0, points.size() - 1, 0, root);
     }

}


template <int Dim>
void KDTree<Dim>::constructKD(vector<Point<Dim>>& newPoints, int left, int right,
                              int dimension, KDTreeNode*& subroot)
                              //subroot must be passed by reference!!
                              //subroot must be passed by reference!!
                              //subroot must be passed by reference!!
//You would want to pass a pointer by reference
//if you have a need to modify the pointer
//rather than the object that the pointer is pointing to.
{
  if(left > right){ //base case
    return;
  }
  size_t median = (left + right) / 2;

  Point<Dim> temp = quickSelect(newPoints, left, right, median, dimension);
  subroot = new KDTreeNode(temp);
  size++;
  if(subroot == NULL){cout << "subroot is null\n"<< endl;}
  constructKD(newPoints, left, median - 1, (dimension + 1) % Dim, subroot->left);
  constructKD(newPoints, median + 1, right, (dimension + 1) % Dim, subroot->right);
}


//group a list (ranging from indices left to right) into two parts:
//those less than a certain element, and those greater than or equal to the element.
template <int Dim>
size_t KDTree<Dim>::partition(vector<Point<Dim>>& list, int dimension, size_t left, size_t right, size_t pivotIndex) {
  //size_t pivotIndex = (left + right) / 2;
  Point<Dim> pivotValue = list.at(pivotIndex);
  //Point<Dim> temp = list.at(right);
  //list.at(right) = list.at(pivotIndex);
  //list.at(pivotIndex) = temp;
  swap(list[pivotIndex], list[right]);

  size_t index = left;

  for (size_t i = left; i < right; i++) {
    if (smallerDimVal(list[i], pivotValue, dimension)) {
      //Point<Dim> loopTemp = list[index];
      //list[index] = list[i];
      //list[i] = loopTemp;
      swap(list[index], list[i]);
      index++;
    }
  }

  //temp = list[index];
  //list[index] = list[right];
  //list[right] = temp;

  swap(list[right], list[index]);
  return index;

}


// Returns the k-th smallest element of list within left..right inclusive
template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int left, int right, size_t k, int dimension){
  if (left == right){     
    return list[left]; 
  }
  size_t pivotIndex = (left + right) / 2;  
  pivotIndex = partition(list, dimension, left, right, pivotIndex);
  if (k == pivotIndex) {
    return list[k];
  }
  else if (k < pivotIndex) {
    return quickSelect(list, left, pivotIndex - 1, k, dimension);
  }
  else {
    return quickSelect(list, pivotIndex + 1, right, k, dimension);
  }
  
  // if (left == right) {
  //   return list[left];
  // }

  // size_t pivotIndex = (left + right) / 2;
  // pivotIndex = partition(list, dimension, left, right, pivotIndex);

  // if (k == pivotIndex) {
  //   return list[k];
  // } else if (k < pivotIndex) {
  //   return quickSelect(list, dimension, left, pivotIndex - 1, k);
  // } else {
  //   return quickSelect(list, dimension, pivotIndex + 1, right, k);
  // }
  
  
  // while (left <= right) {
  //   if (left == right) {
  //     return list.at(left);
  //   }
  //   unsigned pivotIndex = k;
  //   pivotIndex = partition(list, dimension, left, right);

  //   if (k == pivotIndex) {
  //     return list[k];
  //   } else if (k < pivotIndex) {
  //     right = pivotIndex - 1;
  //   } else {
  //     left = pivotIndex + 1;
  //   }

  // }

  // return list[k];
  // if (left == right) {
  //   return list[left];
  // }
  // unsigned pivotIndex = k;
  // pivotIndex = partition(list, dimension, left,right,pivotIndex);
  // if (k == pivotIndex) {
  //   return list.at(k);
  // } else if (k < pivotIndex) {
  //   return quickSelect(list, dimension, left, pivotIndex - 1, k);
  // } else {
  //   return quickSelect(list, dimension, pivotIndex + 1, right, k);
  // }

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
	copy(this->root, other.root);
	size = other.size;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * othersubroot) {
	subroot = new KDTreeNode();
	subroot->point = othersubroot->point;
	copy(subroot->left, othersubroot->left);
	copy(subroot->right, othersubroot->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  	if (this != NULL) {
      clear(root);
    }
  	copy(this->root, rhs.root);
  	size = rhs.size;
  	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root); 

}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot) {
	if (subroot == NULL) {
    return;
  }
	if (subroot->left != NULL) {
    clear(subroot->left);
  }
	if (subroot->right != NULL) {
    clear(subroot->right);
  }
	delete subroot;
	subroot = NULL;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  Point<Dim> returnValue = findNearestNeighbour(query, root, 0);
  return returnValue;
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbour(const Point<Dim>& query, KDTreeNode* subRoot, size_t dimension) const {
  Point<Dim> currentBest = subRoot->point;
  bool index;

  if (subRoot->right ==  NULL && subRoot->left == NULL) {
    return subRoot->point;
  }
  if (smallerDimVal(query, subRoot->point, dimension)) {
    if (subRoot->left == NULL) {
      currentBest = findNearestNeighbour(query, subRoot->right, (dimension - 1) % Dim);
    } else {
      currentBest = findNearestNeighbour(query, subRoot->left, (dimension + 1) % Dim);
    }
    index = true;
  } else {
    if (subRoot->right == NULL) {
      currentBest = findNearestNeighbour(query, subRoot->left, (dimension + 1) % Dim);
    } else {
      currentBest = findNearestNeighbour(query, subRoot->right, (dimension + 1) % Dim);
    }
    index = false;
  }
  if (shouldReplace(query, currentBest, subRoot->point)) {
    currentBest = subRoot->point;
  }

  size_t current_dist = abs(subRoot->point[dimension] - query[dimension]);
  size_t best_dist = 0;
  for (size_t i = 0; i < Dim; i++) {
    best_dist += abs(pow((currentBest[i] - query[i]), 2));
  }
  best_dist = sqrt(best_dist);

  if (best_dist >= current_dist) {
    if (index) {
      if (subRoot->right != NULL) {
        Point<Dim> possibleBest = findNearestNeighbour(query, subRoot->right, (dimension + 1) % Dim);
        if (shouldReplace(query, currentBest, possibleBest)) {
          currentBest = possibleBest;
        }
      }
    } else {
      if (subRoot->left != NULL) {
        Point<Dim> possibleBest = findNearestNeighbour(query, subRoot->left, (dimension + 1) % Dim);
        if (shouldReplace(query, currentBest, possibleBest)) {
          currentBest = possibleBest;
        }
      }
    }
  }

  return currentBest;

}












