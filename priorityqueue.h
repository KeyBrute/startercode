/// @file priorityqueue.h
/// @author Miguel Madrigal lol
#pragma once


#include <iostream>
#include <sstream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child

    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    void copy(NODE* current) {
        if (current== nullptr)
            return;
        copy(current->left);
        NODE* link = current->link;
        while (link != nullptr) {
            enqueue(link->value, link->priority);
            link = link->link;
        }
        copy(current->right);
    }
    NODE* initNode(T value, int priority) {
        NODE* node = new NODE();
        node->value = value;
        node->priority = priority;
        node->dup = false;
        node->left = nullptr;
        node->link = nullptr;
        node->parent = nullptr;
        node->right = nullptr;

        return node;
    }
    void enqueue(NODE* current, NODE* data) {
        if (data->priority == current->priority) {
            NODE* last = current->link;
            while (last->link != nullptr) {
                last = last->link;
            }
            data->parent = current->parent;
            last->link = data;
            size++;
        }
        else if (data->priority < current->priority) {
            if (current->left == nullptr) {
                NODE* leaf = initNode(data->value, data->priority);
                leaf->parent = current;
                leaf->link = data;
                current->left = leaf;
                data->parent = current;
                size++;
            }
            else {
                enqueue(current->left, data);
            }
        }
        else {
            if (current->right == nullptr) {
                NODE* leaf = initNode(data->value, data->priority);
                leaf->parent = current;
                leaf->link = data;
                current->right = leaf;
                data->parent = current;
                size++;
            }
            else {
                enqueue(current->right, data);
            }
        }
    }
    T dequeue(NODE* current) {
        if (current== nullptr) {
            return T();
        }
        else if (current->left == nullptr) {
            NODE* node = current->link;
            T val = node->value;
            NODE* next = node->link;
            current->link = next;
            delete node;
            size--;
            if (next == nullptr) {
                if (current->parent == nullptr) {
                    root = current->right;
                    if(root != nullptr)
                        root->parent = nullptr;
                }
                else {
                    current->parent->left = current->right;
                }
                delete current;
            }
            return val;
        }
        else {
            return dequeue(current->left);
        }
    }
    NODE* getNext(NODE* current, int priority) {

        stack<NODE*> stk;
        vector<NODE*> inoder;

        while (current!= nullptr || !stk.empty()) {
            if (current== nullptr) {
                NODE* n = stk.top(); stk.pop();
                inoder.push_back(n);
                current= current->right;
            }
            else {
                stk.push(current);
                current= current->left;
            }
        }

        for (int i = 0; i < inoder.size(); i++) {
            if (inoder[i]->priority > priority)
                return inoder[i];
        }
        return nullptr;

    }
    void getString(NODE* current, string& str, int& ct) {
        if (current== nullptr) {
            return;
        }
        getString(current->left, str, ct);
        NODE* lnk = current->link;
        while (lnk != nullptr) {
            stringstream ss;
            ss << lnk->value;
            str += to_string(ct) + " value: " + ss.str() + "\n";
            lnk = lnk->link;
        }
        ct++;
        getString(current->right, str, ct);
        
    }
    bool compare(NODE* c1, NODE* c2) const {
        if (c1 == nullptr || c2 == nullptr)
            return c1 == nullptr && c2 == nullptr;
        bool res1 = compare(c1->left, c2->left);

        NODE* l1 = c1->link, l2 = c2->link;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->priority != l2->priority || l1->value != l2->value)
                return false;
        }
        res1 = l1 == nullptr && l2 == nullptr;
        bool res2 = compare(c1->right, c2->right);

        return res1 && res2;
    }
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        
        root = nullptr;
        size = 0;
        curr = nullptr;
        
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        clear();
        copy(other.root);
        // TO DO: write this function.
        return *this;
    }


    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        
        
        // TO DO: write this function.
        while (size > 0) {
            dequeue();
        }
        root = nullptr;
        curr = nullptr;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        
        
        // TO DO: write this function.
        clear();
        
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        
        // TO DO: write this function.
        NODE* newNode = initNode(value, priority);

        if (root == nullptr) {
            NODE* n = initNode(value, priority);
            n->link = newNode;
            size++;
            root = n;
        }
        else {
            enqueue(root, newNode);
        }
    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        
        if (root == nullptr) {

            return T();
        }
        else {
            return dequeue(root);
        }
        
        
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        
        
        return size; // TO DO: update this return
        
        
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        
        
        // TO DO: write this function.
        curr = root;
        while (curr != nullptr && curr->left != nullptr)
            curr = curr->left;

        curr = curr->link;
        
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        
        if (curr == nullptr)
            return false;

        value = curr->value;
        priority = curr->priority;
        
        NODE* next = curr->link;

        if (next == nullptr) {
            curr = getNext(root, curr->priority);
            if (curr != nullptr) {
                curr = curr->link;
            }
        }
        else {
            curr = next;
        }

        
    
        return true; // TO DO: update this return
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        
        
        // TO DO: write this function.
        string str = "";
        int ct = 1;
        getString(root, str, ct);

        return str; // TO DO: update this return
        
        
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        
       
        T valueOut;
        if(root == nullptr)
            return valueOut; 
        NODE* n = root;
        while (n->left != nullptr)
            n = n->left;

        return n->link->value;
        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        return compare(root, other.root);
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
