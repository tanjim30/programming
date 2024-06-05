#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool compare(pair<int, int> p1, pair<int, int> p2)
{
    double r1 = (double)p1.first / p1.second;
    double r2 = (double)p2.first / p2.second;
    return r1 > r2;
}

int main()
{
    ifstream inFile("knapsack.txt");

    if (!inFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int numitems;
    inFile >> numitems;

    vector<pair<int, int>> itemDetails;

    // Read weights
    vector<int> weights(numitems);
    for (int i = 0; i < numitems; ++i)
    {
        inFile >> weights[i];
    }

    // Read profits
    vector<int> profits(numitems);
    for (int i = 0; i < numitems; ++i)
    {
        inFile >> profits[i];
    }
    for (int i = 0; i < numitems; i++)
    {
        itemDetails.push_back(make_pair(profits[i], weights[i]));
    }
    inFile.close();
    double ans = 0;
    for (int i = 0; i < numitems; i++)
    {
        double ratio = (double)itemDetails[i].first / itemDetails[i].second;
        cout << "index: " << i + 1 << " weight: "
             << " " << itemDetails[i].second << " profit: "
             << " " << itemDetails[i].first << " ratio: " << ratio << endl;
    }
    sort(itemDetails.begin(), itemDetails.end(), compare);

    vector<double> selectedItems(numitems, 0); // Initialize all items as not selected

    for (int i = 0; i < numitems; i++)
    {
        if (w >= itemDetails[i].second)
        {
            ans += itemDetails[i].first;
            w -= itemDetails[i].second;
            selectedItems[i] = 1; // Item i is selected
            continue;
        }
        double ratio = (double)itemDetails[i].first / itemDetails[i].second;
        ans = ans + (ratio * w);
        w = 0;
        selectedItems[i] = ratio; // Partial selection of item i
        break;
    }

    cout << "Selected items : ";
        for (int i = 0; i < numitems; i++)
    {
        cout << selectedItems[i] << " ";
    }

    cout << "\nMaximum profit: " << ans << endl;
    cout << endl;
    return 0;
}
