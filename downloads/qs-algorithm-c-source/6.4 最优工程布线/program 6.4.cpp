//program 6.4 最优工程布线 分支限界法 
#include<iostream>
#include<queue>
using namespace std;
const int N=55;
int dir[4][2]={0,1,1,0,0,-1,-1,0};//右下左上四个方向偏移量
struct node{
	int x,y;
};
int grid[N][N];//地图
node pre[N][N];//前驱 

bool bfs(node s,node e){
    if((s.x==e.x)&&(s.y==e.y))
        return true;
    node cur,next;
    queue<node>q;
    grid[s.x][s.y]=0;//标记初始为0,未布线-1,墙壁-2
	q.push(s);
    while(!q.empty()){
    	cur=q.front();
    	q.pop();
        for(int i=0;i<4;i++){//四个方向右下左上
            next.x=cur.x+dir[i][0];
            next.y=cur.y+dir[i][1];
            if(grid[next.x][next.y]==-1){//尚未布线
                grid[next.x][next.y]=grid[cur.x][cur.y]+1;
                pre[next.x][next.y]=cur;
                q.push(next);
                if((next.x==e.x)&&(next.y==e.y))//找到目标
					return true;
            }   
        }
    }
    return false;
}

void print(node s,node cur){//输出最优布线方案 
    if(cur.x==s.x&&cur.y==s.y){
        printf("(%d, %d)\n",cur.x,cur.y);
        return;
    }
    print(s,pre[cur.x][cur.y]);//逆序输出
    printf("(%d, %d)\n",cur.x,cur.y);
}

void init(int m,int n){//标记大于0表示已布线,未布线-1,墙壁-2
    for(int i=1;i<=m;i++) //方格阵列初始化为-1
        for(int j=1;j<=n;j++)
            grid[i][j]=-1;
    for(int i=0;i<=n+1;i++) //方格阵列上下围墙
        grid[0][i]=grid[m+1][i]=-2;
    for(int i=0;i<=m+1;i++) //方格阵列左右围墙
        grid[i][0]=grid[i][n+1]=-2;
}

int main(){
    int t,m,n,a,b;//测试用例数,行数，列数
	node s,e;//起点，终点;
    cin>>t;
    while(t--){
    	cin>>m>>n;
    	init(m,n);
	    while(true){//障碍 
	    	cin>>a>>b;
        	if(a==0&&b==0) break;
        	grid[a][b]=-2;
    	}
    	cin>>s.x>>s.y;
    	cin>>e.x>>e.y;
    	if(bfs(s,e))
    		cout<<grid[e.x][e.y]<<endl;
    	else
    		cout<<-1<<endl;
    	//print(s,e);//输出路径 
    }
    return 0;
}
/*测试数据
1
5 6
1 6
2 3
3 4
3 5
5 1
0 0
2 1
4 6
*/ 
