#ifndef __HUFFMAN__CODING__LIBRARY__DG__H__
#define __HUFFMAN__CODING__LIBRARY__DG__H__

#include <list>

typedef char __datatype;
typedef unsigned long int ulint;

////===========================================================================
////		FREQUENCY PAIR
////===========================================================================

class FrequencyPair
{
public:
	FrequencyPair( const __datatype &, ulint );
	~FrequencyPair(  );

	ulint weight(  );
	__datatype &getData(  );
private:
	__datatype _data;
	ulint _freq;
};


////===========================================================================
////		NODES
////===========================================================================
class HNode
{
public:
	virtual ulint weight(  ) = 0;
	virtual bool isLeaf(  ) = 0;
	virtual HNode *left(  ) const = 0;
	virtual HNode *right(  ) const = 0;
	virtual void setLeft( HNode * ) = 0;
	virtual void setRight( HNode * ) = 0;
};

class HLeaf: public HNode
{
public:
	HLeaf( const __datatype &, ulint );

	~HLeaf(  );

	ulint weight(  );
	FrequencyPair *getPair(  );
	bool isLeaf(  );

	virtual HNode *left(  ) const;
	virtual HNode *right(  ) const;

	virtual void setLeft( HNode * );
	virtual void setRight( HNode * );

private:
	FrequencyPair *_data;
};

class HIntl: public HNode
{
public:
	HIntl( HNode *, HNode * );

	ulint weight(  );
	bool isLeaf(  );

	virtual HNode *left(  ) const;
	virtual HNode *right(  ) const;

	virtual void setLeft( HNode * );
	virtual void setRight( HNode * );
private:
	HNode *_left;
	HNode *_right;
	ulint _frequency;
};


////===========================================================================
////		TREE
////===========================================================================

class HTree
{
	friend class HList;
public:
	HTree( __datatype &, ulint );
	HTree( HTree *, HTree * );

	~HTree(  );

	HNode *getRoot(  );
	ulint weight(  );
private:
	HNode *_root;
};


////===========================================================================
////		HUFFMAN LIST -- for ordering input and building tree
////===========================================================================

class HList
{
public:
	HList(  );

	//HTree *buildTree(  );
	void push( __datatype, ulint );
	//void combineTrees(  );			// combines first two trees automatically

	//size_t size(  ) const;

private:
	std::list<HTree> _hfl;
};


#endif
