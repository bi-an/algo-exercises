#include "Finery.h"
using namespace std;

int main(){

	Person xc("С��");

	Sneaker sneaker;
	BigTrouser bigtrouser;
	TShirts tshirts;

	// װ�ι���
	std::cout << "��һ��װ��: " << std::endl;
	tshirts.Decorate(&xc);
	bigtrouser.Decorate(&tshirts);
	sneaker.Decorate(&bigtrouser);

	sneaker.Show();

	std::cout << std::endl;

	cout << "�ڶ���װ��: " << endl;
	Tie tie;
	Suit suit;
	suit.Decorate(&xc);
	tie.Decorate(&suit);
	
	tie.Show();

	return 0;
}