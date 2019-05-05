#include <iostream>
#include "GiveGift.h"
using namespace std;

int main(){
	SchoolGirl mm("½¿½¿");
	Proxy proxy(&mm);
	
	proxy.GiveDolls();
	proxy.GiveChocolate();
	proxy.GiveFlowers();


	return 0;
}