#include <iostream>
#include <vector>
#include <deque>
#include "Song.h"
#pragma once
using namespace std;

const bool BLACK = true;
const bool RED = false;

int dateToInt(const string& date);

class NodeCountry {
  public:
    string country;
    vector<Song> top50Songs;
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

    void left_rotate(NodeCountry* x);
    void right_rotate(NodeCountry* x);
    void insertCountry(Song &song, string &country);
    void insert_fixup(NodeCountry* z);
    void searchCountry(string &country);
    void level_order(bool print_color = false);
};

class NodeDate {
  public:
    int date;
    RBtreeCountry Countries;
    bool color;
    NodeDate* parent;
    NodeDate* left;
    NodeDate* right;

    NodeDate(int date) {
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
    //int count = 0;

    RBtreeDates() {
      nullNode = new NodeDate(99999);
      nullNode->color = BLACK;
      nullNode->left = nullptr;
      nullNode->right = nullptr;
      root = nullNode;
    }

    void left_rotate(NodeDate* x);
    void right_rotate(NodeDate* x);
    void insertDate(Song &song, string &Sdate);
    void insert_fixup(NodeDate* z);
    void displayTopTen(string &Sdate, string &country);
    void level_order(bool print_color = false);
};
