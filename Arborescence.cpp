#include<bits/stdc++.h>
using namespace std;
#define MAX 999999

vector<vector<int>> edge_to_matrix(vector<vector<int>> inp,int n)
{
    vector<vector<int>> v;
    for(int i=0;i<n;i++){
        vector<int> sam(n);
        for(int j=0;j<n;j++){
            sam[j]=MAX;
        }
        v.push_back(sam);
    }
    for(int i=0;i<inp.size();i++){
        v[inp[i][0]-1][inp[i][1]-1]=inp[i][2];
    }
    return v;
}

int dist_fun(int* parent,int* dist,int n,int s,vector<vector<int>> v)
{
    if(n==s){
        return 0;
    }
    if(dist[n]!=-1){
        return dist[n];
    }
    if(parent[n]==-1){
        return -1;
    }
    return dist_fun(parent,dist,parent[n],s,v)+v[parent[n]][n];

}


int check_cycle(vector<vector<int>> v,map<int,vector<int>> &mapi,int* label,int* parent)
{
    int n=v.size();
    bool check[n];
    bool done[n];
    bool doub_check[n];
    int no_remove[n];
    int end[n];
    for(int i=0;i<n;i++){
        doub_check[i]=false;
        end[i]=0;
        check[i]=false;
        done[i]=false;
        no_remove[i]=0;
    }
    stack<int> qu;
    map<int,vector<int>> dic;
    vector<int> fin;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            done[j]=false;
        }
        if(!doub_check[i]){
            qu.push(i);
            fin.push_back(i);
            doub_check[i]=true;
            check[i]=true;
            no_remove[i]++;
        }
        int t=4;
        done[label[i]]=true;
        while(1){
            if(qu.empty()){
                break;
            }
            int sam=qu.top();
            if(no_remove[sam]==0){
                qu.pop();
                check[label[sam]]=true;
                done[label[sam]]=false;
                dic[sam].clear();
                fin.pop_back();
                continue;
            }
            no_remove[sam]--;
            int cnt=0;
            for(int j=0;j<n;j++){
                if(sam==j){
                    continue;
                }
                if(v[sam][j]==0 && label[sam]!=label[j]){
                    if(cnt==1){
                        no_remove[sam]++;
                        break;
                    }
                    if(done[label[j]]){
                        int ww=0;
                        for(int k=0;k<dic[sam].size();k++){
                            if(dic[sam][k]==j){
                                ww=1;
                            }
                        }
                        if(ww==1){
                            continue;
                        }
                        int sample=label[fin[0]];
                        if(parent[fin[0]]==-1){
                            parent[fin[0]]=fin[fin.size()-1];
                        }
                        for (int k=0;k<fin.size();k++){
                            if(k!=0 & parent[fin[k]]==-1){
                                parent[fin[k]]=fin[k-1];
                            }
                            label[fin[k]]=sample;
                            mapi[fin[k]].clear();
                            int ww=0;
                            for(int w=0;w<mapi[sample].size();w++){
                                if(mapi[sample][w]==fin[k]){
                                    ww=1;
                                    break;
                                }
                            }
                            if(ww==0){
                                mapi[sample].push_back(fin[k]);
                            }
                        }

                        return 1;

                    }
                    else{
                        int ww=0;
                        for(int k=0;k<dic[sam].size();k++){
                            if(dic[sam][k]==j){
                                ww=1;
                            }
                        }
                        if(ww==1){
                            continue;
                        }
                        qu.push(j);
                        fin.push_back(j);
                        dic[sam].push_back(j);
                        no_remove[j]++;
                        cnt++;
                        done[label[j]]=true;
                    }
                }
            }

            for(int j=0;j<mapi[label[sam]].size();j++){
                if(sam==mapi[label[sam]][j]){
                    continue;
                }
                if(v[sam][mapi[label[sam]][j]]==0 && label[sam]!=label[mapi[label[sam]][j]]){
                    if(cnt==1){
                        no_remove[sam]++;
                        break;
                    }
                    if(done[mapi[label[sam]][j]]){
                        for(int k=0;k<dic[sam].size();k++){
                            if(dic[sam][k]==mapi[label[sam]][j]){
                                continue;
                            }
                        }
                        int sample=label[fin[0]];
                        if(parent[fin[0]]==-1){
                            parent[fin[0]]=fin[fin.size()-1];
                        }
                        for (int k=0;k<fin.size();k++){
                            if(k!=0 & parent[fin[k]]==-1){
                                parent[fin[k]]=fin[k-1];
                            }
                            label[fin[k]]=sample;
                            mapi[fin[k]].clear();
                            int ww=0;
                            for(int w=0;w<mapi[sample].size();w++){
                                if(mapi[sample][w]==fin[k]){
                                    ww=1;
                                    break;
                                }
                            }
                            if(ww==0){
                                mapi[sample].push_back(fin[k]);
                            }
                        }

                        return 1;
                    }
                    else{
                        qu.push(mapi[label[sam]][j]);
                        no_remove[sam]++;
                    }
                }
            }

        }
        dic[i].clear();
    }

    return 0;
}

void arbo(vector<vector<int>> v,int s)
{
    s--;
    int n=v.size();
    vector<vector<int>> for_end;
    for(int i=0;i<n;i++){
        vector<int> sam(n);
        for(int j=0;j<n;j++){
            sam[j]=v[i][j];
        }
        for_end.push_back(sam);
    }
    int cnt=0;
    bool check[n];
    int label[n];
    for(int i=0;i<n;i++){
        label[i]=i;
        check[i]=false;
    }
    map<int,vector<int>> mapi;
    for(int i=0;i<n;i++){
        mapi[i].push_back(i);
    }
    int t=4;
    map<int,int> sample;
    map<int,pair<int,int>> inout;
    for(int i=0;i<n;i++){
        inout[i].first=-1;
        inout[i].second=-1;
    }
    int parent[n];
    for (int i=0;i<n;i++){
        parent[i]=-1;
    }
    while(t){
        for(int k=0;k<n;k++){
            if(k==s){
                continue;
            }
            int mini=MAX;
            int sam;
            for(int i=0;i<mapi[k].size();i++){
                for(int j=0;j<n;j++){
                    if(v[j][mapi[k][i]]!=MAX && label[mapi[k][i]]!=label[j]){
                        if(v[j][mapi[k][i]]<mini){
                            mini=v[j][mapi[k][i]];
                            sam=j;
                        }
                    }
                }
            }
            inout[k].second=sam;
            inout[sam].first=k;
            for(int i=0;i<mapi[k].size();i++){
                for(int j=0;j<n;j++){
                    if(v[j][mapi[k][i]]!=MAX && label[mapi[k][i]]!=label[j]){
                        v[j][mapi[k][i]]-=mini;
                    }
                }
                sample[mapi[k][i]]=mini;
            }
        }
        t=check_cycle(v,mapi,label,parent);
    }
    bool here[n];
    for(int i=0;i<n;i++){
        here[i]=false;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(v[i][j]==0 && label[i]!=label[j] & !here[j]){
                parent[j]=i;
                here[j]=true;
            }
        }
    }
    vector<vector<int>> tree;
    for(int i=0;i<n;i++){
        vector<int> sam(n);
        for(int j=0;j<n;j++){
            sam[j]=MAX;
        }
        tree.push_back(sam);
    }
    for(int i=0;i<n;i++){
        if(parent[i]==-1){
            continue;
        }
        tree[parent[i]][i]=for_end[parent[i]][i];
    }
    int dist[n];
    for(int i=0;i<n;i++){
        dist[i]=-1;
    }
    for(int i=0;i<n;i++){
        dist[i]=dist_fun(parent,dist,i,s,tree);
    }
    int total=0;
    for(int i=0;i<n;i++){
        if(parent[i]==-1){
            continue;
        }
        total+=dist[i]-dist[parent[i]];
    }
    cout<<total<<" ";
    for(int i=0;i<n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<"# ";
    for(int i=0;i<n;i++){
        if(i==s){
            cout<<0<<" ";
            continue;
        }
        if(parent[i]!=-1){
            cout<<parent[i]+1<<" ";
            continue;
        }
        cout<<parent[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,m,s;
        cin>>n>>m>>s;
        vector<vector<int>> inp(m);
        for(int i=0;i<m;i++){
            int a,b,c;
            cin>>a>>b>>c;
            if(c<0){
                cout<<-1<<endl;
                return 0;
            }
            inp[i].push_back(a);
            inp[i].push_back(b);
            inp[i].push_back(c);
        }
        vector<vector<int>> v;
        v=edge_to_matrix(inp,n);
        arbo(v,s);
    }
}
