#include <iostream>
#include "Component.h"
using namespace std;

void test() {
	Composite root("root");
	root.Add(make_shared<Leaf>("Leaf A"));

	std::shared_ptr<Composite> comp = make_shared<Composite>("Composite X");
	comp->Add(make_shared<Leaf>("Leaf XA"));
	comp->Add(make_shared<Leaf>("Leaf XB"));

	root.Add(comp);

	std::shared_ptr<Leaf> leafC = make_shared<Leaf>("Leaf C");
	int useC = leafC.use_count();

	root.Add(leafC);
	useC = leafC.use_count();

	root.Remove(leafC);
	useC = leafC.use_count();

	std::shared_ptr<Composite> comp2 = make_shared<Composite>("Composite XY");
	comp2->Add(make_shared<Leaf>("Leaf XYA"));
	comp2->Add(make_shared<Composite>("Composite XYZ")); // Composite XYZ û��Ҷ�ӣ����ǿ������Ҷ��

	comp->Add(comp2);

	root.Add(make_shared<Leaf>("Leaf B"));

	root.Display(1);

	std::shared_ptr<Leaf> leafD = make_shared<Leaf>("Single Leaf D");

	std::cout << std::endl;
}

int main(){

	test(); // �뿪������ʱ, shared_ptr�Զ�����, ���ڳ�����ջģʽ(����shared_ptr����ջ��)���������һ��shared_ptr�����ָ����������
	/* ��������˳���ǣ�
		Single Leaf D 
		Leaf C 
		Leaf A 
		Leaf XA
		Leaf XB 
		Leaf XYA
		Composite XYZ
		Composite XY
		Composite X
		Leaf B 
		root 
	*/ 

	return 0;
}