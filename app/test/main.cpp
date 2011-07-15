
#if defined( _WIN32_WCE )
#	include <windows.h>
#	include <stdio.h>
#	include <stdlib.h>
#else
#	include "stdio.h"
#endif

#include "libpslc.h"

int run()
{
	pslc::PVOID pObj = pslc::psl_create( 128, 0x1234, 0, 0 );
	if ( !pObj )
	{	printf( "pslc::create() failed\n" );
		return -1;
	} // end if

	if ( 1 != pslc::psl_get_ref( pObj ) )
	{	printf( "pslc::psl_get_ref() != 1\n" );
		return -1;
	} // end if

	*(unsigned long*)pObj = 0x12345678;
	printf( "Memory at 0x%x -> 0x%x\n", (unsigned long)pObj, (unsigned long)*(unsigned long*)pObj );
	
	printf( "Block type before set = 0x%x\n", (unsigned long)pslc::psl_get_block_type( pObj ) );
	if ( 0x1234 != pslc::psl_get_block_type( pObj ) )
	{	printf( "pslc::psl_get_block_type() != 0x1234\n" );
		return -1;
	} // end if

	pslc::psl_set_block_type( pObj, 0x5678 );	
	
	printf( "Block type after set = 0x%x\n", (unsigned long)pslc::psl_get_block_type( pObj ) );
	if ( 0x5678 != pslc::psl_get_block_type( pObj ) )
	{	printf( "pslc::psl_get_block_type() != 0x5678\n" );
		return -1;
	} // end if
	
	// Disrupt the heap
	pslc::PVOID pObj2 = pslc::psl_create( 128, 0x1234, 0, 0 );

	// Resize the block
	pObj = pslc::psl_resize( pObj, 256 );
	if ( !pObj )
	{	printf( "pslc::psl_resize() failed\n" );
		return -1;
	} // end if

	// Just show the memory again
	printf( "Memory at 0x%x -> 0x%x\n", (unsigned long)pObj, (unsigned long)*(unsigned long*)pObj );

	// Make sure data was preserved
	if ( *(unsigned long*)pObj != 0x12345678 )
	{	printf( "*(unsigned long*)pObj != 0x12345678\n" );
		return -1;
	} // end if

	// Test under run protection
//	*( (char*)pObj - 1 ) = 0xff;

	// Test over run protection
//	*( (char*)pObj + 128 ) = 0xff;
//	*( (char*)pObj + 128 + 4 ) = 0xff;

	// Free the memory
	pslc::psl_free( pObj );

	pslc::psl_free( pObj2 );

	printf( "success\n" );
	
	return 0;
}

#if defined( _WIN32_WCE )
	int APIENTRY WinMain( HINSTANCE a, HINSTANCE b, LPWSTR c, int d )
#else
	int main( int argc, char* argv[] )
#endif
{
	run();	
	return 0;
}
