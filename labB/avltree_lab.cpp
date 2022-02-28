//File: avltree_lab.cpp
//Name: Josephine Rich
//Date: 11/23/2021

//Description: implementation for AVL tree which is a binary tree that is balanced 
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS202::AVLTree;
using CS202::AVLNode;

bool imbalance(const AVLNode *n) {
	int lh, rh;
	lh = n->left->height; /*left child's height*/
	rh = n->right->height; /*right child's height*/

	if(n->height < 3) return false;
	if(((lh - rh) > 1) || ((lh - rh) < -1)) { /*children's height differs by more than 1*/
		return true;
	}
	else return false;
}

void fix_height(AVLNode *n);
void rotate(AVLNode *n) {
	AVLNode *parent;
	AVLNode *grandparent;
	AVLNode *middle; /*the other child of the given node*/

	parent = n->parent; 
	if(parent->height == 0) return;  //node is the root of the tree
	grandparent = parent->parent;

	n->parent = grandparent; /*settting the given node's parent to be the grandparent*/
	
	//checking if the parent is the left or right child of grandparent and n to point back
	if(grandparent->left == parent) grandparent->left = n;
	else grandparent->right = n;

	if(n->key > parent->key) { /*n is right child of parent*/
		middle = n->left; 
		n->left = parent; /*making parent n's child*/
		parent->parent = n; 
		parent->right = middle; /*switching middle's parent */
		if(middle->height != 0) middle->parent = parent; /*making sure the middle is not sentinel*/
	}
	else { /*n is left child of parent*/
		middle = n->right; 
		n->right = parent; /*making parent n's child*/
		parent->parent = n; 
		parent->left = middle; /*swiching middle's parent*/
		if(middle->height != 0) middle->parent = parent;
	}
	fix_height(parent); /*fixing heights of parent and n order does matter!*/
	fix_height(n);
}

void fix_height(AVLNode *n) {
	if(n->left->height > n->right->height) {
		n->height = n->left->height + 1; /*left height is greater*/
	}
	else {
		n->height = n->right->height + 1; /*right height is greater*/
	}
}

void fix_imbalance(AVLNode *n) {
	
	if(n->left->height == n->height-1) {
		if(n->left->left->height == n->height-2) { //left-left
			rotate(n->left); 
		}
		else{ //left-right
			rotate(n->left->right);
			rotate(n->left);
		}
	}
	else{
		if(n->right->right->height == n->height-2) {//right-right
			rotate(n->right);
		}
		else {//right-left
			rotate(n->right->left);
			rotate(n->right);
		}
	}

}
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
  Clear();
  sentinel->right = recursive_postorder_copy(t.sentinel->right);
  sentinel->right->parent = sentinel;
  size = t.Size();

  return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;
  AVLNode *temp;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->height = 1;
  n->left = sentinel;
  n->right = sentinel;

  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  /* Increment the size */

  size++;

  /*going up to the root and changing the heights and finding imbalances*/
	temp = n;
  while(temp != sentinel) { 
		fix_height(temp);
		if(imbalance(temp) == true) {
			fix_imbalance(temp);
			return true;
		}
		temp = temp->parent;
	}


  return true;
}
    
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc, *temp;
  string tmpkey;
  void *tmpval;

  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
    return true;
  }

  /*traveling from parent of node to the root to check for imbalance and adjusting height*/
	temp = n->parent;	
  while(temp != sentinel) {
		fix_height(temp);
		if(imbalance(temp) == true) fix_imbalance(temp);
		temp = temp->parent;
	}


  return true;
}
               
/* You need to write these two.  You can lift them verbatim from your
   binary search tree lab. */

vector <string> AVLTree::Ordered_Keys() const
{
  vector<string> rv;
  make_key_vector(sentinel->right, rv);
  return rv;
  
}
    
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{
	if(n==sentinel) return;
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}
     
size_t AVLTree::Height() const
{
  return sentinel->right->height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
	AVLNode *node;

	if(n->height == 0) { /*is the sentinel*/
		return sentinel;
	}

	node = new AVLNode;
	node->key = n->key;
	node->val = n->val;
	node->height = n->height;

	node->left = recursive_postorder_copy(n->left); /*copying left subtree*/
	node->left->parent = node; /*setting parent pointer back up to node*/
	node->right = recursive_postorder_copy(n->right); /*copying right subtree*/
	node->right->parent = node; /*setting parent pointer back up to node*/

	return node;
}
