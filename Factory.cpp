#include <iostream>
#include <math.h>
#include <string>

class Operation
{
public:
	Operation(int A = 0, int B = 0) : m_operandA(A), m_operandB(B) {}
	void setOperandA(double num)
	{
		m_operandA = num;
	}
	void setOperandB(double num)
	{
		m_operandB = num;
	}
	virtual double getResult() = 0;

protected:
	int m_operandA;
	int m_operandB;
};

class OperationAdd
    : public Operation
{
public:
	double getResult() override
	{
		double result = 0.0;
		result = m_operandA + m_operandB;
		return result;
	}
};

class OperationSub : public Operation
{
public:
	double getResult() override
	{
		double result = 0.0;
		result = m_operandA - m_operandB;
		return result;
	}
};

class OperationMultiply : public Operation
{
public:
	double getResult() override
	{
		double result = 0.0;
		result = m_operandA * m_operandB;
		return result;
	}
};

class OperationDiv : public Operation
{
public:
	double getResult() override
	{
		if (0 == m_operandB)
		{
			std::cout << "error: num divided by ZERO" << std::endl;
			exit(1);
		}
		double result = 0.0;
		result = m_operandA / m_operandB;
		return result;
	}
};

class FactoryInterface
{
public:
	virtual Operation *CreateFactory() = 0;
	virtual ~FactoryInterface() = default;
};

class FactoryAdd : public FactoryInterface
{
public:
	virtual Operation *CreateFactory()
	{
		return new OperationAdd();
	}
};

class FactorySub : public FactoryInterface
{
public:
	virtual Operation *CreateFactory()
	{
		return new OperationSub();
	}
};

class FactoryMultiply : public FactoryInterface
{
public:
	virtual Operation *CreateFactory()
	{
		return new OperationMultiply();
	}
};

class FactoryDiv : public FactoryInterface
{
public:
	virtual Operation *CreateFactory()
	{
		return new OperationDiv();
	}
};

int main()
{
	FactoryInterface *operationFactory = new FactoryAdd();
	Operation *oper = operationFactory->CreateFactory();
	oper->setOperandA(1);
	oper->setOperandB(2);
	std::cout << "add(1,2): " << oper->getResult() << std::endl;
	delete operationFactory;
	operationFactory = nullptr;
	delete oper;
	oper = nullptr;
	return 0;
}