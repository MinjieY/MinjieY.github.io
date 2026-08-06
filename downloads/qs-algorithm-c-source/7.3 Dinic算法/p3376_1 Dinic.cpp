#include<cstdio>//当前弧优化51ms 
#include<cstring>
#include<queue>
#include<algorithm>
#define ll long long
const int inf=0x3f3f3f3f;
const int N=210;
const int M=5010;
using namespace std;
struct newt{
	int v,w,next;
}E[M<<1];
int head[N],cur[N],d[N],n,m,s,t,cnt;

void init(){//初始化 
    memset(head,-1,sizeof(head));
    cnt=0;
}

void adde(int u,int v,int w){
	E[cnt].v=v;
	E[cnt].w=w;
	E[cnt].next=head[u];
	head[u]=cnt++;
}
 
bool bfs(){//分层
    memset(d,0,sizeof(d));
    queue<int>q;
    d[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next){
        	int v=E[i].v;
        	if(!d[v]&&E[i].w>0){
                d[v]=d[u]+1;
				q.push(v);
				if(v==t)  return 1;
			}	
		}
    }
    return 0;
}

int dfs(int u,int flow){//在分层的基础上dfs 
    if(u==t) return flow;
	int rest=flow;//最小残量 
    for(int &i=cur[u];~i;i=E[i].next){//引用&，cur和i一起更新，或在内部写cur[u]=E[i].next 
    	int v=E[i].v;
    	if(d[v]==d[u]+1&&E[i].w>0){
            int k=dfs(v,min(rest,E[i].w));
			if(!k) d[v]=0;//优化，有当前弧优化时，去掉也没影响 
			E[i].w-=k;
			E[i^1].w+=k;
			rest-=k;
			if(!rest) break;
		}	
	}
	return flow-rest;
}

ll Dinic(int s,int t){
	ll maxflow=0;
	while(bfs()){
		for(int i=1;i<=n;i++)
			cur[i]=head[i];
		maxflow+=dfs(s,inf);
	}
	return maxflow;
}

int main(){
	int u,v,w;
	while(~scanf("%d%d%d%d",&n,&m,&s,&t)){
        init();
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            adde(u,v,w),adde(v,u,0);
        }
        printf("%lld\n", Dinic(s,t));
    }
	return 0;
}
