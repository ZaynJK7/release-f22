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
  searchType_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* searchType, Point & point, PNG & png, double tolerance) {
  searchType_ = searchType;
  png_ = png;
  tolerance_ = tolerance;
  current_ = point;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  if (!searchType_->empty()) {
    current_ = searchType_->pop();
    searchType_->add(current_);
    current_ = searchType_->peek();
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
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (searchType_ == nullptr) { thisEmpty = true; }
  if (other.searchType_ == nullptr) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = searchType_->empty(); }
  if (!otherEmpty) { otherEmpty = other.searchType_->empty(); }

  if (thisEmpty && otherEmpty) return false;
  else if ((!thisEmpty)&&(!otherEmpty)) return (searchType_ != other.searchType_);
  else return true;
}

