#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Point {
  double x, y;
};

bool compareX(const Point& p1, const Point& p2) {
  return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {
  return p1.y < p2.y;
}

vector<Point> readPointsFromFile(string filename) {
  vector<Point> points;
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return {};
  }

  while (file.good()) {
    Point point;
    file >> point.x >> point.y;

    if (file.good()) {
      points.push_back(point);
    }
  }

  file.close();

  return points;
}

bool orient(const Point& p1, const Point& p2, const Point& p3) {
  double crossProduct = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

  if (crossProduct > 0) {
    return true;
  } else if (crossProduct < 0) {
    return false;
  } else {
    return p2.x <= p3.x && p2.y <= p3.y;
  }
}

vector<Point> grahamScan(vector<Point>& points) {
  vector<Point> hull;

  if (points.size() < 3) {
    return hull;
  }

  sort(points.begin(), points.end(), compareX);

  Point p1 = points[0];
  Point p2 = points[points.size() - 1];

  hull.push_back(p1);
  hull.push_back(p2);

  vector<Point> upperPoints;
  vector<Point> lowerPoints;

  for (const Point& p : points) {
    if (orient(p1, p2, p) > 0) {
      upperPoints.push_back(p);
    } else if (orient(p1, p2, p) < 0) {
      lowerPoints.push_back(p);
    }
  }
  vector<Point> upperHull = grahamScan(upperPoints);
  vector<Point> lowerHull = grahamScan(lowerPoints);

  int m = upperHull.size() - 1;
  int n = lowerHull.size() - 1;

  while (m >= 0 && n >= 0) {
    if (orient(hull[hull.size() - 2], hull.back(), upperHull[m])) {
      hull.push_back(upperHull[m]);
      m--;
    } else {
      hull.push_back(lowerHull[n]);
      n--;
    }
  }


  while (m >= 0) {
    hull.push_back(upperHull[m]);
    m--;
  }

  while (n >= 0) {
    hull.push_back(lowerHull[n]);
    n--;
  }

  return hull;
}

int main() {
  vector<Point> points = readPointsFromFile("convex_hull.txt");

  int n = 10000;
  if (points.size() < n) {
    cerr << "Error: not enough points in file" << endl;
    return 1;
  }

  clock_t start1 = clock();
  vector<Point> hull = grahamScan(points);
  clock_t end1 = clock();

  for (const Point& p : hull) {
    cout << "(" << p.x << ", " << p.y << ")" << endl;
  }

  cout << "Execution time : " << (float)(end1 - start1) / CLOCKS_PER_SEC << endl;

  return 0;
}
