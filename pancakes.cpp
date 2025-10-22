#include <bits/stdc++.h>
using namespace std;

signed main(){
  ios_base::sync_with_stdio(0); cin.tie(NULL);

  int n,m; cin>>n>>m;
  //two piles of pancakes
  vector<int>pile1(n,0), pile2(m,0);
  for (auto &a:pile1)cin>>a;
  for (auto &a:pile2)cin>>a;
  //input

  vector<vector<int>>dp(n+1,vector<int>(m+1,0));
  vector<vector<int>>sum=dp;

  for (int i=1; i<=n; i++){
    sum[i][0]=sum[i-1][0]+pile1[i-1];//pile1[i-1] because we have offset -1
    for (int j=1; j<=m; j++){
      int *s = &sum[i][j];
      s=sum[i][j-1]+pile2[j-1];//pile2[j-1] because we have offset -1
      dp[i][j]=max(s-dp[i][j-1], s-dp[i-1][j]);
    }
  }
  cout<<dp[n][m]<<endl;
  return 0;
}
