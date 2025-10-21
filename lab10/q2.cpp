#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<vector<pair<int,int>>> adj;
vector<vector<int>> paths;
vector<int> path;
vector<bool> visited;

void dfs(int u,int t)
{
    if(u==t)
    {
        paths.push_back(path);
        return;
    }
    visited[u]=true;
    for(auto x:adj[u])
    {
        int v=x.first;
        int cap=x.second;
        if(cap>0&&!visited[v])
        {
            path.push_back(v);
            dfs(v,t);
            path.pop_back();
        }
    }
    visited[u]=false;
}

int main()
{
    cin>>n>>m;
    adj.resize(n);
    for(int i=0;i<m;i++)
    {
        int u,v,c;
        cin>>u>>v>>c;
        adj[u].push_back({v,c});
    }
    int s,t;
    cin>>s>>t;

    visited.assign(n,false);
    path.clear();
    paths.clear();

    path.push_back(s);
    dfs(s,t);

    if(paths.empty())
    {
        cout<<"No augmenting paths found"<<endl;
        return 0;
    }

    map<int,vector<vector<int>>> grouped;
    for(auto p:paths)
    {
        int len=p.size()-1;
        grouped[len].push_back(p);
    }

    for(auto &g:grouped)
    {
        cout<<g.second.size()<<" paths of length "<<g.first<<endl;
        for(auto &p:g.second)
        {
            for(int i=0;i<p.size();i++)
            {
                cout<<p[i];
                if(i<p.size()-1) cout<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
