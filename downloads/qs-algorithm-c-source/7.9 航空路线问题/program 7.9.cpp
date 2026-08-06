//program 7.9 航空路线问题 
#include<iostream>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=210;
const int M=10010;
int cnt;
int head[N],dist[N],pre[N];//dist[i]表示源点到点i最短距离，pre[i]记录前驱
bool vis[N];//标记数组
int maxflow,mincost;//maxflow最大流量，mincost最小费用
string str[M];
map<string,int> maze;
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

bool SPFA(int s,int t){//求最短费用路的SPFA
    queue<int> q;
    memset(vis,false,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    memset(dist,0x3f,sizeof(dist));
    vis[s]=true;
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=E[i].next){
            int v=E[i].v;
            if(E[i].cap>E[i].flow&&dist[v]>dist[u]+E[i].cost){//松弛操作
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i;//记录前驱
                if(!vis[v]){ //顶点v不在队内
                    q.push(v);  //入队
                    vis[v]=true; //标记
                }
            }
        }
    }
	return pre[t]!=-1;
}

int MCMF(int s,int t){ //minCostMaxFlow
    maxflow=mincost=0;
    while(SPFA(s,t)){//表示找到了从s到t的最短路
        int d=inf;//可增量
        for(int i=pre[t];~i;i=pre[E[i^1].v])
            d=min(d,E[i].cap-E[i].flow); //找最小可增流量
        for(int i=pre[t];~i;i=pre[E[i^1].v]){//同向增流，反向减流 
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        maxflow+=d; //更新最大流
		mincost+=dist[t]*d; //更新最小费用，dist[t]为该路径上单位流量费用之和
	}
    return maxflow;
}

void print(int s,int t){
    vis[s]=true;
    for(int i=head[s];~i;i=E[i].next){
    	int v=E[i].v;
		if(!vis[v]&&((E[i].flow>0&&E[i].cost<=0)||(E[i].flow<0&&E[i].cost>=0))){
			print(v,t);
			if(v<=t)
				cout<<str[v]<<endl;
		}	
	}
}

int main(){
	int t,n,m;//测试用例数,结点数，边数 
    string str1,str2;
    cin>>t;
    while(t--){
		cin>>n>>m;
	    init();//初始化
	    maze.clear();
	    for(int i=1;i<=n;i++){//输入n个景点 
			cin>>str[i];
			maze[str[i]]=i;//字符串映射到数字
			if(i==1||i==n)
				adde(i,i+n,2,0);//起点和终点，i拆点为i和i+n
			else
				adde(i,i+n,1,0);
	    }
	    for(int i=1;i<=m;i++){//输入m条航线 
	        cin>>str1>>str2;
	        int a=maze[str1],b=maze[str2];//字符串映射到数字 
	        if(a>b)
	        	swap(a,b);//保证a<b 
			if(a==1&&b==n)//起点和终点
				adde(a+n,b,2,-1);
			else
				adde(a+n,b,1,-1);
	    }
	    if(MCMF(1,2*n)==2){//流量
			cout<<-mincost<<endl;
//			cout<<str[1]<<endl;
//			memset(vis,0,sizeof(vis));//访问标记初始化
//			print(1,n);
//			cout<<str[1]<<endl;
	    }
	    else
			cout<<"No Solution!"<<endl;
	}
    return 0;
}
/*测试用例
1
8 10
Zhengzhou
Luoyang
Xian
Chengdu
Kangding
Xianggelila
Motuo
Lasa
Zhengzhou Luoyang
Zhengzhou Xian
Luoyang Xian
Luoyang Chengdu
Xian Chengdu
Xian Xianggelila
Chengdu Lasa
Kangding Motuo
Xianggelila Lasa
Motuo Lasa
*/ 
