/**
 * @file tritree.cpp
 * @author CPSC 221
 * @description TriTree class implementation, CPSC 221 PA3
 *
 * This file must be submitted for grading.
 *
**/

#include "tritree.h"

TriTree::TriTree(PNG& imIn) {
	width = imIn.width();
	height = imIn.height();
	root = BuildNode(imIn, {0, 0}, width, height);
}

void TriTree::Clear() {
	// YOUR CODE HERE
}

void TriTree::Copy(const TriTree& other) {
	// YOUR CODE HERE
}

PNG TriTree::Render() const {
	PNG renderedImg(width, height); // Empty PNG

	renderImage(renderedImg, root); // Fill in pixels

	return renderedImg;
}

void TriTree::Transpose() {
	// YOUR CODE HERE
}

void TriTree::Prune(double tol) {
	// YOUR CODE HERE
}

int TriTree::NumLeaves() const {
	if (root == nullptr) { // Root for this tree
		return 0;
	}

	return countLeaves(root);
}

Node* TriTree::BuildNode(PNG& im, pair<int, int> ul, int w, int h) {
	// Base case (1 pix)
	if (w == 1 && h == 1) {
		Node* leaf = new Node(ul, w, h);
		leaf->avg = *im.getPixel(ul.first, ul.second);
		return leaf;
	}

	Node* newNode = new Node(ul, w, h);

	pair<int, int> ulA, ulB, ulC;
	int wA, hA, wB, hB, wC, hC;

	// Recursively split
	if (max(w, h) >= 3) {
		splitThree(ul, w, h, ulA, wA, hA, ulB, wB, hB, ulC, wC, hC); // (ulx, uly, w, h) in order (A, C, B)
		newNode->A = BuildNode(im, ulA, wA, hA);
		newNode->B = BuildNode(im, ulB, wB, hB);
		newNode->C = BuildNode(im, ulC, wC, hC);
	}
	else {
		splitTwo(ul, w, h, ulA, wA, hA, ulC, wC, hC); // (ulx, uly, w, h) in order (A, C)
		newNode->A = BuildNode(im, ulA, wA, hA);
		newNode->C = BuildNode(im, ulC, wC, hC);
	}

	newNode->avg = weightedAvg(newNode);

	return newNode;
}

/*==== ALSO IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE DECLARED ====*/