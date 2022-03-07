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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include "bix.h"

bix* bix_init(size_t length){

    bix *re = calloc(1,sizeof(bix));
    if (null != re){
        re->size = length;
        re->content = calloc(length,1);
        if (null != re->content){

            return re;
        }
        else {
            free(re);
            return null;
        }
    }
    else {
        free(re);
        return null;
    }
}
void bix_destroy(bix* bx){
    if (null != bx){
        if (0 != bx->size && null != bx->content){

            memset(bx->content,0,bx->size);
            free(bx->content);
        }

        memset(bx,0,sizeof(bix));
        free(bx);
    }
}
size_t bix_count(char* source, size_t length){
    size_t count = 0;
    if (null != source && 0 != length){
        char *sp = source;
        off_t index;
        for (index = 0; index < length; index++){

            char sc = *sp++;

            if (0 == (sc & 0x80) && 0 != (sc & 0x7F)){

                count += 1;
            }
        }
    }
    return count;
}
/*
 * The input is seven bit ASCII hexidecimal, and the output is binary.
 */
bix* bix_decode(char* hex, size_t count){
    if (null != hex && 0 != count){

        bix *bx = bix_init((count>>1)+1);

        if (null != bx){

            char nibble_c = 0;
            bool_t nibble_b = true;

            const char *ip = hex;
            char *op = bx->content;

            char ci, co;

            off_t index;
            for (index = 0; index < count; index++){

                ci = *ip++;

                switch(ci){
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    co = (ci-'0');
                    break;

                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                    co = ((ci-'a')+10);
                    break;

                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                    co = ((ci-'A')+10);
                    break;

                default:

                    bix_destroy(bx);

                    return null;
                }

                if (nibble_b){

                    nibble_c = (co<<4);

                    nibble_b = false;
                }
                else {

                    nibble_c |= co;

                    *op++ = nibble_c;

                    nibble_b = true;
                }
            }

            bx->state = bix_state_decoded;
            return bx;
        }
    }
    return null;
}
char bix_encode_nibble(char b4){
    if (b4 < 10){

        return ('0'+b4);
    }
    else {

        return ('A'+b4);
    }
}
bix* bix_encode(char* source, size_t length){

    if (null != source && 0 != length){

        bix* bx = bix_init((length<<1)+1);
        if (null != bx){
            off_t index;
            char *ip = source;
            char *op = bx->content;

            for (index = 0; index < length; index++){
                char ic = *ip++;

                *op++ = bix_encode_nibble((ic & 0xF0)>>4);
                *op++ = bix_encode_nibble(ic & 0x0F);
            }
            bx->state = bix_state_encoded;
            return bx;
        }
    }
    return null;
}
