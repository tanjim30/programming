#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#define iPair pair<int, int>
using namespace std;


struct Point {
    int x, y;
};
int findSide(iPair p1, iPair p2, iPair p) {
    int val = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}


int lineDist(iPair p1, iPair p2, iPair p) {
    return abs((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

void quickHull(vector<Point>& a, iPair p1, iPair p2, int side) {
    int ind = -1;
    int max_dist = 0;
    for (int i = 0; i < a.size(); i++) {
        int temp = lineDist(p1, p2, {a[i].x, a[i].y});
        if (findSide(p1, p2, {a[i].x, a[i].y}) == side && temp > max_dist) {
            ind = i;
            max_dist = temp;
        }
    }
    if (ind == -1) {
        cout << "(" << p1.first << ", " << p1.second << ") ";
        cout << "(" << p2.first << ", " << p2.second << ") ";
        return;
    }
    quickHull(a, {a[ind].x, a[ind].y}, p1, -findSide({a[ind].x, a[ind].y}, p1, p2));
    quickHull(a, {a[ind].x, a[ind].y}, p2, -findSide({a[ind].x, a[ind].y}, p2, p1));
}

void printHull(vector<Point>& a) {
    if (a.size() < 3) {
        cout << "Convex hull not possible\n";
        return;
    }
    int min_x = 0, max_x = 0;
    for (int i = 1; i < a.size(); i++) {
        if (a[i].x < a[min_x].x)
            min_x = i;
        if (a[i].x > a[max_x].x)
            max_x = i;
    }

    quickHull(a, {a[min_x].x, a[min_x].y}, {a[max_x].x, a[max_x].y}, 1);
    quickHull(a, {a[min_x].x, a[min_x].y}, {a[max_x].x, a[max_x].y}, -1);

    cout << endl;
}

int main() {
    ifstream inputFile("output.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    vector<Point> points;
    Point point;

    int pointsToRead = 20000;

    for (int i = 0; i < pointsToRead && inputFile >> point.x >> point.y; ++i) {
        points.push_back(point);
    }

    inputFile.close();

    clock_t startTime = clock();

    printHull(points);

    clock_t endTime = clock();
    double executionTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Execution time: " << executionTime << " seconds" << endl;

    return 0;
}

