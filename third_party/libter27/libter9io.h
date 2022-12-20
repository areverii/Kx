/* libter9io.h */
/**********
 * Ternary Data Types for C Programmers
 *      9-trit Ternary I/O Support
 * Version 1.0, Dec 29, 2015, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libter9.shtml for documentation
 *
 * Copyright 2015, distributed under the
 *      Creative Commons Attribution 4.0 International license
 *      See https://creativecommons.org/licenses/by/4.0/
 * Disclaimer: This is preliminary work,
 *      the author takes no responsibility for errors in this work
 *      but would appreciate being informed of such errors.
 * Acknowledgement: This work was partially supported by Jinn Labs.
 **********/

#ifndef _LIBTER9_H
#include "libter9.h"
#endif

#ifndef _LIBTER9IO_H
#define _LIBTER9IO_H

#include <stdio.h>
#include "libter9.h"

/* Input/Output */

void puthept_ter9( uter9_t n, FILE *f );
void putdec_uter9( uter9_t n, FILE *f );
void putdec_bter9( bter9_t n, FILE *f );

uter9_t ter9_gethept( FILE *f );
uter9_t uter9_getdec( FILE *f );
bter9_t bter9_getdec( FILE *f );

#endif
