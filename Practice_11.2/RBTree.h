#ifndef RBT_H
#define RBT_H
#include <iostream>
#include <string>
#include <functional>
using namespace std;
template <typename T, typename Compare = less<T>>
class RBTree {

private:
	enum Color { RED, BLACK };
	struct Node {
		T key;
		Color color;
		Node* left;
		Node* right;
		Node* parent;
		Node(const T& k)
			: key(k), color(RED),
			left(nullptr), right(nullptr), parent(nullptr) {
		}
	};
	Node* root;  
	Node* nil;  
	Compare comp; 

public:
	RBTree() : comp(Compare()) {
		nil = new Node(T{}); 
		nil->color = BLACK;
		nil->left = nil;
		nil->right = nil;
		nil->parent = nil;
		root = nil;
	}
	~RBTree() {
		clear(root);
		delete nil;
	} 
	Node* getRoot() const { return root; }
	void printRBT() const {
		Node* _root = getRoot();
		_printRBT(_root, 0);
	}
	void inorderPrint() const {
		inorderPrint(root);
		cout << endl;
	}
	RBTree(const RBTree&) = delete;
	RBTree& operator=(const RBTree&) = delete;
	void inorderPrint(Node * node) const {
		if (node == nil) return;
		inorderPrint(node->left);
		cout << node->key << " ";
		inorderPrint(node->right);
	}
	bool contains(const T& key) const {
		return findNode(key) != nil;
	}
	void transplant(Node* u, Node* v) {
		if (u->parent == nil) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}
	Node* treeMinimum(Node* x) const {
		while (x->left != nil) {
			x = x->left;
		}
		return x;
	}
	void insert(const T& key) {
		Node* z = new Node(key);
		z->left = z->right = z->parent = nil;
		Node* y = nil;
		Node* x = root;
	 
		while (x != nil) {
			y = x;
			if (comp(z->key, x->key)) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y == nil) {  
			root = z;
		}
		else if (comp(z->key, y->key)) {
			y->left = z;  
		}
		else {
			y->right = z;  
		}
		z->color = RED; _insertFixup(z);
	}
	void erase(const T& key) {
		Node* z = findNode(key);
		if (z == nil) {
			return;
		}
		eraseNode(z);
	}

private:
	void _printRBT(Node * node, int depth) const {
		if (node == nil) return;
		_printRBT(node->right, depth + 1);
		for (int i = 0; i < depth; ++i) {
			cout << " ";  
		}
		cout << node->key << (node->color == RED ? " (R)" : " (B)") << "\n";
		_printRBT(node->left, depth + 1);
	}

	bool equalKey(const T& a, const T& b) const {
		return !comp(a, b) && !comp(b, a);
	} 
	Node* findNode(const T& key) const {
		Node* x = root;
		while (x != nil) {
			if (equalKey(key, x->key)) {
				return x;
			}
			else if (comp(key, x->key)) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		return nil;
	} 
	void clear(Node* node) {
		if (node == nil)
			return;
		clear(node->left);
		clear(node->right);
		delete node;
	} 
	void _rotateLeft(Node* x) {
		Node* y = x->right;  
		x->right = y->left;
		if (y->left != nil) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	void _rotateRight(Node* y) {
		Node* x = y->left;
		y->left = x->right;
		if (x->right != nil) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nil) {
			root = x;
		}
		else if (y == y->parent->right) {
			y->parent->right = x;
		}
		else {
			y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	}
	void _insertFixup(Node* z) {
		while (z->parent->color == RED) {
			if (z->parent == z->parent->parent->left) {
				Node* u = z->parent->parent->right;  
				if (u->color == RED) {
					z->parent->color = BLACK;
					u->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {  
					if (z == z->parent->right) {
						 
						z = z->parent; _rotateLeft(z);
					}
					 
					z->parent->color = BLACK;
					z->parent->parent->color = RED; _rotateRight(z->parent->parent);
				}  
			}  
			else { 
				Node* u = z->parent->parent->left;
				if (u->color == RED) {
					z->parent->color = BLACK;
					u->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {  
					if (z == z->parent->left) {
						z = z->parent; _rotateRight(z);
					} 
					z->parent->color = BLACK;
					z->parent->parent->color = RED; _rotateLeft(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	} 
	void eraseNode(Node* z) {
		Node* y = z;
		Node* x;
		Color yOriginalColor = y->color;
		if (z->left == nil) {  
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == nil) {  
			x = z->left;
			transplant(z, z->left);
		}
		else {  
			y = treeMinimum(z->right); 
			yOriginalColor = y->color; x = y->right;
			if (y->parent == z) {  
				x->parent = y;
			}
			else {  
				transplant(y, y->right); y->right = z->right; y->right->parent = y;
			}
			transplant(z, y); y->left = z->left; y->left->parent = y; y->color = z->color;
		}
		delete z;
		if (yOriginalColor == BLACK) { _eraseFixup(x); }
	}
	void _eraseFixup(Node* x) {
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {  
				Node* w = x->parent->right;  
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED; _rotateLeft(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK &&
					w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED; _rotateRight(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK; _rotateLeft(x->parent);
					x = root;
				}
			}
			else {  
				Node* w = x->parent->left;  
				if (w->color == RED) { 
					w->color = BLACK;
					x->parent->color = RED; _rotateRight(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK &&
					w->left->color == BLACK) { 
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left->color == BLACK) { 
						w->right->color = BLACK;
						w->color = RED; _rotateLeft(w);
						w = x->parent->left;
					} 
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK; _rotateRight(x->parent);
					x = root;
				}
			}  
		}  
		x->color = BLACK;
	}
}; 
#endif