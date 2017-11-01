#pragma once

#include "operations.h"
#include <string>


// the structure of the tree
class MathTree
{
	MathTree *LeftPart; // left part of the sum
	MathTree *RightPart; // right part of the sum
	MathTree *Parent; // pointer to the root node
	operation nodeOperation; // operation to be applied to the left and the right part
	bool bNegative; // true if tle value is negative
	double absValue; // the absolute value. let it be double.
	bool bEmptyValue; // represents the flag of an empty value (not set)
	std::string GetParenthesesContent(std::string _str);
	std::string strMath;  // a string representing the sum to be calculated

	MathTree * GetRoot();
	MathTree * GetParenthesesNode(); // go up the tree and get the node ptr (if no parentheses node exists, returns the most upper node - the root)
	bool IsRoot(); // returns "true" if it's a root node

	void SetDefaultValues(std::string, bool);
	operation GetOperationFromChar(char ch);
	operation GetPreviousOperation(MathTree * const pNode);
	
	bool GetSignAndDeletePlusesAndMinuses(std::string &_str); // _str will be left trimed from '+' and '-'
	std::string OperationToString(operation _oper);

	double GetNodeValue();
	void Split();
	
public:

	MathTree(std::string = "", bool = false);
	~MathTree();

	// functions for releasing the memory
	void destroyTree();		// delete all nodes except "this"
	
	void BuildTree();
	void PrintNodes(MathTree* = nullptr, std::string = "0");
	bool Calculate(); // calculate the value in the Root Node
	double GetResult(); // returns the value of the Root Node
};

