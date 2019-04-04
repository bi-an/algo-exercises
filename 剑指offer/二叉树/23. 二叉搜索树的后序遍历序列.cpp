/*
输入一个整数数组，判断该数组是不是某二叉搜索树（又名二叉排序树）的后序遍历的结果。
如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
*/

// @Athor zzg
// 二叉搜索树：左子树的所有节点值都小于根节点，右子树的所有节点的值都大于根节点。(1)
// 后序遍历：最后一个数是根节点。
// 根据这个特点，每次从左到右找到第一个大于根节点的位置，分成左、右子树和根节点。
// 这样左子树一定满足条件(1);
// 如果分开的右子树的所有节点不满足条件(1)，则false.
// 递归结束条件：如果最后只剩一个节点，则当前遍历的所有节点都满足条件，退出。
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.size() == 0) return false;//or true
		return VerifyCore(sequence, 0, sequence.size() - 1);
	}

	bool VerifyCore(vector<int> &sequence, int start, int end) {
		if (start >= end) return true;
		int rootVal = sequence[end];
		int pos = -1;//左子树的最后一个节点位置
		bool res = true; // bool left=false, right=false;
		for (int i = start; i < end; i++) {
			if (sequence[i] > rootVal)
				break;
			pos++;
		}
		for (int i = start + pos + 1; i < end; i++) {
			if (sequence[i] <= rootVal) {
				res = false; // right=false;
				break;
			}
		}
		if (pos >= 0)
			res = res && VerifyCore(sequence, start, start + pos); // left=VerifyCore(sequence, start, start + pos);
		if (pos < end-1)
			res = res && VerifyCore(sequence, pos + 1, end - 1); // right=VerifyCore(sequence, pos + 1, end - 1);

		return res; //return left&&right;
	}
};


//1. 递归
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return false;
		size_t len = sequence.size();
		int root = sequence[len-1];
		vector<int> leftV, rightV;
		//左子树序列
		size_t i = 0;
		for ( i = 0; i < len-1; i++) {
			if (sequence[i] >= root) break;
			leftV.push_back(sequence[i]);
		}
		//右子树序列
		for (size_t j = i; j < len-1; j++) {
			if (sequence[j] <= root) return false;
			rightV.push_back(sequence[j]);
		}
		bool bLeft = true;
		if(!leftV.empty())//如果存在左子树
			bLeft = VerifySquenceOfBST(leftV);
		//if(!bLeft) return false;//提前结束递归，节约时间开支
		bool bRight = true;
		if(!rightV.empty())//如果存在右子树
			bRight = VerifySquenceOfBST(rightV);
		return bLeft && bRight;
	}
};


class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int size=sequence.size();
        if(size==0)return false;
        else if(size==1)return true;
        int root=sequence.back();
        int i,iLeftEnd;
        bool result=true;
        for(i=0;i<size-1;i++)
        {
            if(sequence[i]>root)
            {
                iLeftEnd=i;
                break;
            }
        }
        for(;i<size-1;i++)
        {
            if(sequence[i]<root)
               return false;
        }
        if(iLeftEnd>0)//保证左子树有成员才判断，避免迭代空vector
        {
            vector<int>leftson;
            leftson.assign(sequence.begin(),sequence.begin()+iLeftEnd);
            result=VerifySquenceOfBST(leftson);
            if(!result)return false;
        }
        if(iLeftEnd<size-1)//保证右子树有成员才判断，避免迭代空vector
        {
            vector<int>rightson;
            rightson.assign(sequence.begin()+iLeftEnd,sequence.end()-1);
            result=VerifySquenceOfBST(rightson);
        }
        return result;
    }
};


//2. 非递归
class Solution
{
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return false;
		size_t forIdx = 0, backIdx = sequence.size();
		while (backIdx--) {
			while (sequence[forIdx] < sequence[backIdx]) forIdx++;
			while (sequence[forIdx] > sequence[backIdx]) forIdx++;//结束时，forIdx应该和backIdx相等
			if (forIdx < backIdx) return false;
			forIdx = 0;
		}
		return true;
	}
};

class Solution
{
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return false;
		size_t forIdx = 0, backIdx = sequence.size();
		while (--backIdx) {
			while (sequence[forIdx] < sequence[backIdx]) forIdx++;
			for (size_t i = forIdx; i < backIdx; i++) {
				if (sequence[forIdx] >= sequence[backIdx]) 
					forIdx++;
				else
					return false;
			}
			forIdx = 0;
		}
		return true;
	}
};
 
// 以下为测试部分 
int main()
{
	Solution sol;
	vector<int> vec1={2,5,3,7,9,8,6};
	vector<int> vec2={5,7,6,9,11,10,8};	
	vector<int> vec3={7,4,6,5};		
	bool res1=sol.VerifySquenceOfBST(vec1);
	bool res2=sol.VerifySquenceOfBST(vec2);
	bool res3=sol.VerifySquenceOfBST(vec3);
		
	printf("%d\n",res1);
	printf("%d\n",res2);
	printf("%d\n",res3);		
	return 0;
}
