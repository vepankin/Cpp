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
	
	void SetDefaultValues(std::string);
	bool UncoverParentheses();
	operation GetOperationFromChar(char ch);
	
	void MakeNewRoot();

	operation GetPreviousOperation(MathTree * const pNode);

public:
	std::string strMath;  // a string representing the sum to be calculated

	MathTree(std::string="");
	~MathTree();

	// functions for releasing the memory
	void release();			// delete this
	void destroyTree();		// delete all nodes except "this"


	bool IsRoot(); // returns "true" if it's a root node
	void Split();
	MathTree * GetRoot();
	void BuildTree();
};
