/*
题意： 在出入栈的过程中，min函数要能及时更新
故: 用中间量来存储最小值不可行，因为如果栈中的最小值弹出之后，中间量无法更新
*/

class Solution {
public:
    void push(int value) {
        m_data.push();
        if(m_min.empty() || value<m_min.top()){
        	m_min.push(value);
        }
    }
    void pop() {
        if(m_data.top()==m_min.top())
        	m_min.pop();
        m_data.pop();
    }
    int top() {
        if(m_data.empty()){
        	return 0; //assert(m_data.size()>0);
        }
        return m_data.top();
    }
    int min() {
        if(m_min.empty())
        	return 0;
        return m_min.top();
    }

private:
	stack<int> m_data;
	stack<int> m_min;
};