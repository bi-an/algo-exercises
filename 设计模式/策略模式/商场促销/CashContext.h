#pragma once
#include <string>
#include "CashSuper.h"

// 策略模式
// 需要在客户端判断打折类型
class CashContext{
public:
	CashContext(CashSuper *csuper) // 通过构造函数，传入具体策略指针
		:cs(csuper){}

	double GetResult(double money){
		return cs->acceptCash(money);
	}

private:
	CashSuper *cs;
};

// 策略模式 + 工厂模式
// 把打折策略判断移入工厂，不需要在客户端判断打折类型
class CashContextFactory{
public:
	CashContextFactory(std::string type){ // 参数不再是策略对象指针
		if(type=="正常收费")
			cs=new CashNormal;
		else if(type=="打8折") // 中文乱码“打8折”，报错为“'{': no matching token found”
			// 解决：编码改成“Chinese Simplified(GB2312)-Codepage 936”
			cs=new CashRebate(0.8);
		else if(type=="满300减100")
			cs=new CashReturn(300,100);
		else
			;
	}

	double GetResult(double money){
		return cs->acceptCash(money);
	}

private:
	CashSuper *cs=nullptr;
};


// 点评：
// 如果只采用工厂模式：客户端需要接触CashSuper和CashFactory类；
// 采用策略模式+工厂模式：客户端只需要接触CashContext类，耦合度更低。