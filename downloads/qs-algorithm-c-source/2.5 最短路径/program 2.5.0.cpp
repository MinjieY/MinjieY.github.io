//program 2.5.0 dijkstra算法
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
const int N=1005;
const int INF=0x3f3f3f3f; //无穷大
int G[N][N],dist[N]; //G[][]为邻接矩阵，dist[i]表示源点到结点i的最短路径长度
int p[N]; //p[i]表示源点到结点i的最短路径上i的前驱
int n,m; //n为结点数，m为边数
bool flag[N]; //如果flag[i]等于true，说明结点i已经加入到S集合;否则i属于V-S集合

void dijkstra(int u){
	for(int i=1;i<=n;i++){ //初始化
		dist[i]=G[u][i]; //初始化源点u到其他各个结点的最短路径长度
		flag[i]=false;
		if(dist[i]==INF)
			p[i]=-1; //源点u到该结点的路径长度为无穷大，说明源点u与结点i不相邻
		else
			p[i]=u; //说明结点i与源点u相邻，设置i的前驱为u
	}
    dist[u]=0;
    flag[u]=true; //初始时，集合S中只有源点u
	for(int i=1;i<n;i++){
		int temp=INF,t=u;
		for(int j=1;j<=n;j++){ //在集合V-S中寻找距离源点u最近的结点t
			if(!flag[j]&&dist[j]<temp){
				t=j;
				temp=dist[j];
			}
		}
		if(t==u) return; //找不到t，跳出循环
		flag[t]=true;  //否则，将t加入S集合
		for(int j=1;j<=n;j++){ //更新t的邻接点j的最短路径长度，松弛操作 
			if(!flag[j]&&dist[j]>dist[t]+G[t][j]){
		    	dist[j]=dist[t]+G[t][j];
		    	p[j]=t;
		    }
		}
	}
}
//
//void findpath(int u){//输出源点到其它各结点的路径 
//	int x;
//	stack<int>s;
//	cout<<"源点为："<<u<<endl;
//	for(int i=1;i<=n;i++){
//    	x=p[i];
//    	while(x!=-1){
//    		s.push(x);
//    		x=p[x];
//    	}
//	    cout<<"源点到其它各结点最短路径为：";
//    	while(!s.empty()){
//	    	cout<<s.top()<<"--";
//      		s.pop();
//    	}
//		cout<<i<<";最短距离为："<<dist[i]<<endl;
//	}
//}

int main(){
    int u,v,w,st;//u、v表示结点，w表示u--v的距离，st表示源点
    int t;//测试用例数 
    cin>>t;
    while(t--){
    	cin>>n>>m;
        for(int i=1;i<=n;i++)
        	for(int j=1;j<=n;j++)
            	G[i][j]=INF;//初始化邻接矩阵为无穷大
        while(m--){
            cin>>u>>v>>w;
            G[u][v]=min(G[u][v],w); //邻接矩阵储存，保留最小的距离
        }
        cin>>st;//输入源点 
        dijkstra(st);
        for(int i=1;i<=n;i++){//输出源点到各结点的最短路径长度，即dist[]数组 
        	if(i!=1) cout<<" ";
            if(dist[i]==INF)
               cout<<"impossible";
            else
               cout<<dist[i];
        }
        cout<<endl;
//		findpath(st);
    }
    return 0;
}
