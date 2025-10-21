#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to,capacity,rev;
};

int n,m;
vector<vector<Edge>>adj;
vector<bool>usedVertex;

void addEdge(int u,int v,int c)
{
    Edge a={v,c,(int)adj[v].size()};
    Edge b={u,0,(int)adj[u].size()};
    adj[u].push_back(a);
    adj[v].push_back(b);
}

bool bfs(int s,int t,vector<int>&parent,vector<int>&parentEdge)
{
    fill(parent.begin(),parent.end(),-1);
    queue<int>q;
    q.push(s);
    parent[s]=s;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<adj[u].size();i++)
        {
            Edge &e=adj[u][i];
            if(parent[e.to]==-1&&e.capacity>0)
            {
                if(usedVertex[e.to]&&e.to!=t)continue;
                parent[e.to]=u;
                parentEdge[e.to]=i;
                q.push(e.to);
                if(e.to==t)return true;
            }
        }
    }
    return false;
}

int maxFlow(int s,int t)
{
    int totalFlow=0;
    vector<int>parent(n),parentEdge(n);
    while(bfs(s,t,parent,parentEdge))
    {
        int pathFlow=INT_MAX;
        for(int v=t;v!=s;v=parent[v])
        {
            int u=parent[v];
            Edge &e=adj[u][parentEdge[v]];
            pathFlow=min(pathFlow,e.capacity);
        }
        for(int v=t;v!=s;v=parent[v])
        {
            int u=parent[v];
            Edge &e=adj[u][parentEdge[v]];
            e.capacity-=pathFlow;
            adj[e.to][e.rev].capacity+=pathFlow;
            if(v!=s&&v!=t)usedVertex[v]=true;
            if(u!=s&&u!=t)usedVertex[u]=true;
        }
        totalFlow+=pathFlow;
    }
    return totalFlow;
}

int main()
{
    cin>>n>>m;
    adj.resize(n);
    usedVertex.assign(n,false);
    for(int i=0;i<m;i++)
    {
        int u,v,c;
        cin>>u>>v>>c;
        addEdge(u,v,c);
    }
    int s,t;
    cin>>s>>t;
    cout<<"Maximum Flow: "<<maxFlow(s,t)<<endl;
}
