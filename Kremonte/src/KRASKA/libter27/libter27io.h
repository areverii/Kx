/* libter27io.h */
/**********
 * Ternary Data Types for C Programmers
 *      27-trit Ternary I/O Support
 * Version 1.0, Dec 29, 2015, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libter27.shtml for documentation
 *
 * Copyright 2015, distributed under the
 *      Creative Commons Attribution 4.0 International license
 *      See https://creativecommons.org/licenses/by/4.0/
 * Disclaimer: This is preliminary work,
 *      the author takes no responsibility for errors in this work
 *      but would appreciate being informed of such errors.
 * Acknowledgement: This work was partially supported by Jinn Labs.
 **********/

#ifndef _LIBTER27_H
#include "libter27.h"
#endif

#ifndef _LIBTER27IO_H
#define _LIBTER27IO_H

#include <stdio.h>

/* Input/Output */

void puthept_ter27( uter27_t n, FILE *f );
void putdec_uter27( uter27_t n, FILE *f );
void putdec_bter27( bter27_t n, FILE *f );

uter27_t ter27_gethept( FILE *f );
uter27_t uter27_getdec( FILE *f );
bter27_t bter27_getdec( FILE *f );

#endif
