#include "Finery.h"
using namespace std;

int main(){

	Person xc("小菜");

	Sneaker sneaker;
	BigTrouser bigtrouser;
	TShirts tshirts;

	// 装饰过程
	std::cout << "第一种装扮: " << std::endl;
	tshirts.Decorate(&xc);
	bigtrouser.Decorate(&tshirts);
	sneaker.Decorate(&bigtrouser);

	sneaker.Show();

	std::cout << std::endl;

	cout << "第二种装扮: " << endl;
	Tie tie;
	Suit suit;
	suit.Decorate(&xc);
	tie.Decorate(&suit);
	
	tie.Show();

	return 0;
}