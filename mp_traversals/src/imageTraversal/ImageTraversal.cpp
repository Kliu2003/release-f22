#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  startPoint_ = Point(-1, -1);
  currPoint_ = Point(-1 ,-1);
  tolerance_ = 0.0;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, PNG png, Point startPoint, double tolerance) {
  /** @todo [Part 1] */
  traversal_ = traversal;
  png_ = png;
  startPoint_ = startPoint;
  currPoint_ = traversal_->peek();
  tolerance_ = tolerance;
  visited_ = new bool* [png.width()];
  for(unsigned i = 0; i < png.width(); i++){
    visited_[i] = new bool[png.height()];
    for(unsigned j = 0; j < png.height(); j++){
      visited_[i][j] = false;
    }
  }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!traversal_->empty()){
    
    currPoint_ = traversal_->pop();

    visited_[currPoint_.x][currPoint_.y] = true;
    
    Point right = Point(currPoint_.x+1, currPoint_.y);
    Point down = Point(currPoint_.x, currPoint_.y+1);
    Point left = Point(currPoint_.x-1, currPoint_.y);
    Point up = Point(currPoint_.x, currPoint_.y-1);

    if(right.x < png_.width() && right.x >= 0 && !visited_[right.x][right.y] && calculateDelta(png_.getPixel(right.x, right.y), png_.getPixel(startPoint_.x, startPoint_.y)) <= tolerance_){
      traversal_->add(right);
    }
    if(down.y < png_.height() && down.y >= 0 && !visited_[down.x][down.y] && calculateDelta(png_.getPixel(down.x, down.y), png_.getPixel(startPoint_.x, startPoint_.y)) <= tolerance_){
      traversal_->add(down);
    }
    if(left.x < png_.width() && left.x >= 0 && !visited_[left.x][left.y] && calculateDelta(png_.getPixel(left.x, left.y), png_.getPixel(startPoint_.x, startPoint_.y)) <= tolerance_){
      traversal_->add(left);
    }
    if(up.y < png_.height() && up.y >= 0 && !visited_[up.x][up.y] && calculateDelta(png_.getPixel(up.x, up.y), png_.getPixel(startPoint_.x, startPoint_.y)) <= tolerance_){
      traversal_->add(up);
    }

    while(!traversal_->empty() && visited_[traversal_->peek().x][traversal_->peek().y]){
      traversal_->pop();
    }
    
    if(!traversal_->empty()){
      currPoint_ = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->currPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  
  bool isEmpty = false;
  bool otherIsEmpty = false;

  if (traversal_ == NULL){
    isEmpty = true;
  }
  if (other.traversal_ == NULL){
    otherIsEmpty = true;
  } 
  if (!isEmpty){
    isEmpty = traversal_->empty();
  }
  if (!otherIsEmpty){
    otherIsEmpty = other.traversal_->empty();
  } 
  if (isEmpty && otherIsEmpty){
    return false;
  } 

  return true;

}

