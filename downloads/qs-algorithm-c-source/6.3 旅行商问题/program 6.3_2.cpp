//program 6.3 旅行商问题 回溯法 
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=1e7;
const int N=105;
int g[N][N];
int x[N],bestx[N]; //记录当前路径,当前最优路径
int cl,bestl; //当前路径长度,当前最短路径长度
int n,m;     //城市个数n,边数m

void traveling(int t){//回溯法 
    if(t>n){ //到达叶子结点
        if(g[x[n]][1]!=inf&&(cl+g[x[n]][1]<bestl)){
            for(int j=1;j<=n;j++)//记录最优解 
            	bestx[j]=x[j];
            bestl=cl+g[x[n]][1];//记录最优值
        }
        return; 
    }
    for(int j=t;j<=n;j++){
        if(g[x[t-1]][x[j]]!=inf&&(cl+g[x[t-1]][x[j]]<bestl)){
            swap(x[t],x[j]);//交换两个元素的值
            cl=cl+g[x[t-1]][x[t]];
            traveling(t+1);
            cl=cl-g[x[t-1]][x[t]];//还原现场
            swap(x[t],x[j]);//复位 
        }
    }
}

void init(){//初始化
    bestl=inf;
    cl=0;
    memset(g,0x3f,sizeof(g));
    memset(bestx,0,sizeof(bestx));
    for(int i=0;i<=n;i++)
        x[i]=i;
}

void print(){//打印路径
    cout<<"最短路径:  ";
    for(int i=1;i<=n;i++)
        cout<<bestx[i]<<"--->";
    cout<<"1"<<endl;
}

int main(){
    int t;//测试用例数 
	int u,v,w;//u,v代表结点，w代表u和v之间路的长度;
    cin>>t;
    while(t--){
    	cin>>n>>m;
    	init();
	    for(int i=1;i<=m;i++){
	        cin>>u>>v>>w;
	        g[u][v]=g[v][u]=w;
	    }
    	traveling(2);
    	cout<<bestl<<endl;
    	//print();
    }
    return 0;
}
/*测试数据
1
5 9
1 2 3
1 4 8
1 5 9
2 3 3
2 4 10
2 5 5
3 4 4
3 5 3
4 5 20
*/ 
