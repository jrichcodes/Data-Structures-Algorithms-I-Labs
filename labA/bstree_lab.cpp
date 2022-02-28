//File: bstree_lab.cpp
//Name: Josephine Rich
//Date: 11/12/2021

//Description: Wrote some functions for a binary search tree

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

int BSTree::Depth(const string &key) const
{
  BSTNode *n;
  int depth = 0;

  n = sentinel->right;
  while(1) {
	  if(n == sentinel) return -1;			/*didn't find key*/
	  if(key == n->key) return depth;		/*found key*/ 
	  if(key < n->key) {					/*deciding which way to go by comparing key values*/
		n = n->left;
		depth += 1;							/*adding to the depth while movie farther down the tree*/
	  }
	  else {
		n = n->right;
		depth += 1;
	  }
  }
  return -1;
}
           
int BSTree::Height() const
{
  return recursive_find_height(sentinel->right);
}

vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right, rv);
  return rv;
}
    
BSTree::BSTree(const BSTree &t)        
{
	/*creating a new sentinel node and setting all the data*/
	sentinel = new BSTNode;
	sentinel->parent = sentinel;
	sentinel->left = sentinel;
	sentinel->right = sentinel;
	sentinel->key = "---SENTINEL---";
	sentinel->val = sentinel;
	size = 0;

	/*calling assignment overload*/
	*this = t;
}

BSTree& BSTree::operator= (const BSTree &t) 
{
	vector <string> keys;
	vector<void *> vals;
	size_t num_indices;
	
	Clear();
	keys = t.Ordered_Keys();
	vals = t.Ordered_Vals();
	num_indices = t.Size();
	/*setting the sentinel right pointer to the balanced tree copy*/
	sentinel->right = make_balanced_tree(keys, vals, 0, num_indices);
	/*setting the size for the copy*/
	size = t.Size();

	return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const
{
  int lheight, rheight, height = 0;
  if(n == sentinel) return height; /*base case- sentinel doesn't have any parents*/
  else {
	  lheight = recursive_find_height(n->left);	  /*finding the heights of the subtrees*/
	  rheight = recursive_find_height(n->right);
	  if(lheight > rheight) {                     /*returning the bigger height*/
		  return height = (lheight += 1);
	  }
	  else {
		  return height = (rheight += 1);
	  }
  }
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
	/*inorder traveral that vists each modes in sorted order of the keys*/
	if(n== sentinel) return; 
	make_key_vector(n->left, v);
	v.push_back(n->key);			/*pushing back on to vector with key*/
	make_key_vector(n->right, v);
}

BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
                            const vector<void *> &vals,
                            size_t first_index,
                            size_t num_indices) const
{ 
	int middle;
	BSTNode *root;

	/*making the middle the root*/

	middle = first_index + (num_indices/2);

	root = new BSTNode;
	root->parent = sentinel; 
	root->val = vals[middle];
	root->key = sorted_keys[middle];

	/*base case*/
	if(num_indices == 1) {      /*at last node*/
		root->left = sentinel;
		root->right = sentinel;
		return root;
	}

	/*recursively call function to make left subtree*/
	root->left = make_balanced_tree(sorted_keys, vals, first_index, num_indices/2);
	root->left->parent = root;
	
	/*only make rihgt subtrees if there are 3 or more indices*/
	if(num_indices > 2) {
		/*recusivley call function to make right subtree*/
		root->right = make_balanced_tree(sorted_keys, vals, middle+1, ((num_indices + first_index) -(middle+1)));
		root->right->parent = root;
	}
	else {
		root->right = sentinel;
	}

  return root;
}
