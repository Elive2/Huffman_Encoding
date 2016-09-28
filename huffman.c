/*File huffman.c
  *
  *Eli Yale
  *coen 12 lab 5:15 tues
  *TA Jesse Hardy
  *Project 5
  *May 16, 2016
  *
  *Description: This file contains the the implementation
  *a huffman coding technique. It builds the huffman code 
  *from text in a text file. It counts character occurnces,
  *inserts these characters into a priority queue, and uses
  *this queue to build a binary tree bottom up;
  *
  *It then generates a binary representation of each letter
  *accordingly, and displays this.
  *
  *Notes:
  *check all asserts
  *Do bitstring need to match what he has??//ar mine correct
  *
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#define TREE struct tree
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2 + 1)
#define r(x) ((x)*2 + 2)

/*the nodes of the binary tree*/

struct tree {
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
};

/*three arrays are maintaned golabblly for ASCII character
  *counts, binary heap of trees, and array of leaves.
*/

int counts[257]; //coresponds to ascii value
struct tree *heap[257];
struct tree *leaves[257];
int count = 0;

/*Function Declerations*/

void insert(struct tree *treeIn);
void removeMin(); //finish decleration
void shiftUp(int crntSlot);
void shiftDown(int crntSlot);
void build(void);
void preorder(struct tree *t);
void print(struct tree *t);

/* Function: MAin
   *
   *Description: The main funtion handles file input, and calls to build
   *the heap and the binary trees.
*/

int main(int argc, char *argv[]) {
	FILE *infp;
	int i, j, m;
	char c = 'a';


	for (i = 0; i < 257; i++) {
		counts[i] = 0;
		leaves[i] = NULL;
		heap[i] = NULL;
	}

	/*makes sure file usage is correct*/

	if (argc != 3) {
		printf("please specify two files\n");
		exit(EXIT_FAILURE);
	}

	if ((infp = fopen(argv[1], "r")) == NULL) {
		printf("the file could not be opened\n");
		exit(EXIT_FAILURE);
	}

	while (c!= EOF) {
		c = fgetc(infp);
		counts[(int)c] += 1;
	}

	for (j = 0; j < 257; j++) {
		if (counts[j] != 0) {
			leaves[j] = createTree(counts[j], NULL, NULL);
		}
	}

	leaves[256] = createTree(0, NULL, NULL);
	

	for (m = 0; m < 257; m++) {
		if (leaves[m] != NULL) {
			insert(leaves[m]);
		}
	}

	build();


	for (int y = 0; y < 257; y++) {
		if (leaves[y] != NULL) {
			if (isprint(y)) {
				printf("'%c': %d ", y, getData(leaves[y]));
			}

			else {
				printf("%.3o: %d ", y, getData(leaves[y]));
			}

			print(leaves[y]);
			printf("\n");
		}
	}

	pack(argv[1], argv[2], leaves);

	destroyTree(heap[0]);

exit(EXIT_SUCCESS);

}

/*Function: insert
  *
  *Description: inserts into priority queue (binary heap array)
  *
*/

void insert(struct tree *treeIn) {
	assert(treeIn != NULL);
	
	heap[count++] = treeIn;
	shiftUp(count-1);
	
	return;

	
}

/*Function: shiftUp
  *
  *Description: Recursive function to shift nodes if they are larger
  *than their parent to maintian the binary heap property of the 
  *priority queue. Used by insert.
*/

void shiftUp(int crntSlot) {
	int parentIndex;
	struct tree *tmp;

	if(crntSlot != 0) {
		parentIndex = p(crntSlot);

		if (getData(heap[parentIndex]) > getData(heap[crntSlot])) {
			tmp = heap[parentIndex];
			heap[parentIndex] = heap[crntSlot];
			heap[crntSlot] = tmp;
			shiftUp(parentIndex);
		}
	}

	return;
}

/*Fucntion: removeMin
  *
  *Description: deletes the highest priority node in the binary heap
*/

void removeMin(void) {
	if (count == 0) {
		
		return;
	}

	heap[0] = heap[--count];
	heap[count+1] = NULL;

	if (count > 0)
		shiftDown(0);
	
	return;
}

/*Funciton: shiftDown
  *
  *Description: Recursive function to shift the root node down
  *in the binary heap. Used by removeMin.
*/

void shiftDown(int crntSlot) {
	int leftChildIndex, rightChildIndex, minIndex;
	struct tree *temp;
	leftChildIndex = l(crntSlot);
	rightChildIndex = r(crntSlot);
	
	if (rightChildIndex >= count)  {
		
		if(leftChildIndex >= count)
		
			return;
		
		else
			minIndex = leftChildIndex;
	}

	else {
		
		if (getData(heap[leftChildIndex]) <= getData(heap[rightChildIndex]))
			minIndex = leftChildIndex;
		
		else
			minIndex = rightChildIndex;
	}

	if (getData(heap[crntSlot]) > getData(heap[minIndex])) {
			temp = heap[minIndex];
			heap[minIndex] = heap[crntSlot];
			heap[crntSlot] = temp;
			shiftDown(minIndex);
	}

	return;
}

/*Function: build
  *
  *Description: This function handles the assembly of the huffman tree
  *by taking the two lowest priority trees and combining them
  *as roots of a new tree.
*/

void build(void) {
	while(count > 1) {
		struct tree *leftSub = heap[0];
		int leftData = getData(heap[0]);
		removeMin();
		struct tree *rightSub = heap[0];
		int rightData = getData(heap[0]);
		removeMin();

		struct tree *new = createTree(leftData + rightData, leftSub, rightSub);

		insert(new);
	}

	return;
}

/*Function: print
  *
  *This function provides the formated printing of each leaf of the huffman tree
  *ands its corresponding bitcode. It is recursive traversing from the leave up
  *then printing a 0 if left, and 1 if right on the return back down.
*/

void print(struct tree *tree) {
	if (getParent(tree) == NULL) {
		return;
	}

	print(getParent(tree));

	if(getLeft(getParent(tree)) == tree) {
		printf("1");
	}

	else
		printf("0");
}


	
	

