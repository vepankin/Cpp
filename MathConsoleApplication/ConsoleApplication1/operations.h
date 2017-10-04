#pragma once

// typedef enum  {OPERATION_PLUS, OPERATION_MINUS, OPERATION_MULTIPLY, OPERATION_DIVIDE, OPERATION_PARENTHESIS, OPERATION_EMPTY} operation;

enum class operation { OPERATION_PLUS, OPERATION_MINUS, OPERATION_MULTIPLY, OPERATION_DIVIDE, OPERATION_PARENTHESIS, OPERATION_EMPTY };


inline bool operator== (const operation lhs, const operation rhs) {

	bool result;

	switch (lhs) {
	case operation::OPERATION_MULTIPLY:
	case operation::OPERATION_DIVIDE:
		result = ( ((int)rhs == (int)operation::OPERATION_MULTIPLY) || ( (int)rhs == (int)operation::OPERATION_MULTIPLY) );
		break;
	case operation::OPERATION_PLUS:
	case operation::OPERATION_MINUS:
		result = (((int)rhs == (int)operation::OPERATION_PLUS) || ((int)rhs == (int)operation::OPERATION_MINUS));
		break;
	default:
		result = ( (int)rhs == (int)lhs );
	}
	
	return result;
};

inline bool operator!= (const operation lhs, const operation rhs) {

	return !(lhs==rhs);
};


inline bool operator< (const operation lhs, const operation rhs) {

	bool result;

	switch (lhs) {
	case operation::OPERATION_PLUS:
	case operation::OPERATION_MINUS:
		result = (((int)rhs == (int)operation::OPERATION_MULTIPLY) || ((int)rhs == (int)operation::OPERATION_DIVIDE));
		break;
	default:
		result = false;
	}

	return result;

};

inline bool operator<= (const operation lhs, const operation rhs) {
	return ((lhs<rhs) || (lhs==rhs));
};

inline bool operator> (const operation lhs, const operation rhs) {
	bool result;

	switch (lhs) {
	case operation::OPERATION_MULTIPLY:
	case operation::OPERATION_DIVIDE:
		result = (((int)rhs == (int)operation::OPERATION_PLUS) || ((int)rhs == (int)operation::OPERATION_MINUS));
		break;
	default:
		result = false;
	}

	return result;
};

inline bool operator>= (const operation lhs, const operation rhs) {
	return ((lhs>rhs) || (lhs == rhs));
};