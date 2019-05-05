#pragma once
#include <string>
#include "CashSuper.h"

// ����ģʽ
// ��Ҫ�ڿͻ����жϴ�������
class CashContext{
public:
	CashContext(CashSuper *csuper) // ͨ�����캯��������������ָ��
		:cs(csuper){}

	double GetResult(double money){
		return cs->acceptCash(money);
	}

private:
	CashSuper *cs;
};

// ����ģʽ + ����ģʽ
// �Ѵ��۲����ж����빤��������Ҫ�ڿͻ����жϴ�������
class CashContextFactory{
public:
	CashContextFactory(std::string type){ // ���������ǲ��Զ���ָ��
		if(type=="�����շ�")
			cs=new CashNormal;
		else if(type=="��8��") // �������롰��8�ۡ�������Ϊ��'{': no matching token found��
			// ���������ĳɡ�Chinese Simplified(GB2312)-Codepage 936��
			cs=new CashRebate(0.8);
		else if(type=="��300��100")
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


// ������
// ���ֻ���ù���ģʽ���ͻ�����Ҫ�Ӵ�CashSuper��CashFactory�ࣻ
// ���ò���ģʽ+����ģʽ���ͻ���ֻ��Ҫ�Ӵ�CashContext�࣬��϶ȸ��͡�