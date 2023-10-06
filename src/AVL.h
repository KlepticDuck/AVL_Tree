#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class AVL {

public:

    class Node{

    public:
        //Student data
        string name;
        int UFID = 0;

        //Node data
        Node* left = nullptr;
        Node* right = nullptr;
        int nodeHeight = 1;
        int balanceFactor = 0;

        //Constructor & Destructor
        Node(string name, int UFID, int level){
            this->name = name;
            this->UFID = UFID;
            nodeHeight = level;
        };
        ~Node(){};
    };

    Node* head = nullptr;
    int height = 0;
    int balanceThreshold = 1;

    //Constructor/Destructor
    AVL(){};
    ~AVL(){};

    //Project Functionalities
    Node* insert(Node* root, string name, int ID, int level = 0);
    void remove(int ID);
    Node* removeHelper(Node* node_to_remove, int &direction);
    Node* search(int ID, Node* root, int &direction, bool print = true, bool found = false);
    void search(string name, Node* root, bool found = false);
    void printInorder(Node* root, int& target, int &count, int& foundID, bool print = true);
    void printPreorder(Node* root);
    void printPostorder(Node* root);
    void printLevelCount();
    void removeInorder(int nth);
    void updateBalanceFactor(Node* root);
    int getMaxHeight(Node* root);
    Node* searchTransversal(int &ID, Node* root, bool &found, Node* found_root, int &direction, bool &print);
    void searchTransversal(string &name, Node* root, bool &found);
    Node* getSuccessor(Node* , int &currentMin);
private:

//AVL Operations
Node* leftRotate(Node* root);
Node* rightRotate(Node* root);
void balance();
};


