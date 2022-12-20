/* test9io.c */
/**********
 * Test and demonstration of
 *      9-trit Ternary I/O Support
 * Version 1.001, Jan 5, 2016, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libter9.shtml for documentation
 *
 * Copyright 2016, distributed under the
 *      Creative Commons CC0 1.0 Universal License
 *      See https://creativecommons.org/publicdomain/zero/1.0/
 * Disclaimer: This is preliminary work,
 *      the author takes no responsibility for errors in this work
 *      but would appreciate being informed of such errors.
 * Acknowledgement: This work was partially supported by Jinn Labs.
 **********/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "libter9io.h"

FILE *tmp; /* temp file */

void fail( char * s ) {
	fputs( s, stdout );
	exit( EXIT_FAILURE );
}

int make_uter9data() {
	uter9_t ti, tj;
	uint16_t i, j;
	int count;

	printf( "Generate uter9_t test data\n" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = UTER9_C_0;
	tj = UTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter9_t tk = uter9_add(ti, tj);
		uint16_t k = i + j;

		if (k > UINT16_UTER9_C_MAX) break;

		puthept_ter9( tk, tmp );
		putc( ' ', tmp );
		putdec_uter9( tk, tmp );
		putc( '\n', tmp );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to " ); putdec_uter9( tj, stdout );
	putchar( '\n' );
}

int test_uter9data() {
	uter9_t ti, tj;
	uint16_t i, j;
	int count;

	printf( "Consume uter9_t test data\n" );

	ti = UTER9_C_0;
	tj = UTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter9_t tk = uter9_add(ti, tj);
		uint16_t k = i + j;
		uter9_t in;

		if (k > UINT16_UTER9_C_MAX) break;

		in = ter9_gethept( tmp );
		if (in != tk) fail( " ter9_gethept\n" );
		if (getc( tmp ) != ' ') fail (" space delimiter\n" );
		in = uter9_getdec( tmp );
		if (in != tk) fail( " uter9_getdec\n" );
		if (getc( tmp ) != '\n') fail (" newline delimiter\n" );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    success\n" );
}

int make_bter9data() {
	bter9_t ti, tj;
	int16_t i, j;
	int count;

	printf( "Generate bter9_t test data\n" );

	printf( "  Addition with Fibonacci numbers\n" );
	ti = BTER9_C_0;
	tj = BTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter9_t tk = bter9_add(ti, tj);
		int16_t k = i + j;

		if (k > INT16_BTER9_C_MAX) break;

		puthept_ter9( tk, tmp );
		putc( ' ', tmp );
		putdec_bter9( tk, tmp );
		putc( '\n', tmp );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to " ); putdec_bter9( tj, stdout );
	putchar( '\n' );
}

int test_bter9data() {
	bter9_t ti, tj;
	int16_t i, j;
	int count;

	printf( "Consume bter9_t test data\n" );

	ti = BTER9_C_0;
	tj = BTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter9_t tk = bter9_add(ti, tj);
		int16_t k = i + j;
		bter9_t in;

		if (k > INT16_BTER9_C_MAX) break;

		in = ter9_gethept( tmp );
		if (in != tk) fail( " ter9_gethept\n" );
		if (getc( tmp ) != ' ') fail (" space delimiter\n" );
		in = bter9_getdec( tmp );
		if (in != tk) {
			puthept_ter9( in, stdout );
			printf( " != " );
			puthept_ter9( tk, stdout );
			putchar( '\n' );
			fail( " bter9_getdec\n" );
		}
		if (getc( tmp ) != '\n') fail (" newline delimiter\n" );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    success\n" );
}

/* BUG:  Multiply and divide would be nice to add into test mix */
void ut9muldiv() {
	uter9_t ti, tj;
	uint16_t i, j;
	int count;

	printf( "Test uter9_t with 3n+1 (Collatz conjecture)\n" );
	/* see standard references for the 3n+1 mechanism used here */
	ti = UTER9_C_2;
	tj = UTER9_C_0;
	i = 2;
	j = 0;
	while (i == uint16_uter9( ti )) {
		if (i > j) j = i;
		if (ti > tj) tj = ti;
		while (i != 1) {
			/* do it in ternary first */
			if (  (void_uter9_div( ti, UTER9_C_2 ), uter9_rem)
			   == UTER9_C_0) { /* even case */
				ti = uter9_quo;
			} else { /* odd case */
				ti = uter9_mul( UTER9_C_3, ti );
				ti = uter9_add( ti, UTER9_C_1 );
			}
			if (ti > tj) tj = ti;

			/* then do it in binary */
			if ((i & 1) == 0) { /* even case */
				i = i >> 1;
			} else { /* odd case */
				i = (3 * i) + 1;
			}
			if (i > j) j = i;

			if (j <= UINT16_UTER9_C_MAX) { /* test */
				uter9_t quoxti;
				if (i != uint16_uter9( ti ))
					fail( "  fails, ternary != binary\n" );
				/* do real divide test, note, j >= i */
				void_uter9_div( tj, ti );
				quoxti = uter9_mul( uter9_quo, ti );
				if (tj != uter9_add( uter9_rem, quoxti ))
					fail( "  fails:"
					      " j != j%i + ((j/i) * i)\n"
					    );
				void_uter9_mul( uter9_quo, ti );
				if (quoxti != uter9_prod_low)
					fail( "  fails:"
					      " uter9_mul != void_uter9_mul\n"
					    );
			}
		}
		ti = uter9_add( tj, UTER9_C_1 );
		i = j + 1;
	}
	if ( i <= UINT16_UTER9_C_MAX ) fail( "  fails to reach max\n" );
	printf( "  success\n" );
}

void bt9muldiv() {
	bter9_t ti, tj;
	int16_t i, j;
	int count;

	printf( "Test bter9_t with 3n+1 (Collatz conjecture)\n" );
	/* see standard references for the 3n+1 mechanism used here */
	ti = BTER9_C_2;
	tj = BTER9_C_0;
	i = 2;
	j = 0;
	while (i == int16_bter9( ti )) {
		if (i > j) j = i;
		if (ti > tj) tj = ti;
		while (i != 1) {
			/* do it in ternary first */
			if (  (void_bter9_div_down( ti, BTER9_C_2 ), bter9_rem)
			   != BTER9_C_1) { /* even case */
				ti = bter9_quo;
			} else { /* odd case */
				ti = bter9_mul( BTER9_C_3, ti );
				ti = bter9_add( ti, BTER9_C_1 );
			}
			if (ti > tj) tj = ti;

			/* then do it in binary */
			if ((i & 1) == 0) { /* even case */
				i = i >> 1;
			} else { /* odd case */
				i = (3 * i) + 1;
			}
			if (i > j) j = i;

			if (j <= INT16_BTER9_C_MAX) { /* test */
				bter9_t quoxti;
				if (i != int16_bter9( ti ))
					fail( "  fails, ternary != binary\n" );
				/* do real divide test, note, j >= i */
				void_bter9_div( tj, ti );
				quoxti = bter9_mul( bter9_quo, ti );
				if (tj != bter9_add( bter9_rem, quoxti ))
					fail( "  fails:"
					      " j != j\%i + ((j/i) * i)\n"
					    );

				/* setup second test, note, j >= i */
				bter9_t tk = bter9_sub( ti, BTER9_C_MAX );
				int16_t k = i - INT16_BTER9_C_MAX;

				/* second test, note k <= 0 and j > 0 */
				void_bter9_div_up( tk, tj );
				if (tk != bter9_add( bter9_rem
						   , bter9_mul( bter9_quo
							      , tj
				   )               )          )
					fail( "  fails:"
					      " j != j\%i + ((j/i) * i)\n"
					    );
			}
		}
		ti = bter9_add( tj, BTER9_C_1 );
		i = j + 1;
	}
	if ( i <= INT16_BTER9_C_MAX ) fail( "  fails to reach max\n" );
	printf( "  success\n" );
}

int main() {
	tmp = tmpfile();
	if (tmp == NULL) fail ( "Can't create temp file\n" );

	make_uter9data();
	make_bter9data();

	fseek( tmp, 0, SEEK_SET );

        test_uter9data();
	test_bter9data();

	exit( EXIT_SUCCESS );
}
