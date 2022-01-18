
//File created on Jan 1/2022
//Author: Henry Betsaleel
//ID: 0810976
//Maximum K-core of undirected graph

#include <stdbool.h>
#include <iostream> 
#include <cstdlib>

using namespace std;

int Cardinality = 0;
class NetworkXforCpp{

public:
bool **Adj_Network()
{
    bool **Network = (bool **)malloc(sizeof(bool *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        Network[i] = (bool *)malloc(sizeof(bool) * 1000);
    }

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            Network[i][j] = 0;
        }
    }

return Network;
}

//this help us save memory by removing the obsolete data from memory.
void freeNetwork(bool **Network)
{
    for (int i = 0; i < 1000; i++)
    {
        free(Network[i]);
    }
    free(Network);
}
//This function gets the input from the automatic handler 
//and pasted it to our two variables x and y that later on will be indexes of our adjacency matrix
void GetData(bool **Network)
{
    int x, y;
    while (cin>>x>>y) 
    {
        Cardinality = Cardinality > y ? Cardinality : y;
        Network[x][y] = 1;
        Network[y][x] = 1;
    }
        Cardinality++;
}

//gets the values of eaches of the notches.
int *getNotches(bool **Network)
{
int *Notches = (int *)malloc(sizeof(int) * Cardinality); 
for (int i = 0; i < Cardinality; i++)
{
    Notches[i] = 0;
}

for (int i = 0; i < Cardinality; i++)
{
    for (int j = 0; j < Cardinality; j++)
    {
        if (Network[i][j] == 1)
        {
           Notches[i]++;
        }
    }
}
return Notches;
}






//deletes the vertices until theres none for the particular core.

bool **deleteVertex(bool **Network, int redundant)
{
for (int i = 0; i < Cardinality; i++)
{
    Network[i][redundant] = 0;
}
for (int j = 0; j < Cardinality; j++)
{
    Network[redundant][j] = 0;
}
return Network;
}
bool **Prune_core(int k, bool **Network)
{
    bool **Output = (bool **)malloc(sizeof(bool *) * Cardinality); 
for (int i = 0; i < Cardinality; i++)
{
    Output[i] = (bool *)malloc(sizeof(bool) * Cardinality); 
}

for (int i = 0; i < Cardinality; i++)
{
    for (int j = 0; j < Cardinality; j++)
    {
        Output[i][j] = Network[i][j];
    }
}
while (true)
{
    int *Notches = getNotches(Output);
    int sum = 0;
    for (int i = 0; i < Cardinality; i++)
    {
        if(Notches[i]!=0&&Notches[i]<k)
        {     
            sum++;
        }
    }

    if (sum == 0)
    {
    free(Notches);
    break;
    }

    for (int i = 0; i < Cardinality; i++)
    {
        if (Notches[i] < k)
        {
            Output = deleteVertex(Output, i);
        }
    }
    free(Notches);
}
return Output;
}
//this function is actual a checkpoint to see if we erased the graph, then we would know that we have passed the maximum
bool NullTab(bool **Network)
{
    for (int i = 0; i < Cardinality; i++)
    {
        for (int j = 0; j < Cardinality; j++)
        {
            if (Network[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}
//This outputs our final result along with the first part.
void Print_Max_KCore(bool **Network)
{
    for (int i = 0; i < Cardinality; i++)
    {
        for (int j = 0; j < Cardinality; j++)
        {
            if (Network[i][j] != 0 && j > i)
            {    
                cout<<i<<" "<<j<<endl; 
            }
        }
    }
}
//pruning operation consists of gething read of the unnecessary parts.
void Pruned(bool **Network)
{
    for (int i = 0; i < Cardinality; i++)
        {
            free(Network[i]);
        }
    free(Network);
}


};


int main()
{
NetworkXforCpp Nx;
bool **Network = Nx.Adj_Network(); 
Nx.GetData(Network);
bool **Output;
//this for loop takes into consideration the k value until it reaches the maximum core, then it would break.
for (int k = 1;; k++)
{
    Output = Nx.Prune_core(k, Network);
    //the if statement guaranties that we have a maximum k core (k-1), which is also output in our final results first part.
    if (Nx.NullTab(Output))
    {
       Nx.Pruned(Output);
        Output = Nx.Prune_core(k - 1, Network);
        cout<<(k-1)<<"-core"<<endl; 
        break;//means we are done with the iterations to find the maximum core.
    }
    else
    {
    Nx.Pruned(Output);
    }
}
Nx.Print_Max_KCore(Output);
Nx.freeNetwork(Network);
Nx.Pruned(Output);

return 0;
}