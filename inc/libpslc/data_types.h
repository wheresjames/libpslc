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

	// Data element size
#	define	PSL_TYPE_Size			0x00ff

	// Elements are signed values
#	define	PSL_TYPE_Signed			0x0100

	// Array
#	define	PSL_TYPE_Element		0x0200

	// Array
#	define	PSL_TYPE_Floating		0x0400

	// Array
#	define	PSL_TYPE_Array			0x1000

	// Null terminated
#	define	PSL_TYPE_NullTerm		0x2000

	// User type
#	define	PSL_TYPE_USER			0x10000

	// Type id's
#	define PSL_tBin 				( PSL_TYPE_Array | 1 )
#	define PSL_tInt					( PSL_TYPE_Signed | sizeof( int ) )
#	define PSL_tUInt           		( sizeof( oexUINT ) )
#	define PSL_tInt8           		( PSL_TYPE_Signed | 1 )
#	define PSL_tUInt8          		( 1 )
#	define PSL_tInt16          		( PSL_TYPE_Signed | 2 )
#	define PSL_tUInt16         		( 2 )
#	define PSL_tInt32          		( PSL_TYPE_Signed | 4 )
#	define PSL_tUInt32         		( 4 )
#	define PSL_tInt64          		( PSL_TYPE_Signed | 8 )
#	define PSL_tUInt64         		( 8 )
#	define PSL_tChar           		( PSL_TYPE_Signed | PSL_TYPE_Element | sizeof( char ) )
#	define PSL_tUChar          		( PSL_TYPE_Element | sizeof( unsigned char ) )
#	define PSL_tChar8          		( PSL_TYPE_Signed | PSL_TYPE_Element | 1 )
#	define PSL_tUChar8         		( PSL_TYPE_Element | 1 )
#	define PSL_tChar16         		( PSL_TYPE_Signed | PSL_TYPE_Element | 2 )
#	define PSL_tUChar16        		( PSL_TYPE_Element | 2 )
#	define PSL_tChar32         		( PSL_TYPE_Signed | PSL_TYPE_Element | 4 )
#	define PSL_tUChar32        		( PSL_TYPE_Element | 4 )
#	define PSL_tChar64         		( PSL_TYPE_Signed | PSL_TYPE_Element | 8 )
#	define PSL_tUChar64        		( PSL_TYPE_Element | 8 )
#	define PSL_tFloat          		( PSL_TYPE_Floating | sizeof( float ) )
#	define PSL_tDouble         		( PSL_TYPE_Floating | sizeof( double ) )
#	define PSL_tLongDouble     		( PSL_TYPE_Floating | sizeof( long double ) )
#	define PSL_tStr					( PSL_TYPE_Array | PSL_TYPE_NullTerm | sizeof( TNPCHAR ) )
#	define PSL_tStrW           		( PSL_TYPE_Array | PSL_TYPE_NullTerm | sizeof( TNPWCHAR ) )
#	define PSL_tStr8           		( PSL_TYPE_Array | PSL_TYPE_NullTerm | 1 )
#	define PSL_tStr16          		( PSL_TYPE_Array | PSL_TYPE_NullTerm | 2 )
#	define PSL_tStr32          		( PSL_TYPE_Array | PSL_TYPE_NullTerm | 4 )
#	define PSL_tStr64          		( PSL_TYPE_Array | PSL_TYPE_NullTerm | 8 )
#	define PSL_tGuid           		( 16 )
