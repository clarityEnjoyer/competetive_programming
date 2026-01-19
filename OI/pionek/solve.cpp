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

struct points{
	ll x,y;
	bool ori=0;
	ll cross(points &a){
		return x*a.y-y*a.x;
	}
	ll dot(points &a){
		return x*a.x+y*a.y;
	}
	points operator + (points &a){
		return {x+a.x, y+a.y};
	}
}t,fso={1,0},p={0,0},up={0,0},up2={0,0};

ostream& operator << (ostream& is, points &a){
    is<<'('<<a.x<<" "<<a.y<<")\n";
    return is;
}
// ll orient(points &a){
// 	return x*a.y-y*a.x;
// }


int main() {
ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
ll n,a,b,l,maks=0;
cin>>n;
vv(points)v1,v2;
rep(i, n){
	cin>>a>>b;
	if (a==b&&a==0)continue;
	t={a,b};
	l=t.cross(fso);
	if (l<0||(l==0&&t.dot(fso)>0)){
		v1.pb({a,b,1});
		v2.pb({-a,-b});
	}else{
		v2.pb({a,b,1});
		v1.pb({-a,-b});
	}
	
}
sort(all(v1),[](points &p1, points &p2){
	return p1.cross(p2)>0;
});
sort(all(v2),[](points &p1, points &p2){
	return p1.cross(p2)>0;
});
each(i,v1)v2.pb(i);
each(i,v1){
	if(i.ori){
		if(i.y>up.y||(i.y==up.y&&i.x>up.x))up=i;
		if(i.y>=0)up2=up2+i;
	}
}
// wr up<<up2;
if (up2.y>up.y)up=up2;
else if (up.y==up2.y)up.x=max(up.x, up2.x);
// wrut(v2)
// wr up;
each(i,v2){
	p=p+i;
	t=p+up;
	maks=max(maks,t.dot(t));
	// wrot(maks,i,p)
}
wr maks;
}
