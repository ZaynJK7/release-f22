#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) : start_(start), png_(png) {  
  /** @todo [Part 1] */
  for (size_t y = 0; y < png_.height(); y++) {
    std::vector<bool> vector;
    visited_.push_back(vector);
    for (size_t x = 0; x < png_.width(); x++) {
      visited_[y].push_back(false);
    }
  }
  tolerance_ = tolerance;
  stack_.push(start_);
}

double DFS::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_, png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  size_t x = point.x;
  size_t y = point.y;
  HSLAPixel pointPixel = png_.getPixel(start_.x, start_.y);
  
  if (x + 1 < png_.width()) {
    HSLAPixel rightPixel = png_.getPixel(x + 1, y);
    Point right = Point(x + 1, y);
    if (!beenVisited(right) && calculateDelta(rightPixel, pointPixel) <= tolerance_) {
      stack_.push(right);
    }
  }
  if (y + 1 < png_.height()) {
    HSLAPixel belowPixel = png_.getPixel(x, y + 1);
    Point below = Point(x, y + 1);
    if (!beenVisited(below) && calculateDelta(belowPixel, pointPixel) <= tolerance_) {
      stack_.push(below);
    }
  }
  if (x - 1 < png_.width()) {
    HSLAPixel leftPixel = png_.getPixel(x - 1, y);
    Point left = Point(x - 1, y);
    if (!beenVisited(left) && calculateDelta(leftPixel, pointPixel) <= tolerance_) {
      stack_.push(left);
    }
  }
  if (y - 1 < png_.height()) {
    HSLAPixel abovePixel = png_.getPixel(x, y - 1);
    Point above = Point(x, y - 1);
    if (!beenVisited(above) && calculateDelta(abovePixel, pointPixel) <= tolerance_) {
      stack_.push(above);
    }
  }
  //std::cout << "done adding: (" << x << "," << y << ")" << std::endl;
}

bool DFS::beenVisited(Point & point) const {
  if (point.x < png_.width() && point.y < png_.height()) {
    return visited_[point.y][point.x];
  }

  return true;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point toReturn = stack_.top();
  visited_[toReturn.y][toReturn.x] = true;
  Point nextPoint = toReturn;
  while (!empty() && beenVisited(nextPoint)) {
    stack_.pop();
    nextPoint = peek();
  }
  return toReturn;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point(4294967295, 4294967295) : stack_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack_.empty();
}
