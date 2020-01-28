////Figure It Out Avl Tree
////Made by Stephen Shoemaker
#ifndef FIOAVLTREE_H
#define FIOAVLTREE_H
#include <iostream>
#include <vector>
using namespace std;
template <typename DataType>
class FIOAvlTree{
    public:
        FIOAvlTree();
        FIOAvlTree(const FIOAvlTree<DataType>&);

        ~FIOAvlTree();

        const DataType& findMin() const;
        const DataType& findMax() const;

        bool contains(const DataType&) const;

        DataType& get(DataType);

        bool isEmpty() const;

        void makeEmpty();

        void insert(const DataType&);

        void remove(const DataType);

        void printTree();

        FIOAvlTree<DataType>& operator=(const FIOAvlTree<DataType>&cpy){
            if(this != &cpy){
                makeEmpty();
                rootNode= clone(cpy.rootNode);
            }
            return *this;
        }


        void inOrder(void (*func)(DataType));

        vector<DataType> getDataAsVector();

    private:
        struct AVLNode{
            DataType data;
            AVLNode* left;
            AVLNode* right;
            int height;

            AVLNode(DataType initData, AVLNode* l, AVLNode* r, int initHeight= 0){
                data = initData;
                left = l;
                right = r;
                height = initHeight;
            }
       };

       AVLNode* rootNode;

       void insert(const DataType & , AVLNode*&);

       AVLNode* findMin(AVLNode* currNode) const{
           //If there is no node to the left, this is the most left node on the tree
           //and therefore is the minimum node
           if(currNode->left == nullptr) return currNode;

           //If there is a node to the left, go to the left and keep going left until
           //there is no more left
           return findMin(currNode->left);
       }

       AVLNode* findMax(AVLNode* currNode) const{
           //Same as above but going to the right
           if(currNode->right == nullptr) return currNode -> data;

           //keep going right until you cant
           return findMax(currNode-> right);
       }

       bool contains(const DataType&, AVLNode*) const;

       DataType& get(DataType, AVLNode*);

       void makeEmpty(AVLNode*&);

       AVLNode* clone(AVLNode* cloneNode) const{
           if (cloneNode== nullptr){
               return nullptr;
           } else {
               return new AVLNode(cloneNode->data, cloneNode->left, cloneNode->right, cloneNode->height);
           }
       }

       void printTree(AVLNode *) const;

       int height(AVLNode*) const;

       int max(int, int);

       void case1(AVLNode *&);
       void case2(AVLNode *&);
       void case3(AVLNode *&);
       void case4(AVLNode *&);

       void inOrder(AVLNode*, void (*f)(DataType));

       void getDataAsVector(AVLNode*, vector<DataType>&);
};

//Default Constructor
template <typename DataType>
FIOAvlTree<DataType>::FIOAvlTree(){
    rootNode = nullptr;
}

//Copy Constructor
template <typename DataType>
FIOAvlTree<DataType>::FIOAvlTree(const FIOAvlTree<DataType> & cpy){
    //Overloaded Assignment operator makes this a deep copy
    *this = cpy;
}

template <typename DataType>
FIOAvlTree<DataType>::~FIOAvlTree(){
    //destroying every node and scattering the ashes
    makeEmpty();
}

template <typename DataType>
const DataType& FIOAvlTree<DataType>::findMin() const{
    //Making sure there is data
    if(isEmpty()) throw underflow_error();

    //Calling recursive private function to get the minimum
    return findMin(rootNode->data);
}

template <typename DataType>
const DataType& FIOAvlTree<DataType>::findMax() const{
    //Making sure there is data
    if(isEmpty()) throw underflow_error();

    //calling recursive private function to get the maximum
    return findMax(rootNode->data);
}

//returns the height of the node
template <typename DataType>
int FIOAvlTree<DataType>::height(AVLNode * node) const{
    if(node == nullptr) return -1;
    return node->height;
}


template <typename DataType>
bool FIOAvlTree<DataType>::contains(const DataType & searchValue) const{
    //calling recursive private contains
    if(rootNode == nullptr) return false;
    return contains(searchValue, rootNode);
}

template <typename DataType>
int FIOAvlTree<DataType>::max(int left, int right){
    if (left < right) return right;
    return left;
}
//Searches the binary tree for the search value
template <typename DataType>
bool FIOAvlTree<DataType>::contains(const DataType & searchValue, AVLNode * currNode) const{
    //return true if the current node is the same as the dataType
    if(currNode->data == searchValue) return true;

    //Go right if search value is greater and right exists
    else if(currNode->data < searchValue && currNode->right != nullptr)
        return contains(searchValue, currNode->right);
    //Go left if left exists, search must be left do to simple logic
    else if(currNode->left != nullptr && searchValue < currNode->data)
        return contains(searchValue, currNode->left);
    //If end of tree is reached return false
    return false;
}


template <typename DataType>
DataType& FIOAvlTree<DataType>::get(DataType searchValue){
    //calls recursive private getter
    return get(searchValue, rootNode);
}

//Goes left or right and searches the tree then returns a reference to it
//Contains should be called first
template <typename DataType>
DataType& FIOAvlTree<DataType>::get(DataType searchValue, AVLNode* currNode){
    //if we found it, return it
    if(currNode-> data == searchValue) return currNode->data;

    //if the search value is greater than the current node, go right
    else if(currNode->data < searchValue && currNode->right!= nullptr)
        return get(searchValue, currNode->right);
    //if the search value is less, and left exists go left
    else if(currNode->left != nullptr)
        return get(searchValue, currNode ->left);

    //if we reach here, it is not in the list
    throw "Data is not present in the list";
}

//returns true if root points to nothing
template <typename DataType>
bool FIOAvlTree<DataType>::isEmpty() const {
    return rootNode == nullptr;
}

//calls a recursive post order emptying function
template <typename DataType>
void FIOAvlTree<DataType>::makeEmpty(){
    makeEmpty(rootNode);
}

//goes left, then right, then deletes the current node, bottom up deletion
template <typename DataType>
void FIOAvlTree<DataType>::makeEmpty(AVLNode*& curr){
    if(curr != nullptr){
        makeEmpty(curr->left);
        makeEmpty(curr->right);
        delete curr;
    }

    //sets the reference pointer to null so it is no longer referenced
    curr = nullptr;
}

//calling private insertion method
template <typename DataType>
void FIOAvlTree<DataType>::insert(const DataType& value){
    insert(value, rootNode);
}

//Adding newValue recursively
template <typename DataType>
void FIOAvlTree<DataType>::insert(const DataType& value, AVLNode*& currNode){
    //Create a location for the value if it's "home" is found
    if(currNode == nullptr){
        currNode = new AVLNode(value, nullptr, nullptr);
    }
    //If it belongs to the left, send it to the left
    else if(value < currNode->data){
        insert(value, currNode ->left);

        //Balance the tree
        if(height(currNode->left) - height(currNode->right) ==2){
            if(value < currNode -> left ->data){
                case1(currNode);
            } else {
                case2(currNode);
            }
        }
    //same as above but mirrored
    } else if (currNode->data < value ){
        insert(value, currNode->right);
        if((height(currNode->right) - height(currNode->left)) == 2){
            if(currNode ->right->data < value){
                case4(currNode);
            } else{
                case3(currNode);
            }
        }
    }

    //updating the height
    currNode->height = max(height(currNode->left), height(currNode->right)) + 1;
}
template <typename DataType>
void FIOAvlTree<DataType>::case1(AVLNode*& oldTop){
    //This node will be the new top of this subtree
    AVLNode* newTop = oldTop ->left;

    //Setting the oldTop to point to the its left subtree's right subtree
    oldTop->left = newTop -> right;

    //Making the new top point to the old Top
    newTop->right = oldTop;

    //updating height
    oldTop->height = max(height(oldTop->left), height(oldTop->right)) + 1;
    newTop->height = max(height(newTop->left), oldTop->height) + 1;

    //Changing the reference to the old top to the newTop
    oldTop = newTop;
}

//Mirror of case 1
template <typename DataType>
void FIOAvlTree<DataType>::case4(AVLNode*& oldTop){
    //new Top
    AVLNode* newTop = oldTop -> right;

    //Setting old top right to be its right subtree's left subtree
    oldTop->right = newTop -> left;

    //Making the new top point to oldTop
    newTop -> left = oldTop;

    //Updating height
    oldTop->height = max(height(oldTop->left), height(oldTop->right)) + 1;
    newTop->height = max(height(oldTop), height(newTop->right))+1;

    //changing reference
    oldTop = newTop;
}

//Double Rotation starting with a case 4 then case 1
template <typename DataType>
void FIOAvlTree<DataType>::case2(AVLNode*& oldTop){
    case4(oldTop->left);
    case1(oldTop);
}

//Double rotation starting with case 1 then case 4
template <typename DataType>
void FIOAvlTree<DataType>::case3(AVLNode *& oldTop){
    case1(oldTop ->right);
    case4(oldTop);
}

template <typename DataType>
void FIOAvlTree<DataType>::printTree(){
    printTree(rootNode);
}

template<typename DataType>
void FIOAvlTree<DataType>::printTree(AVLNode *currNode) const{
    if(currNode!= nullptr){
        printTree(currNode->left);
        cout << currNode->data << endl;
        printTree(currNode->right);
    }

}

template<typename DataType>
void FIOAvlTree<DataType>::inOrder(void (*f)(DataType)){
    inOrder(rootNode, f);
}

template<typename DataType>
void FIOAvlTree<DataType>::inOrder(AVLNode* currNode, void (*f)(DataType)){
    if(currNode == nullptr);
    else{
        inOrder(currNode->left, f);
        f(currNode->data);
        inOrder(currNode->right, f);
    }
}

template <typename DataType>
vector<DataType> FIOAvlTree<DataType>::getDataAsVector(){
    vector<DataType> output;
    getDataAsVector(rootNode, output);
    return output;
}

template <typename DataType>
void FIOAvlTree<DataType>::getDataAsVector(AVLNode* currNode, vector<DataType>& output){
    if(currNode!= nullptr){
        output.push_back(currNode->data);
        getDataAsVector(currNode->left, output);
        getDataAsVector(currNode->right, output);
    }
}

#endif // FIOAVLTREE_H
