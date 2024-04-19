#include "RBtree.h"
using namespace std;

//getter for height of node
int TreeNode::getHeight(TreeNode* root) { //O(log(n)) because it recursively travels a number, height, times which is log(n) where n is the # of nodes 
    if (root == NULL) return 0;
    return root->height;
}

//returns the balance factor by calling getHeight on root->left and right and subtracting them
int TreeNode::getBalanceFactor(TreeNode* root) { //O(log(n)) because it calls 2 of O(log(n)) functions
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

//calls insertHelper
void TreeNode::insert(string date, string country) { //O(log(n)) because it calls on insertHelper which is of O(log(n))
    this->root = insertHelper(this->root, date, country);
}

double dateToInt(string& date){
    istringstream iss(date);
    char dash;
    double year, month, day;
    iss >> year >> dash >> month >> dash >> day;
    double intDate = year + (month/100) + (day/10000);
    return intDate;
}
//helper to insert nodes
TreeNode* TreeNode::insertHelper(TreeNode* root, string date, string country) { //O(log(n) because of property of AVL trees)
    //base case
    if (root == nullptr) {
        cout << "successful adding date: " << date << "\n";
        return new TreeNode(date, country);
    }

    //inserting node recursively
    if (dateToInt(date) < dateToInt(root->DATE))
        root->left = insertHelper(root->left, date, country);
    else if (dateToInt(date) > dateToInt(root->DATE)) 
        root->right = insertHelper(root->right, date, country);
    else if (dateToInt(date) == dateToInt(root->DATE)){ // if it already exists, print unsuccessful
        cout << "already inserted date: " << root->DATE << "\n";
    }
    //setting the initial height of the root
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // checking balance factor, performing rotations, and updating height
    if (-1 <= getBalanceFactor(root) && getBalanceFactor(root) <= 1) {
        return root;
    }
    if (getBalanceFactor(root) == -2) {
        if (getBalanceFactor(root->right) == 1) {
            //cout << "performing Right-Left rotation" << endl;
            root->right = rightRotation(root->right);
            return leftRotation(root);
        } 
        else { 
            //cout << "performing Left rotation" << endl;
            return leftRotation(root);
        }
    }
    else if (getBalanceFactor(root) == 2){
        if (getBalanceFactor(root->left) == -1) {
            //cout << "performing Left-Right rotation" << endl;
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        else {
            //cout << "performing Right rotation" << endl;
            return rightRotation(root);
        }
    }
    return root;
}

//right rotation function
TreeNode* TreeNode::rightRotation(TreeNode* a) { //O(1), constant number of operations when rotating
    TreeNode* b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

//left rotation function
TreeNode* TreeNode::leftRotation(TreeNode* c) { //O(1), constant number of operations when rotating
    TreeNode* b = c->right;
    c->right = b->left;
    b->left = c;

    c->height = max(getHeight(c->left), getHeight(c->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;
    return b;
}

//master function called by processInput that is called whenever user wants to print in whatever order
void TreeNode::order(string& command) { //O(n) because it has to run one of the orderers which are O(n)
    if (command == "printInorder") {
        inorderHelper(this->root);
    }
    else if (command == "printPreorder") {
        preorderHelper(this->root);
    }
    else if (command == "printPostorder") {
        postorderHelper(this->root);
    }
    //updating substringOrdList to remove the comma at the end of ordered list
    substringOrdList = orderedList.substr(0, orderedList.length() - 2);
}

//helper for printPreorder
void TreeNode::preorderHelper(TreeNode* root) { //O(n), goes through all nodes
    if(root==NULL) {
        cout<<"";
        return;
    }
    else{
        orderedList += root->DATE + ", ";
        preorderHelper(root->left);
        preorderHelper(root->right);
    }
}

//helper for printInorder
void TreeNode::inorderHelper(TreeNode* root) { //O(n), goes through all nodes
    if(root==NULL) {
        cout<<"";
        return;
    }
    else {
        inorderHelper(root->left);
        orderedList += root->DATE + ", ";
        inorderHelper(root->right);
    }
}

//helper for printPostorder
void TreeNode::postorderHelper(TreeNode* root) { //O(n), goes through all nodes
    if(root==NULL){
        cout<<"";
        return;
    }
    else {
        postorderHelper(root->left);
        postorderHelper(root->right);
        orderedList += root->DATE + ", ";
    }
}

//master function called by processInput that is called when a user wants to search for or remove a node
void TreeNode::access(string& command, string attribute, bool isValidUfid, bool isValidName) { //O(n) worst case due to searchName
    if (command == "search" && isValidUfid == true) {
        searchIdHelper(this->root, attribute);
    }
    else if (command == "search" && isValidName == true) {
        bool found = false;
        searchNameHelper(this->root, attribute, found);
        if (!found) cout << "unsuccessful" << endl;
    }
    else if (command == "remove" && isValidUfid) {
        removeId(attribute);
    }
    else if (command == "remove" && isValidName) {
        cout << "unsuccessful" << endl;
    }
}

//helper for searching for the UFID of a node to return the Name
void TreeNode::searchIdHelper(TreeNode* root, string date) { // O(log(n)) because of avl tree properties
    if (root == NULL) {
        cout << "unsuccessful" << endl;
        return;
    }
    if (dateToInt(root->DATE) == dateToInt(date)) {
        cout << root->COUNTRY << endl;
        return;
    }
    else {
        if (dateToInt(date) < dateToInt(root->DATE)) {
            searchIdHelper(root->left, date);
        }
        else if (dateToInt(date) > dateToInt(root->DATE)) {
            searchIdHelper(root->right, date);
        }
    }
}

//helper for searching for the name of a node to return the ID (or multiple IDs if there is duplicate names)
void TreeNode::searchNameHelper(TreeNode* root, string& searchName, bool& found){ // O(n) because it needs to check for duplicates across all nodes
    if (root == nullptr) {
        return;
    }
    if (root->COUNTRY == searchName) {
        cout << root->DATE << endl;
        found = true;
    }
    searchNameHelper(root->left, searchName, found);
    searchNameHelper(root->right, searchName, found);
}

//calls on the removeIdHelper function 
void TreeNode::removeId(string country) {
    this->root = removeIdHelper(this->root, country);
}

//removes the id and rebalances the tree
TreeNode* TreeNode::removeIdHelper(TreeNode* root, string country) {
    if (root == NULL) {
    cout << "unsuccessful" << endl;
    return NULL;
    }
    if (root->COUNTRY == country) {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            cout << "successful" << endl;
            return NULL;
        }
        else if (root->left == NULL) {
            TreeNode* temp = root->right;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        // if node has two children, find inorder successor
        else if (root->left != NULL && root->right != NULL) {
            TreeNode* inorderSuccessor;
            TreeNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            inorderSuccessor = temp;
            root->DATE = inorderSuccessor->DATE;
            root->COUNTRY = inorderSuccessor->COUNTRY;
            root->right = removeIdHelper(root->right, inorderSuccessor->COUNTRY);
        }
    }
    else {
        if (country < root->COUNTRY) {
            root->left = removeIdHelper(root->left, country);
        }
        else if (country > root->COUNTRY) {
            root->right = removeIdHelper(root->right, country);
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    //updating height and rebalancing nodes
    if (-1 <= getBalanceFactor(root) && getBalanceFactor(root) <= 1){
    return root;
    }
    if (getBalanceFactor(root) == -2) {
        if (getBalanceFactor(root->right) == 1) {
            //cout << "performing Right-Left rotation" << endl;
            root->right = rightRotation(root->right);
            return leftRotation(root);
        } 
        else { 
            //cout << "performing Left rotation" << endl;
            return leftRotation(root);
        }
    }
    else if (getBalanceFactor(root) == 2){
        if (getBalanceFactor(root->left) == -1) {
            //cout << "performing Left-Right rotation" << endl;
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        else {
            //cout << "performing Right rotation" << endl;
            return rightRotation(root);
        }
    }
    return root;
}

//resets inorderCount and bool found to false to then call on the helper and afterwards prints unsuccessful if not found
void TreeNode::removeInorderNth(int Nth) {
    inorderCount = 0;
    bool found = false;
    removeInorderNthHelper(this->root, Nth, found);
    if (!found) cout << "unsuccessful" << endl;
}

//helper for removing Nth node from inorder
void TreeNode::removeInorderNthHelper(TreeNode* root, int Nth, bool& found) {
    if (root == NULL || inorderCount > Nth) {
        return;
    }
    if (Nth == 0) {
        //TreeNode* prevRoot;
        while (root->left != NULL) {
            //prevRoot = root;
            root = root->left;
        }
        removeId(root->COUNTRY);
        found = true;
        return;
    }
    removeInorderNthHelper(root->left, Nth, found);
    //updates count to keep track of how many nodes it has inorderly traversed to then remove the corresponding node once it equals N
    inorderCount += 1;
    if (inorderCount - 1 == Nth) {
        removeId(root->COUNTRY);
        found = true;
        return;
    }
    removeInorderNthHelper(root->right, Nth, found);
}

//Grandmaster function that processes the input from the user
void TreeNode::processInput(const string& line){ //O(1) 
    istringstream in(line);

    string command;
    string name;
    string id;
    string nameORid; // used for searching and removal
    string lastName; // used to properly add last names when inserting
    string Nth;
    in >> command;
    if (command == "insert") { // if insert, skip the 1st quote, read the id, then continue to lower if statements
        string next;
        getline(in, next, '"');
        getline(in, name, '"');
        in >> id;
    }
    else if (command == "removeInorder") {
        int intNth;
        in >> Nth;
        try //making sure the user inputs a number
        {
            intNth = stoi(Nth);
            if (!(intNth < 0)) {
                removeInorderNth(intNth);
            } else {
                cout << "unsuccessful" << endl;
                return;
            }
            
            return;
        }
        catch(const exception& e)
        {
            cout << "unsuccessful"  << endl;
            return;
        }
    }
    else {
        in >> nameORid;
        regex checkIfName = regex("^\"");
        // checks to see if the second word in the input is a name or id
        bool isName = regex_search(nameORid, checkIfName);
        if (isName){
            if (getline(in, lastName)) { // if its a name, see if there is a 3rd word that would be their last name and add it
                nameORid += lastName;
            }
            //remove the quote mark from the end of the last name string
            string removeQuote = nameORid.substr(1, nameORid.length() - 2);
            nameORid = removeQuote;
        }
    }
    //continue normally with parsing input
    regex objName = regex("[a-zA-Z\\s]+");
    bool isValidName = regex_match(name, objName);
    regex objUFID = regex("[0-9]{8,8}");
    bool isValidUfid = regex_search(id, objUFID);

    if (command == "insert") {
        if (isValidName && isValidUfid) {
            insert(name, id);
        }
        else cout << "unsuccessful" << endl;
    }
    else if (command == "printPreorder" || command == "printInorder" || command == "printPostorder") {
        orderedList = "";
        order(command);
        cout << substringOrdList << endl;
    }
    else if (command == "search" || command == "remove") {
        //check to see if whatever inputted after search or remove is a name or ufid
        isValidUfid = regex_search(nameORid, objUFID);
        isValidName = regex_match(nameORid, objName);
        if (isValidUfid || isValidName) {
            //pass it into the master command that takes care of further conditions
            access(command, nameORid, isValidUfid, isValidName);
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    else if (command == "printLevelCount") {
        //simply print the height of the root of the whole tree if there exists one
        if (this->root != NULL) {
            cout << this->root->height << endl;
        } else {
            cout << "0" << endl;
        }
    }
    else {
        cout << "unsuccessful" << endl;
    }
}