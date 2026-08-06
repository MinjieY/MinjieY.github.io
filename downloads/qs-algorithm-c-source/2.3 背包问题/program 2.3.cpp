//program 2.3 背包问题 
#include<iostream>
#include<algorithm>
using namespace std;
const int M=10005;
struct node{
    double w;//每个物品的重量
    double v;//每个物品的价值
    double p;//性价比
}s[M];

bool cmp(node a,node b){//自定义比较函数 
    return a.p>b.p;//根据物品的单位价值从大到小排序
}

double solve(int n,double W){
	double sum=0.0;//sum表示示装入物品的价值之和
	double cleft=W;//背包剩余容量 
    for(int i=0;i<n;i++){//贪心算法求解 
        if(s[i].w<=cleft){//如果物品的重量小于等于剩余容量 
            cleft-=s[i].w;
            sum+=s[i].v;
        }
        else{//如果物品的重量大于剩余容量 
            sum+=cleft*s[i].p;//部分装入
            break;
        }
    }
    return sum; 
}

int main(){
    int t,n;//t为测试用例个数,n为物品个数
    double W;//背包容量 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    for(int i=0;i<n;i++){
	        cin>>s[i].w>>s[i].v;
	        s[i].p=s[i].v/s[i].w;//每个宝物单位价值
	    }
	    sort(s,s+n,cmp);
    	cout<<solve(n,W)<<endl;//输出装入宝物的最大价值
    }
    return 0;
}
