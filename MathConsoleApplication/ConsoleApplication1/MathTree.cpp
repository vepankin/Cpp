#include "stdafx.h"
#include "MathTree.h"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <iostream>
#include <cstdio>
#include <cctype>



void MathTree::SetDefaultValues(std::string _strSum, bool _bNegative)
{
	LeftPart = NULL;
	RightPart = NULL;
	Parent = NULL;
	nodeOperation = operation::OPERATION_EMPTY;
	strMath = _strSum;
	bEmptyValue = true;
	bNegative = _bNegative;
	absValue = 0;
}


void MathTree::destroyTree() {

	MathTree * root = NULL;

	// cut the connection to the ancestor for the "this" node should'nt be deleted from the root
	if (Parent != nullptr)
		Parent->LeftPart == this ? Parent->LeftPart = NULL : Parent->RightPart = NULL;
		
	// delete the root node
	root = GetRoot();
	if (this != root) delete root;
	
	// delete descendants 
	delete LeftPart;
	LeftPart = NULL;
	
	delete RightPart;
	RightPart = NULL;
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
	case ')':
		result = operation::OPERATION_BACK_PARENTHESIS;
		break;
	default:
		result = operation::OPERATION_EMPTY;
	}

	return result;
}


operation MathTree::GetPreviousOperation(MathTree * const pNode)
{
	operation result = operation::OPERATION_EMPTY;
	
	if((pNode!=nullptr)&&(pNode->Parent!=nullptr))
		result = pNode->Parent->nodeOperation;
	
	return result;
}

bool MathTree::GetSignAndDeletePlusesAndMinuses(std::string & _str)
{
	bool result = false;
	int pos = 0;

	for (int i = 0; (i < _str.length()); i++)
		if ((_str[i] == '+') || (_str[i] == '-')){
			pos++;
			if (_str[i] == '-') result = !result; // negotiation 
		}
		else
			break;

	_str = _str.substr(pos); // return the sum without prefixes of '+' and '-'
	
	return result;
}

MathTree * MathTree::GetParenthesesNode()
{
	MathTree * ParenthesesNode = this;

	// go up the tree until the Parentheses node is found or the topmost node is reached
	while ((ParenthesesNode->nodeOperation != operation::OPERATION_PARENTHESIS) && (ParenthesesNode->Parent != nullptr))
		ParenthesesNode = ParenthesesNode->Parent;
	
	return ParenthesesNode;
}

std::string MathTree::OperationToString(operation _oper)
{
	std::string result;

	switch (_oper) {
	case operation::OPERATION_PLUS:
		result = "+";
		break;
	case operation::OPERATION_MINUS:
		result = "-";
		break;
	case operation::OPERATION_MULTIPLY:
		result = "*";
		break;
	case operation::OPERATION_DIVIDE:
		result = "/";
		break;
	case operation::OPERATION_PARENTHESIS:
		result = "(";
		break;
	case operation::OPERATION_EMPTY:
		result = "[empty]";
		break;
	case operation::OPERATION_VALUE:
		result = "[Value]";
		break;
	default:
		result = "[unknown]";
		break;
	}
	
	return result;
}


std::string MathTree::GetParenthesesContent(std::string strToParse)
{
	std::string result{""}; //c++11 style ;)
	bool bfoundLastParenthesis = false;

	// the first char should be a '(' !!!
	if (strToParse[0] == '(') {

		int counter{0};

		for (int i = 0; (i < strToParse.length()) && (!bfoundLastParenthesis); i++) {
			switch (strToParse[i])
			{
			case '(':
				counter++;
				break;
			case ')':
				counter--;
				break;

			default:
				break;
			}
			
			if (counter == 0) {
				bfoundLastParenthesis = true;

				result = strToParse.substr(0, i + 1);  
			}
		}

	}

	if (!bfoundLastParenthesis) {
		// ERROR in the strToParse - the last ')' wasn't foound
		// TO DO - return an error message...
	}

	return result; // returns the sum substring in parentheses
}


MathTree::MathTree(std::string _strSum, bool _bNegative)
{
	SetDefaultValues(_strSum, _bNegative); // initialization
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
	bool IsNegative; // a local boolean of the sign

	// Here we should get rid of Minuses and Pluses before the sum
	IsNegative = GetSignAndDeletePlusesAndMinuses(strMath);

	if (strMath[0] == '(') {
		
		//-----------------------------------------------------------------------
		// если это "pure" скобки - вся часть примера обрамлена скобками - 
		// раскрыть скобки и передать в LeftPart, текущую операцию установить в значение
		// OPERATION_PARENTHESIS
		//-----------------------------------------------------------------------

		std::string strParenthesContent = GetParenthesesContent(strMath);

		if (strMath == strParenthesContent) {
			// this is "PURE Parentheses Sum"
			
			// if the whole Sum is in the parentheses
			nodeOperation = operation::OPERATION_PARENTHESIS;
			bNegative = (bNegative || IsNegative); // the sign before the Parentheses
						
			std::string strContentWithoutParentheses = strParenthesContent.substr(1, strParenthesContent.length()-2);
			LeftPart = new MathTree(strContentWithoutParentheses); // a node with the uncovered parentheses
			LeftPart->Parent = this;
			LeftPart->Split();

		}
		else {
			// not a "PURE Parentheses Sum".
			// the fist symbol after the parentheses is an operation
			std::string strAfterParentheses = strMath.substr(strParenthesContent.length());
			foundOp = strAfterParentheses.find_first_of("+-*/");
			
			if ( (foundOp != std::string::npos) && (foundOp == 0) ) {
			
				curOp = GetOperationFromChar(strAfterParentheses[foundOp]);
				prevOp = GetPreviousOperation(this); // получить предыдущую операцию - поиск вверх по дереву

				CompRes = CompareOperPriority(curOp, prevOp);

				// if the priority of the current operation is greater or equal to the previous operation do:
				if ((CompRes == GT) || (prevOp == operation::OPERATION_EMPTY) || (prevOp == operation::OPERATION_PARENTHESIS)) {
					// идём вниз

					std::string strLeft, strRight;

					nodeOperation = curOp; // current node operation

					strLeft = strParenthesContent; // the sum with the parentheses
					strRight = strAfterParentheses.substr(foundOp + 1);

					LeftPart = new MathTree(strLeft,IsNegative); // pass the sign that is before the parentheses
					LeftPart->nodeOperation = operation::OPERATION_PARENTHESIS; // assign the operation

					RightPart = new MathTree(strRight);

					LeftPart->Parent = this;
					RightPart->Parent = this;
					
					LeftPart->Split();
					RightPart->Split();

				}
				else {
					// одём вверх (до скобки, если есть, или до корня, при отсутствии скобок)
					// и переносим правую часть выше корня/корня-скобки

					MathTree * ParNode = GetParenthesesNode();

					if (ParNode->nodeOperation == operation::OPERATION_PARENTHESIS) {
						// it is a parentheses node

						std::string strLeft, strRight;

						nodeOperation = operation::OPERATION_VALUE; // current node operation

						strLeft = strParenthesContent; // the sum with the parentheses
						strRight = strAfterParentheses.substr(foundOp + 1);

						LeftPart = new MathTree(strLeft, IsNegative); // pass the sign of the left side
						LeftPart->Parent = this;
						LeftPart->nodeOperation = operation::OPERATION_PARENTHESIS; // assign the operation

						// insert a node right after the parentheses node into the left part
						MathTree * NewTopNode = new MathTree("..." + strRight);
						NewTopNode->nodeOperation = curOp;
						NewTopNode->LeftPart = ParNode->LeftPart;
						ParNode->LeftPart = NewTopNode;
						NewTopNode->Parent = ParNode;
						NewTopNode->LeftPart->Parent = NewTopNode;


						NewTopNode->RightPart = new MathTree(strRight);
						NewTopNode->RightPart->Parent = NewTopNode;

						LeftPart->Split();
						NewTopNode->RightPart->Split();

					}
					else
					{
						// this is a root node

						std::string strLeft, strRight;

						nodeOperation = operation::OPERATION_VALUE; // current node operation

						strLeft = strParenthesContent; // the sum with the parentheses
						strRight = strAfterParentheses.substr(foundOp + 1);

						LeftPart = new MathTree(strLeft, IsNegative); // pass the sign of the left side
						LeftPart->Parent = this;


						MathTree * NewTopNode = new MathTree("..." + strRight);
						NewTopNode->nodeOperation = curOp;
						NewTopNode->LeftPart = ParNode;
						ParNode->Parent = NewTopNode;

						NewTopNode->RightPart = new MathTree(strRight);
						NewTopNode->RightPart->Parent = NewTopNode;

						LeftPart->Split();
						NewTopNode->RightPart->Split();

					}


				}

			}
			else
			{
				// ERROR in Math!!!
				// an operation is expected
				// Report an error ...
			}


		} // end of "not a pure parentheses sum"
		
	}
	else 
	{ // the first char is not '('
		
		foundOp = strMath.find_first_of("+-*/()");
	
		if (foundOp != std::string::npos) {

			curOp = GetOperationFromChar(strMath[foundOp]);

			if ( (curOp == operation::OPERATION_PARENTHESIS) || (curOp == operation::OPERATION_BACK_PARENTHESIS) ) {
				// ERROR !!!
				// The first operation cannot be a PARENTHESIS (only if the first char is '('). 
				// What is worse - cannot be a back parenthesis ')'.
				// Report an error ...

			}
			else 
			{
				prevOp = GetPreviousOperation(this); // получить предыдущую операцию - поиск вверх по дереву

				CompRes = CompareOperPriority(curOp, prevOp);

				// if the priority of the current operation is greater or equal to the previous operation do:
				if ((CompRes == GT) || (prevOp == operation::OPERATION_EMPTY) || (prevOp == operation::OPERATION_PARENTHESIS)) {
					// going down the tree

					std::string strLeft, strRight;

					nodeOperation = curOp; // current node operation

					strLeft = strMath.substr(0, foundOp);
					strRight = strMath.substr(foundOp + 1);

					LeftPart = new MathTree(strLeft, IsNegative); // pass the sign of the left side
					RightPart = new MathTree(strRight);

					LeftPart->Parent = this;
					RightPart->Parent = this;

					LeftPart->Split();
					RightPart->Split();

				}
				else {
					// одём вверх (до скобки, если есть, или до корня, при отсутствии скобок)
					// и переносим правую часть выше корня/корня-скобки
					
					MathTree * ParNode = GetParenthesesNode();
					
					if (ParNode->nodeOperation == operation::OPERATION_PARENTHESIS) {
						// it is a parentheses node
						
						std::string strLeft, strRight;

						nodeOperation = operation::OPERATION_VALUE; // current node operation

						strLeft = strMath.substr(0, foundOp);
						strRight = strMath.substr(foundOp + 1);

						LeftPart = new MathTree(strLeft, IsNegative); // pass the sign of the left side
						LeftPart->Parent = this;

						// insert a node right after the parentheses node into the left part
						MathTree * NewTopNode = new MathTree("..." + strRight);
						NewTopNode->nodeOperation = curOp;
						NewTopNode->LeftPart = ParNode->LeftPart;
						ParNode->LeftPart = NewTopNode;
						NewTopNode->Parent = ParNode;
						NewTopNode->LeftPart->Parent = NewTopNode;
												

						NewTopNode->RightPart = new MathTree(strRight);
						NewTopNode->RightPart->Parent = NewTopNode;

						LeftPart->Split();
						NewTopNode->RightPart->Split();

					}
					else
					{
						// this is a root node

						std::string strLeft, strRight;

						nodeOperation = operation::OPERATION_VALUE; // current node operation

						strLeft = strMath.substr(0, foundOp);
						strRight = strMath.substr(foundOp + 1);

						LeftPart = new MathTree(strLeft, IsNegative); // pass the sign of the left side
						LeftPart->Parent = this;

						
						MathTree * NewTopNode = new MathTree("..."+strRight);
						NewTopNode->nodeOperation = curOp;
						NewTopNode->LeftPart = ParNode;
						ParNode->Parent = NewTopNode;

						NewTopNode->RightPart = new MathTree(strRight);
						NewTopNode->RightPart->Parent = NewTopNode;
						
						LeftPart->Split();
						NewTopNode->RightPart->Split();
											
					}
				}
				
				
			} // not a parenthesis operation == OK

		}
		else {
			// Не нашли символа операции...
			// ... it means this is the value string (or empty)
			if (strMath.length() == 0) {
				// report an ERROR ...
				// the Value is expected
			}
			else
			{
				// This 'strMath' is a value string
				bNegative = (bNegative || IsNegative); // set the sign (if it is a Left side - the sign has been set before)
				try
				{
					absValue = std::stod(strMath);
					bEmptyValue = false; // ОК
				}
				catch (const std::exception&)
				{
					// report an ERROR
					//std::cout << "ERROR";
				}
				

			}
		}


	} // the first char is not a '('

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
	// To start with - we should get rid of the spaces " ".

	//--------------------------------------------------------------------
	// TO DO :
	// there might be a situation when the string is wrong e.g.: "6 7 8". 
	// as for now it would be transformed to "678" by deleting the spaces.
	// It seems wrong...
	// That's why - the ERROR message should be shown before going ahead.
	// ...
	//--------------------------------------------------------------------


	//std::string::iterator it = std::remove(strMath.begin(), strMath.end(), ' '); // <algorithm>
	//strMath.erase(it, strMath.end()); // <algorithm>
		
	// remove not only spaces but olso tabs.
	// <cctype> is needed for "std::isspace"
	for (int i = (int)strMath.length() - 1; i >= 0; i--)
		if (std::isspace(strMath[i])) strMath.erase(i,1);
	
	
	// now we split ahead the sum and build the tree.
	Split();
}

void MathTree::PrintNodes(MathTree *pNode, std::string strLevel)
{
	
	if(pNode==nullptr)
		pNode = GetRoot();

	std::cout << "Level   " << strLevel << "   " << pNode->strMath << " Operation = " << OperationToString(pNode->nodeOperation) << ". Sign: "<< (pNode->bNegative ? "- . Value = " : "+ . Value = ") << pNode->absValue  << std::endl;
	
	
	if (pNode->LeftPart != nullptr) 
		PrintNodes(pNode->LeftPart, strLevel + "-1");
		
	if (pNode->RightPart != nullptr) 
		PrintNodes(pNode->RightPart, strLevel + "-2");

}

// Returns if the Root Node Value is Calculated
bool MathTree::Calculate()
{
	MathTree *pRoot = GetRoot();

	// if the value has not been set
	if (pRoot->bEmptyValue) {
		double result = pRoot->GetNodeValue(); // recursive call from the root 
	}
	
	return !(pRoot->bEmptyValue); // returns true if the Root has a value.
}

// returns the Value of the Root Node
double MathTree::GetResult()
{
	MathTree * pRoot = GetRoot();
	return pRoot->bNegative ? -(pRoot->absValue) : pRoot->absValue;
}

double MathTree::GetNodeValue()
{
	double leftValue, rightValue;

	if ((LeftPart == nullptr) && (RightPart == nullptr)) {

		try
		{
			absValue = std::stod(strMath); // TO DO: "123tyu457" transforms to 123. A string check should be added.
			bEmptyValue = false; // ОК
		}
		catch (const std::exception&)
		{
			// report an ERROR
			//std::cout << "ERROR";
		}

	}
	else if (LeftPart == nullptr) {
		absValue = RightPart->GetNodeValue();
		bEmptyValue = RightPart->bEmptyValue;
	}
	else if (RightPart == nullptr) {
		absValue = LeftPart->GetNodeValue();
		bEmptyValue = LeftPart->bEmptyValue;
	}
	else {
		// the node has an Operation
		leftValue = LeftPart->GetNodeValue();
		rightValue = RightPart->GetNodeValue();
		bEmptyValue = ((LeftPart->bEmptyValue) || (RightPart->bEmptyValue));

		if (!bEmptyValue) {

			switch (nodeOperation) {
			case operation::OPERATION_PLUS:
				absValue = leftValue + rightValue;
				break;
			case operation::OPERATION_MINUS:
				absValue = leftValue - rightValue;
				break;
			case operation::OPERATION_MULTIPLY:
				absValue = leftValue * rightValue;
				break;
			case operation::OPERATION_DIVIDE:
				if(rightValue!=0.0){
					absValue = leftValue / rightValue;
				}
				else 
				{
					// ERROR MESSAGE !!!
					// DIVISION BY ZERO!!!
				}
				
				break;
			default:
				// ERROR!!!
				// incompatible node operation !!!

				break;

			} // end switch

		}
				
	}
	
	return bNegative ? -absValue : absValue;
}