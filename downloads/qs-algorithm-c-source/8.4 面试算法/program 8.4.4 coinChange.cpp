int coinChange(vector<int>& coins,int amount){//零钱兑换 动态规划 leetcode322 
    vector<int> dp(amount+1,amount+1);//初始化dp[]，最少硬币数为最大值（总金额+1） 
    dp[0]=0;
    for(int i=1;i<=amount;i++){//枚举所有金额 
        for(int j=0;j<coins.size();j++){//枚举所有硬币面额 
            if(coins[j]<=i)
                dp[i]=min(dp[i],dp[i-coins[j]]+1);//状态转移 
        }
    }
    return dp[amount]>amount? -1:dp[amount];//如果仍为初值，说明没找到答案，返回-1
}

vector<int> dp; 
int solve(vector<int>& coins,int m){//零钱兑换 记忆化递归
    if(m<0) return -1;
    if(m==0) return 0;
    if(dp[m]!=0) return dp[m];//已有答案，直接返回 
    int res=m+1; //初始化为最大值（总金额+1）
    for(int j=0;j<coins.size();j++){//枚举所有硬币面额 
        int sub=solve(coins,m-coins[j]);//求解子问题 
        if(sub==-1) continue;
        res=min(res,sub+1);//求最少硬币数
    }
    return dp[m]=res>m?-1:res;//如果仍为初值，说明没找到答案，返回-1
}

int coinChange(vector<int>& coins,int amount){//记忆化递归 leetcode322 
    dp.resize(amount+1);
    return solve(coins,amount);
}


int change(int amount,vector<int>& coins){//零钱兑换II leetcode518 
    vector<int> dp(amount+1,0);//初始化数组为0 
    dp[0]=1;
    for(int i=0;i<coins.size();i++){//枚举硬币，如果先枚举金额再枚举硬币会重复计算3=1+2 3=2+1
        for(int j=1;j<=amount;j++){//枚举金额
            if(j>=coins[i])
            	dp[j]+=dp[j-coins[i]];
        }
    }
    return dp[amount];
}
