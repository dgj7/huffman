#ifndef __HUFFMAN__CODING__LIBRARY__DG__H__
#define __HUFFMAN__CODING__LIBRARY__DG__H__

#include <list>

typedef char __datatype;
typedef unsigned long int ulint;

class HNode
{
public:
	HNode( ulint );					// for leaf node
	HNode( ulint, __datatype );		// for internal node



	__datatype _data;
	ulint _weight;
	bool leaf;
	HNode *_left, *_right, *_parent;
};

class HTree
{
	friend class HList;
public:
	HTree( HNode );

	ulint size(  );					// # of elements in the tree




private:
	HNode *_root;
};

class HList
{
public:
	HList(  );

	HTree buildTree(  );
	void push( ulint, __datatype );
	void combineTrees(  );			// combines first two trees automatically

	size_t size(  ) const;

private:
	std::list<HTree> _hfl;
};





#endif
