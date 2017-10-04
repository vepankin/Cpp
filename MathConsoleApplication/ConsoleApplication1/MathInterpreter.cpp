// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>
#include <cstring>
#include <iostream>
#include <cstdio>
#include "operations.h" // enum "operation" declared
#include "mathtree.h" // the main class with the binary tree

using namespace std;

int main()
{	
	char ch; 
	string strTheSum;
	
	cout << "Type the sum: "; 
	getline(cin, strTheSum); // get the string 
		
	MathTree *root = NULL, TheTree(strTheSum), *leaf(new MathTree(strTheSum));
	
	//operation op1 = operation::OPERATION_MULTIPLY, op2 = operation::OPERATION_PLUS, op3 = operation::OPERATION_DIVIDE;
	//cout << "op1 ? op2 = " << (op1 >= op2)  << ". op2 ? op3 = " << (op2 >= op3);

	//cout << strTheSum.find_first_of("+-*/(");

	//delete (MathTree *)NULL;
		
	cout << endl << "Root=" << TheTree.IsRoot() << ". Math=" << TheTree.strMath << endl;
		
	TheTree.BuildTree();
	root = TheTree.GetRoot();

	cout << endl << "Root=" << root->IsRoot() << ". Math=" << root->strMath << endl;

	TheTree.destroyTree(); // delete all nodes except this one

	//---
	delete leaf;
	leaf = NULL;
	//leaf->release();			// OK
	// TheTree.release();		// WRONG !!!
	// (&TheTree)->release();	// WRONG !!!
	// root->release();			// WRONG !!!

	cout << endl << "Press any key to exit" << endl;
	ch = _getch(); // wait for a keypress

    //printf("Hello, world!\n");
    //printf(pStr);
    //printf("Enter a string: ");
    //gets_s(str);
    //printf("Hehe's your string: %s\n",str.front);

	//std::getchar();
	//std::cin.clear();
	//std::cin.get();

    return 0;
}

