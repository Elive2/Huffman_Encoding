/*File: Tree.c
  *
  *Eli Yale
  *Coen 12 Lab Tues: 5:15
  *TA Jesse Hardy
  *Project 5
  *May 16, 2016
  *
  *Description: This file contains the implementation of a
  *Binary tree data type. Each node has a pointer to
  *its parent, and two children. It provides for such functionality
  *as creation, destruction, insertion, and retrival.
  *The declerations can be found in tree.h
*/

#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#define TREE struct tree

struct tree {
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
};

void cut(struct tree *child) { //cuts parent f=rom child
	assert(child != NULL);
	
	if (child -> parent == NULL) {
	
		return;
	}

	else if (child->parent->left == child) {
		child->parent->left = NULL;
	}

	else {
		child->parent->right = NULL;
	}

	child->parent = NULL;
	
	return;
}



/*Function: createTree
  *
  *Description: Creates a new tree with left and right child pointers to left
  *and right repectfully, whith data,
  *
  *Complexity: O(1)
*/

struct tree *createTree(int data, struct tree *left, struct tree *right) {
	TREE *root =  malloc(sizeof(TREE));
	assert(root != NULL);
	root->data = data;
	root->parent = NULL;
	
	root->left = left;
	root->right = right;

	if (left == NULL && right == NULL) {
	
		return root;
	}

	else if (left != NULL && right == NULL) {
		cut(left);
		root->left->parent = root;
	
		return root;
	}

	else if (left == NULL && right != NULL) {
		cut(right);
		root->right->parent = root;
	
		return root;
	}

	
	else {
		cut(left);
		cut(right);
		root->left->parent = root;
		root->right->parent = root;
	}


	return root;
}

/*Function; destroyTree
  *
  *Description: Deallocates all memory associates with the subtree pointes to by root
  *by iterating through the tree recursively and deleting in postorder
  *
  *Comlexity: O(n)
*/

void destroyTree(struct tree *root) {

	if (root == NULL) {
		return;
	}

	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

/*Funciton: getData
  *
  *Description: returns the data in the root pointed to by root
  *
  *Complexity: O(1)
*/

int getData(struct tree *root) {
	assert(root != NULL);
	
	return root->data;
}

/*Function: getLeft
  *
  *Description: returns the left subtree pointed to by root
  *
  *Complexity: O(1)
*/

struct tree *getLeft(struct tree *root) {
	assert(root != NULL);
	
	return root->left;
}

/*Function: getRight
  *
  *Description: Returns the right subtree pointed to by root
  *
  *Complexity: O(1)
*/

struct tree *getRight(struct tree *root) {
	assert(root != NULL);

	return root->right;
}

/*Funciton: getParent
  *
  *Description: returns the paretn of the subtree pointed to by root
  *
  *Complexity: O(1)
*/

struct tree *getParent(struct tree *root) {
	assert(root != NULL);

	return root->parent;
}

/*Function: setLeft
  *
  *Description: Update the left subtree of root, and pointers
  *
  *Complexity: O(1)
*/

void setLeft(struct tree *root, struct tree *left) {
	assert(root != NULL);
	root->left = left;
	
	if (root->left == NULL) {
	
		return;
	}
	
	root->left->parent = NULL;
	cut(root->left);
	root->left->parent = root;

	return;
}

/*Function: setRight
  *
  *Description: Update the left subtree of root, and pointers
  *
  *Complexity: O(1)
*/

void setRight(struct tree *root, struct tree *right) {
	assert(root != NULL);
	root->right = right;

	if (root->right == NULL) {
		root->right = right;

		return;
	}

	root->right->parent = NULL;
	cut(root->right);
	root->right->parent = root;

	return;
}
