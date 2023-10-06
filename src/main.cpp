#include <iostream>
#include <sstream>
#include "AVL.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
    AVL tree;   // Create a Tree object
    string numCommands;
    cin >> numCommands;
    tree.insert(tree.head, "Bratt pls", 11111111);
    cout << numCommands;
    cout << tree.head;
	return 0;
}

