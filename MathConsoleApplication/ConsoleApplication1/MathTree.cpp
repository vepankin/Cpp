#include "stdafx.h"
#include "MathTree.h"
#include <cstring>
#include <iostream>
#include <conio.h>
#include <iostream>
#include <cstdio>



void MathTree::SetDefaultValues(std::string _strSum)
{
	LeftPart = NULL;
	RightPart = NULL;
	Parent = NULL;
	nodeOperation = operation::OPERATION_EMPTY;
	strMath = _strSum;
	bEmptyValue = true;
	bNegative = false;
	absValue = 0;
}

void MathTree::release() {
	delete this;
}

void MathTree::destroyTree() {

	MathTree * root = NULL;

	// cut the connection to the ancestor for the "this" node should'nt be deleted from the root
	if (Parent != nullptr)
		Parent == LeftPart ? Parent->LeftPart = NULL : Parent->RightPart = NULL;
		
	// delete the root node
	root = GetRoot();
	if (this != root) delete root;
	
	// delete descendants 
	delete LeftPart;
	LeftPart = NULL;
	
	delete RightPart;
	RightPart = NULL;
}

bool MathTree::UncoverParentheses()
{
	bool result = true;
	std::size_t foundBegin, foundEnd, foundOp;

	foundBegin = strMath.find_first_of("(((");
	if (foundBegin != std::string::npos) {

		foundEnd = strMath.find_last_of(")))");
		if (foundEnd != std::string::npos) {

			std::string strLeft = strMath.substr(foundBegin + 1, foundEnd - foundBegin - 1);
			if (foundEnd == strMath.length() - 1) {
				// no operation ahead

			}
			else if (strMath.length() - 1 - foundEnd >= 2) {
				// ")" is followed by an operator and
			}
			else result = false; // there should be an operator and one or more digits

			std::string strRight = strMath.substr(foundEnd);
			

			std::cout << strLeft; // testing

		}
		else result = false; // no closing ")"
	};

	return result;
}

operation MathTree::GetOperationFromChar(char ch)
{
	operation result;

	// получить текущую операцию
	switch (ch) {
	case '+':
		result = operation::OPERATION_PLUS;
		break;
	case '-':
		result = operation::OPERATION_MINUS;
		break;
	case '*':
		result = operation::OPERATION_MULTIPLY;
		break;
	case '/':
		result = operation::OPERATION_DIVIDE;
		break;
	case '(':
		result = operation::OPERATION_PARENTHESIS;
		break;
	default:
		result = operation::OPERATION_EMPTY;
	}

	return result;
}

void MathTree::MakeNewRoot()
{
	//(*Root) = new MathTree("new root created", Root);
	//(*Root)->LeftPart = this;
}

operation MathTree::GetPreviousOperation(MathTree * const pNode)
{
	operation result = operation::OPERATION_EMPTY;
	//MathTree * pLocalNode = pNode;
	
	if((pNode!=nullptr)&&(pNode->Parent!=nullptr))
		result = pNode->Parent->nodeOperation;
	
	return result;
}


MathTree::MathTree(std::string _strSum)
{
	SetDefaultValues(_strSum); // initialization
}


MathTree::~MathTree()
{
	delete LeftPart;
	delete RightPart;
}


bool MathTree::IsRoot()
{
	return (GetRoot() == this);
}


void MathTree::Split()
{
	std::size_t foundOp;
	operation prevOp, curOp;
	compareResult CompRes; 

	MakeNewRoot();

	if (strMath[0] == '(') {
		bool bUP = UncoverParentheses();
		
		//-----------------------------------------------------------------------
		// если это "pure" скобки - вся часть примера обрамлена скобками - 
		// раскрыть скобки и передать в LeftPart, операцию установить в значение
		// OPERATION_PARENTHESIS
		//-----------------------------------------------------------------------

		// ...
	}
	else {
		//
		
		foundOp = strMath.find_first_of("+-*/(");
	
		if (foundOp != std::string::npos) {

			curOp = GetOperationFromChar(strMath[foundOp]);
			
			prevOp = GetPreviousOperation(this); // получить предыдущую операцию - поиск вверх по дереву

			CompRes = CompareOperPriority(curOp,prevOp); 

			if (prevOp != operation::OPERATION_PARENTHESIS) {
				//...
				// if the priority of the current operation is greater or equal to the previous operation do:
				if ( (CompRes == GT) || (CompRes == EQ) || (prevOp == operation::OPERATION_EMPTY) ) {
					// идём вниз

					std::string strLeft, strRight;
					
					nodeOperation = curOp; // current node operation

					strLeft = strMath.substr(0, foundOp);
					strRight = strMath.substr(foundOp+1);

					LeftPart = new MathTree(strLeft);
					RightPart = new MathTree(strRight);

					LeftPart->Parent = this;
					RightPart->Parent = this;

				}else{
					// одём вверх (до скобки, если есть, или до корня, при отсутствии скобок)
					// и переносим правую часть выше корня/корня-скобки

				};
			}

		}
		else {
			// Не нашли символа операции...
			// ... it means this is the value string (or empty)
		}


	};

}


MathTree * MathTree::GetRoot()
{
	MathTree *leaf = this;
			
	while (leaf->Parent != nullptr)
		leaf = leaf->Parent;

	return leaf; // the root
}


void MathTree::BuildTree() 
{
	Split();
}