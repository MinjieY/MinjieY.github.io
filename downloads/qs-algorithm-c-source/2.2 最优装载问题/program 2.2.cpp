//program 2.2 最优装载问题 
#include<iostream>
#include<algorithm> 
const int N=10005;
using namespace std;
double w[N]; //古董的重量数组

int solve1(int n,double W){
	double tmp=0.0;//tmp为已装载到船上的古董重量
    int ans=0; //ans为已装载的古董个数，初始化为0
    for(int i=0;i<n;i++){
        tmp+=w[i];
        if(tmp<=W)
            ans++;
        else
            break;
    }
    return ans;
} 

int solve2(int n,double W){//优化算法 
	double tmp=0.0;//tmp为已装载到船上的古董重量
	int ans=n; //ans为已装载的古董个数，初始化为n
    for(int i=0;i<n;i++){
        tmp+=w[i];
        if(tmp>=W){//最后一次才满足条件 
        	if(tmp==W)
        		ans=i+1;
        	else
        		ans=i;
        	break;
		}     
    }
    return ans;
}

int main(){
    int t,n;//t为测试用例个数，n为古董数量
    double W;//重量约束 
	cin>>t;
    while(t--){
        cin>>W>>n;
        for(int i=0;i<n;i++)//输入每个物品重量
            cin>>w[i]; 
        sort(w,w+n); //按古董重量升序排序
        cout<<solve1(n,W)<<endl;
    }
    return 0;
}
