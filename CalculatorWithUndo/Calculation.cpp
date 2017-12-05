#include "stdafx.h"
#include "Calculation.h"
#include "Memento.h"
#include <regex>
#include <string>
#include <sstream>


Calculation::Calculation()
{
	value = leftHand = rightHand = 0.0;
	decimalPt = false;
	lastOp = mathOps::none;
	lastCom = lastCommand::equa;
	operations = 0;
	
}

double Calculation::add() {
	return operationLogic(mathOps::addition);
}

double Calculation::sub() {
	return operationLogic(mathOps::subtraction);
}

double Calculation::mul() {
	return operationLogic(mathOps::multiplicaton);
}

double Calculation::div() {
	return operationLogic(mathOps::division);
}

double Calculation::decimal() {
	switch (lastCom) {
	case lastCommand::equa:
	case lastCommand::oper:
		digit(0);
		decimalPt = true;
		powerOfTen = 1;
		return rightHand;
		break;

	case lastCommand::digi:
		if (!decimalPt) {
			decimalPt = true;
			return rightHand;
		}
		break;
	}
}

double Calculation::equal() {
	decimalPt = false;
	/*switch (lastCom) {
	case lastCommand::digi:
		pushMemento();
		value = doOperation();
		leftHand = value;
		lastCom = lastCommand::equa;
		
		break;
	case lastCommand::oper:
		pushMemento();
		value = doOperation();
		rightHand = value;
		lastCom = lastCommand::equa;
		
		break;
	case lastCommand::equa:*/
		pushMemento();
		value = doOperation();
		leftHand = value;
		lastCom = lastCommand::equa;
		
		//break;
	//}
		powerOfTen = 1;
	return value;
}

double Calculation::digit(const char d) {
	switch (lastCom) {
	case lastCommand::digi:
		if (decimalPt) {
			double append = d;
			for (int i = 0; i < powerOfTen; ++i) {
				append /= 10;
			}
			rightHand += append;
			++powerOfTen;
		}
		else {
			rightHand *= 10;
			rightHand += d;
		}
		lastCom = lastCommand::digi;
		break;
	case lastCommand::oper:
		if (decimalPt) {
			double append = d;
			rightHand = append / 10;
			powerOfTen = 1;
		}
		else {
			rightHand = d;
		}
		lastCom = lastCommand::digi;
		
		break;
	case lastCommand::equa:
		if (decimalPt) {
			double append = d;
			rightHand = (append / 10);
			powerOfTen = 1;
		}
		else {
			rightHand = d;
		}
		lastOp = mathOps::none;
		value = leftHand = 0;
		lastCom = lastCommand::digi;
		
		break;
	}
	
	return rightHand;
}

double Calculation::undo() {
	if (undoList.size() > 0) {
		rightHand = leftHand = value = *(undoList.top()->getData());
		--operations;
		powerOfTen = 1;
		lastOp = mathOps::none;
		undoList.pop();
		return value;
	}
	else { return 0.0; }
}

double Calculation::clear() {
	while (undoList.size() > 0) {
		undoList.pop();
	}
	operations = 0;
	powerOfTen = 1;
	leftHand = rightHand = value = 0.0;
	decimalPt = false;
	return value;
}

/*bool Calculation::checkForDecimal() {
	string str = to_string(value);
	if (regex_match(str.c_str(), regex("[.]"))) {
		return true;
	}
	else {
		return false;
	}
}*/

double Calculation::operationLogic(mathOps oper) {
	decimalPt = false;
	switch (lastCom) {
	case lastCommand::digi:
		pushMemento();
		value = doOperation();
		lastOp = oper;
		lastCom = lastCommand::oper;
		leftHand = value;
		break;
	case lastCommand::oper:
		lastOp = oper;
		lastCom = lastCommand::oper;
		value = rightHand;
		break;
	case lastCommand::equa:
		rightHand = leftHand = value;
		lastCom = lastCommand::oper;
		lastOp = oper;
		break;
	}
	powerOfTen = 1;
	return value;
}

double Calculation::doOperation() {
	switch (lastOp) {
	case mathOps::addition:
		return leftHand + rightHand;
		break;
	case mathOps::subtraction:
		return leftHand - rightHand;
		break;
	case mathOps::multiplicaton:
		return leftHand * rightHand;
		break;
	case mathOps::division:
		return leftHand / rightHand;
		break;
	case mathOps::none:
		return rightHand;
	default:
		return NULL;
	}
}

void Calculation::pushMemento() {
	++operations;
	undoList.push(new Memento<double>(value));
}

double Calculation::getValue() {
	return value;
}

int Calculation::getOperations() {
	return operations;
}

Calculation::~Calculation()
{
}
