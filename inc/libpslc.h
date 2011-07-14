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

//------------------------------------------------------------------
// NAMESPACE
//------------------------------------------------------------------

#if defined ( __cplusplus )
#	ifndef PSL_NO_NAMESPACE
#		ifndef PSL_NAMESPACE
#			define PSL_NAMESPACE	pslc
#		endif
		namespace PSL_NAMESPACE {
#		define	_PSL( v ) v
#		define	_psl( v ) v
#	endif
	extern "C" {
#endif

#ifndef _PSL
#	define	_PSL( v )	PSL_##v
#endif
#ifndef _psl
#	define	_psl( v )	psl_##v
#endif

//------------------------------------------------------------------
// Types
//------------------------------------------------------------------

#ifdef PSL_USE_STDDEF
	typedef size_t			_PSL(SIZE);
	typedef wchar_t			_PSL(WCHAR);
	typedef ptrdiff_t		_PSL(PTRDIFF);
#else
	typedef long			_PSL(SIZE);
	typedef char			_PSL(WCHAR);
	typedef unsigned long	_PSL(PTRDIFF);
#endif

	typedef long			_PSL(INT);
	typedef char			_PSL(CHAR);
	typedef void*			_PSL(PVOID);

//------------------------------------------------------------------
// Memory
//------------------------------------------------------------------

	// Memory allocation functions
	typedef void		( *_psl(fn_free) )		( _PSL(PVOID) p );
	typedef _PSL(PVOID) ( *_psl(fn_malloc) ) 	( _PSL(SIZE) sz );
	typedef _PSL(PVOID) ( *_psl(fn_calloc) ) 	( _PSL(SIZE) items, _PSL(SIZE) sz );
	typedef _PSL(PVOID) ( *_psl(fn_realloc) )	( _PSL(PVOID) p, _PSL(SIZE) sz );

//------------------------------------------------------------------
// Memory
//------------------------------------------------------------------

	/// Sets allocation functions for alloc, realloc, free
	void psl_set_allocation_functions( _psl(fn_malloc) pmalloc, _psl(fn_calloc) pcalloc, _psl(fn_realloc) prealloc, _psl(fn_free) pfree );

	/// Free an object
	void psl_free( _PSL(PVOID) p );

	/// Allocate space for a new object
	/**
		@param [in] size	-	Size of the new object in bytes
		@param [in] type	-	Type of the allocated object
		@param [in] f		-	Optional function that should be called upon
								releasing the memory.
		@param [in] init	-	Set to non-zero if the memory should be initialized
								to zero.
	*/
	void* psl_create( _PSL(SIZE) size, _PSL(INT) type, _psl(fn_free) f, _PSL(INT) init );

	/// Resizes the specified object
	/**
		@param [in] p		-	Pointer to the object.
		@param [in] size	-	New size for the object
	*/
	_PSL(PVOID) psl_resize( _PSL(PVOID) p, _PSL(SIZE) size );
	
	/// Returns the type id for the allocated block
	/**
		@param [in] p		-	Pointer to the object.
	*/
	_PSL(INT) psl_get_block_type( _PSL(PVOID) p );

	/// Set the block type for the allocated block
	/**
		@param [in] p		-	Pointer to the object.
		@param [in] type	-	New block type
	*/
	
	void psl_set_block_type( _PSL(PVOID) p, _PSL(INT) type );
	
	/// Adds a reference to the memory block
	/**
		@param [in] p		-	Pointer to the object.
		
		@return The previous reference count
	*/
	_PSL(INT) psl_add_ref( _PSL(PVOID) p );

	/// Returns the reference count on the memory block
	/**
		@param [in] p		-	Pointer to the object.
		
		@return The current reference count
	*/
	_PSL(INT) psl_get_ref( _PSL(PVOID) p );

//------------------------------------------------------------------
// Data types
//------------------------------------------------------------------

#if defined ( __cplusplus )
	}
#	ifndef PSL_NO_NAMESPACE
	}
#	endif
#endif
