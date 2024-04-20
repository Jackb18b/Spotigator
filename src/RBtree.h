#include <iostream>
#include <iomanip>
#include <sstream>
//#include <cstring>
//#include <algorithm>
#include <vector>
//#include <regex>
#include <deque>
#include "Song.h"
#pragma once
using namespace std;
class Song;

double dateToInt(string& date);

const bool BLACK = true;
const bool RED = false;

class RBtree;

class Node {
  public:
    double date;
    string country;
    Node* parent;
    bool color;
    Node* left;
    Node* right;
    RBtree* Countries;

    Node(double date) : 
    date(date), 
    parent(nullptr), 
    color(RED), 
    left(nullptr), 
    right(nullptr),
    Countries(nullptr) 
    {}


    Node(string country) : 
    country(country), 
    parent(nullptr), 
    color(RED), 
    left(nullptr), 
    right(nullptr) {}

    string print_color();
    
};

class RBtree {
  public:
    Node* nullNode;
    Node* root;
    bool isCountryTree = false;

    RBtree() {
      nullNode = new Node(99999);
      nullNode->color = BLACK;
      nullNode->left = nullptr;
      nullNode->right = nullptr;
      root = nullNode;
    }

    RBtree(bool isCountryTree) {
    this->isCountryTree = isCountryTree;
    nullNode = new Node("ZZZZ");
    nullNode->color = BLACK;
    nullNode->left = nullptr;
    nullNode->right = nullptr;
    root = nullNode;
    }

    void songDecomposer(Song Song);
    void left_rotate(Node* x);
    void right_rotate(Node* x);
    void insertDate(Song &song, double date);
    void insertCountry(Song &song, string country);
    void insertSongName(Song &song, string songName);
    void insert_fixup(Node* z);
    Node* search(double date);
    void level_order(bool print_color = false);
};

// class TreeNode {
//      public:
//        string DATE;
//        string COUNTRY;
//        string orderedList = "";
//        string substringOrdList = "";
//        int inorderCount = 0;
//        int height;
//        TreeNode* left;
//        TreeNode* right;
//        TreeNode* root;

//        int getHeight(TreeNode* root);
//        int getBalanceFactor(TreeNode* a);

//        TreeNode() : DATE(""), COUNTRY(""), height(1), left(nullptr), right(nullptr), root(nullptr) {}
//        TreeNode(string& date, string& country) : DATE(date), COUNTRY(country), height(1), left(nullptr), right(nullptr), root(nullptr) {}

//        void insert(string date, string country);
//        TreeNode* insertHelper(TreeNode* root, string date, string country);

//        TreeNode* rightRotation(TreeNode* a);
//        TreeNode* leftRotation(TreeNode* c);

//        void processInput(const string& line);

//        void order(string& command);
//        void preorderHelper(TreeNode* root);
//        void inorderHelper(TreeNode* root);
//        void postorderHelper(TreeNode* root);

//        void access(string& command, string attribute, bool isValidUfid, bool isValidName);
//        void searchIdHelper(TreeNode* root, string date);
//        void searchNameHelper(TreeNode* root, string& searchName, bool& found);
//        //void removeId(string country);
//        //TreeNode* removeIdHelper(TreeNode* root, string country);
//        //TreeNode* findInorderSuccessor(TreeNode* root);

//        //void removeInorderNth(int Nth);
//        //void removeInorderNthHelper(TreeNode* root, int Nth, bool& found);
//  };
        
