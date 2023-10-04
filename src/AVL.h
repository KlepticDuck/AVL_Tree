#pragma once
#include "avl_node.h"
#include <vector>
using namespace std;

class AVL {

private:
    node* root = nullptr;
    vector<int> ufid_storage;
    int height = 0;

    //AVL Operations
    void leftRotate(student_node* node);
    void rightRotate(student_node* node);
    void balance();

public:
    //Constructor/Destructor
    AVL(){};
    ~AVL(){};

    //Project Functionalities
    void insertStudent(string name, int id);
    void removeUFID(int id);
    void searchUFID(int id);
    void searchName(string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    int getLevels();
    void removeInorder(int nth);
};


