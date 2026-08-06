#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100;
const int M=10000;
int cnt,n,m;
int head[N],d[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M];

void init(){//初始化 
    memset(head,-1,sizeof(head));
    cnt=0;
}

void add(int u,int v,int c){
    E[cnt].v=v;
    E[cnt].cap=c;
    E[cnt].flow=0;
    E[cnt].next=head[u];
    head[u]=cnt++;
}

bool bfs(int s,int t){//分层
    memset(d,0,sizeof(d));
    queue<int>q;
    d[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next){
        	int v=E[i].v;
        	if(!d[v]&&E[i].cap>E[i].flow){
                d[v]=d[u]+1;
				q.push(v);
				if(v==t)  return 1;
			}	
		}
    }
    return 0;
}

int dfs(int u,int flow,int t){//在分层的基础上dfs 
    if(u==t) return flow;
	int rest=flow;//可增量 
    for(int i=head[u];~i&&rest;i=E[i].next){
    	int v=E[i].v;
    	if(d[v]==d[u]+1&&E[i].cap>E[i].flow){
            int k=dfs(v,min(rest,E[i].cap-E[i].flow),t);
			if(!k) d[v]=0,cout<<"d["<<v<<"]="<<d[v]<<endl;
			E[i].flow+=k;
			E[i^1].flow-=k;
			rest-=k;
			cout<<u<<"--"<<v<<"增流 k="<<k<<endl;
		}	
	}
	return flow-rest;
}

int Dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)){
		for(int i=1;i<=n;i++)
			cout<<"d["<<i<<"]="<<d[i]<<endl;
		maxflow+=dfs(s,inf,t);
		cout<<"增流后："<<maxflow<<endl;
	}
	return maxflow;
}

void printg(){//输出网络
	cout<<endl;
	cout<<"----------网络（链式前向星）：----------"<<endl;
	for(int i=1;i<=n;i++){
		cout<<"v"<<i<<"  ["<<head[i];
		for(int j=head[i];~j;j=E[j].next)
			cout<<"]--["<<E[j].v<<"\t"<<E[j].cap<<"\t"<<E[j].flow<<"\t"<<E[j].next;
		cout<<"]"<<endl;
   }
   cout<<endl;
}

void printflow(){//输出实流边
	cout<<endl;
	cout<<"----------实流边：----------"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=head[i];~j;j=E[j].next)
			if(E[j].flow>0){
				cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"\t"<<E[j].flow;
				cout<<endl;
        	}
}
/*
请输入结点个数n和边数m:
6 9
1 3 15
1 2 10
2 5 4
2 4 8
3 5 13
3 2 2
4 6 18
5 6 9
5 4 6
*/
int main(){
    int u,v,w;
    cout<<"请输入结点个数n和边数m:"<<endl;
    cin>>n>>m;
    init();
    cout<<"请输入两个结点u,v及边(u--v)的容量w:"<<endl;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        add(u,v,w);
		add(v,u,0);
    }
    printg();//输出初始网络
    cout<<"最大流值："<<Dinic(1,n)<<endl;
    printg();//输出最终网络
    printflow();//输出实流边
    return 0;
}
