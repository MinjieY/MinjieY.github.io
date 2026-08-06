//program 2.4 会议安排问题
#include<iostream>
#include<algorithm>
using namespace std;
struct Meet{
    int beg;   //会议的开始时间
    int end;   //会议的结束时间
    int num;   //记录会议的编号
}meet[10005];   //会议的最大个数为10000

bool cmp(Meet x,Meet y){//自定义排序优先级 
    if(x.end==y.end)
        return x.beg>y.beg;
    return x.end<y.end;
}

void init(int n){//读入数据
    int s,e;
    for(int i=0;i<n;i++){
        cin>>s>>e;
        meet[i].beg=s;
        meet[i].end=e;
        meet[i].num=i+1;
    }
}


int solve(int n){
	sort(meet,meet+n,cmp); //对会议按结束时间排序
    int ans=1;
    int last=meet[0].end;  //记录刚刚被选中会议的结束时间
    for(int i=1;i<n;i++){
        if(meet[i].beg>=last){ //如果会议i开始时间大于等于刚选中的会议的结束时间
        	ans++;
        	last=meet[i].end;
        }
    }
    return ans;
}

int main(){
    int t,n;//t为测试用例数,n为会议数
    cin>>t;
    while(t--){
    	cin>>n;
		init(n);
		cout<<solve(n)<<endl;
    }
	return 0;
}
