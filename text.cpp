#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure to represent a 2D point
struct Point {
    long long x, y;
};

// Function to generate random points and write them to a file
void generateRandomPoints(int n) {
    // Seed for random number generation
    srand(time(0));

    // Generate random points and write to file
    ofstream file("convex_hull.txt");

    for (int i = 0; i < n; i++) {
        Point p;
        p.x = rand() % 200;  // Adjust the range of x-coordinate as needed
        p.y = rand() % 200;  // Adjust the range of y-coordinate as needed
        file << p.x << " " << p.y << endl;
    }

    file.close();
}

int main() {
    int numberOfPoints;
    cout << "Enter the number of points to generate: ";
    cin >> numberOfPoints;

    generateRandomPoints(numberOfPoints);

    cout << "Random points generated and written to convex_point.txt." << endl;

    return 0;
}
