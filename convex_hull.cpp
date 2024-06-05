#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define ll long long
#define MOD 1000000007
using namespace std;
ll V;
ll mx_in= 2147483640;
ll graph[100][100];
int minDistance(int dist[], bool sptSet[])
{
 int min = mx_in, min_index;

 for (int v = 0; v < V; v++)
  if (sptSet[v] == false && dist[v] <= min)
   min = dist[v], min_index = v;

 return min_index;
}

void printSolution(int dist[])
{
 cout << "Vertex \t                 Distance from Source" << endl;
 for (int i = 0; i < V; i++)
  cout << i << " \t\t\t\t" << dist[i] << endl;
}

void dijkstra(int src)
{
 int dist[V];

 bool sptSet[V];
 for (int i = 0; i < V; i++)
  dist[i] = mx_in, sptSet[i] = false;
 dist[src] = 0;
 for (int count = 0; count < V - 1; count++) {
  int u = minDistance(dist, sptSet);
  sptSet[u] = true;
  for (int v = 0; v < V; v++)
   if (!sptSet[v] && graph[u][v]
    && dist[u] != mx_in
    && dist[u] + graph[u][v] < dist[v])
    dist[v] = dist[u] + graph[u][v];
 }
 printSolution(dist);
}

int main()
{



    ll number, weight, starting_in, n = 0, vrtx_num;
    char vrtx1, vrtx2;
    vector<ll> arr;

    string filename = "dijkstra_data.txt";
    ifstream inputFile(filename);

    starting_in= vrtx1-'A';

    while (inputFile >> number) {
        arr.push_back(number);
        //cout << number <<" ";
    }

    vrtx_num= sqrt(arr.size()+1);
    V= vrtx_num;

    for(ll i= 0;i<vrtx_num;i++){
        for(ll j=0;j<vrtx_num;j++){
            graph[i][j]= arr[i*vrtx_num+j];
        }
    }

 dijkstra(0);

 return 0;
}
