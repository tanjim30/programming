#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

#define ll long long

using namespace std;

int numNumbers = 15;

void create_file() {
    string filename = "search_input.txt";

    ofstream outputFile(filename);

    outputFile << numNumbers;
    outputFile << endl;

    // Seed for random numbers
    srand(static_cast<unsigned int>(time(0)));

    // Generate and write random numbers to the file
    for (int i = 0; i < numNumbers; ++i) {
        outputFile << rand()%1000 << "\n";
    }
    outputFile << endl;
    for (int i = 0; i < numNumbers; ++i) {
        outputFile << rand()%10000 << "\n";
    }

    outputFile.close();
}

struct Iteam {
    int weight;
    int value;
    int index;
    double ratio;
};

bool compare(Iteam a, Iteam b) {
    return a.ratio > b.ratio;
}

double func_knp(int capacity, vector<Iteam>& items) {
    sort(items.begin(), items.end(), compare);
    vector<double> out(numNumbers, 0);

    for (auto item : items) {
        cout << "index: " << item.index << ", Weight: " << item.weight << ", Value: " << item.value << ", Ratio: " << item.ratio << endl;
    }

    double ttl = 0.0;

    for (auto item : items) {
        if (capacity >= item.weight) {
            ttl += item.value;
            capacity -= item.weight;
            out[item.index]++;
        } else {
            ttl += ((double)(capacity) / item.weight) * item.value;
            out[item.index] += ((double)(capacity) / item.weight);
            break;
        }
    }

    for (auto x : out) cout << x << " ";
    cout << endl;

    return ttl;
}

int main() {
    create_file();
    int capacity , i = 0, number;
    cout<<"Give the maximum capacity in the knapsack : "<<endl;
    cin>>capacity;
    vector<Iteam> items(numNumbers);

    string filename = "search_input.txt";
    ifstream inputFile(filename);

    inputFile >> number;
    cout<<"Weight : ";
    for (i = 0; i < numNumbers; i++) {
        inputFile >> number;
        cout << number <<" " ;
        items[i].weight = number;
        items[i].index = i;
    }
    cout<< endl;
    cout<<"Value : ";
    for (i = 0; i < numNumbers; i++) {
        inputFile >> number;
        items[i].value = number;
        cout << number <<" ";
    }
    cout << endl;
    inputFile.close();

    for (auto& item : items) {
        item.ratio = (double)(item.value) / item.weight;
    }

    double maxValue = func_knp(capacity, items);

    cout << "\nMaximum value in knapsack: " << maxValue << endl;

    return 0;
}
