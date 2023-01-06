#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

class Node {

    public:
        int data;
        Node* leftBranch = nullptr;
        Node* rightBranch = nullptr;
        Node (int nodeValue) { data = nodeValue;}
        ~Node () { delete leftBranch; delete rightBranch;}

};

class BST {
    public:
        BST() {root = nullptr;}
        BST(Node* newRoot) {root = newRoot;}
        ~BST() {delete root;}
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();

    private:
        Node* root;
};

void BST::insertKey (int newKey) { 

    if (root == nullptr) { 
        root = new Node (newKey);
        return;
    }

    Node *currentRoot = root;
    Node *temporaryRoot = nullptr;

    while (currentRoot != nullptr) {

        temporaryRoot = currentRoot;

        if (currentRoot->data == newKey) {
            return;
        } else if (currentRoot->data < newKey) {
            currentRoot = currentRoot->rightBranch;
        } else if (currentRoot->data > newKey) {
            currentRoot = currentRoot->leftBranch;
        }

    }

    if (temporaryRoot->data < newKey) { //Actually creates the node
        temporaryRoot->rightBranch = new Node(newKey);
    } else if (temporaryRoot->data > newKey) {
        temporaryRoot->leftBranch = new Node(newKey);
    }

}

bool BST::hasKey (int searchKey) {

    Node* currentRoot = root;

    while (currentRoot != nullptr) {

        if (currentRoot->data == searchKey) {
            return true;
        } else if (currentRoot->data > searchKey) {
            currentRoot = currentRoot->leftBranch;
        } else if (currentRoot->data < searchKey) {
            currentRoot = currentRoot->rightBranch;
        }
    }

    return false;

}

std::vector<int> BST::inOrder () {
    
    std::vector<int> numbersList;
    std::stack<Node*> numbersStack;
    Node* currentRoot = root;

    if (root == nullptr) {return numbersList;}

    while (currentRoot != nullptr || !(numbersStack.size() == 0)) {

        if (currentRoot != nullptr) {
            numbersStack.push(currentRoot);
            currentRoot = currentRoot->leftBranch;
        } else {
            currentRoot = numbersStack.top();
            numbersStack.pop();
            numbersList.push_back(currentRoot->data);
            currentRoot = currentRoot->rightBranch;
        }
    }

    return numbersList;
}

int BST::getHeight () {

    Node* initialRoot = root;

    int leftBranchHeight;
    int rightBranchHeight;

    if (initialRoot == nullptr) {
        return 0;
    } 

    if (initialRoot != nullptr) {

        root = initialRoot->leftBranch;
        leftBranchHeight = getHeight();
        root = initialRoot->rightBranch;
        rightBranchHeight = getHeight();
        root = initialRoot;

    }

    return 1 + std::max(leftBranchHeight, rightBranchHeight);
}

int main () {

    BST binarySearchTree;

    int inputValue;
    int searchKey;
    std::string hasBeenFoundMessage;

    std::cout << "Enter the numbers to be stored (end with a letter): ";
    std::cin >> inputValue;

    while (!(std::cin.fail())) {
        binarySearchTree.insertKey(inputValue);
        std::cin >> inputValue;
    }

    std::cin.clear(); //I need to clear and ignore the input buffer to access the other input buffers, else, it runs the program automatically with junk in the search key
    std::cin.ignore();
    std::cout << "Which number do you want to look up? ";
    std::cin >> searchKey;

    bool hasKeyBeenFound = binarySearchTree.hasKey(searchKey);
    hasKeyBeenFound ? hasBeenFoundMessage = "yes" : hasBeenFoundMessage = "no";

    std::cout << searchKey << " is in the tree: " << hasBeenFoundMessage << std::endl;

    std::cout << "The numbers in sorted order: ";

    std::vector<int> sortedList = binarySearchTree.inOrder();

    for (int i = 0; i < sortedList.size(); i++) {
        std::cout << sortedList.at(i) << " ";
    }

    std::cout << std::endl;

    std::cout << "Height of the tree: " << binarySearchTree.getHeight() << std::endl;
  
    return 0;

}