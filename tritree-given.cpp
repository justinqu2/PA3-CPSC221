/**
 * @file tritree-given.cpp
 * @author CPSC 221
 * @description TriTree partial class implementation, CPSC 221 PA3
 *
 * This file will not be submitted for grading.
 *
**/

#include "tritree.h"

// TriTree destructor, given.
TriTree::~TriTree() {
	Clear();
}

// TriTree copy constructor, given.
TriTree::TriTree(const TriTree& other) {
	Copy(other);
}

// TriTree assignment operator, given.
TriTree& TriTree::operator=(const TriTree& rhs) {
	if (this != &rhs) {
		Clear();
		Copy(rhs);
	}
	return *this;
}