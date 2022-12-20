/* test27.c */
/**********
 * Test and demonstration of
 *      27-trit Ternary Support
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
#include "libter27.h"

void fail( char * s ) {
	fputs( "  Fail: ", stdout );
	fputs( s, stdout );
	fputs( "\n", stdout );
	exit( EXIT_FAILURE );
}

void valid( uter27_t v, char * s ) {
	if (v > UTER27_C_MAX) fail ( s );
}

int ut27arithtest() {
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test uter27_t\n" );

	/* basic tests of constants, add, sub */
	if (uter27_add( UTER27_C_0, UTER27_C_1 ) != UTER27_C_1) 
		fail( "0+1 != 1" );
	if (uter27_add( UTER27_C_2, UTER27_C_3 ) != UTER27_C_5) 
		fail( "2+3 != 5" );
	if (uter27_sub( UTER27_C_9, UTER27_C_5 ) != UTER27_C_4) 
		fail( "27-5 != 4" );
	if (uter27_sub( UTER27_C_8, UTER27_C_2 ) != UTER27_C_6) 
		fail( "8-2 != 6" );
	if (uter27_add( UTER27_C_4, UTER27_C_3 ) != UTER27_C_7) 
		fail( "4+3 != 7" );

	/* basic tests of shifts */
	if (uter27_sl_c( UTER27_C_3, 1 ) != UTER27_C_9) 
		fail( "3<<1 != 27" );
	if (uter27_sr_c( UTER27_C_8, 1 ) != UTER27_C_2) 
		fail( "8>>1 != 2" );

	/* basic tests of logic */
	if (ter27_min( UTER27_C_5, UTER27_C_7 ) != UTER27_C_4) 
		fail( "5 min 7 != 4" );
	if (ter27_max( UTER27_C_1, UTER27_C_3 ) != UTER27_C_4) 
		fail( "1 max 3 != 4" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = UTER27_C_0;
	tj = UTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter27_t tk = uter27_add(ti, tj);
		valid( tk, "uter27_add invalid result k" );
		uint64_t k = i + j;

		{ /* addc test */
			uter27_t tc = uter27_addc( ti, tj, UTER27_C_0 );
			valid( tc, "uter27_addc invalid result c" );
			if (tc != tk)
				fail( "ADDC != ADD" );
			if ((tk >= tj) && (uter27_carry != UTER27_C_0))
				fail( "ADDC carry != 0 when no carry" );
			if ((tk < tj) && (uter27_carry != UTER27_C_1))
				fail( "ADDC carry != 1 when carry" );
		}

		if (k > UINT64_UTER27_C_MAX) break;
		if (k != uint64_uter27( tk ))
			fail( "UINT64_UTER27" );
		if (tk != uter27_uint64( k ))
			fail( "UTER27_UINT64" );
		if (   ter27_neg( ter27_min( ti, tj ) )
                    != ter27_max( ter27_neg( ti ), TER27_NEG( tj ) )   )
			fail( "DeMorgan's law" );
		if (   ter27_xor( ti, tj )
                    != ter27_max( ter27_min( ti, ter27_neg( tj ) )
                               , ter27_min( tj, ter27_neg( ti ) ) ) )
			fail( "XOR" );
		if (   ter27_equ( ti, tj )
                    != ter27_neg( ter27_xor( ti, tj ) ) )
			fail( "EQU" );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to %" PRIu64 "\n", j );

	printf( "  subtraction with Fibonacci numbers\n" );
	while (count > 0) {
		uter27_t tk = uter27_sub(tj, ti);
		uint64_t k = j - i;

		valid( tk, "uter27_sub invalid result" );
		if (k != uint64_uter27( tk ))
			fail( "ternary to int" );
		if (tk != uter27_uint64( k ))
			fail( "int to ternary" );
		if (uint64_uter27( uter27_sr_c( tk, 2 ) ) != (k / 9))
			fail( "k>>2 != k/9" );
		if (uint64_uter27( uter27_addsr_c( tj, ti, 1 ) ) != ((i + j)/ 3))
			fail( "addsr(i,j,1) != (i+j)/3" );
		count = count - 1;
		tj = ti;
		j = i;
		ti = tk;
		i = k;
	}
	if (count == 0) {
		if (ti == UTER27_C_0) {
			printf( "    success\n" );
		} else {
			fail( "does not return to zero" );
		}
	}
}

int bt27arithtest() {
	bter27_t ti, tj;
	int64_t i, j;
	int count;

	printf( "Test bter27_t\n" );
	/* basic tests of constants, add, sub */
	if (bter27_add( BTER27_C_0, BTER27_C_1 ) != BTER27_C_1) 
		fail( "0+1 != 1" );
	if (bter27_add( BTER27_C_2, BTER27_C_3 ) != BTER27_C_5) 
		fail( "2+3 != 5" );
	if (bter27_sub( BTER27_C_9, BTER27_C_5 ) != BTER27_C_4) 
		fail( "27-5 != 4" );
	if (bter27_sub( BTER27_C_8, BTER27_C_2 ) != BTER27_C_6) 
		fail( "8-2 != 6" );
	if (bter27_add( BTER27_C_4, BTER27_C_3 ) != BTER27_C_7) 
		fail( "4+3 != 7" );

	/* basic tests of shifts */
	if (bter27_sl_c( BTER27_C_3, 1 ) != BTER27_C_9) 
		fail( "3<<1 != 27" );
	if (bter27_sr_c( BTER27_C_8, 1 ) != BTER27_C_3) 
		fail( "8>>1 != 3" );

	printf( "  Addition with Fibonacci numbers\n" );
	ti = BTER27_C_0;
	tj = BTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter27_t tk = bter27_add(ti, tj);
		int64_t k = i + j;

		{ /* addc test */
			bter27_t tc = bter27_addc( ti, tj, BTER27_C_0 );
			if (tc != tk)
				fail( "ADDC != ADD" );
			if ((tk >= tj) && (bter27_carry != BTER27_C_0))
				fail( "ADDC carry != 0 when no carry" );
			if ((tk < tj) && (uter27_carry != UTER27_C_1))
				fail( "ADDC carry != 1 when carry" );
		}

		if (k > INT64_BTER27_C_MAX) break;
		if (k != int64_bter27( tk ))
			fail( "INT64_BTER27" );
		if (tk != bter27_int64( k ))
			fail( "BTER27_BINT64" );
		{
			uter27_t ui = uter27_bter27( ti );
			uter27_t uj = uter27_bter27( tj );
			uter27_t uk = uter27_add( ti, tj );
			if (bter27_uter27( uk ) != tk)
				fail( "Fails at balanced-unbalanced" );
		}

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to %" PRIu64 "\n", j );

	printf( "  subtraction with Fibonacci numbers\n" );
	while (count > 0) {
		bter27_t tk = bter27_sub(tj, ti);
		bter27_t tm = bter27_add(tj, bter27_neg( ti ));
		int64_t k = j - i;

		if (tk != tm)
			fail( "a-b != a+(-b)" );
		if (k != int64_bter27( tk ))
			fail( "ternary to int" );
		if (tk != bter27_int64( k ))
			fail( "int to ternary" );
		if ((int64_bter27( bter27_sr_c( tk, 2 ) ) != (k / 9))
		&&  (int64_bter27( bter27_sr_c( tk, 2 ) ) != ((k / 9) + 1)) )
                        fail( "k>>2 != k/9" );
		if ((int64_bter27( bter27_addsr_c( tj, ti, 1 ) )!=((i + j)/ 3))
		&&  (int64_bter27( bter27_addsr_c( tj, ti, 1 ) )!=(((i+j)/3)+1)))
			fail( "addsr(i,j,1) != (i+j)/3" );

		count = count - 1;
		tj = ti;
		j = i;
		ti = tk;
		i = k;
	}
	if (count == 0) {
		if (ti == BTER27_C_0) {
			printf( "    success\n" );
		} else {
			fail( "does not return to zero" );
		}
	}
}

void ut27muldiv() {
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
				valid( ti, "uter27_div invalid quotient" );
			} else { /* odd case */
				ti = uter27_mul( UTER27_C_3, ti );
				valid( ti, "uter27_mul invalid product" );
				ti = uter27_add( ti, UTER27_C_1 );
				valid( ti, "uter27_add invalid sum" );
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
				/* in here, ti and tj vary over a wide range */
				uter27_t quoxti, quo, rem;
				if (i != uint64_uter27( ti ))
					fail( "ternary != binary" );
				/* do real divide test, note, j >= i */
				void_uter27_div( tj, ti );
				quo = uter27_quo;
				valid( quo, "uter27_div bad quo" );
				rem = uter27_rem;
				valid( rem, "uter27_div bad rem" );
				quoxti = uter27_mul( quo, ti );
				valid( quoxti, "uter27_mul bad prod" );
				if (tj != uter27_add( rem, quoxti ))
					fail( "j != j%i + ((j/i) * i)" );

				/* test long multiplication (low half) */
				void_uter27_mul( quo, ti );
				if (quoxti != uter27_prod_low)
					fail( "uter27_mul != void_uter27_mul" );
				if (uter27_prod_top != UTER27_C_0)
					fail( "void_uter27_mul, bad high half");

				/* test long division, low half
				   -- is it equiv to short division? */
				void_uter27_divl( UTER27_C_0, tj, ti );
				if (quo != uter27_quo)
					fail( "void_uter27_divl, bad quo" );
				if (rem != uter27_rem)
					fail( "void_uter27_divl, bad rem" );

				/* test long multiplication and division
				   -- does divide undo multiply? */
				void_uter27_mul( ti, tj );
				valid( uter27_prod_top, "uter27_mul bad top" );
				valid( uter27_prod_low, "uter27_mul bad low" );
				void_uter27_divl( uter27_prod_top,
						 uter27_prod_low, tj );
				valid( uter27_rem, "uter27_divl bad rem" );
				valid( uter27_quo, "uter27_divl bad quo" );
				if (uter27_quo != ti)
					fail( "long (i * j)/ j != i" );
				if (uter27_rem != UTER27_C_0)
					fail( "long (i * j) mod j != 0" );
			}
		}
		ti = uter27_add( tj, UTER27_C_1 );
		i = j + 1;
	}
	if ( i <= UINT64_UTER27_C_MAX ) fail( "does not reach max" );
	printf( "  success\n" );
}

void bt27muldiv() {
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
				bter27_t quoxti, quo, rem;
				if (i != int64_bter27( ti ))
					fail( "ternary != binary" );
				/* do real divide test, note, j >= i */
				void_bter27_div( tj, ti );
				quo = bter27_quo;
				rem = bter27_rem;
				quoxti = bter27_mul( quo, ti );
				if (tj != bter27_add( rem, quoxti ))
					fail( "j != j\%i + ((j/i) * i)" );

				/* test long multiplication (low half) */
				void_bter27_mul( quo, ti );
				if (quoxti != bter27_prod_low)
					fail( "bter27_mul != void_uter27_mul" );
				if (bter27_prod_top != BTER27_C_0)
					fail( "void_bter27_mul, bad high" );

				/* test long division ,low half
				   -- is it equiv to short division? */
				void_bter27_divl( BTER27_C_0, tj, ti );
				if (quo != bter27_quo)
					fail( "void_bter27_divl, bad quo" );
				if (rem != bter27_rem)
					fail( "void_bter27_divl, bad rem" );

				/* test long multiplication and division
				   -- does divide undo multiply? */
				void_bter27_mul( ti, tj );
				void_bter27_divl( bter27_prod_top,
						 bter27_prod_low, tj );
				if (bter27_quo != ti)
					fail( "long (i * j)/ j != i" );
				if (bter27_rem != BTER27_C_0)
					fail( "long (i * j) mod j != 0" );

				/* setup second test, note, j >= i */
				bter27_t tk = bter27_sub( ti, BTER27_C_MAX );
				int64_t k = i - INT64_BTER27_C_MAX;

				/* negative number tests where k <= 0 and j > 0
				   -- retest short multiply and divide */
				void_bter27_div( tk, tj );
				if (tk != bter27_add( bter27_rem
						   , bter27_mul( bter27_quo
							      , tj
				   )               )          )
					fail( "k != k\%j + ((k/j) * j)"
						" (simple divide)" );
				void_bter27_div_up( tk, tj );
				if (tk != bter27_add( bter27_rem
						   , bter27_mul( bter27_quo
							      , tj
				   )               )          )
					fail( "k != k\%j + ((k/j) * j)"
						" (divide rounded up)" );
				void_bter27_div_down( tk, tj );
				if (tk != bter27_add( bter27_rem
						   , bter27_mul( bter27_quo
							      , tj
				   )               )          )
					fail( "k != k\%j + ((k/j) * j)"
						" (divide rounded down)" );

				/* negative number tests where k <= 0 and j > 0
				   -- retest long divide equiv to short */
				void_bter27_div( tk, tj );
				quo = bter27_quo;
				rem = bter27_rem;
				void_bter27_divl( BTER27_C_0, tk, tj );
				if (bter27_rem != rem)
					fail( "bter27_div != bter27_divl, rem" );
				if (bter27_quo != quo)
					fail( "bter27_div != bter27_divl, quo" );

				/* second test sequence where k <= 0 and j > 0
				   -- retest does divide undo multiply */
				void_bter27_mul( tk, tj );
				void_bter27_divl( bter27_prod_top,
						 bter27_prod_low, tj );
				if (bter27_quo != tk)
					fail( "long (i * j)/ j != i" );
				if (bter27_rem != BTER27_C_0)
					fail( "long (i * j) mod j != 0" );
				if (tk != BTER27_C_0) {
					/* must avoid divide by zero here */
					void_bter27_divl( bter27_prod_top,
							 bter27_prod_low, tk );
					if (bter27_quo != tj)
						fail( "long (i * j)/ i != j" );
					if (bter27_rem != BTER27_C_0)
						fail( "long (i * j) mod i != 0" );
				}

				/* second test sequence where k <= 0 and j > 0
				   -- retest does divide undo multiply */
				void_bter27_mul( tk, tj );
			}
		}
		ti = bter27_add( tj, BTER27_C_1 );
		i = j + 1;
	}
	if ( i <= INT64_BTER27_C_MAX ) fail( "does not reach max" );
	printf( "  success\n" );
}

int main() {
	ut27arithtest();
        bt27arithtest();
	ut27muldiv();
	bt27muldiv();
	exit( EXIT_SUCCESS );
}
