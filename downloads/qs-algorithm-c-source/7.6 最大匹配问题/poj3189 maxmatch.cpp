#include<cstdio>//二分图多重匹配，匈牙利算法，0ms
#include<cstring>
using namespace std;
const int N=1005;
int cap[25],g[N][25],cnt[25],match[25][N];
bool vis[25];
int n,m;

int dfs(int u,int l,int r){
    for(int i=l;i<=r;i++){
    	int v=g[u][i];
        if(!vis[v]){
            vis[v]=1;
            if(cnt[v]<cap[v]){//匹配次数小于容量 
                match[v][cnt[v]++]=u;
                return 1;
            }
            for(int j=0;j<cnt[v];j++){
                if(dfs(match[v][j],l,r)){
                    match[v][j]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool maxmatch(int l,int r){
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(!dfs(i,l,r))
            return 0;
    }
    return 1;
}

bool check(int len){
    for(int i=1;i+len-1<=m;i++)
        if(maxmatch(i,i+len-1))
            return 1;
    return 0;
}

int solve(){
	int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid))
			ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&g[i][j]);
        for(int i=1;i<=m;i++)
            scanf("%d",&cap[i]);
        printf("%d\n",solve());
    }
    return 0;
}
