vector<int> maxSlidingWindow(vector<int>& nums,int k){ //滑动窗口最大值 leetcode239 
    if(k==0) return {};
	vector<int>ans; //记录答案 
	deque<int>q;    //双端队列模拟单调队列 
	for(int i=0;i<k;i++){ //处理前k个元素 
		while(!q.empty() && nums[i]>nums[q.back()]) //保持单调性 
			q.pop_back();
		q.push_back(i); //将下标入队 
	}
	ans.push_back(nums[q.front()]); //记录答案
	for(int i=k;i<nums.size();i++){
		if(!q.empty() && q.front()<i-k+1) //删除过时元素 
			q.pop_front();
		while(!q.empty() && nums[i]>nums[q.back()]) //保持单调性 
			q.pop_back();
		q.push_back(i); //将下标入队 
		ans.push_back(nums[q.front()]); //记录答案
	}
	return ans;
}
