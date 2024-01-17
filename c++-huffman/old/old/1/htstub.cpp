#include <iostream>
#include <string>
#include <list>

#include "htree.h"

void print_line( std::string );

int main( int argc, char **argv )
{
	print_line( "making single-node trees" );
	HTree atree( 'A', 20 );
	HTree btree( 'B', 30 );
	atree.print_contents_inorder(  );
	btree.print_contents_inorder(  );
	
	print_line( "combining the above two trees into a new tree" );
	HTree abtree( atree, btree );
	abtree.print_contents_inorder(  );
	
	print_line( "creating list of trees nao" );
	std::list<HTree> hlist;
	hlist.push_back( atree );
	hlist.push_back( btree );

	
	
	std::cout << "\n\nDONE!!!\n\n";
	return 0;
}

void print_line( std::string message )
{
	std::cout << std::endl;
	for( int i = 0; i < 80; i++ )
		std::cout << "=";
	std::cout << message;
}
