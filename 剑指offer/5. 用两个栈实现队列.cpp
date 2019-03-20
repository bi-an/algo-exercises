//写法1
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if(stack2.empty()){
            //throw new expection("The queue is empty!");
            cout<<"The queue is empty!"<<endl;
            return -1;//可以用一个全局变量来表明 //但是，抛出异常似乎更好
        }
        int value=stack2.top();
        stack2.pop();
        return value;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};



//写法2
class Solution
{
public:
	void push(int node) {
		stack1.push(node);
		if (stack2.empty()) {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
	}

	int pop() {
		if (stack1.empty() && stack2.empty()) {
			cout << "The queue is empty!" << endl;
			exit(1);
		}
		if (!stack2.empty()) {
			int temp= stack2.top();
			stack2.pop();
			return temp;
		}
		else {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
			int temp= stack2.top();
			stack2.pop();
			return temp;
		}
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};


