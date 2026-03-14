/**
 * @file tritree.h
 * @author CPSC 221
 * @description TriTree class declaration, CPSC 221 PA3
 * 
 * This file will NOT be submitted for grading.
 *
**/

#ifndef _TRITREE_H_
#define _TRITREE_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"

using namespace std;
using namespace cs221util;

/**
 * The Node class is normally made private to the tree class via the principle of
 * encapsulation---the end user does not need to know our node-based
 * implementation details.
 * For PA3, this class will be made public.
**/
class Node {
	public:
		pair<int, int> upperleft;	// upper-left coordinates of Node's subimage
		int width;		 // horizontal dimension of Node's subimage in pixels
		int height;      // vertical dimension of Node's subimage in pixels
		RGBAPixel avg;   // Average color of Node's subimage
		Node* A;	     // ptr to left or upper subtree
		Node* B;	     // ptr to middle subtree
		Node* C;	     // ptr to right or lower subtree
		
		// Node constructors
		Node(pair<int, int> ul, int w, int h) : upperleft(ul), width(w), height(h), A(NULL), B(NULL), C(NULL) { }
};

/**
 * Ternary Tree: This is a structure used in decomposing an image
 * into rectangular regions of similarly colored pixels.
 *
 * You should not remove anything from this class definition, but if
 * you find it helpful to add your own private helper functions,
 * you can add them to tritree-private.h.
**/

class TriTree {
	public:

		/* =============== start of given functions ====================*/

		/**
		 * TriTree destructor.
		 * Destroys all of the memory associated with the
		 * current TriTree. This function should ensure that
		 * memory does not leak on destruction of a TriTree.
		 *
		 * @see TriTree.cpp
		**/
		~TriTree();

		/**
		 * Copy constructor for a TriTree.
		 * Since TriTree allocates dynamic memory (i.e., they use "new", we
		 * must define the Big Three). This uses your implementation
		 * of the copy funtion.
		 * @see tritree.cpp
		 *
		 * @param other = the TriTree we are copying.
		**/
		TriTree(const TriTree& other);

		/**
		 * Overloaded assignment operator for TriTree.
		 * Part of the Big Three that we must define because the class
		 * allocates dynamic memory. This uses your implementation
		 * of the copy and clear funtions.
		 *
		 * @param rhs = the right hand side of the assignment statement.
		**/
		TriTree& operator=(const TriTree& rhs);

		/* =============== end of given functions ====================*/

		/* =============== public PA3 FUNCTIONS =========================*/

		/**
		 * Constructor that builds a TriTree out of the given PNG.
		 *
		 * The TriTree represents the subimage from (0,0) to (w-1, h-1) where
		 * w-1 and h-1 are the largest valid image coordinates of the original PNG.
		 * Every node corresponds to a rectangle of pixels in the original PNG,
		 * represented by an (x,y) pair for the upper left corner of the
		 * square and two integers for the number of pixels on the width and
		 * height dimensions of the rectangular region the node defines.
		 *
		 * The node's three children correspond to a partition
		 * of the node's rectangular region into three approximately equal-size strips.
		 *
		 * If the rectangular region is taller than it is wide, the region is divided
		 * into horizontal strips:
		 *  +-------+
		 *  |   A   |
		 *  |       |
		 *  +-------+
		 *  |   B   |
		 *  |       |    (Split tall)
		 *  +-------+
		 *  |   C   | 
		 *  |       |
		 *  +-------+
		 * 
		 * If the rectangular region is wider than it is tall, the region is divided
		 * into vertical strips:
		 *  +---------+---------+---------+
		 *  |    A    |    B    |    C    |
		 *  |         |         |         |    (Split wide)
		 *  +---------+---------+---------+
		 * 
		 * Your regions are not guaranteed to have dimensions exactly divisible by 3.
		 * If the dimensions of your rectangular region are 3p x q or q x 3p where 3p
		 * represents the length of the long side, then your rectangular regions will
		 * each have dimensions p x q (or q x p)
		 * 
		 * If the dimensions are (3p+1) x q, subregion B gets the extra pixel of size
		 * while subregions A and C have dimensions p x q.
		 * 
		 * If the dimensions are (3p+2) x q, subregions A and C each get an extra pixel
		 * of size, while subregion B has dimensions p x q.
		 * 
		 * If the region to be divided is a square, then apply the Split wide behaviour.
		 * 
		 * Every leaf in the constructed tree corresponds to a pixel in the PNG.
		 *
		**/
		TriTree(PNG& imIn);

		/**
		 * Render returns a PNG image consisting of the pixels
		 * stored in the tree. It may be used on pruned trees. Draws
		 * every leaf node's rectangle onto a PNG canvas using the
		 * average color stored in the node.
		**/
		PNG Render() const;

		/**
		 * Rearranges the nodes and their pixel data so that the rendered
		 * tree appears to be transposed over a diagonal axis. See the example on
		 * PrairieLearn for details.
		**/
		void Transpose();

		/**
		 * Prune function trims subtrees as high as possible in the tree.
		 * A subtree is pruned (cleared) if all of its leaves are within
		 * tol of the average color stored in the root of the subtree.
		 * Pruning criteria should be evaluated on the original tree
		 * or a transposed tree, but not on a pruned subtree.
		 * (we only expect that trees would be pruned once.)
		 *
		 * You may want a recursive helper function for this.
		**/
		void Prune(double tol);

		/**
		 * Returns the number of leaf nodes in the tree.
		 * 
		 * You may want a recursive helper function for this.
		**/
		int NumLeaves() const;

		/* =============== end of public PA3 FUNCTIONS =========================*/

	private:
		/**
		 * Private member variables.
		 *
		 * You must use these as specified in the spec and may not rename them.
		 * You may add more if you need them.
		**/
		Node* root;  // pointer to the root of the TriTree
		int width;   // width of PNG represented by the tree
		int height;  // height of PNG represented by the tree

		/* =================== private PA3 functions ============== */

		/**
		 * Destroys all dynamically allocated memory associated with the
		 * current TriTree object. To be completed for PA3.
		 * You may want a recursive helper function for this one.
		**/
		void Clear();

		/**
		 * Copies the parameter other TriTree into the current TriTree.
		 * Does not free any memory. Called by copy constructor and operator=.
		 * You may want a recursive helper function for this one.
		 * @param other The TriTree to be copied.
		**/
		void Copy(const TriTree& other);

		/**
		 * Private helper function for the constructor. Recursively builds
		 * the tree according to the specification of the constructor.
		 * @param im reference image used for construction
		 * @param ul upper left point of node to be built's rectangle.
		 * @param w width of node to be built's rectangle.
		 * @param h height of node to be built's rectangle.
		**/
		Node* BuildNode(PNG& im, pair<int, int> ul, int w, int h);

		/* =================== end of private PA3 functions ============== */

		/****************************************************
		* IF YOU WITH TO DEFINE YOUR OWN PRIVATE FUNCTIONS, *
		* ADD YOUR DEFINITIONS TO tritree-private.h         *
		****************************************************/

		#include "tritree-private.h"
};

#endif