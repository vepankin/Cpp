// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.

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
		
	MathTree TheTree(strTheSum);
	TheTree.BuildTree();
		
	std::cout.precision(10); // sets the precision 

	if (TheTree.Calculate())
		cout << "The result: " << TheTree.GetResult(); 
	else
		cout << "The result: N/A.";

	cout << endl << "----------------------------------------------" << endl;
	TheTree.PrintNodes(); // print the tree
	
	TheTree.destroyTree(); // delete all nodes except this one

	cout << endl << "Press any key to exit" << endl;
	ch = _getch(); // wait for a keypress
	
    return 0;
}

