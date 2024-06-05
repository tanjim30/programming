#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

struct Edge {
    Point p1, p2;
};

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

vector<Edge> convexHull(const vector<Point>& points) {
    vector<Edge> hull;
    int n = points.size();

    if (n < 3) {
        return hull;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool isEdge = true;

            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;

                if (orient(points[i], points[j], points[k])) {
                    isEdge = false;
                    break;
                }
            }

            if (isEdge) {
                Edge edge = { points[i], points[j] };
                hull.push_back(edge);
            }
        }
    }

    return hull;
}

int main() {
    vector<Point> points = readPointsFromFile("output.txt");
    int n = 20000;
    if (points.size() < n) {
        cerr << "Error: not enough points in file" << endl;
        return 1;
    }
    clock_t start1 = clock();
    vector<Point> hullPoints(points.begin(), points.begin() + n);
    vector<Edge> hull = convexHull(hullPoints);
    clock_t end1 = clock();

    for (const Edge& edge : hull) {
        cout << "(" << edge.p1.x << ", " << edge.p1.y << "), (" << edge.p2.x << ", " << edge.p2.y << ")" << endl;
    }
    cout << "Execution time : " << (float)(end1 - start1) / CLOCKS_PER_SEC << endl;

    return 0;
}

