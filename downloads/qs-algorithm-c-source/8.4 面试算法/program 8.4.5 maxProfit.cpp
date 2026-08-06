int maxProfit(vector<int>& prices){//买卖股票的最佳时机 leetcode121 
    int buy=prices[0],sell=0;//当前最低点，当前最大收益 
    for(int i=1;i<prices.size();i++){
        buy=min(buy,prices[i]);
		sell=max(sell,prices[i]-buy);
    }
    return sell;
}

int maxProfit(vector<int>& prices){//买卖股票的最佳时机II leetcode122 
    int sell=0;
    for(int i=1;i<prices.size();i++)
        sell+=max(0,prices[i]-prices[i-1]);//累加低买高卖差价 
    return sell;
}

int maxProfit(vector<int>& prices){//买卖股票的最佳时机III leetcode123
	int buy1=prices[0],sell1=0; //第1次买入最低点、卖出最大收益  
	int buy2=prices[0],sell2=0; //第2次买入最低点、卖出最大收益 
	for(int i=1;i<prices.size();i++){
		buy1=min(buy1,prices[i]);
		sell1=max(sell1,prices[i]-buy1);
		buy2=min(buy2,prices[i]-sell1);//当前价格减去上次收益 
		sell2=max(sell2,prices[i]-buy2);
	}
	return sell2;
}

int maxProfit(int k,vector<int>& prices){//买卖股票的最佳时机IV leetcode188
	if(prices.size()==0||k==0) return 0;
	vector<int>buy(k+1,prices[0]);//初始化买入最低点为prices[0] 
    vector<int>sell(k+1,0);       //初始化最大收益为0 
    for(int i=1;i<prices.size();i++){
        for(int j=1;j<=k;j++){//枚举k次买卖
            buy[j]=min(buy[j],prices[i]-sell[j-1]);//当前价格减去上次收益 
            sell[j]=max(sell[j],prices[i]-buy[j]);
        }
    }
    return sell[k];
}
