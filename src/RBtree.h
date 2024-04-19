//all of this is my AVL tree code
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <regex>
#pragma once
using namespace std;

class TreeNode {
     public:
       string DATE;
       string COUNTRY;
       string orderedList = "";
       string substringOrdList = "";
       int inorderCount = 0;
       int height;
       TreeNode* left;
       TreeNode* right;
       TreeNode* root;

       int getHeight(TreeNode* root);
       int getBalanceFactor(TreeNode* a);

       TreeNode() : DATE(""), COUNTRY(""), height(1), left(nullptr), right(nullptr), root(nullptr) {}
       TreeNode(string& date, string& country) : DATE(date), COUNTRY(country), height(1), left(nullptr), right(nullptr), root(nullptr) {}

       void insert(string date, string country);
       TreeNode* insertHelper(TreeNode* root, string date, string country);

       TreeNode* rightRotation(TreeNode* a);
       TreeNode* leftRotation(TreeNode* c);

       void processInput(const string& line);

       void order(string& command);
       void preorderHelper(TreeNode* root);
       void inorderHelper(TreeNode* root);
       void postorderHelper(TreeNode* root);

       void access(string& command, string attribute, bool isValidUfid, bool isValidName);
       void searchIdHelper(TreeNode* root, string date);
       void searchNameHelper(TreeNode* root, string& searchName, bool& found);
       void removeId(string country);
       TreeNode* removeIdHelper(TreeNode* root, string country);
       TreeNode* findInorderSuccessor(TreeNode* root);

       void removeInorderNth(int Nth);
       void removeInorderNthHelper(TreeNode* root, int Nth, bool& found);
 };
        
