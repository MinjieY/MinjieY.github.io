//program 4.4 最长公共子序列 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005;
int c[maxn][maxn],m,n;
char s1[maxn],s2[maxn];

void LCS(){
    memset(c,0,sizeof(c));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1])
                c[i][j]=c[i-1][j-1]+1;
            else
                c[i][j]=max(c[i-1][j],c[i][j-1]);
        }
    }
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
    }
    return 0;
}
