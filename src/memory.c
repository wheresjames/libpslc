/*------------------------------------------------------------------
//
// Copyright (c) 1997-2011
// Robert Umbehant
// libpslc@wheresjames.com
// https://code.google.com/p/libpslc/
//
// Redistribution and use in source and binary forms, with or
// without modification, are permitted for commercial and
// non-commercial purposes, provided that the following
// conditions are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * The names of the developers or contributors may not be used to
//   endorse or promote products derived from this software without
//   specific prior written permission.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------*/

#include "libpslc/libpslc_internal.h"
#include "stdlib.h"

//------------------------------------------------------------------
// Memory
//------------------------------------------------------------------

// Default alloc functions
PSL_PVOID psl_mem_malloc( PSL_SIZE sz ) 
{
	return malloc( sz ); 
}

PSL_PVOID psl_mem_calloc( PSL_SIZE items, PSL_SIZE sz )
{
	return calloc( items, sz ); 
}

PSL_PVOID psl_mem_realloc( PSL_PVOID p, PSL_SIZE sz )
{
	return realloc( p, sz ); 
}

void psl_mem_free( PSL_PVOID p )
{
	free( p ); 
}

// Active alloc funtions
psl_fn_malloc 	psl_g_malloc 	= psl_mem_malloc;
psl_fn_calloc 	psl_g_calloc 	= psl_mem_calloc;
psl_fn_realloc 	psl_g_realloc 	= psl_mem_realloc;
psl_fn_free		psl_g_free 		= psl_mem_free;

void psl_set_allocation_functions( psl_fn_malloc pmalloc, psl_fn_calloc pcalloc, psl_fn_realloc prealloc, psl_fn_free pfree )
{
	psl_g_malloc = pmalloc;
	psl_g_calloc = pcalloc;
	psl_g_realloc = prealloc;
	psl_g_free = pfree;
}

//------------------------------------------------------------------
// Structures
//------------------------------------------------------------------

/// Structure holding information about an allocated block
/**
	The size of this structure should
	divide by 8 with 32 bit pointers,
	and 16 with 64 bit pointers.
*/
typedef struct 
{
	/// Data pointer
	PSL_PVOID			data;

	/// Pointer to function used to free the data
	psl_fn_free			free;

	/// Data structure size
	PSL_SIZE			sz;

	/// Type of data
	PSL_INT				type;

	/// Type of data
	PSL_INT				ref;

	/// Data element size
	PSL_SIZE			size;

} PSL_SData;


#define PSL_PTR_BLOCK_PTR( p ) 	( (PSL_PVOID*)( ( (PSL_CHAR*)p ) - sizeof( PSL_INT ) - sizeof( PSL_PVOID ) ) )
#define PSL_PTR_ALIGN( p, a )	( (PSL_PVOID*)( ( ( (PSL_PTRDIFF)p ) + ( (PSL_PTRDIFF)a - 1 ) ) & ( ~( (PSL_PTRDIFF)a - 1 ) ) ) )

#ifdef PSL_MEMORY_CHECK
#	define PSL_PTR_UNDER_RUN_ID( p ) 		( (PSL_INT*)( ( (PSL_CHAR*)p ) - sizeof( PSL_INT ) ) )
#	define PSL_PTR_OVER_RUN_ID1( p, sz ) 	( (PSL_INT*)( ( (PSL_CHAR*)p ) + sz ) )
#	define PSL_PTR_OVER_RUN_ID2( p, sz ) 	( (PSL_INT*)( ( (PSL_CHAR*)p ) + sz + sizeof( PSL_INT ) ) )
#endif


PSL_INT psl_get_block_type( PSL_PVOID p )
{
	PSL_SData *d;

	if ( !p )
	{	PSL_MSG( "Invalid pointer" );
		return 0;
	} // end if

	// Get data pointer
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return 0;
	} // end if

	return d->type;
}


void psl_set_block_type( PSL_PVOID p, PSL_INT type )
{
	PSL_SData *d;

	if ( !p )
	{	PSL_MSG( "Invalid pointer" );
		return;
	} // end if
	
	// Get block pointer
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return;
	} // end if

	d->type = type;
}

PSL_INT psl_add_ref( PSL_PVOID p )
{
	PSL_SData *d;

	if ( !p )
	{	PSL_MSG( "Invalid pointer" );
		return 0;
	} // end if
	
	// Free the data
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return 0;
	} // end if

	return d->ref++;
}

PSL_INT psl_get_ref( PSL_PVOID p )
{
	PSL_SData *d;

	if ( !p )
	{	PSL_MSG( "Invalid pointer" );
		return 0;
	} // end if
	
	// Free the data
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return 0;
	} // end if

	return d->ref;
}

void psl_free( void *p )
{
	PSL_SData *d;

	// Just ignore null pointer
	if ( !p )
		return;

	// Free the data
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return;
	} // end if

	// Ensure valid
	if ( sizeof( PSL_SData ) != d->sz )
	{	PSL_MSG( "Block has invalid size field" );
		return;
	} // end if
	
	if ( d->ref )
		d->ref--;

	if ( d->ref )
		return;

#ifdef PSL_MEMORY_CHECK

	// Check for memory under run
	if ( PSL_UNDER_RUN_ID != *PSL_PTR_UNDER_RUN_ID( p ) )
	{	PSL_MSG( "Under Run check failed" );
		return;
	} // end if

	// Check for memory over run
	if ( PSL_OVER_RUN_ID1 != *PSL_PTR_OVER_RUN_ID1( p, d->size ) )
	{	PSL_MSG( "Over Run check failed : ID1" );
		return;
	} // end if
	
	if ( PSL_OVER_RUN_ID2 != *PSL_PTR_OVER_RUN_ID2( p, d->size ) )
	{	PSL_MSG( "Over Run check failed : ID2" );
		return;
	} // end if

#endif

	// Clear the size
	d->sz = 0;

	// Destructor?
	if ( d->free )
	{	d->free( d->data );
		d->free = 0;
	} // end if

	// Free the structure
	psl_g_free( d );
}


PSL_PVOID psl_create( PSL_SIZE size, PSL_INT type, psl_fn_free f, PSL_INT init )
{
	PSL_SData 	*d;
	PSL_SIZE	total;

	if ( 0 >= size )
	{	PSL_MSG( "Invalid size" );
		return 0;
	} // end if

	// What's the total size of the memory we need?
	total = sizeof( PSL_SData ) + size;

#ifdef PSL_MEMORY_CHECK

	// Add for under/over run id's if needed
	total += sizeof( PSL_INT ) * 3;

#endif

#ifdef PSL_MEMORY_BLOCK_ALIGN

	// Add block alignment if needed
	total += PSL_MEMORY_BLOCK_ALIGN;

#endif

#ifdef PSL_MINIMUM_ALLOCATION_BLOCK_SIZE

	// Enforce minimum block size
	if ( PSL_MINIMUM_ALLOCATION_BLOCK_SIZE > total )
		total = PSL_MINIMUM_ALLOCATION_BLOCK_SIZE;

#endif

	// Allocate list structure
	d = (PSL_SData*)( init ? psl_g_calloc( total, 1 ) : psl_g_malloc( total ) );
	if ( !d )
	{	PSL_MSG( "Memory allocation failed" );
		return 0;
	} // end if

	// Point to the start of the data
	d->data = ( (PSL_CHAR*)d ) 
			  + sizeof( PSL_SData )		// Skip to the end of the data block
			  + sizeof( PSL_PVOID )		// Add space for block pointer
#ifdef PSL_MEMORY_CHECK
			  + sizeof( PSL_INT )			// Add space for under run id
#endif
			  ;

#ifdef PSL_MEMORY_BLOCK_ALIGN

	// Align the memory
	d->data = PSL_PTR_ALIGN( d->data, PSL_MEMORY_BLOCK_ALIGN );

#endif

	// Destructor?
	d->free = f;

	// Size of the data structure
	d->sz = sizeof( PSL_SData );
	
	// Type of the data block
	d->type = type;
	
	// Size of the data block
	d->size = size;
	
	// Initialize reference count
	d->ref = 1;

	// Set reversing pointer
	*PSL_PTR_BLOCK_PTR( d->data ) = d;

#ifdef PSL_MEMORY_CHECK

	// Save over/under run id's
	*PSL_PTR_UNDER_RUN_ID( d->data ) = PSL_UNDER_RUN_ID;
	*PSL_PTR_OVER_RUN_ID1( d->data, d->size ) = PSL_OVER_RUN_ID1;
	*PSL_PTR_OVER_RUN_ID2( d->data, d->size ) = PSL_OVER_RUN_ID2;

#endif

	return d->data;
}


PSL_PVOID psl_resize( PSL_PVOID p, PSL_SIZE size )
{
	PSL_SData *d, *r;
	PSL_INT total, old_size;
	
	if ( !p )
	{	PSL_MSG( "Invalid pointer" );
		return 0;
	} // end if

	// Just free the block if resizing to zero
	if ( 0 >= size )
	{	psl_free( p );
		return 0;
	} // end if

	// Allocate list structure
	d = (PSL_SData*)*PSL_PTR_BLOCK_PTR( p );
	if ( !d )
	{	PSL_MSG( "Invalid block pointer" );
		return 0;
	} // end if

	// Is it already the desired size?
	if ( d->size == size )
		return p;

	// Sanity check
	if ( sizeof( PSL_SData ) != d->sz )
	{	PSL_MSG( "Block data is currupted" );
		return 0;
	} // end if
	
	// What's the total size of the memory we need?
	total = sizeof( PSL_SData ) + size;

#ifdef PSL_MEMORY_CHECK

	// Add for under/over run id's if needed
	total += sizeof( PSL_INT ) * 3;

#endif

#ifdef PSL_MEMORY_BLOCK_ALIGN

	// Add block alignment if needed
	total += PSL_MEMORY_BLOCK_ALIGN;

#endif

#ifdef PSL_MINIMUM_ALLOCATION_BLOCK_SIZE

	// Enforce minimum block size
	if ( PSL_MINIMUM_ALLOCATION_BLOCK_SIZE > total )
		total = PSL_MINIMUM_ALLOCATION_BLOCK_SIZE;

#endif

	// Attempt to resize memory
	r = (PSL_SData*)psl_g_realloc( d, total );
	if ( !r )
	{	PSL_MSG( "Memory allocation failed" );
		return p;
	} // end if

	// Sanity check
	if ( sizeof( PSL_SData ) != r->sz )
	{	PSL_MSG( "Block data is currupted after resize" );
		return 0;
	} // end if

	// Did the memory move?
	if ( d != r )
	{
//		PSL_MSG( "iii. Block has moved" );

		// Where is the data now?
		r->data = ( (PSL_CHAR*)r ) 
				  + sizeof( PSL_SData )		// Skip to the end of the data block
				  + sizeof( PSL_PVOID )		// Add space for block pointer
#ifdef PSL_MEMORY_CHECK
				  + sizeof( PSL_INT )			// Add space for under run id
#endif
				  ;

#ifdef PSL_MEMORY_BLOCK_ALIGN

		// Align pointer
		r->data = PSL_PTR_ALIGN( r->data, PSL_MEMORY_BLOCK_ALIGN );
		
		// Set reversing pointer
		*PSL_PTR_BLOCK_PTR( r->data ) = r;

		// We have to copy data if alignment offset changed
		if ( ( (PSL_CHAR*)r->data - (PSL_CHAR*)r ) != ( (PSL_CHAR*)p - (PSL_CHAR*)d ) )
		{
			// What was the old size
			PSL_INT copy_size = r->size;

			// Get pointer to the data at the old offset
			PSL_PVOID op = (PSL_PVOID)( (PSL_CHAR*)r + ( (PSL_CHAR*)p - (PSL_CHAR*)d ) );

//			PSL_MSG( "iii. Block has to be realigned after resize" );

			// Don't over run the new buffer
			if ( copy_size > size )
				copy_size = size;

			// Sux, but now we have to copy the data
			// Btw, data will almost certainly overlap
			memmove( r->data, op, copy_size );

#ifdef PSL_MEMORY_CHECK

			// Restore under run protection id's
			*PSL_PTR_UNDER_RUN_ID( r->data ) = PSL_UNDER_RUN_ID;

#endif

		} // end if
		
#endif

	} // end if

#ifdef PSL_MEMORY_CHECK

	// Restore over run protection id's
	*PSL_PTR_OVER_RUN_ID1( r->data, size ) = PSL_OVER_RUN_ID1;
	*PSL_PTR_OVER_RUN_ID2( r->data, size ) = PSL_OVER_RUN_ID2;

#endif

	// Save the new size
	r->size = size;

	return r->data;
}

