//program 4.8 01背包 一维数组优化 
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=105;
const int maxw=10005;
int dp[maxw];//dp[j]表示放入容量为j的背包获得的最大价值
int w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值 

int knapsack_opt(int n,int W){//一维数组优化 01背包 
    for(int i=1;i<=n;i++)
        for(int j=W;j>=w[i];j--)//倒推 
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
    return dp[W];
}

int main(){
    int n,W,t;//n表示n个物品，W表示背包的容量，t表示测试用例数 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    for(int i=1;i<=n;i++)
	        cin>>w[i]>>v[i];
	    for(int j=1;j<=W;j++)//初始化为0
        	dp[j]=0;
	    cout<<knapsack_opt(n,W)<<endl;
    }
    return 0;
}
/*测试数据 
2
5 10
2 6
5 3
4 5
2 4
3 6
4 52
12 13
10 24
22 13
9 24
*/
