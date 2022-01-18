
//File created on Jan 1/2022
//Author: Henry Betsaleel
//ID: 0810976
//Maximum K-core of undirected graph

#include <stdbool.h>
#include <iostream> 
//#include <cmath>
//#include <cstdlib> 
//clock_t  t_end,t_start = clock(); 
using namespace std;


int Cardinality = 0;

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

void freeNetwork(bool **Network)
{
    for (int i = 0; i < 1000; i++)
    {
        free(Network[i]);
    }
    free(Network);
}

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
while (1)
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

void Pruned(bool **Network)
{
    for (int i = 0; i < Cardinality; i++)
        {
            free(Network[i]);
        }
    free(Network);
}

int main()
{
bool **Network = Adj_Network(); 
GetData(Network);
bool **Output;

for (int k = 1;; k++)
{
    Output = Prune_core(k, Network);
    if (NullTab(Output))
    {
        Pruned(Output);
        Output = Prune_core(k - 1, Network);
        cout<<(k-1)<<"-core"<<endl; 
        break;
    }
    else
    {
    Pruned(Output);
    }
}
Print_Max_KCore(Output);
freeNetwork(Network);
Pruned(Output);

return 0;
}