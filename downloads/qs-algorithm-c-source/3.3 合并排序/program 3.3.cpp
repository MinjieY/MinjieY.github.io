//program 3.3 合并排序
#include<iostream>
using namespace std;
const int M=10005;
int A[M];

void Merge(int A[],int low,int mid,int high){ //合并函数，合并有序序列A[low:mid]和A[mid+1:high]
    int *B=new int[high-low+1];//申请一个辅助数组
    int i=low,j=mid+1,k=0;
    while(i<=mid&&j<=high) {
        if(A[i]<=A[j]) //将较小元素存放到B[]中
            B[k++]=A[i++];
        else
            B[k++]=A[j++];
    }
    while(i<=mid) B[k++]=A[i++]; //如果前半部分有剩余，将剩余元素放置到B[]中
    while(j<=high) B[k++]=A[j++]; //如果后半部分有剩余，将剩余元素放置到B[]中
    for(i=low,k=0;i<=high;i++) //将有序序列放回A[]数组
        A[i]=B[k++];
    delete []B;
}

void MergeSort(int A[],int low,int high){//合并排序 
    if(low<high){
        int mid=(low+high)/2; //取中点
        MergeSort(A,low,mid); //对A[low:mid]中的元素合并排序
        MergeSort(A,mid+1,high); //对A[mid+1:high]中的元素合并排序
        Merge(A,low,mid,high); //将两个有序序列A[low:mid]和A[mid+1:high]合并
    }
}

int main(){
    int t,n; //测试用例数，元素个数
    cin>>t;
    while(t--){
	    cin>>n;
	    for(int i=0;i<n;i++)
	       cin>>A[i];
	    MergeSort(A,0,n-1);
	    for(int i=0;i<n;i++)
	    	cout<<A[i]<<" ";
	    cout<<endl;
    }
    return 0;
}
