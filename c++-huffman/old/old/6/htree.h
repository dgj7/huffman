/******************************************************************************
	EARLY ALPHA VERSION OF HUFFMAN TREE CODE (NOT YET A WORKING BUILD).
	Notes:
		-it appears that in no case can a tree/leaf/intnode be created without
			parameter data for the constructor.  it wouldnt make much sense.






******************************************************************************/

#ifndef __HUFFMAN__CODING__TREE__DG__H__
#define __HUFFMAN__CODING__TREE__DG__H__

#include <vector>
#include <utility>		// for std::pair<T1, T2>

typedef unsigned long int ulint;
typedef std::pair<ulint, char> freqpair;

//=============================================================================
//
//=============================================================================
class HNode
{
public:
	virtual ulint frequency(  ) const = 0;
	virtual bool is_leaf(  ) const = 0;
};

//=============================================================================
//
//=============================================================================
class HLeaf: public HNode
{
public:
	HLeaf( char, ulint );
	ulint frequency(  ) const { return _freq;}
	bool is_leaf(  ) const { return true; }
	
private:
	char _data;
	ulint _freq;
};

//=============================================================================
//
//=============================================================================
class HInternal: public HNode
{
public:
	HInternal( ulint weight ):_weight( weight ) {  }
	ulint frequency(  ) const { return _weight; }
	bool is_leaf(  ) const { return false; }
private:
	ulint _weight;
	HNode *left;
	HNode *right;
};

//=============================================================================
//
//=============================================================================
class HTree
{
public:
	HTree( char data, ulint frequency )
	{
		_root = new HLeaf( data, frequency );
	}
	
	ulint frequency(  ) const;
private:
	HNode *_root;
};

//=============================================================================
// HUFFMAN CODING TREE
// The class that will, in the end, be visible to and usable by the client.
// Will manage tree creation, adding of data, and rendering of huffman codes.
//=============================================================================
class HuffmanTree
{
public:
	HuffmanTree( /*std::vector<std::pair<char, ulint> >*/ )
	{
		keepPushingData = true;
		rawFrequencyData.clear(  );
		treeData.clear(  );
	}
	
	// Add a data item to the tree.  If the item exists, it's frequency
	// portion is simply incremented.  This data that is inserted is
	// first inserted into a std::vector<std::pair<char, ulint> > of
	// chars and ulints.  After done_pushing_data is called, the data
	// is built into a tree, and other functions can then be called.
	void insert( char input )
	{
        freqpair fpinput( 0, input );        

		// if we're done inserting frequency data, do nothing
		if( !keepPushingData )
        {
			return;
        }
		else
		{
            // GENERAL ALGORITHM:
			// insert input into rawFrequencyData in the following way:
			// 1) check to see if input already exists in the array (search)
			// 2a) if not, push_back( input )
			// 2b) if so, get the old data (pair) from the array 
			//	(store it outside the array), delete that data
			//	from the array, increment the frequency
			//	value for that item, and reinsert it into the array.
			// 3) sort the array so it's ready for next iteration
			
			// Step 1: does it already exist in the array?
            // someiterator = rawFrequencyData.find( fpinput )

            // Step 2:
			
			// Step 3: sort the data.
            sort( rawFrequencyData.begin(  ), rawFrequencyData.end(  ) );
		}
	}
	
	// Tell the system we dont want to insert any more data from input stream.
	void done_pushing_data(  )
	{
		keepPushingData = false;
	}
	
	//
	
private:
	bool keepPushingData;
	std::vector<freqpair> rawFrequencyData;
	std::vector<HTree> treeData;
	
	// Utility functions
	void build_tree(  );
	HTree combine_trees( HTree &, HTree & );
};


#endif
