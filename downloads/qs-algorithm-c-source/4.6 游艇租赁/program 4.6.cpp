//program 4.6 游艇租赁 
#include<iostream>
using namespace std;
const int maxn=105;
int r[maxn][maxn],m[maxn][maxn],s[maxn][maxn];

int rent(int n){ //求最少租金 
    for(int d=3;d<=n;d++){ //问题规模为d
        for(int i=1;i<=n-d+1;i++){ //起始站点 
            int j=i+d-1; //结束站点
            for(int k=i+1;k<j;k++){ //枚举停靠站点 
                int temp=m[i][k]+m[k][j];
                if(temp<m[i][j]){
                    m[i][j]=temp;
                    s[i][j]=k;
                }
            }
        }
    }
    return m[1][n];
}

//void print(int i,int j){ //构造最优解 
//    if(s[i][j]==0){
//    	cout<< "--"<<j;
//    	return ;
//    }
//    print(i,s[i][j]); //递归求解 
//    print(s[i][j],j); //递归求解
//}

int main(){
    int t,n; //测试用例数,站点数 
    cin>>t;
    while(t--){
		cin>>n;
	    for(int i=1;i<=n;i++){
	    	for(int j=i+1;j<=n;j++){
	            cin>>r[i][j];
	            m[i][j]=r[i][j];
	        }
		}
	    cout<<rent(n)<<endl;
//		cout<<"最少租金经过的站点："<<1;
//		print(1,n);
//		cout<<endl;
	}
	return 0;
}
/*测试数据 
1
6
2 6 9 15 20 3 5 11 18 3 6 12 5 8 6
*/
