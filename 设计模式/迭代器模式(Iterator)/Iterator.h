#pragma once

// Iterator迭代器抽象类
class Iterator{
public:
	virtual void First()=0;
	virtual void Next()=0;
	virtual bool IsDone()=0;
	virtual void CurrentItem()=0;
};

// Aggregate聚集抽象类
class Aggregate{
public:
	Iterator CreateIterator()=0;
};

// ConcreteIterator具体迭代器类
class ConcreteIterator : public Iterator{
public:
	ConcreteIterator(ConcreteAggregate* aggregate)
		: aggregate(aggregate)
	{}
	

private:
	ConcreteAggregate *aggregate;
	int current=0;
};