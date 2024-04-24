#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

const int MAXN=1e5;
vector<int> adj[MAXN+5];
bool visited[MAXN+5];

void dfs(int node)
{
	visited[node]=true;
	cout<<node<<" ";
	
	#pragma omp parallel for
	for(int i=0;i<adj[node].size();i++)
	{
		int next_node=adj[node][i];
		if(!visited[next_node])
		{
			dfs(next_node);
		}
	}
}

void search (int n){
    if(!visited[n]){
        cout<<"Node not found";
    }
    else{
        cout<<"Node exists";
    }
}

int main()
{

	cout<<"Enter the number of nodes and edges: ";
	int n ,m;
	cin>>n>>m;
	
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	int start_node;
	cout<<"Enter the start node: ";
	cin>>start_node;
	dfs(start_node);
	
		int x;
        cout<<"Enter the node to be found : ";
        cin>>x;
        search(x);
	cout<<endl;
	return 0;
}
