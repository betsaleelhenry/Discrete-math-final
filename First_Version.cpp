#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;

vector<vector<int> > graph(1000);
vector<vector<int> > D(1000);
vector<int> dv;
vector<int> dv1;
vector<int> kco(1000);
vector<int> L(1000);

int kcore;
int k_core(vector<vector<int> > &graph ){
  //  cout<<"1~"<<endl;
    for(int i=0;i<1000;i++){
        D[dv[i]].push_back(i);
        L[i]=0;
        kco[i]=0;
    }
    for(int i = 0;i<1000;i++){//degree
        if(D[i].size()==0)continue;
     //   cout<<"degree"<<i<<endl;
        for(int j=0;j<D[i].size();j++){//vertex this degree
            if(dv[D[i][j]]!=i)continue;
            if(L[D[i][j]]==1)continue;
          //  cout<<"vertexthisdegree"<<i<<endl;
            for(int z = 0;z < graph[D[i][j]].size();z++){
                if(L[graph[D[i][j]][z]] == 1 || dv[graph[D[i][j]][z]]==i)continue;
                dv[graph[D[i][j]][z]]-=1;
            //    cout<<"push"<<endl;
                D[dv[graph[D[i][j]][z]]].push_back(graph[D[i][j]][z]);   
            }
            L[D[i][j]]=1;
            kco[D[i][j]]=i;
            kcore = i;
        }
    }
   // cout<<"1.1~"<<endl;
    return kcore;
}
void print_Kcore(int k)
{
for(int i;i<1000;i++){

	
}
}
// This class represents a undirected graph using adjacency
// list representation
class Graph
{   int V; // No. of vertices
	// Pointer to an array containing adjacency lists
	list<int> *adj;
public:
	Graph(int V); // Constructor
	// function to add an edge to graph
	void addEdge(int u, int v);
	// A recursive function to print DFS starting from v
	bool DFSUtil(int, vector<bool> &, vector<int> &, int k);
	// prints k-Cores of given graph
	void printKCores(int k);
};
// A recursive function to print DFS starting from v.
// It returns true if degree of v after processing is less
// than k else false
// It also updates degree of adjacent if degree of v
// is less than k. And if degree of a processed adjacent
// becomes less than k, then it reduces of degree of v also,
bool Graph::DFSUtil(int v, vector<bool> &visited,
					vector<int> &vDegree, int k)
{	// Mark the current node as visited and print it
	visited[v] = true;
	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{	// degree of v is less than k, then degree of adjacent
		// must be reduced
		if (vDegree[v] < k)
			vDegree[*i]--;
		// If adjacent is not processed, process it
		if (!visited[*i])
		{	// If degree of adjacent after processing becomes
	     	// less than k, then reduce degree of v also.
			DFSUtil(*i, visited, vDegree, k);
		}
	}
	// Return true if degree of v is less than k
	return (vDegree[v] < k);
}
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
void Graph::addEdge(int A, int B)
{   if ( A == B ) return;
	adj[A].push_back(B);
	adj[B].push_back(A);
	//dv[A]++;
    //dv[B]++;
}
// Prints k cores of an undirected graph
void Graph::printKCores(int k)
{   // INITIALIZATION
	// Mark all the vertices as not visited and not
	// processed.
	vector<bool> visited(V, false);
	vector<bool> processed(V, false);
	int mindeg = 1000;
	int startvertex;
	// Store degrees of all vertices
	vector<int> vDegree(V);
	for (int i=0; i<V; i++)
	{  vDegree[i] = adj[i].size();
		if (vDegree[i] < mindeg)
		{	mindeg = vDegree[i];
			startvertex=i;
		}
	}
	DFSUtil(startvertex, visited, vDegree, k);
	// If Graph is disconnected.
	for (int i=0; i<V; i++)
		if (visited[i] == false)
			DFSUtil(i, visited, vDegree, k);
	// PRINTING K CORES
	for (int v=0; v<V; v++)
	{	// Only considering those vertices which have degree
		// >= K after BFS
		if (vDegree[v] >= k)
		{   //cout << "\n[" << v << "]";
			// Traverse adjacency list of v and print only
			// those adjacent which have vDegree >= k after
			// BFS.
			list<int>::iterator itr;
			for (itr = adj[v].begin(); itr != adj[v].end(); ++itr)
				if (vDegree[*itr] >= k){
				if (*itr>v)
				   {
					cout << v<<" "<<*itr<<endl;
					}
				}/*
 list<int>::iterator itr;
            for (itr = adj[v].begin(); itr != adj[v].end(); ++itr)
                if (vDegree[*itr] >= k)
                    cout << " -> " << *itr;
*/		}
	}
}

// Driver program to test methods of graph class
int main()
{
	Graph g1(1000);
	int A , B;
    dv.assign(1000,0);
    while(cin >> A >> B){
        graph[A].push_back(B);
        graph[B].push_back(A);
		g1.addEdge(A,B);
        dv[A]++;
        dv[B]++;
    }
  for(int i = 0 ; i < 1000 ; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    kcore = k_core(graph);
  cout<<kcore<<"-core"<<endl;
  
	g1.printKCores(kcore);

	return 0;
}
