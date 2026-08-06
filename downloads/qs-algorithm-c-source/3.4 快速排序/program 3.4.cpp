/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-10-18 15:31:47
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-03-04 00:09:36
 * @FilePath: \《趣学算法》第2版 c源码\3.4 快速排序\program 3.4.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//program 3.4 ��������
#include<iostream>
using namespace std;
const int M=10005;
int R[M];

int Partition(int R[],int low,int high){//���ֺ���
    int i=low,j=high,pivot=R[low];//��׼Ԫ��
    while(i<j){
        while(i<j&&R[j]>pivot) j--;//����ɨ��
        if(i<j)
            swap(R[i++],R[j]);//R[i]��R[j]������,i+1����һλ
        while(i<j&&R[i]<=pivot) i++;//����ɨ��
        if(i<j)
            swap(R[i],R[j--]);//R[i]��R[j]������,j-1����һλ
    }
    return i;//���ػ�����ɺ��׼Ԫ��λ��
}

int Partition2(int R[],int low,int high){//���ֺ����Ż� 
    int i=low,j=high,pivot=R[low];//��׼Ԫ��
    while(i<j){
        while(i<j&&R[j]>pivot) j--;//����ɨ��
        while(i<j&&R[i]<=pivot) i++;//����ɨ��
        if(i<j)
            swap(R[i++],R[j--]);//R[i]��R[j]����
    }
    if(R[i]>pivot){
        swap(R[i-1],R[low]);//R[i-1]��R[low]����
        return i-1;//���ػ�����ɺ��׼Ԫ��λ��
    }
    swap(R[i],R[low]);//R[i]��R[low]����
    return i;//���ػ�����ɺ��׼Ԫ��λ��
}

void QuickSort(int R[],int low,int high){//ʵ�ֿ����㷨
    if(low<high){
        int mid=Partition(R,low,high); //��׼λ��
        QuickSort(R,low,mid-1);//������ݹ����
        QuickSort(R,mid+1,high);//������ݹ����
    }
}

int main(){
    int t,n; //������������Ԫ�ظ���
    cin>>t;
    while(t--){
		cin>>n;
    	for(int i=0;i<n;i++)
        	cin>>R[i];
    	QuickSort(R,0,n-1);
	    for(int i=0;i<n;i++){
	        if(i!=0)
	            cout<<" ";
	        cout<<R[i];
	    }
	    cout<<endl;
    }
    return 0;
}
