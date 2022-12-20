/* test27io.c test and demo of libter27io */
/**********
 * Test and demonstration of
 *      27-trit Ternary I/O Support
 * Version 1.001, Jan 5, 2016, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libter27.shtml for documentation
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

#include "libter27io.h"

FILE *tmp; /* temp file */

void fail( char * s ) {
	fputs( s, stdout );
	exit( EXIT_FAILURE );
}

int make_uter27data() {
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Generate uter27_t test data\n" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = UTER27_C_0;
	tj = UTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter27_t tk = uter27_add(ti, tj);
		uint64_t k = i + j;

		if (k > UINT64_UTER27_C_MAX) break;

		puthept_ter27( tk, tmp );
		putc( ' ', tmp );
		putdec_uter27( tk, tmp );
		putc( '\n', tmp );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to " ); putdec_uter27( tj, stdout );
	putchar( '\n' );
}

int test_uter27data() {
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Consume uter27_t test data\n" );

	ti = UTER27_C_0;
	tj = UTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter27_t tk = uter27_add(ti, tj);
		uint64_t k = i + j;
		uter27_t in;

		if (k > UINT64_UTER27_C_MAX) break;

		in = ter27_gethept( tmp );
		if (in != tk) fail( " ter27_gethept\n" );
		if (getc( tmp ) != ' ') fail (" space delimiter\n" );
		in = uter27_getdec( tmp );
		if (in != tk) fail( " uter27_getdec\n" );
		if (getc( tmp ) != '\n') fail (" newline delimiter\n" );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    success\n" );
}

int make_bter27data() {
	bter27_t ti, tj;
	int64_t i, j;
	int count;

	printf( "Generate bter27_t test data\n" );

	printf( "  Addition with Fibonacci numbers\n" );
	ti = BTER27_C_0;
	tj = BTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter27_t tk = bter27_add(ti, tj);
		int64_t k = i + j;

		if (k > INT64_BTER27_C_MAX) break;

		puthept_ter27( tk, tmp );
		putc( ' ', tmp );
		putdec_bter27( tk, tmp );
		putc( '\n', tmp );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to " ); putdec_bter27( tj, stdout );
	putchar( '\n' );
}

int test_bter27data() {
	bter27_t ti, tj;
	int64_t i, j;
	int count;

	printf( "Consume bter27_t test data\n" );

	ti = BTER27_C_0;
	tj = BTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter27_t tk = bter27_add(ti, tj);
		int64_t k = i + j;
		bter27_t in;

		if (k > INT64_BTER27_C_MAX) break;

		in = ter27_gethept( tmp );
		if (in != tk) fail( " ter27_gethept\n" );
		if (getc( tmp ) != ' ') fail (" space delimiter\n" );
		in = bter27_getdec( tmp );
		if (in != tk) {
			puthept_ter27( in, stdout );
			printf( " != " );
			puthept_ter27( tk, stdout );
			putchar( '\n' );
			fail( " bter27_getdec\n" );
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
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test uter27_t with 3n+1 (Collatz conjecture)\n" );
	/* see standard references for the 3n+1 mechanism used here */
	ti = UTER27_C_2;
	tj = UTER27_C_0;
	i = 2;
	j = 0;
	while (i == uint64_uter27( ti )) {
		if (i > j) j = i;
		if (ti > tj) tj = ti;
		while (i != 1) {
			/* do it in ternary first */
			if (  (void_uter27_div( ti, UTER27_C_2 ), uter27_rem)
			   == UTER27_C_0) { /* even case */
				ti = uter27_quo;
			} else { /* odd case */
				ti = uter27_mul( UTER27_C_3, ti );
				ti = uter27_add( ti, UTER27_C_1 );
			}
			if (ti > tj) tj = ti;

			/* then do it in binary */
			if ((i & 1) == 0) { /* even case */
				i = i >> 1;
			} else { /* odd case */
				i = (3 * i) + 1;
			}
			if (i > j) j = i;

			if (j <= UINT64_UTER27_C_MAX) { /* test */
				uter27_t quoxti;
				if (i != uint64_uter27( ti ))
					fail( "  fails, ternary != binary\n" );
				/* do real divide test, note, j >= i */
				void_uter27_div( tj, ti );
				quoxti = uter27_mul( uter27_quo, ti );
				if (tj != uter27_add( uter27_rem, quoxti ))
					fail( "  fails:"
					      " j != j%i + ((j/i) * i)\n"
					    );
				void_uter27_mul( uter27_quo, ti );
				if (quoxti != uter27_prod_low)
					fail( "  fails:"
					      " uter27_mul != void_uter27_mul\n"
					    );
			}
		}
		ti = uter27_add( tj, UTER27_C_1 );
		i = j + 1;
	}
	if ( i <= UINT64_UTER27_C_MAX ) fail( "  fails to reach max\n" );
	printf( "  success\n" );
}

void bt9muldiv() {
	bter27_t ti, tj;
	int64_t i, j;
	int count;

	printf( "Test bter27_t with 3n+1 (Collatz conjecture)\n" );
	/* see standard references for the 3n+1 mechanism used here */
	ti = BTER27_C_2;
	tj = BTER27_C_0;
	i = 2;
	j = 0;
	while (i == int64_bter27( ti )) {
		if (i > j) j = i;
		if (ti > tj) tj = ti;
		while (i != 1) {
			/* do it in ternary first */
			if (  (void_bter27_div_down( ti, BTER27_C_2 ), bter27_rem)
			   != BTER27_C_1) { /* even case */
				ti = bter27_quo;
			} else { /* odd case */
				ti = bter27_mul( BTER27_C_3, ti );
				ti = bter27_add( ti, BTER27_C_1 );
			}
			if (ti > tj) tj = ti;

			/* then do it in binary */
			if ((i & 1) == 0) { /* even case */
				i = i >> 1;
			} else { /* odd case */
				i = (3 * i) + 1;
			}
			if (i > j) j = i;

			if (j <= INT64_BTER27_C_MAX) { /* test */
				bter27_t quoxti;
				if (i != int64_bter27( ti ))
					fail( "  fails, ternary != binary\n" );
				/* do real divide test, note, j >= i */
				void_bter27_div( tj, ti );
				quoxti = bter27_mul( bter27_quo, ti );
				if (tj != bter27_add( bter27_rem, quoxti ))
					fail( "  fails:"
					      " j != j\%i + ((j/i) * i)\n"
					    );

				/* setup second test, note, j >= i */
				bter27_t tk = bter27_sub( ti, BTER27_C_MAX );
				int64_t k = i - INT64_BTER27_C_MAX;

				/* second test, note k <= 0 and j > 0 */
				void_bter27_div_up( tk, tj );
				if (tk != bter27_add( bter27_rem
						   , bter27_mul( bter27_quo
							      , tj
				   )               )          )
					fail( "  fails:"
					      " j != j\%i + ((j/i) * i)\n"
					    );
			}
		}
		ti = bter27_add( tj, BTER27_C_1 );
		i = j + 1;
	}
	if ( i <= INT64_BTER27_C_MAX ) fail( "  fails to reach max\n" );
	printf( "  success\n" );
}

int main() {
	tmp = tmpfile();
	if (tmp == NULL) fail ( "Can't create temp file\n" );

	make_uter27data();
	make_bter27data();

	fseek( tmp, 0, SEEK_SET );

        test_uter27data();
	test_bter27data();

	exit( EXIT_SUCCESS );
}
