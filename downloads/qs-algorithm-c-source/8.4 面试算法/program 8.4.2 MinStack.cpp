class MinStack{ //最小栈 leetcode155  面试题03.02 
    stack<int> data_stack;//数据栈，保存数据元素 
    stack<int> min_stack;//最小栈，栈顶为当前栈的最小值，是一个单调栈（栈中元素非递增）
public:
    MinStack(){//初始化 
        
    }
    
    void push(int val){//入栈 
        data_stack.push(val);
        if(min_stack.empty() || val<=min_stack.top())//最小栈为空或者val小于等于最小栈的栈顶
        	min_stack.push(val);//最小栈入栈 
    }
    
    void pop(){//出栈 
        if(min_stack.top() == data_stack.top())//如果最小栈的栈顶与数据栈的栈顶相等
			min_stack.pop();//最小栈出栈 
		data_stack.pop();
    }
    
    int top(){//取栈顶 
        return data_stack.top();
    }
    
    int getMin(){//取栈的最小值
        return min_stack.top();
    }
};
