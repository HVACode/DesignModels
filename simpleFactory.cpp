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
	virtual double getResult()
	{
		double result = 0.0;
		return result;
	}

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

class OperationOrder
    : public Operation
{
public:
	double getResult() override
	{
		double result = 0;
		result = pow(m_operandA, m_operandB);
		return result;
	}
};

class OperationFactory
{
public:
	Operation *createOperation(std::string operate)
	{
		Operation *oper = nullptr;
		if (operate == "+")
		{
			oper = new OperationAdd();
		}
		if (operate == "-")
		{
			oper = new OperationSub();
		}
		if (operate == "*")
		{
			oper = new OperationMultiply();
		}
		if (operate == "/")
		{
			oper = new OperationDiv();
		}

		return oper;
	}
};

int main()
{
	OperationFactory factory;
	Operation *oper = factory.createOperation("+");
	oper->setOperandA(1);
	oper->setOperandB(2);
	std::cout << "add(1,2): " << oper->getResult() << std::endl;
	delete oper;
	oper = nullptr;
	return 0;
}