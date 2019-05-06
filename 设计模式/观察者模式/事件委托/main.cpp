#include "Observer.h"

int main(){
	Publisher boss, secrectary;

	GameObserver gamer2("小孔", &secrectary);
	StockObserver stoker2("小红", &secrectary);
	secrectary.Attach(&gamer2);
	secrectary.Attach(&stoker2);

	secrectary.Detach(&stoker2); // 小红没有被通知到，所以她被老板抓到了

	secrectary.Notify(); // 秘书通知小孔，老板来了

	GameObserver gamer("小李", &boss);
	StockObserver stoker("小明", &boss);
	boss.Attach(&gamer);
	boss.Attach(&gamer); // 小李被添加了两次
	boss.Attach(&stoker);

	boss.Notify(); // 小李和小明看见老板，关闭了当前界面，开始工作

	return 0;
}