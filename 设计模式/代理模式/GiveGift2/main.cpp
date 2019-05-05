#include <iostream>
#include "GiveGift.h"
using namespace std;

int main(){
	SchoolGirl mm("½¿½¿");
	Pursuit gg(&mm);
	Proxy proxy(&gg);
	
	proxy.GiveDolls();
	proxy.GiveChocolate();
	proxy.GiveFlowers();


	return 0;
}