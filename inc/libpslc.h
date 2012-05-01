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

#ifdef PSL_USE_STDDEF
#	include "stddef.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------
// Types
//------------------------------------------------------------------

#ifdef PSL_USE_STDDEF
	typedef size_t			PSL_SIZE;
	typedef wchar_t			PSL_WCHAR;
	typedef ptrdiff_t		PSL_PTRDIFF;
#else
	typedef long			PSL_SIZE;
	typedef char			PSL_WCHAR;
	typedef unsigned long	PSL_PTRDIFF;
#endif

	typedef long			PSL_INT;
	typedef char			PSL_CHAR;
	typedef void*			PSL_PVOID;

//------------------------------------------------------------------
// Memory
//------------------------------------------------------------------

	// Memory allocation functions
	typedef void		( *psl_fn_free )	( PSL_PVOID p );
	typedef PSL_PVOID	( *psl_fn_malloc )	( PSL_SIZE sz );
	typedef PSL_PVOID	( *psl_fn_calloc )	( PSL_SIZE items, PSL_SIZE sz );
	typedef PSL_PVOID	( *psl_fn_realloc )	( PSL_PVOID p, PSL_SIZE sz );

//------------------------------------------------------------------
// Memory
//------------------------------------------------------------------

	/// Sets allocation functions for alloc, realloc, free
	void psl_set_allocation_functions( psl_fn_malloc pmalloc, psl_fn_calloc pcalloc, psl_fn_realloc prealloc, psl_fn_free pfree );

	/// Free an object
	void psl_free( PSL_PVOID p );

	/// Allocate space for a new object
	/**
		@param [in] size	-	Size of the new object in bytes
		@param [in] type	-	Type of the allocated object
		@param [in] f		-	Optional function that should be called upon
								releasing the memory.
		@param [in] init	-	Set to non-zero if the memory should be initialized
								to zero.
	*/
	void* psl_create( PSL_SIZE size, PSL_INT type, psl_fn_free f, PSL_INT init );

	/// Resizes the specified object
	/**
		@param [in] p		-	Pointer to the object.
		@param [in] size	-	New size for the object
	*/
	PSL_PVOID psl_resize( PSL_PVOID p, PSL_SIZE size );
	
	/// Returns the type id for the allocated block
	/**
		@param [in] p		-	Pointer to the object.
	*/
	PSL_INT psl_get_block_type( PSL_PVOID p );

	/// Set the block type for the allocated block
	/**
		@param [in] p		-	Pointer to the object.
		@param [in] type	-	New block type
	*/
	
	void psl_set_block_type( PSL_PVOID p, PSL_INT type );
	
	/// Adds a reference to the memory block
	/**
		@param [in] p		-	Pointer to the object.
		
		@return The previous reference count
	*/
	PSL_INT psl_add_ref( PSL_PVOID p );

	/// Returns the reference count on the memory block
	/**
		@param [in] p		-	Pointer to the object.
		
		@return The current reference count
	*/
	PSL_INT psl_get_ref( PSL_PVOID p );

//------------------------------------------------------------------
// Data types
//------------------------------------------------------------------

#ifdef __cplusplus
}
#endif