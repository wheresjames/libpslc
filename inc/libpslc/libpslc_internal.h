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

#include "libpslc.h"
#include "libpslc/data_types.h"

//------------------------------------------------------------------
// Debug
//------------------------------------------------------------------

	// Define to check for buffer over/under runs
#	define PSL_MEMORY_CHECK

	// Debug messages
#ifndef PSL_MSG
#	ifdef _DEBUG
#		define PSL_MSG( s )	printf( "%s(%lu) : libpslc : %s\n", __FILE__, (unsigned long)__LINE__, s )
#	else
#		define PSL_MSG
#	endif
#endif

	// Memory buffer under run value
#	define PSL_UNDER_RUN_ID		0x01234567

	// Memory buffer over run values
#	define PSL_OVER_RUN_ID1		0x21000021
#	define PSL_OVER_RUN_ID2		0x89ABCDEF

	// Block alignment, !!! MUST BE A POWER OF 2 !!!
#	define PSL_MEMORY_BLOCK_ALIGN					16

	// Minimum block size
#	define PSL_MINIMUM_ALLOCATION_BLOCK_SIZE		256
