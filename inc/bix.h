/*
 * Syntelos BIX
 * Copyright (C) 2022, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _syntelos_bix_h
#define _syntelos_bix_h

#include "syntelos.h"
/*
 * The state of the binary octet sequence found in the
 * "bix" structure "content".
 */
typedef enum bix_state {

    bix_state_none = 0,
    bix_state_encoded = 1,
    bix_state_decoded = 2

} bix_state;
/*
 * Note that (1 == sizeof(void)) and (void*)++ == ((void*)+1)
 */
typedef struct bix {

    bix_state state;

    size_t size;

    void *content;

} bix;
/*
 * Allocate structure and content sequence.
 */
bix* bix_init(size_t);
/*
 * Free structure and content sequence.
 */
void bix_destroy(bix*);
/*
 * Count the length of the hexidecimal encoding found within
 * the argument octet sequence.  May return zero.
 */
size_t bix_count(char*,size_t);
/*
 * Decode HEX to BIN, maintaining sequential order.  The
 * input and output strings are null terminated.  The output
 * string is allocated dynamically and must be freed by the
 * caller.
 *
 * N.B.  A null terminated output string would be
 * nonsensical in a generic HEX2BIN context.  In this
 * context, null is a possibly redundant terminal.
 */
bix* bix_decode(char*,size_t);
/*
 *
 */
bix* bix_encode(char*,size_t);

#endif
