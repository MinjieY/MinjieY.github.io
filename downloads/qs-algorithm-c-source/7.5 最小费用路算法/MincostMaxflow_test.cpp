#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100;
const int M=10000;
int cnt;
int head[N],dist[N],pre[N];//dist[i]表示源点到点i最短距离，pre[i]记录前驱
bool vis[N];//标记数组
int maxflow,mincost;//最大流
struct Edge{
   int v,next;
   int cap,flow,cost;
}E[M<<1];

void init(){//初始化 
    memset(head,-1,sizeof(head));
    cnt=0;
}

void add(int u,int v,int c,int cost){
    E[cnt].v=v;
    E[cnt].cap=c;
    E[cnt].flow=0;
    E[cnt].cost=cost;
    E[cnt].next=head[u];
    head[u]=cnt++;
}

void adde(int u,int v,int c,int cost){
    add(u,v,c,cost);
    add(v,u,0,-cost);
}

bool SPFA(int s,int t,int n){//求最短费用路的SPFA
    queue<int> q; //队列，STL实现
    memset(vis,false,sizeof(vis));//访问标记初始化
    memset(pre,-1,sizeof(pre)); //前驱初始化
    memset(dist,0x3f,sizeof(dist));
    vis[s]=true; //顶点入队vis要做标记
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        //队头元素出队，并且消除标记
        for(int i=head[u];~i;i=E[i].next){//遍历顶点u的邻接表
            int v=E[i].v;
            if(E[i].cap>E[i].flow&&dist[v]>dist[u]+E[i].cost){//松弛操作
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i; //记录前驱
                if(!vis[v]){ //顶点v不在队内
                    q.push(v);   //入队
                    vis[v]=true; //标记
                }
            }
        }
    }
    cout<<"最短路数组"<<endl;
    cout<<"dist[ ]=";
    for(int i=1;i<=n;i++)
       cout<<"  "<<dist[i];
    cout<<endl;
	return pre[t]!=-1;
}

int MCMF(int s,int t,int n){ //minCostMaxFlow
    maxflow=mincost=0;//maxflow 当前最大流量，mincost当前最小费用
    while(SPFA(s,t,n)){//表示找到了从s到t的最短路
        int d=inf;
        cout<<endl;
        cout<<"增广路径："<<t;
        for(int i=pre[t];~i;i=pre[E[i^1].v]){
            d=min(d,E[i].cap-E[i].flow); //找最小可增流量
            cout<<"--"<<E[i^1].v;
        }
        cout<<"增流："<<d<<endl;
        cout<<endl;
        maxflow+=d; //更新最大流
        for(int i=pre[t];~i;i=pre[E[i^1].v]){//沿最小费用路增减流 
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        mincost+=dist[t]*d; //dist[t]为该路径上单位流量费用之和 ，最小费用更新
	}
    return mincost;
}

void printg(int n){//输出网络邻接表
	cout<<"----------网络邻接表如下：----------"<<endl;
	for(int i=1;i<=n;i++){
		cout<<"v"<<i<<"  ["<<head[i];
		for(int j=head[i];~j;j=E[j].next)
			cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].cost<<"   "<<E[j].next;
		cout<<"]"<<endl;
	}
	cout<<endl;
}

void printflow(int n){//输出实流边
	cout<<"----------实流边如下：----------"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=head[i];~j;j=E[j].next)
			if(E[j].flow>0){
				cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"   "<<E[j].flow<<"   "<<E[j].cost;
				cout<<endl;
			}
}
/*
6 10
1 3 4 7
1 2 3 1
2 5 4 5
2 4 6 4
2 3 1 1
3 5 3 6
3 4 5 3
4 6 7 6
5 6 3 2
5 4 3 3
*/
int main(){
    int n,m;
    int u,v,w,c;
    cout<<"请输入结点个数n和边数m:"<<endl;
    cin>>n>>m;
    init();//初始化
    cout<<"请输入两个结点u,v,边(u--v)的容量w,单位容量费用c:"<<endl;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w>>c;
        adde(u,v,w,c);
    }
    cout<<endl;
    printg(n);//输出初始网络邻接表
    cout<<"网络的最小费用:"<<MCMF(1,n,n)<<endl;
    cout<<"网络的最大流值:"<<maxflow<<endl;
    cout<<endl;
    printg(n);//输出最终网络
    printflow(n);//输出实流边
    return 0;
}
