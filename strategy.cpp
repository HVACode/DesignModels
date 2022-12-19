#include <iostream>
#include <memory>
class CashSuper
{
public:
	virtual ~CashSuper() = default;
	virtual double acceptableCash(double money) = 0;
};
class CashNormal : public CashSuper
{
public:
	double acceptableCash(double money) override
	{
		return money;
	}
};

class CashRebate : public CashSuper
{
public:
	CashRebate(double disc) : m_discount(disc)
	{
	}
	double acceptableCash(double money) override
	{
		return money * m_discount;
	}

private:
	double m_discount;
};

class CashReturn : public CashSuper
{
public:
	CashReturn(double dCondition, double dReturn)
	    : m_condition(dCondition), m_return(dReturn)
	{
	}
	double acceptableCash(double money) override
	{
		double result = money;
		if (money >= m_condition)
		{
			result = money - (money / m_condition) * m_return;
		}
		return result;
	}

private:
	double m_condition;
	double m_return;
};

class CashContext
{
public:
	CashContext(std::string type);
	double GetResult(double money);
	~CashContext()
	{
		delete m_CashSuper;
		m_CashSuper = nullptr;
	}

private:
	CashSuper *m_CashSuper;
};

CashContext::CashContext(std::string type)
{
	if ("正常收费" == type)
	{
		m_CashSuper = new CashNormal();
	}
	else if ("满300返100" == type)
	{
		m_CashSuper = new CashReturn(300, 100);
	}
	else if ("打8折" == type)
	{
		m_CashSuper = new CashRebate(0.8);
	}
}
double CashContext::GetResult(double money)
{
	return m_CashSuper->acceptableCash(money);
}

int main()
{
	std::string strType;
	double dPrice = 0.0;
	int iNum = 0;

	double total = 0.0, totalPrice = 0.0;
	while (std::cin >> strType)
	{
		std::cin >> dPrice >> iNum;
		CashContext *pCC = new CashContext(strType);
		totalPrice = pCC->GetResult(dPrice * iNum);
		total += totalPrice;

		delete pCC;
		pCC = nullptr;
	}
	return 0;
}