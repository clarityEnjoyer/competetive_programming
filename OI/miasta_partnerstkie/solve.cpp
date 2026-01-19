#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i= 0; i<(n); i++)
#define reps(i,s, n) for(int i= (s); i<(n); i++)
#define each(a, x) for (auto &a : x)
#define vv(T) vector<T>
#define endl '\n'
#define sz(x) (int)x.size()
#define ll long long
#define all(c) begin(c), end(c)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define wr cout<<
#define wre wr endl;
#define wrut(a) {wre each(i,(a))wr i<<" "; wre}
#define wrot(a,b,c) {wre wr a<<" "<<b<<" "<<c; wre}

const int B=62;
vv(int)adj[50005*2];
struct trie{
    struct node{
        int child[2],info;
        node(){
            info=child[0]=child[1]=-1;
        };
    };
    vector<node> nodes;
    trie() {
        nodes = {node()};
    }
    int newnode(){
        nodes.emplace_back(node());
        return sz(nodes)-1;
    }
    void add(ll x,int info){
        int v=0;
        for (int i=B-1; i>=0; i--){
            //wrot(x, i, ((x >> i) & 1))
                if(nodes[v].child[(x >> i) & 1] == -1) {
                int t = newnode();
                nodes[v].child[(x >> i) & 1] = t;
            }
            v = nodes[v].child[(x >> i) & 1];
        }
        nodes[v].info=info;
    }
    int GetInfoOfMax(ll x) {
        int v = 0;
        for(int i = B - 1; i >= 0; i--) {
            if(nodes[v].child[((x >> i) & 1) ^ 1] == -1) {
                v = nodes[v].child[(x >> i) & 1];
            } else {
                v = nodes[v].child[((x >> i) & 1) ^ 1];
            }
        }
        return nodes[v].info;
    }   
};
vv(bool)vis;
vv(int)match;
bool augment(int v){
    vis[v]=1;
    each(i,adj[v]){
        if (match[i]==-1){
            match[i]=v;match[v]=i;
            return 1;
        }
    }
    each(i,adj[v]){
        if (!vis[match[i]]&&augment(match[i])){
            match[i]=v;match[v]=i;
            return 1;
        }
    }
    return 0;
}

int main() {
ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int n; cin>>n;
vv(ll)city1(n), city2(n);
trie t,t2;

each(i,city1){
    cin>>i;
    //m1=max(m1,i);
}
each(i,city2){
    cin>>i;
    //m2=max(m2,i);
}
//if (m1<m2)swap(city1,city2);
rep(i,n){
    t.add(city1[i],i);
    t2.add(city2[i],i);
}
rep(i,n){
    adj[i].pb(t2.GetInfoOfMax(city1[i])+n);//z ktorym miastem z city2 chce byc połączone miasto z city1
    adj[i+n].pb(t.GetInfoOfMax(city2[i]));//z ktorym miastem z city1 chce byc połączone miasto z city2
    adj[t2.GetInfoOfMax(city1[i])+n].pb(i);
    adj[t.GetInfoOfMax(city2[i])].pb(i+n);
    // wrot ("city1 <->",i,t2.GetInfoOfMax(city1[i])+n)
    // wrot ("city2 <->",i+n,t.GetInfoOfMax(city2[i]))
}
//adj - city1 added - city2 we ask
//rep(i,n+n)wrut(adj[i])
bool any=1;
match.assign(n+n,-1);
while(any){
    any=0;
    vis.assign(n,0);
    rep(i,n){
        if (match[i]==-1&&augment(i)){
            any=1;
        }
    }
}
//wrut (match)
rep(i,n){
    if (match[i]==-1){
        wr "NIE";
        return 0;
    }
}

wr "TAK";
wre
rep(i,n){
    cout<<match[i]-n+1<<" ";
}

}
