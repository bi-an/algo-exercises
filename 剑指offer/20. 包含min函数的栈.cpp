/*
题意： 在出入栈的过程中，min函数要能及时更新
故: 用中间量来存储最小值不可行，因为如果栈中的最小值弹出之后，中间量无法更新
*/

// 基本思想：m_min始终存放m_data中的最小值
// 所以只要始终保证这一点，就有如下性质：
// 从第一次入栈开始，如果m_data不为空，那么m_min一定不为空；
// 如果m_data出栈，那么就要检查出栈元素是否与m_min相同，如果相同则m_min也要同时出栈。

class Solution {
public:
    void push(int value) {
        m_data.push(value);
        if(m_min.empty() || value<=m_min.top()){
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