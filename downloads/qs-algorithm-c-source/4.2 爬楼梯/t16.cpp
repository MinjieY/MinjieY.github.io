//program 4.2 爬楼梯，t16
#include<cstdio>
#include<cstring>
const int maxn=50;
using namespace std;
int dp[maxn+1];

int solve1(int n){//递归，TLE,超时 
    if(n==1||n==2)
        return n;
    else
        return solve1(n-2)+solve1(n-1);
}

int solve2(int n){//记忆化递归(备忘录)
    if(dp[n]!=0)
		return dp[n];
	if(n==1||n==2)
        dp[n]=n;
    else
        dp[n]=solve2(n-2)+solve2(n-1);
    return dp[n];
}

int solve3(int n){//动态规划 
	dp[1]=1;
	dp[2]=2;
    for(int i=3;i<=n;i++)
    	dp[i]=dp[i-2]+dp[i-1];
    return dp[n];
}

int solve4(int n){//动态规划，迭代(空间优化)
	if(n==1||n==2)
        return n;
    int s1=1,s2=2,temp=0;
    for(int i=3;i<=n;i++){
    	temp=s1+s2;
    	s1=s2;
    	s2=temp;
	}
    return s2;
}

void solve(){//动态规划，打表
	dp[1]=1;
	dp[2]=2;
    for(int i=3;i<=maxn;i++)
    	dp[i]=dp[i-2]+dp[i-1];
}

int main(){
    int n;
    //solve();//动态规划，打表
    while(~scanf("%d",&n)){
        printf("%d\n",solve1(n));
        //memset(dp,0,sizeof(dp)); //记忆化递归的初始化
        //printf("%d\n",solve2(n));
        //printf("%d\n",solve3(n));
        //printf("%d\n",solve4(n));
        //printf("%d\n",dp[n]); //动态规划，打表
    }
    return 0;
}
