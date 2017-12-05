#pragma once

#include <stack>
#include <list>
#include "Memento.h"

using namespace std;



class Calculation
{
public:
	

	Calculation();
	~Calculation();
	double add();
	double sub();
	double mul();
	double div();
	double decimal();
	double equal();
	double digit(const char d);
	double undo();
	double clear();
	double getValue();
	int getOperations();
private:
	enum class mathOps : short {
		addition,
		subtraction,
		multiplicaton,
		division,
		none

	};

	enum class lastCommand : short {
		digi,
		oper,
		equa
	};

	//bool checkForDecimal();
	double doOperation();
	double operationLogic(mathOps oper);
	void pushMemento();
	int operations = 0;
	double value;
	double leftHand;
	double rightHand;
	stack<Memento<double>*, list<Memento<double>*>> undoList;
	mathOps lastOp;
	lastCommand lastCom;
	bool decimalPt;
	int powerOfTen = 1;
	
	
};

