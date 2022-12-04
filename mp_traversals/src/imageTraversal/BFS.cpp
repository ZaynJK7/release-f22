#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
  /** @todo [Part 1] */
  BFS::BFS(const PNG & png, const Point & start, double tolerance) : start_(start), png_(png) {
    for (size_t y = 0; y < png_.height(); y++) {
      std::vector<bool> vector;
      visited_.push_back(vector);
    for (size_t x = 0; x < png_.width(); x++) {
      visited_[y].push_back(false);
    }
  }
  tolerance_ = tolerance;
  visited_[start_.y][start_.x] = true;
  queue_.push(start_);
}

double BFS::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_, png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  size_t x = point.x;
  size_t y = point.y;
  HSLAPixel pointPixel = png_.getPixel(start_.x, start_.y);
  
  if (x + 1 < png_.width()) {
    HSLAPixel rightPixel = png_.getPixel(x + 1, y);
    Point right = Point(x + 1, y);
    if (!visited(right) && calculateDelta(pointPixel, rightPixel) <= tolerance_) {
      queue_.push(right);
      visited_[right.y][right.x] = true;
    }
  }
  if (y + 1 < png_.height()) {
    HSLAPixel belowPixel = png_.getPixel(x, y + 1);
    Point below = Point(x, y + 1);
    if (!visited(below) && calculateDelta(pointPixel, belowPixel) <= tolerance_) {
      queue_.push(below);
      visited_[below.y][below.x] = true;
    }
  }
  if (x - 1 < png_.width()) {
    HSLAPixel leftPixel = png_.getPixel(x - 1, y);
    Point left = Point(x - 1, y);
    if (!visited(left) && calculateDelta(pointPixel, leftPixel) <= tolerance_) {
      queue_.push(left);
      visited_[left.y][left.x] = true;
    }
  }
  if (y - 1 < png_.height()) {
    HSLAPixel abovePixel = png_.getPixel(x, y - 1);
    Point above = Point(x, y - 1);
    if (!visited(above) && calculateDelta(pointPixel, abovePixel) <= tolerance_) {
      queue_.push(above);
      visited_[above.y][above.x] = true;
    }
  }
}

bool BFS::visited(Point & point) const {
  if (point.x < png_.width() && point.y < png_.height()) {
    return visited_[point.y][point.x];
  }
  return true;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point toReturn = queue_.front();
  queue_.pop();
  return toReturn;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue_.empty();
}
