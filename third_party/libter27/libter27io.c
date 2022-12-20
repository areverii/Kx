/* libter27io.c */
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

#include <stdio.h>
#include "libter27io.h"

/* Input/Output: heptavintimal */

static unsigned char tern_to_hept[64] = {
	/* BCT codes that are illegal convert to # */
	'0','1','2','#', '3','4','5','#', '6','7','8','#', '#','#','#','#',
	'9','A','B','#', 'C','D','E','#', 'F','G','H','#', '#','#','#','#',
	'K','M','N','#', 'P','R','T','#', 'V','X','Z','#', '#','#','#','#',
	'#','#','#','#', '#','#','#','#', '#','#','#','#', '#','#','#','#',
};

/* Heptavintimal numbers in other bases:
 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  G  H  K  M  N  P  R  T  V  X  Z
 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
   Ternary
000   002   011   020   022   101   110   112   121   200   202   211   220  222
   001   010   012   021   100   102   111   120   122   201   210   212   331
   Hex representation of BCT
00 01 02 04 05 06 08 09 0A 10 11 12 14 15 16 18 19 1A 20 21 22 24 25 26 28 29 2A
   Octal representation of BCT
00 01 02 04 05 06 10 11 12 20 21 22 24 25 26 30 31 32 40 41 42 44 45 46 50 51 52
*/

#define XXX 0x3F
static unsigned char hept_to_tern[256] = {
	/* chars that are not heptavintimal convert to XXX, others in octal */
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	000,001,002,004, 005,006,010,011, 012,020,XXX,XXX, XXX,XXX,XXX,XXX,

	XXX,021,022,024, 025,026,030,031, 032,001,001,040, 001,041,042,000,
	044,000,045,006, 046,050,050,050, 051,001,052,XXX, XXX,XXX,XXX,XXX,
	XXX,021,022,024, 025,026,030,031, 032,001,001,040, 001,041,042,000,
	044,000,045,006, 046,050,050,050, 051,001,052,XXX, XXX,XXX,XXX,XXX,

	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,

	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
	XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX, XXX,XXX,XXX,XXX,
};

void puthept_ter27( uter27_t n, FILE *f ) {
	int i;
	for (i = 9; i > 0; i--) {
		fputc( tern_to_hept[(n >> 48) & UINT64_C(0x000000000000003F)],
		       f );
		n = n << 6;
	}
}

void putdec_uter27( uter27_t n, FILE *f ) {
	char digit;
	void_uter27_div( n, UTER27_C_10 );
	digit = tern_to_hept[uter27_rem];
	if (uter27_quo != UTER27_C_0) putdec_uter27( uter27_quo, f );
	fputc( digit, f );
}

void putdec_bter27( bter27_t n, FILE *f ) {
	if (n < BTER27_C_0) {
		fputc( '-', f );
		n = bter27_neg( n );
	}
	putdec_uter27( uter27_bter27( n ), f );
}

uter27_t ter27_gethept( FILE *f ) {
	/* returns with file positioned to read the immediate next character */
	uter27_t n = UTER27_C_0;
	uter27_t digit;
	int ch = getc( f );
	for (;;) { /* loop exit by break statements, two exits */
		if (ch == EOF) break;
		uter27_t digit = (uter27_t) hept_to_tern[ ch ];
		if (digit == XXX) break;
		/* BUG:  What if too many digits in number? */
		n = UTER27_SL_C( n, 3 ) | digit; /* dangerous but OK code */
		ch = getc( f );
	}
	/* put the character after the number back on the stream */
	if (ch != EOF) ungetc( ch, f );
	return n;
}

uter27_t uter27_getdec( FILE *f ) {
	/* returns with file positioned to read the immediate next character */
	uter27_t n = UTER27_C_0;
	uter27_t digit;
	int ch = getc( f );
	for (;;) { /* loop exit by break statements, three exits */
		if (ch == EOF) break;
		digit = (uter27_t) hept_to_tern[ ch ];
		if (digit == XXX) break;
		if (digit > UTER27_C_9) break;
		/* BUG:  What if too many digits in number? */
		n = uter27_add( uter27_mul( n, UTER27_C_10 ), digit );
		ch = getc( f );
	}
	/* put the character after the number back on the stream */
	if (ch != EOF) ungetc( ch, f );
	return n;
}

bter27_t bter27_getdec( FILE *f ) {
	/* returns with file positioned to read the immediate next character */
	int ch = getc( f );
	bter27_t n;
	if (ch == EOF) return BTER27_C_0;
	/* BUG:  The above line ought to report an error */
	if ((ch != '-') && (ch != '+')) ungetc( ch, f );
	/* BUG:  The following ought to include a range check */
	n = bter27_uter27( uter27_getdec( f ) );
        if (ch == '-') n = bter27_neg( n );
	return n;
}
