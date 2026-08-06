//program 4.4 最长公共子序列 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005;
int c[maxn][maxn],m,n,b[maxn][maxn];//b[][]记录最优值来源 
char s1[maxn],s2[maxn];

void LCS(){
    memset(c,0,sizeof(c));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1]){
            	c[i][j]=c[i-1][j-1]+1;
            	b[i][j]=1;
			} 
            else if(c[i][j-1]>=c[i-1][j]){//两者找最大值，并记录最优值来源
					c[i][j]=c[i][j-1];
                	b[i][j]=2;
            	}
            	else{
            		c[i][j]=c[i-1][j];
                	b[i][j]=3;
				}
        }
    }
}

void print(int i,int j){//根据b[i][j]构造最长公共子序列
    if(i==0||j==0) return;
    if(b[i][j]==1){
        print(i-1,j-1);
        printf("%c",s1[i-1]);
    }
    else if(b[i][j]==2)
            print(i,j-1);
        else
			print(i-1,j);
}

int main(){
    int t;//测试用例数 
    scanf("%d",&t);
    while(t--){
        scanf("%s",s1);
        scanf("%s",s2);
        m=strlen(s1);
        n=strlen(s2);
		LCS();
        printf("%d\n",c[m][n]);
        print(m,n);
    }
    return 0;
}
/*测试样例 
1
ABCADAB
BACDBA
*/
