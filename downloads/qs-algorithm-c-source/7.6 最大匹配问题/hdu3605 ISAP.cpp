#include<cstdio>//缩点+ISAP 1279ms
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1050;
const int M=10500;
int cnt,n,m;
int head[N],pre[N],h[N],g[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M<<1];//双边

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

int main(){
    int x,c;
	while(~scanf("%d%d",&n,&m)){
    	init();
		map<int,int> mp; 
        for(int i=0;i<n;i++){
            int res=0; 
            for(int j=0;j<m;j++){
                scanf("%d",&x);
                if(x) res+=(1<<j);
            }
            mp[res]++;
        }
        int nn=(1<<m),s=0,t=nn+m+1;
        for(int i=0;i<nn;i++){
            if(mp[i]==0) continue;
            adde(s,i+1,mp[i]);
            for(int j=0;j<m;j++){
                if(i&(1<<j))
                    adde(i+1,j+nn+1,mp[i]);
            }
        }
        for(int i=0;i<m;i++){
            scanf("%d",&c);
            adde(i+nn+1,t,c);
        }
        if(ISAP(s,t,t+1)==n) printf("YES\n");
        else printf("NO\n");
    }
    return 0 ;
}
