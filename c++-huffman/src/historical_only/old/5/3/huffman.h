#ifndef __HUFFMAN__CODING__DATASTRUCTS__DG__H__
#define __HUFFMAN__CODING__DATASTRUCTS__DG__H__

typedef char __datatype;
typedef unsigned long int ulint;

class HNode
{
public:
	HNode( __datatype, ulint );

	bool isLeaf(  );

//--------------------

	__datatype _data;
	ulint _frequency;

	HNode *left;
	HNode *right;
	HNode *parent;
};

class HTree
{
	friend class HList;
public:
	HTree( __datatype, ulint );
	HTree( HTree *, HTree * );

	~HTree(  );

	ulint weight(  );

private:
	HNode *_root;
};




#endif
