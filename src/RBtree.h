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


double dateToInt(string& date);

const bool BLACK = true;
const bool RED = false;

class NodeCountry {
  public:
    string country;
    vector<string> top50Songs;
    bool color;
    NodeCountry* parent;
    NodeCountry* left;
    NodeCountry* right;

    NodeCountry(string country) {
    this->country = country;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
    }

    string print_color();
};

class RBtreeCountry {
  public:
    NodeCountry* nullNode;
    NodeCountry* root;

    RBtreeCountry() {
      nullNode = new NodeCountry("ZZZZZ");
      nullNode->color = BLACK;
      nullNode->left = nullptr;
      nullNode->right = nullptr;
      root = nullNode;
    }

    void songDecomposer(Song Song);
    void left_rotate(NodeCountry* x);
    void right_rotate(NodeCountry* x);
    void insertCountry(Song &song, string country);
    void insertSongName(Song &song, string songName);
    void insert_fixup(NodeCountry* z);
    NodeCountry* search(string country);
    void level_order(bool print_color = false);
};

class NodeDate {
  public:
    double date;
    RBtreeCountry Countries;
    bool color;
    NodeDate* parent;
    NodeDate* left;
    NodeDate* right;

    NodeDate(double date) {
      this->date = date;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      color = RED;
    }

    string print_color();
};

class RBtreeDates {
  public:
    NodeDate* nullNode;
    NodeDate* root;
    bool isCountryTree = false;

    RBtreeDates() {
      nullNode = new NodeDate(99999);
      nullNode->color = BLACK;
      nullNode->left = nullptr;
      nullNode->right = nullptr;
      root = nullNode;
    }

    void songDecomposer(Song Song);
    void left_rotate(NodeDate* x);
    void right_rotate(NodeDate* x);
    void insertDate(Song &song, string Sdate);
    void insert_fixup(NodeDate* z);
    NodeDate* search(string Sdate);
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
        
