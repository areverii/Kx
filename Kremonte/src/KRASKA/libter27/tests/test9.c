/* test9.c */
/**********
 * Test and demonstration of
 *      9-trit Ternary Support
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
#include "libter9.h"

void fail( char * s ) {
	fputs( "  Fail: ", stdout );
	fputs( s, stdout );
	fputs( "\n", stdout );
	exit( EXIT_FAILURE );
}

int ut9arithtest() {
	uter9_t ti, tj;
	uint16_t i, j;
	int count;

	printf( "Test uter9_t\n" );

	/* basic tests of constants, add, sub */
	if (uter9_add( UTER9_C_0, UTER9_C_1 ) != UTER9_C_1) 
		fail( "0+1 != 1" );
	if (uter9_add( UTER9_C_2, UTER9_C_3 ) != UTER9_C_5) 
		fail( "2+3 != 5" );
	if (uter9_sub( UTER9_C_9, UTER9_C_5 ) != UTER9_C_4) 
		fail( "9-5 != 4" );
	if (uter9_sub( UTER9_C_8, UTER9_C_2 ) != UTER9_C_6) 
		fail( "8-2 != 6" );
	if (uter9_add( UTER9_C_4, UTER9_C_3 ) != UTER9_C_7) 
		fail( "4+3 != 7" );

	/* basic tests of shifts */
	if (uter9_sl_c( UTER9_C_3, 1 ) != UTER9_C_9) 
		fail( "3<<1 != 9" );
	if (uter9_sr_c( UTER9_C_8, 1 ) != UTER9_C_2) 
		fail( "8>>1 != 2" );

	/* basic tests of logic */
	if (ter9_min( UTER9_C_5, UTER9_C_7 ) != UTER9_C_4) 
		fail( "5 min 7 != 4" );
	if (ter9_max( UTER9_C_1, UTER9_C_3 ) != UTER9_C_4) 
		fail( "1 max 3 != 4" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = UTER9_C_0;
	tj = UTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter9_t tk = uter9_add(ti, tj);
		uint16_t k = i + j;

		{ /* addc test */
			uter9_t tc = uter9_addc( ti, tj, UTER9_C_0 );
			if (tc != tk)
				fail( "ADDC != ADD" );
			if ((tk >= tj) && (uter9_carry != UTER9_C_0))
				fail( "ADDC carry != 0 when no carry" );
			if ((tk < tj) && (uter9_carry != UTER9_C_1))
				fail( "ADDC carry != 1 when carry" );
		}

		if (k > UINT16_UTER9_C_MAX) break;
		if (k != uint16_uter9( tk ))
			fail( "UINT16_UTER9" );
		if (tk != uter9_uint16( k ))
			fail( "UTER9_UINT16" );
		if (   ter9_neg( ter9_min( ti, tj ) )
                    != ter9_max( ter9_neg( ti ), TER9_NEG( tj ) )   )
			fail( "DeMorgan's law" );
		if (   ter9_xor( ti, tj )
                    != ter9_max( ter9_min( ti, ter9_neg( tj ) )
                               , ter9_min( tj, ter9_neg( ti ) ) ) )
			fail( "XOR" );
		if (   ter9_equ( ti, tj )
                    != ter9_neg( ter9_xor( ti, tj ) ) )
			fail( "EQU" );

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to %d\n", j );

	printf( "  subtraction with Fibonacci numbers\n" );
	while (count > 0) {
		uter9_t tk = uter9_sub(tj, ti);
		uint16_t k = j - i;

		if (k != uint16_uter9( tk ))
			fail( "ternary to int" );
		if (tk != uter9_uint16( k ))
			fail( "int to ternary" );
		if (uint16_uter9( uter9_sr_c( tk, 2 ) ) != (k / 9))
			fail( "k>>2 != k/9" );
		if (uint16_uter9( uter9_addsr_c( tj, ti, 1 ) ) != ((i + j)/ 3))
			fail( "addsr(i,j,1) != (i+j)/3" );
		count = count - 1;
		tj = ti;
		j = i;
		ti = tk;
		i = k;
	}
	if (count == 0) {
		if (ti == UTER9_C_0) {
			printf( "    success\n" );
		} else {
			fail( "does not return to zero" );
		}
	}
}

int bt9arithtest() {
	bter9_t ti, tj;
	int16_t i, j;
	int count;

	printf( "Test bter9_t\n" );
	/* basic tests of constants, add, sub */
	if (bter9_add( BTER9_C_0, BTER9_C_1 ) != BTER9_C_1) 
		fail( "0+1 != 1" );
	if (bter9_add( BTER9_C_2, BTER9_C_3 ) != BTER9_C_5) 
		fail( "2+3 != 5" );
	if (bter9_sub( BTER9_C_9, BTER9_C_5 ) != BTER9_C_4) 
		fail( "9-5 != 4" );
	if (bter9_sub( BTER9_C_8, BTER9_C_2 ) != BTER9_C_6) 
		fail( "8-2 != 6" );
	if (bter9_add( BTER9_C_4, BTER9_C_3 ) != BTER9_C_7) 
		fail( "4+3 != 7" );

	/* basic tests of shifts */
	if (bter9_sl_c( BTER9_C_3, 1 ) != BTER9_C_9) 
		fail( "3<<1 != 9" );
	if (bter9_sr_c( BTER9_C_8, 1 ) != BTER9_C_3) 
		fail( "8>>1 != 3" );

	printf( "  Addition with Fibonacci numbers\n" );
	ti = BTER9_C_0;
	tj = BTER9_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter9_t tk = bter9_add(ti, tj);
		int16_t k = i + j;

		{ /* addc test */
			bter9_t tc = bter9_addc( ti, tj, BTER9_C_0 );
			if (tc != tk)
				fail( "ADDC != ADD" );
			if ((tk >= tj) && (bter9_carry != BTER9_C_0))
				fail( "ADDC carry != 0 when no carry" );
			if ((tk < tj) && (uter9_carry != UTER9_C_1))
				fail( "ADDC carry != 1 when carry" );
		}

		if (k > INT16_BTER9_C_MAX) break;
		if (k != int16_bter9( tk ))
			fail( "INT16_BTER9" );
		if (tk != bter9_int16( k ))
			fail( "BTER9_BINT16" );
		{
			uter9_t ui = uter9_bter9( ti );
			uter9_t uj = uter9_bter9( tj );
			uter9_t uk = uter9_add( ti, tj );
			if (bter9_uter9( uk ) != tk)
				fail( "Fails at balanced-unbalanced" );
		}

		count = count + 1;
		ti = tj;
		i = j;
                tj = tk;
		j = k;
	}
	printf( "    up to %d\n", j );

	printf( "  subtraction with Fibonacci numbers\n" );
	while (count > 0) {
		bter9_t tk = bter9_sub(tj, ti);
		bter9_t tm = bter9_add(tj, bter9_neg( ti ));
		int16_t k = j - i;

		if (tk != tm)
			fail( "a-b != a+(-b)" );
		if (k != int16_bter9( tk ))
			fail( "ternary to int" );
		if (tk != bter9_int16( k ))
			fail( "int to ternary" );
		if ((int16_bter9( bter9_sr_c( tk, 2 ) ) != (k / 9))
		&&  (int16_bter9( bter9_sr_c( tk, 2 ) ) != ((k / 9) + 1)) )
                        fail( "k>>2 != k/9" );
		if ((int16_bter9( bter9_addsr_c( tj, ti, 1 ) )!=((i + j)/ 3))
		&&  (int16_bter9( bter9_addsr_c( tj, ti, 1 ) )!=(((i+j)/3)+1)))
			fail( "addsr(i,j,1) != (i+j)/3" );

		count = count - 1;
		tj = ti;
		j = i;
		ti = tk;
		i = k;
	}
	if (count == 0) {
		if (ti == BTER9_C_0) {
			printf( "    success\n" );
		} else {
			fail( "does not return to zero" );
		}
	}
}

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
				/* in here, ti and tj vary over a wide range */
				uter9_t quoxti, quo, rem;
				if (i != uint16_uter9( ti ))
					fail( "ternary != binary" );

				/* do real divide test, note, j >= i */
				void_uter9_div( tj, ti );
				quo = uter9_quo;
				rem = uter9_rem;
				quoxti = uter9_mul( quo, ti );
				if (tj != uter9_add( rem, quoxti ))
					fail( "j != j%i + ((j/i) * i)" );

				/* test long multiplication (low half) */
				void_uter9_mul( quo, ti );
				if (quoxti != uter9_prod_low)
					fail( "uter9_mul != void_uter9_mul" );
				if (uter9_prod_top != UTER9_C_0)
					fail( "void_uter9_mul, bad high half" );

				/* test long division, low half
				   -- is it equiv to short division? */
				void_uter9_divl( UTER9_C_0, tj, ti );
				if (quo != uter9_quo)
					fail( "void_uter9_divl, bad quo" );
				if (rem != uter9_rem)
					fail( "void_uter9_divl, bad rem" );

				/* test long multiplication and division
				   -- does divide undo multiply? */
				void_uter9_mul( ti, tj );
				void_uter9_divl( uter9_prod_top,
						 uter9_prod_low, tj );
				if (uter9_quo != ti)
					fail( "long (i * j)/ j != i" );
				if (uter9_rem != UTER9_C_0)
					fail( "long (i * j) mod j != 0" );
			}
		}
		ti = uter9_add( tj, UTER9_C_1 );
		i = j + 1;
	}
	if ( i <= UINT16_UTER9_C_MAX ) fail( "does not reach max" );
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
				bter9_t quoxti, quo, rem;
				if (i != int16_bter9( ti ))
					fail( "ternary != binary" );
				/* do real divide test, note, j >= i */
				void_bter9_div( tj, ti );
				quo = bter9_quo;
				rem = bter9_rem;
				quoxti = bter9_mul( quo, ti );
				if (tj != bter9_add( rem, quoxti ))
					fail( "j != j\%i + ((j/i) * i)" );

				/* test long multiplication (low half) */
				void_bter9_mul( quo, ti );
				if (quoxti != bter9_prod_low)
					fail( "bter9_mul != void_uter9_mul" );
				if (bter9_prod_top != BTER9_C_0)
					fail( "void_bter9_mul, bad high half" );

				/* test long division ,low half
				   -- is it equiv to short division? */
				void_bter9_divl( BTER9_C_0, tj, ti );
				if (quo != bter9_quo)
					fail( "void_bter9_divl, bad quo" );
				if (rem != bter9_rem)
					fail( "void_bter9_divl, bad rem" );

				/* test long multiplication and division
				   -- does divide undo multiply? */
				void_bter9_mul( ti, tj );
				void_bter9_divl( bter9_prod_top,
						 bter9_prod_low, tj );
				if (bter9_quo != ti)
					fail( "long (i * j)/ j != i" );
				if (bter9_rem != BTER9_C_0)
					fail( "long (i * j) mod j != 0" );

				/* setup second test, note, j >= i */
				bter9_t tk = bter9_sub( ti, BTER9_C_MAX );
				int16_t k = i - INT16_BTER9_C_MAX;

				/* negative number tests where k <= 0 and j > 0
				   -- retest short multiply and divide */
				void_bter9_div_up( tk, tj );
				if (tk != bter9_add( bter9_rem
						   , bter9_mul( bter9_quo
							      , tj
				   )               )          )
					fail( "j != j\%i + ((j/i) * i)"
						" (divide rounded up)" );
				void_bter9_div_down( tk, tj );
				if (tk != bter9_add( bter9_rem
						   , bter9_mul( bter9_quo
							      , tj
				   )               )          )
					fail( "j != j\%i + ((j/i) * i)"
						" (divide rounded down)" );

				/* negative number tests where k <= 0 and j > 0
				   -- retest long divide equiv to short */
				void_bter9_div( tk, tj );
				quo = bter9_quo;
				rem = bter9_rem;
				void_bter9_divl( BTER9_C_0, tk, tj );
				if (bter9_rem != rem)
					fail( "bter9_div != bter9_divl, rem" );
				if (bter9_quo != quo)
					fail( "bter9_div != bter9_divl, quo" );

				/* second test sequence where k <= 0 and j > 0
				   -- retest does divide undo multiply */
				void_bter9_mul( tk, tj );
				void_bter9_divl( bter9_prod_top,
						 bter9_prod_low, tj );
				if (bter9_quo != tk)
					fail( "long (i * j)/ j != i" );
				if (bter9_rem != BTER9_C_0)
					fail( "long (i * j) mod j != 0" );
				if (tk != BTER9_C_0) {
					/* must avoid divide by zero here */
					void_bter9_divl( bter9_prod_top,
							 bter9_prod_low, tk );
					if (bter9_quo != tj)
						fail( "long (i * j)/ i != j" );
					if (bter9_rem != BTER9_C_0)
						fail( "long (i * j) mod i != 0" );
				}

				/* second test sequence where k <= 0 and j > 0
				   -- retest does divide undo multiply */
				void_bter9_mul( tk, tj );
			}
		}
		ti = bter9_add( tj, BTER9_C_1 );
		i = j + 1;
	}
	if ( i <= INT16_BTER9_C_MAX ) fail( "does not reach max" );
	printf( "  success\n" );
}

int main() {
	ut9arithtest();
        bt9arithtest();
	ut9muldiv();
	bt9muldiv();
	exit( EXIT_SUCCESS );
}
