//program 7.8 最大收益问题 ISAP
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=210;
const int M=10210;
int cnt;
int head[N],pre[N],h[N],g[N];
bool vis[N];//访问标记 
struct Edge{
   int v,next;
   int cap,flow;
}E[M<<1];//双边

void init(){//初始化 
    memset(vis,false,sizeof(vis));
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

void adde(int u,int v,int c){
    add(u,v,c);
    add(v,u,0);
}

void set_h(int t,int n){//标高 
    queue<int> q;
    memset(h,-1,sizeof(h));
    memset(g,0,sizeof(g));
    h[t]=0;
    q.push(t);
    while(!q.empty()){
		int u=q.front();q.pop();
		++g[h[u]];//高度为h[u]的节点个数
		for(int i=head[u];~i;i=E[i].next){
			int v=E[i].v;
			if(h[v]==-1){
				h[v]=h[u]+1;
				q.push(v);
			}
        }
    }
}

int ISAP(int s,int t,int n){
    set_h(t,n);
    int ans=0,u=s,d;
    while(h[s]<n){
        int i=head[u];
        if(u==s)
           d=inf;
        for(;~i;i=E[i].next){
			int v=E[i].v;
			if(E[i].cap>E[i].flow&&h[u]==h[v]+1){
				u=v;
                pre[v]=i;
                d=min(d,E[i].cap-E[i].flow);
                if(u==t){
					while(u!=s){
						int j=pre[u];
						E[j].flow+=d;
						E[j^1].flow-=d;
						u=E[j^1].v;
					}
					ans+=d;
					d=inf;
                }
                break;
            }
        }
        if(i==-1){
			if(--g[h[u]]==0)
				break;
			int hmin=n-1;
			for(int j=head[u];~j;j=E[j].next)
				if(E[j].cap>E[j].flow)
					hmin=min(hmin,h[E[j].v]);
			h[u]=hmin+1;
			++g[h[u]];
			if(u!=s)
				u=E[pre[u]^1].v;
        }
    }
    return ans;
}

void dfs(int u){//深度搜索最大获益方案
	vis[u]=true;
	for(int i=head[u];~i;i=E[i].next){//读当前结点的邻接表
    	if(E[i].cap>E[i].flow){
        	int v=E[i].v;
        	if(!vis[v])
            	dfs(v);
    	}
    }
}

void print(int m,int n){//输出最佳方案
	cout<<"----------最大获益方案如下：----------"<<endl;
	dfs(0);
	cout<<"选中的实验编号："<<endl;
	for(int i=1;i<=m;i++)
		if(vis[i])
        	cout<<i<<"  ";
	cout<<endl;
	cout<<"选中的仪器编号："<<endl;
	for(int i=m+1;i<=m+n;i++)
    	if(vis[i])
        	cout<<i-m<<"  ";
}

int main(){
	int t;//测试用例数
	cin>>t;
    while(t--){
    	int m,n,c,num,total,sum=0;
    	cin>>m>>n;//实验数m和仪器数n
    	init();
		total=m+n;//实验数m和仪器数n
		for(int i=1;i<=m;i++){
			cin>>c;//实验收益 
			sum+=c;//累加实验收益 
			adde(0,i,c);//源点到实验i的边，容量为c 
			while(cin>>num,num)//为该项目需要的仪器编号，为0时结束
				adde(i,m+num,inf);//实验到需要仪器的边，容量为无穷大
		}
		for(int j=m+1;j<=total;j++){
        	cin>>c;
        	adde(j,total+1,c);//仪器到汇点的边，容量为仪器费用
    	}
        cout<<sum-ISAP(0,total+1,total+2)<<endl;
//		print(m,n);
    }
    return 0;
}
/*测试用例
1
5 15
20 2 4 8 11 0
38 1 5 14 0
25 2 5 7 15 0
17 1 3 6 9 13 0
22 10 12 15 0
2 7 4 8 10 1 3 7 5 9 15 6 12 17 8
*/ 
