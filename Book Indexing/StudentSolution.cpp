#include <bits/stdc++.h>
#include <vector>
#include <cstring>
using namespace std;

string toggle(string& str)
{
    int length = str.length();
    for (int i = 0; i < length; i++) {
        int c = str[i];
        if (isupper(c)) 
            str[i] = tolower(c);        
    }
    return str;
}

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "red";    // Color of the node
    vector<pair<string, int>> occurance;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}

    void increase_count(string chap_name){
        if(occurance.size()==0){
            occurance.push_back(make_pair("Chapter1",0));
            occurance.push_back(make_pair("Chapter2",0));
            occurance.push_back(make_pair("Chapter3",0));
        }
        for(int i=0;i<occurance.size();i++){
            if(chap_name == "Chapter1.txt"){
                occurance[0].second++;
                break;
            }
            else if(chap_name == "Chapter2.txt"){
                occurance[1].second++;
                break;
            }
            else{
                occurance[2].second++;
                break;
            }
        }
    }
    HybridNode *uncle()
    {
        // If no parent or grandparent, then no uncle
        if (parent == NULL or parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right_child;
        else
            // uncle on left
            return parent->parent->left_child;
    }

    // check if HybridNode is left child of parent
    bool isOnLeft() { return this == parent->left_child; }

    // returns pointer to sibling
    HybridNode *sibling()
    {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right_child;

        return parent->left_child;
    }

    // moves HybridNode down and moves given HybridNode in its place
    void moveDown(HybridNode *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left_child = nParent;
            }
            else
            {
                parent->right_child = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild()
    {
        return (left != NULL and left_child->color == "red") or
               (right != NULL and right_child->color == "red");
    }

};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }

    void leftRotate(HybridNode *x)
    {
        // new parent will be HybridNode's right child
        HybridNode *nParent = x->right_child;

        // update root if current HybridNode is root
        if (x == getRoot())
            setRoot(nParent);

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right_child = nParent->left_child;
        // connect new parent's left element with HybridNode
        // if it is not null
        if (nParent->left_child != NULL)
            nParent->left_child->parent = x;

        // connect new parent with x
        nParent->left_child = x;
    }

    void rightRotate(HybridNode *x)
    {
        // new parent will be HybridNode's left child
        HybridNode *nParent = x->left_child;

        // update root if current HybridNode is root
        if (x == getRoot())
            setRoot(nParent);

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left_child = nParent->right_child;
        // connect new parent's right element with HybridNode
        // if it is not null
        if (nParent->right_child != NULL)
            nParent->right_child->parent = x;

        // connect new parent with x
        nParent->right_child = x;
    }

    void swapColors(HybridNode *x1, HybridNode *x2)
    {
        string temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(HybridNode *u, HybridNode *v)
    {
        string temp1,temp2;
        temp1 = u->element;
        temp2 = u->key;
        u->element = v->element;
        u->key = v->key;
        v->element = temp1;
        v->key = temp2;
    }

    HybridNode *successor(HybridNode *x)
    {
        HybridNode *temp = x;

        while (temp->left_child != NULL)
            temp = temp->left_child;
        //cout<<"successor: "<<temp->key<<"--->"<<temp->element<<endl;
        return temp;
    }

    HybridNode *BSTreplace(HybridNode *x)
    {
        // when HybridNode have 2 children
        if (x->left_child != NULL and x->right_child != NULL)
            return successor(x->right_child);

        // when leaf
        if (x->left_child == NULL and x->right_child == NULL)
            return NULL;

        // when single child
        if (x->left_child != NULL)
            return x->left_child;
        else
            return x->right_child;
    }

    void deleteHybridNode(HybridNode *v)
    {
        //cout<<"BST REPLACE KEY: "<<BSTreplace(v)->key<<endl;
        HybridNode *u = BSTreplace(v);
        // True when u and v are both black
        bool uvBlack = ((u == NULL or u->color == "black") and (v->color == "black"));
        HybridNode *parent = v->parent;
        if (u == NULL)
        {
            //cout<<"U == NULL TRIGGERED"<<endl;
            // u is NULL therefore v is leaf
            if (v == getRoot())
            {
                //cout<<"V == GETROOT() TRIGGERED"<<endl;
                // v is root, making root null
                setRoot(nullptr);
            }
            else
            {
                //cout<<"V != GETROOT() TRIGGERED"<<endl;
                if (uvBlack)
                {
                    //cout<<"UVBLACK TRUE TRIGGERED"<<endl;
                    // u and v both black
                    // v is leaf, fix double black at v
                    fixDoubleBlack(v);
                }
                else
                {
                    //cout<<"UVBLACK FALSE TRIGGERED"<<endl;
                    // u or v is red
                    if (v->sibling() != NULL){
                        //cout<<"V->SIBLING() != NULL TRIGGERED"<<endl;
                        // sibling is not null, make it red"
                        v->sibling()->color = "red";
                    }
                }

                // delete v from the tree
                if (v->isOnLeft())
                {
                    //cout<<"V->ISONLEFT() TRUE TRIGGERED"<<endl;
                    parent->left_child = NULL;
                }
                else

                {
                    //cout<<"V->ISONLEFT() FLASE TRIGGERED"<<endl;
                    parent->right_child = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left_child == NULL or v->right_child == NULL)
        {
            //cout<<"v->left_child == NULL or v->right_child == NULL TRIGGERED"<<endl;
            // v has 1 child
            if (v == getRoot())
            {
                //cout<<"V == GETROOT() TRIGGERED"<<endl;
                // v is root, assign the value of u to v, and delete u
                swapValues(u,v);
                v->left_child = v->right_child = NULL;
                delete u;
            }
            else
            {
                //cout<<"V != GETROOT() TRIGGERED"<<endl;
                // Detach v from tree and move u up
                if (v->isOnLeft())
                {
                    //cout<<"V->ISONLEFT() TRIGGERED"<<endl;
                    parent->left_child = u;
                }
                else
                {
                    //cout<<"V ISONLEFT() FALSE TRIGGERED"<<endl;
                    parent->right_child = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {
                    //cout<<"UVBLACK TRUE TRIGGERED"<<endl;
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                }
                else
                {
                    //cout<<"UVBLACK FALSE TRIGGERED"<<endl;
                    // u or v red, color u black
                    u->color = "black";
                }
            }
            return;
        }

        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteHybridNode(u);
    }

    void fixDoubleBlack(HybridNode *x)
    {
        //cout<<"FIX DOUBLE BLACK INITIATED!"<<endl;
        if (x == getRoot())
            cout<<"x == getroot() TRIGGERED"<<endl; //******
            // Reached root
            return;

        HybridNode *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)
        {
            //cout<<"sibling == NULL TRIGGERED"<<endl;
            // No sibling, double black pushed up
            fixDoubleBlack(parent);
        }
        else
        {
            //cout<<"sibling != NULL TRIGGERED"<<endl;
            if (sibling->color == "red")
            {
                //cout<<"sibling->color == red TRIGGERED"<<endl;
                // Sibling red
                parent->color = "red";
                sibling->color = "black";
                if (sibling->isOnLeft())
                {
                    //cout<<"sibling->isOnLeft() TRIGGERED"<<endl;
                    // left case
                    rightRotate(parent);
                }
                else
                {
                    //cout<<"sibling->isOnLeft() FALSE TRIGGERED"<<endl;
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {
                //cout<<"sibling is black TRIGGERED"<<endl;
                // Sibling black
                if (sibling->hasRedChild())
                {
                    //cout<<"sibling->hasRedChild() TRIGGERED"<<endl;
                    // at least 1 red children
                    if (sibling->left_child != NULL and sibling->left_child->color == "red")
                    {
                        //cout<<"sibling->left_child != NULL and sibling->left_child->color == red TRIGGERED"<<endl;
                        if (sibling->isOnLeft())
                        {
                            //cout<<"sibling->isOnLeft() TRIGGERED"<<endl;
                            // left left
                            sibling->left_child->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            //cout<<"sibling->isOnLeft() FALSE TRIGGERED"<<endl;
                            // right left
                            sibling->left_child->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            //cout<<"sibling->isOnLeft() TRIGGERED"<<endl;
                            // left right
                            sibling->right_child->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            //cout<<"sibling->isOnLeft() FALSE TRIGGERED"<<endl;
                            // right right
                            sibling->right_child->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = "black";
                }
                else
                {
                    //cout<<"sibling HAS BLACK CHILD TRIGGERED"<<endl;
                    // 2 black children
                    sibling->color = "red";
                    if (parent->color == "black")
                        fixDoubleBlack(parent);
                    else
                        parent->color = "black";
                }
            }
        }
    }

    // fix red red at given HybridNode
    void fixRedRed(HybridNode *x)
    {
        // if x is root color it black and return
        if (x == getRoot())
        {
            x->color = "black";
            //cout<<"its a root!"<<endl;
            return;
        }

        // initialize parent, grandparent, uncle
        HybridNode *parent = x->parent, *grandparent = parent->parent,
             *uncle = x->uncle();

        if (parent->color != "black")
        {
            if (uncle != NULL && uncle->color == "red")
            {
                // uncle red, perform recoloring and recurse
                parent->color = "black";
                uncle->color = "black";
                grandparent->color = "red";
                fixRedRed(grandparent);
                //cout<<"fixing red red for grandpa"<<endl;
            }
            else
            {
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                    {
                        // for left right
                        swapColors(parent, grandparent);
                        //cout<<"swapping colors"<<endl;
                    }
                    else
                    {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                        
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                    //cout<<"swapping colors"<<endl;
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else
                    {
                        swapColors(parent, grandparent);
                    }

                    // for right right and right left
                    leftRotate(grandparent);
                    //cout<<"swapping colors"<<endl;
                }
            }
        }
    }

    HybridNode* search(string key){
        HybridNode *temp = getRoot();
        while (temp != NULL)
        {
            if (key < temp->key)
            {
                if (temp->left_child == NULL)
                    return nullptr;
                else
                    temp = temp->left_child;
            }
            else if (key == temp->key)
            {
                break;
            }
            else
            {
                if (temp->right_child == NULL)
                    return nullptr;
                else
                    temp = temp->right_child;
            }
        }

        return temp;
    }

    void insert(string key, string element) {
        // Implement Red-Black Tree insertion
        HybridNode* newnode = new HybridNode(key,element);
        if (getRoot() == NULL)
        {
            // when root is null
            // simply insert value at root
            newnode->color = "black";
            setRoot(newnode);
            getRoot()->increase_count(element);
        }
        else
        {
            HybridNode *temp = searchforinsert(newnode->key);

            if (temp->key == newnode->key)
            {
                // return if value already exists
                temp->increase_count(element);
                return;
            }

            // if value is not found, search returns the HybridNode
            // where the value is to be inserted

            // connect new HybridNode to correct HybridNode
            newnode->parent = temp;

            if (newnode->key < temp->key){
                temp->left_child = newnode;
                temp->left_child->increase_count(element);
                //cout<<newnode->key<<" ";
            }
            else{
                temp->right_child = newnode;
                temp->right_child->increase_count(element);
                //cout<<newnode->key<<" ";
            }

            // fix red red violation if exists
            fixRedRed(newnode);
            //cout<<newnode->key<<" "<<endl;
        }
    }

    void deleteNode(string key) {
        // Implement Red-Black Tree deletion
        HybridNode* temp = search(key);
        deleteHybridNode(temp);
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
        vector<HybridNode*> path;
        while(node!=nullptr){
            path.push_back(node);
            node = node->parent;

        }
        return path;
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        vector<HybridNode*> path;
        for(int i=0;i<bit_sequence.size();i++){
            if(bit_sequence[i]=='1'){
                if(node==nullptr){
                    return path;
                }
                else{
                    path.push_back(node);
                    node = node->left_child;
                }
            }
            else{
                if(node==nullptr){
                    return path;
                }
                else{
                    path.push_back(node);
                    node = node->right_child;
                }
            }
        }
    }
    vector<HybridNode*> inOrderTraversal(HybridNode* node) {
        vector<HybridNode*> result;
        if (node) {
            vector<HybridNode*> left_result = inOrderTraversal(node->left_child);
            result.insert(result.end(), left_result.begin(), left_result.end());  // Visit left subtree
            result.push_back(node);  // Visit the current node
            vector<HybridNode*> right_result = inOrderTraversal(node->right_child);
            result.insert(result.end(), right_result.begin(), right_result.end());  // Visit right subtree
        }
        return result;
    }
    // vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {

    //     vector<HybridNode*> result;
    //     if (node != nullptr && depth > 0) {
    //         // Process the current node
    //         result.push_back(node);

    //         // Recursively traverse the left subtree with reduced depth
    //         vector<HybridNode*> left_subtree = preOrderTraversal(node->left_child, depth - 1);

    //         // Recursively traverse the right subtree with reduced depth
    //         vector<HybridNode*> right_subtree = preOrderTraversal(node->right_child, depth - 1);
    //         result.insert(result.end(), left_subtree.begin(), left_subtree.end());
    //         result.insert(result.end(), right_subtree.begin(), right_subtree.end());
    //     }
    //     return result;
    // }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        depth = depth+1;
        vector<HybridNode*> result;
        if (node != nullptr && depth > 0) {
            // Process the current node
            result.push_back(node);

            // Recursively traverse the left subtree with reduced depth
            vector<HybridNode*> left_subtree = preOrderTraversal(node->left_child, depth - 1);

            // Recursively traverse the right subtree with reduced depth
            vector<HybridNode*> right_subtree = preOrderTraversal(node->right_child, depth - 1);
            result.insert(result.end(), left_subtree.begin(), left_subtree.end());
            result.insert(result.end(), right_subtree.begin(), right_subtree.end());
        }
        return result;
    }

    // void preOrderTraversal(HybridNode* node) {
    //     if (node != nullptr) {
    //         // Print the current node's key (or element)
    //         cout<< node->key << endl;
            
    //         // Recursively traverse the left subtree
    //         preOrderTraversal(node->left_child);
            
    //         // Recursively traverse the right subtree
    //         preOrderTraversal(node->right_child);
    //     }
    // }

    HybridNode* searchforinsert(string key) {
        // Implement Red-Black Tree search
        HybridNode *temp = getRoot();
        while (temp != NULL)
        {
            if (key < temp->key)
            {
                if (temp->left_child == NULL)
                    break;
                else
                    temp = temp->left_child;
            }
            else if (key == temp->key)
            {
                break;
            }
            else
            {
                if (temp->right_child == NULL)
                    break;
                else
                    temp = temp->right_child;
            }
        }

        return temp;
    }
    
    int blackheight(HybridNode* node){
    //     // Implement blackheight
    //     if (node == nullptr) {
    //         cout<<endl<<"NODE IS NULL"<<endl;
    //     // Empty subtree has a black height of 0
    //         return 0;
    //     }

    //     // Initialize variables to count black height
    //     cout<<"chuta"<<endl;
    //     int leftBlackHeight = 0;
    //     int rightBlackHeight = 0;

    //     // Recursively find black height for left and right subtrees
    //     if (node->color == "black") {
    //         cout<<"node is black"<<endl;
    //         leftBlackHeight = 1 + blackheight(node->left_child);
    //         cout<<"LEFT BLACK HEIGHT COUNT UPDATED: "<<leftBlackHeight<<endl;
    //         rightBlackHeight = 1 + blackheight(node->right_child);
    //         cout<<"RIGHT BLACK HEIGHT COUNT UPDATED: "<<rightBlackHeight<<endl;
    //     } else {
    //         leftBlackHeight = blackheight(node->left_child);
    //         cout<<"LEFT BLACK HEIGHT COUNT: "<<leftBlackHeight<<endl;
    //         rightBlackHeight = blackheight(node->right_child);
    //         cout<<"RIGHT BLACK HEIGHT COUNT: "<<rightBlackHeight<<endl;
    //     }

    //     // Ensure the black heights of left and right subtrees are the same
    //     if (leftBlackHeight != rightBlackHeight) {
    //         // Handle an error or return a specific value to indicate inconsistency
    //         return -1;
    //     }

    //     // Return the black height for this subtree
    //     return leftBlackHeight;
    // }
        int count=0;
        while(node!= nullptr){
            if(node->color=="black"){
                count++;
            }
            if(node->left_child!=nullptr){
                node = node->left_child;
            }
            else{
                node = node->right_child;
            }
        }
        return count;
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;  // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {  
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        int i,count=0;
        RedBlackTree rbt = getRedBlackTree();
        for(i=0;i<chapter_names.size();i++){
            //cout<<"Chapter Going on: "<<chapter_names[i]<<endl;
            ifstream inputFile(chapter_names[i]);
            if (!inputFile.is_open()) {
                cout<< "Failed to open the file." << endl;
            }
            string line;
            char bom[3] = {0};
            inputFile.read(bom, sizeof(bom));
            if (bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF) {
                // BOM detected (UTF-8 encoding), skip it
            } else {
                // No BOM detected, reset the file position
                inputFile.seekg(0);
            }
            while(getline(inputFile, line)){
                //cout<<"line reading start"<<endl; //nikalo
                istringstream iss(line);
                string word;
                while(getline(iss,word,' ')){
                    //cout<<word<<endl; // nikalo
                    word = toggle(word);
                    rbt.insert(word,chapter_names[i]);
                }
            }
            //cout<<"MAAKICHUUUU: "<<rbt.getRoot()->element<<endl;
        }
        setRedBlackTree(rbt);
        //cout<<getRedBlackTree().preOrderTraversal(getRedBlackTree().getRoot(),9).size()<<endl;
        HybridNode* rootboi = getRedBlackTree().getRoot();
        vector<HybridNode*> nodes = getRedBlackTree().preOrderTraversal(rootboi,11);
        for(int i=0;i<nodes.size();i++){
            //cout<<"fuck bitch "<<nodes[i]->key<<endl;
            if(nodes[i]->occurance[0].second>0 && nodes[i]->occurance[1].second>0 && nodes[i]->occurance[2].second>0){
                ///count++;
                //cout<<"***********NODE GOING oN: "<<nodes[i]->key<<endl;
                HybridNode* temp = getRedBlackTree().searchforinsert(nodes[i]->key);
                getRedBlackTree().deleteHybridNode(temp);
            }
        }
        //<<"********************cout number boiiii************"<<count<<endl;
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
        vector<IndexEntry> result;
        vector<HybridNode*> iot = getRedBlackTree().inOrderTraversal(getRedBlackTree().getRoot());
        //cout<<iot[0]->key<<endl;
        for(int i=0;i<iot.size();i++){
            IndexEntry* newind = new IndexEntry(iot[i]->key);
            newind->setChapterWordCounts(iot[i]->occurance);
            result.push_back(*newind);
        }
        return result;
    }
};

// vector<string> chapters_list;
// void get_chapter_list() {
//     ifstream inputfile("chapterNames.txt");

//     if(!inputfile.is_open()) {
//         cerr << "Unable to open file" << endl;
//         return;
//     }

//     string line;
//     while(getline(inputfile, line)){
//         istringstream iss(line);
//         string word;

//         while(iss >> word){
//             chapters_list.push_back(word);
//             cout << word << endl;
//         }
//     }
// }

// int main()
// {
//     get_chapter_list();
//     Lexicon* lexicon = new Lexicon();
//     lexicon->readChapters(chapters_list);
//     vector<HybridNode*> namaskaram = lexicon->getRedBlackTree().preOrderTraversal(lexicon->getRedBlackTree().getRoot(),12);
//     cout<<namaskaram.size()<<endl;
//     cout<<lexicon->getRedBlackTree().search("AKR")<<endl;
//     HybridNode* exo = lexicon->getRedBlackTree().searchforinsert("he");
//     //cout<<"master boi"<<exo->occurance[2].second<<endl;
//     // cout<<exo<<"---->"<<exo->key<<endl;
//     // lexicon->getRedBlackTree().deleteHybridNode(exo);
//     // lexicon->getRedBlackTree().deleteNode("he");
//     // cout<<"erervvvvvvv "<<lexicon->getRedBlackTree().search("he")<<endl;
//     cout<<"eveverv---"<<lexicon->buildIndex().size()<<endl;
//     // for(int i=0;i<lexicon->buildIndex().size();i++){
//     //     if(lexicon->buildIndex()[i].getWord()=="emily"){
//     //         cout<<"emily found"<<endl;
//     //         cout<<lexicon->buildIndex()[i].getChapterWordCounts()[1].second<<endl;
//     //     }
//     // }
//     vector<HybridNode*> preorder_traversal = lexicon->getRedBlackTree().preOrderTraversal(lexicon->getRedBlackTree().getRoot(), 9);

//     cout<<lexicon->getRedBlackTree().blackheight(lexicon->getRedBlackTree().getRoot())<<endl;

//     lexicon->getRedBlackTree().deleteNode("he");
//     cout<<lexicon->getRedBlackTree().search("he");
//     // vector<HybridNode*> path = lexicon->getRedBlackTree().traverseUp(lexicon->getRedBlackTree().search("Clara"));
//     // for(int i=0;i<path.size();i++){
//     //     cout<<path[i]->key<<endl;
//     // }
//     //cout<<lexicon->getRedBlackTree().search("curious")->parent->key<<endl;
// //     Lexicon lexo;
// //     vector<string>chapname;
// //     chapname.push_back("Chapter1.txt");
// //     chapname.push_back("Chapter2.txt");
// //     chapname.push_back("Chapter3.txt");
// //     lexo.readChapters(chapname);
// //     //cout<<"**********************hello****************************"<<endl;
// //     HybridNode* node = lexo.getRedBlackTree().getRoot();
// //     //cout<<"************************************************"<<node<<"--->"<<node->key<<endl;
// //     //lexo.getRedBlackTree().preOrderTraversal(node);
// //     vector<HybridNode*> namaskaram = lexo.getRedBlackTree().preOrderTraversal(node,11);
// //     //cout<<lexo.getRedBlackTree().preOrderTraversal(lexo.getRedBlackTree().getRoot(),11).size()<<endl;
// //     //lexo.getRedBlackTree().preOrderTraversal(node);
// //     for(int i=0;i<namaskaram.size();i++){
// //         //cout<<namaskaram[i]->key<<" ";
// //     }
// //     // cout<<"Bleck hight: "<<lexo.getRedBlackTree().blackheight(lexo.getRedBlackTree().getRoot())<<endl;
// //     //<<lexo.getRedBlackTree().getRoot()->left_child->key<<"--->"<<lexo.getRedBlackTree().getRoot()->left_child->occurance[0].first<<"--->"<<lexo.getRedBlackTree().getRoot()->left_child->occurance[0].second<<endl;
// //     //cout<<"Namaskaram : "<<lexo.getRedBlackTree().getRoot()->key<<endl;
// //     // lexo.getRedBlackTree().deleteHybridNode(node);
// //     // cout<<lexo.getRedBlackTree().getRoot()->key<<endl;
// //     // cout<<lexo.getRedBlackTree().search("couldn't")->key<<endl;
// //     cout<<namaskaram.size()<<endl;
// }
