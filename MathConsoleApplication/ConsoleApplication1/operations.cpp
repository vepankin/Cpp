#include "stdafx.h"
#include "operations.h"

// returns true if op2
compareResult CompareOperPriority(operation const& op1, operation const& op2) {

	compareResult result;

	switch (op1)
	{
	//---------------------------------
	case operation::OPERATION_PLUS:
	case operation::OPERATION_MINUS:
		switch (op2) 
		{
		case operation::OPERATION_PLUS:
		case operation::OPERATION_MINUS:
			result = EQ;
			break;

		case operation::OPERATION_MULTIPLY:
		case operation::OPERATION_DIVIDE:
			result = LT;
			break;

		} 
		break;
	//---------------------------------
	case operation::OPERATION_MULTIPLY:
	case operation::OPERATION_DIVIDE:
		switch (op2)
		{
		case operation::OPERATION_PLUS:
		case operation::OPERATION_MINUS:
			result = GT;
			break;

		case operation::OPERATION_MULTIPLY:
		case operation::OPERATION_DIVIDE:
			result = EQ;
			break;

		}
		break;
	//---------------------------------
	default:
		if (op1 == op2) 
			result = EQ; 
		else
			result = NE;
		break;
	}

	return result;
}