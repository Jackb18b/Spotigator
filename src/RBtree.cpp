#include "RBtree.h"

using namespace std;


int dateToInt(const string &date)
{
    int intDate = 0;
    string monthDay = "";
    if (date.length() != 10)
    {
        //std::cout << "Invalid Date & time\t";
        //std::cout << date << "\n";
        return intDate;
    }

    monthDay += date.substr(5,2);
    monthDay += date.substr(8,2);

    intDate = stoi(monthDay);
    if (date[3] == '4') {
        intDate+= 24000; // to differentiate between 2024 dates and 2023. This means 2023 dates will be 3 digits always
     }
    return intDate;
}

string NodeCountry::print_color(){
    if (color == BLACK) return "(b)";
      return "(r)";
}
string NodeDate::print_color(){
    if (color == BLACK) return "(b)";
      return "(r)";
}

void RBtreeCountry::left_rotate(NodeCountry* x) {
      NodeCountry* y = x->right;
      x->right = y->left;

      if (y->left != nullNode) {
        y->left->parent = x; 
      }
      
      y->parent = x->parent;

      if (x->parent == nullptr) {
        root = y;
      } else if (x == x->parent->left){
        x->parent->left = y;
      } else 
        x->parent->right = y;

      y->left = x;
      x->parent = y;
    }
void RBtreeDates::left_rotate(NodeDate* x) {
      NodeDate* y = x->right;
      x->right = y->left;

      if (y->left != nullNode) {
        y->left->parent = x; 
      }
      
      y->parent = x->parent;

      if (x->parent == nullptr) {
        root = y;
      } else if (x == x->parent->left){
        x->parent->left = y;
      } else 
        x->parent->right = y;

      y->left = x;
      x->parent = y;
    }

void RBtreeCountry::right_rotate(NodeCountry* x) {
      NodeCountry* y = x->left;
      x->left = y->right;

      if (y->right != nullNode){
        y->right->parent = x;
      }

      y->parent = x->parent;

      if (x->parent == nullptr){
        root = y;
      } else if (x == x->parent->right) {
        x->parent->right = y;
      } else 
        x->parent->left = y;

      y->right = x;
      x->parent = y;
    }
void RBtreeDates::right_rotate(NodeDate* x) {
      NodeDate* y = x->left;
      x->left = y->right;

      if (y->right != nullNode){
        y->right->parent = x;
      }

      y->parent = x->parent;

      if (x->parent == nullptr){
        root = y;
      } else if (x == x->parent->right) {
        x->parent->right = y;
      } else 
        x->parent->left = y;

      y->right = x;
      x->parent = y;
    }

void RBtreeCountry::insertCountry(Song &song, string &country) {
      NodeCountry* z = new NodeCountry(country);
      z->left = nullNode;
      z->right = nullNode;

      NodeCountry* y = nullptr;
      NodeCountry* x = root;

      while (x != nullNode) {
        if (z->country == x->country) {
            x->top50Songs.push_back(song);
            return;
        }
        y = x;
        if (z->country < x->country) {
          x = x->left;
        } else
          x = x->right;
      }

      z->parent = y;
      if (y == nullptr) {
        root = z;
      } else if (z->country < y->country) {
        y->left = z;
      } else 
        y->right = z;
      
      z->top50Songs.push_back(song);
      insert_fixup(z);
    }
void RBtreeDates::insertDate(Song &song, string &Sdate) {
      int date = dateToInt(Sdate);
      
      if (date < 101) { //skip invalid songs. date wont ever go below 101 which is 01-01 -> 101
        //cout << count++ << endl; //prints how many invalid song objects are read
        return;
      }
      NodeDate* z = new NodeDate(date);
      z->left = nullNode;
      z->right = nullNode;

      NodeDate* y = nullptr;
      NodeDate* x = root;

      while (x != nullNode) {
        if (z->date == x->date) {
            x->Countries.insertCountry(song, song.country);
            return;
        }
        y = x;
        if (z->date < x->date) {
          x = x->left;
        } else
          x = x->right;
      }

      z->parent = y;
      if (y == nullptr) {
        root = z;
      } else if (z->date < y->date) {
        y->left = z;
      } else 
        y->right = z;

      z->Countries.insertCountry(song, song.country);
      insert_fixup(z);
    }

void RBtreeCountry::insert_fixup(NodeCountry* z) {
      while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
          NodeCountry* y = z->parent->parent->right;
          if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent; //checking iteratively
          } else {
            if (z == z->parent->right) {
              z = z->parent;
              left_rotate(z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            right_rotate(z->parent->parent);
          }
        } else {
          NodeCountry* y = z->parent->parent->left;
          if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
          } else {
            if (z == z->parent->left) {
              z = z->parent;
              right_rotate(z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            left_rotate(z->parent->parent);
          }
        }
        if (z == root) break;
      }
      root->color = BLACK;
    }
void RBtreeDates::insert_fixup(NodeDate* z) {
      while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
          NodeDate* y = z->parent->parent->right;
          if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent; //checking iteratively
          } else {
            if (z == z->parent->right) {
              z = z->parent;
              left_rotate(z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            right_rotate(z->parent->parent);
          }
        } else {
          NodeDate* y = z->parent->parent->left;
          if (y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
          } else {
            if (z == z->parent->left) {
              z = z->parent;
              right_rotate(z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            left_rotate(z->parent->parent);
          }
        }
        if (z == root) break;
      }
      root->color = BLACK;
    }

std::string RBtreeCountry::searchCountry(string &country) {
    std::string returnString = "";
      NodeCountry* x = root;
      while (x != nullNode && country != x->country) {
        if (country < x->country) x = x->left;
        else x = x->right;
      }
      for (int i = 0; i < 10; i++) {
        returnString += x->top50Songs[i].printSong();

      }
      return returnString;
    }
std::string RBtreeDates::displayTopTen(string &Sdate, string &country) {
      std::string returnString;
      int date = dateToInt(Sdate);
      NodeDate* x = root;
      while (x != nullNode && date != x->date) {
        if (date < x->date) x = x->left;
        else x = x->right;
      }
      returnString = x->Countries.searchCountry(country);
      return returnString;
    }

void RBtreeCountry::level_order(bool print_color) {
      deque<NodeCountry*> q;
      q.push_back(root);
      
      while (!q.empty()) {
        NodeCountry* node = q.front();
        q.pop_front();

        if (print_color) {
          cout << node->country << node->print_color() << " ";
        } else {
          cout << node->country << " ";
        }

        if (node->left != nullNode) q.push_back(node->left);
        if (node->right != nullNode) q.push_back(node->right);
      }
    }
void RBtreeDates::level_order(bool print_color) {
      deque<NodeDate*> q;
      q.push_back(root);
      
      while (!q.empty()) {
        NodeDate* node = q.front();
        q.pop_front();

        if (print_color) {
          cout << node->date << node->print_color() << " ";
        } else {
          cout << node->date << " ";
        }

        if (node->left != nullNode) q.push_back(node->left);
        if (node->right != nullNode) q.push_back(node->right);
      }
    }
