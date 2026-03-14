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
	// REPLACE THE LINEs BELOW WITH YOUR CODE
	width = 0;
	height = 0;
	root = nullptr;
}

void TriTree::Clear() {
	// YOUR CODE HERE
}

void TriTree::Copy(const TriTree& other) {
	// YOUR CODE HERE
}

PNG TriTree::Render() const {
	// REPLACE THE LINE BELOW WITH YOUR CODE
	return PNG();
}

void TriTree::Transpose() {
	// YOUR CODE HERE
}

void TriTree::Prune(double tol) {
	// YOUR CODE HERE
}

int TriTree::NumLeaves() const {
	// REPLACE THE LINE BELOW WITH YOUR CODE
	return 0;
}

Node* TriTree::BuildNode(PNG& im, pair<int, int> ul, int w, int h) {
	// REPLACE THE LINE BELOW WITH YOUR CODE
	return nullptr;
}

/*==== ALSO IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE DECLARED ====*/