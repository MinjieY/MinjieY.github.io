/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-10-18 15:31:47
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-03-04 00:11:44
 * @FilePath: \《趣学算法》第2版 c源码\5.5 n皇后问题\program 5.5.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//program 5.5 n�ʺ����� 
#include<iostream>
#include<cmath> //�����ֵ������Ҫ�����ͷ�ļ�
using namespace std;
const int maxn=105;
int n;//n��ʾn���ʺ�
int x[maxn]; //x[i]��ʾ��i���ʺ�����ڵ�i�е�x[i]��
int sum;   //��¼��ĸ���

bool place(int t){ //�жϵ�t���ʺ��ܷ����
    for(int j=1;j<t;j++){
		if(x[t]==x[j]||t-j==abs(x[t]-x[j]))//�ж��С��Խ����Ƿ��ͻ
        	return false;
    }
    return true;
}

void backtrack(int t){
    if(t>n){ //����Ҷ��,��ʾ�Ѿ��ҵ�һ����
        sum++;
//        for(int i=1; i<=n;i++) //��ӡ�ʺ�λ�� 
//        	cout<<x[i]<<" ";
//        cout<<endl;
//        cout<<"----------"<<endl;
		return ; 
    }
    for(int i=1;i<=n;i++){ //�ֱ��ж�n����֧
        x[t]=i;
        if(place(t))
            backtrack(t+1);
    }
}

int main(){
	int t;//���������� 
	cin>>t;
	while(t--){
    	cin>>n;
	    sum=0;
	    backtrack(1);
	    cout<<sum<<endl;
    }
    return 0;
}
/*�������� 
2
4
10
*/
