/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

// 思路:用一个成员nextElement保存下一个元素,然后调用Iterator::next()跳转到下下一个元素
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
        if(Iterator::hasNext()) {
            nextElement_ = Iterator::next();
            volatile_ = true;
        }
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        return nextElement_;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
	    int ret = nextElement_;
        if((volatile_ = Iterator::hasNext())) {
            nextElement_ = Iterator::next();
        }
        return ret;
	}
	
	bool hasNext() const {
        return volatile_;
	}
private:
    int nextElement_;
    bool volatile_; // 标识nextElement_是否有效
};