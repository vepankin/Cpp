#pragma once

enum class operation { OPERATION_PLUS, OPERATION_MINUS, OPERATION_MULTIPLY, OPERATION_DIVIDE, OPERATION_PARENTHESIS, OPERATION_BACK_PARENTHESIS, OPERATION_EMPTY, OPERATION_VALUE};

enum compareResult { GT/*>*/, LT/*<*/, EQ/*==*/, NE/*!=*/ };

compareResult CompareOperPriority(operation const &op1, operation const &op2);
