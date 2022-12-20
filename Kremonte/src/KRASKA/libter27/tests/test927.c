/* test927.c */
/**********
 * Test and demonstration of 9-trit and 27-trit Ternary Support,
 *      focusing on conversions and long operations built from short ones.
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
#include "libter9.h"

void fail( char * s ) {
	fputs( "  Fail: ", stdout );
	fputs( s, stdout );
	fputs( "\n", stdout );
	exit( EXIT_FAILURE );
}

int ut927arithtest() {
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test uter27_t\n" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = UTER27_C_0;
	tj = UTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		uter27_t tk = uter27_add(ti, tj);

		uter9_t titop = TER9_TER27_TOP( ti );
		uter9_t timid = TER9_TER27_MID( ti );
		uter9_t tilow = TER9_TER27_LOW( ti );

		if (ti != TER27_TER9_PACK( titop, timid, tilow ))
			fail( "tk != PACK( unpack( ti ) )" );

		uter9_t tjtop = TER9_TER27_TOP( tj );
		uter9_t tjmid = TER9_TER27_MID( tj );
		uter9_t tjlow = TER9_TER27_LOW( tj );

		uter9_t tklow = uter9_addc( tilow, tjlow, UTER9_C_0 );
		uter9_t tkmid = uter9_addc( timid, tjmid, uter9_carry );
		uter9_t tktop = uter9_addc( titop, tjtop, uter9_carry );

		int64_t k = i + j;
		
		if (k > UINT64_UTER27_C_MAX) break;

		if ( (k < UINT16_UTER9_C_MAX)
		&&   (tk != UTER27_UTER9( TER9_TER27( tk ))) )
			fail( "tk != UTER27_UTER9( TER9_TER27( tk ) )" );

		if (tk != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( addc( unpack( ti, tj ) ) )" );

		tklow = ter9_min( tilow, tjlow );
		tkmid = ter9_min( timid, tjmid );
		tktop = ter9_min( titop, tjtop );

		if (   ter27_min( ti, tj )
		    != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( min( unpack( ti, tj ) ) )" );

		tklow = ter9_xor( tilow, tjlow );
		tkmid = ter9_xor( timid, tjmid );
		tktop = ter9_xor( titop, tjtop );

		if (   ter27_xor( ti, tj )
		    != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( xor( unpack( ti, tj ) ) )" );

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

		uter9_t titop = TER9_TER27_TOP( ti );
		uter9_t timid = TER9_TER27_MID( ti );
		uter9_t tilow = TER9_TER27_LOW( ti );

		uter9_t tjtop = TER9_TER27_TOP( tj );
		uter9_t tjmid = TER9_TER27_MID( tj );
		uter9_t tjlow = TER9_TER27_LOW( tj );

		uter9_t tklow = uter9_addc( tjlow, ter9_neg( tilow ),
					    UTER9_C_1 );
		uter9_t tkmid = uter9_addc( tjmid, ter9_neg( timid ),
					    uter9_carry );
		uter9_t tktop = uter9_addc( tjtop, ter9_neg( titop ),
					    uter9_carry );

		uint64_t k = j - i;
		
		if (tk != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( subb( unpack( ti, tj ) ) )" );

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

int bt927arithtest() {
	bter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test bter27_t and bter9_t\n" );

	printf( "  addition with Fibonacci numbers\n" );
	ti = BTER27_C_0;
	tj = BTER27_C_1;
	i = 0;
	j = 1;
	count = 0;
	for (;;) {
		bter27_t tk = bter27_add(ti, tj);

		bter9_t titop = TER9_TER27_TOP( ti );
		bter9_t timid = TER9_TER27_MID( ti );
		bter9_t tilow = TER9_TER27_LOW( ti );

		if (ti != TER27_TER9_PACK( titop, timid, tilow ))
			fail( "tk != PACK( unpack( ti ) )" );

		bter9_t tjtop = TER9_TER27_TOP( tj );
		bter9_t tjmid = TER9_TER27_MID( tj );
		bter9_t tjlow = TER9_TER27_LOW( tj );

		bter9_t tklow = bter9_addc( tilow, tjlow, BTER9_C_0 );
		bter9_t tkmid = bter9_addc( timid, tjmid, bter9_carry );
		bter9_t tktop = bter9_addc( titop, tjtop, bter9_carry );

		int64_t k = i + j;
		
		if (k > INT64_BTER27_C_MAX) break;

		if ( (k <= INT16_BTER9_C_MAX)
		&&   (k >= -INT16_BTER9_C_MAX)
		&&   (tk != BTER27_BTER9( TER9_TER27( tk ))) )
			fail( "tk != BTER27_BTER9( TER9_TER27( tk ) )" );

		if (tk != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( addc( unpack( ti, tj ) ) )" );

		tklow = ter9_min( tilow, tjlow );
		tkmid = ter9_min( timid, tjmid );
		tktop = ter9_min( titop, tjtop );

		if (   ter27_min( ti, tj )
		    != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( min( unpack( ti, tj ) ) )" );

		tklow = ter9_xor( tilow, tjlow );
		tkmid = ter9_xor( timid, tjmid );
		tktop = ter9_xor( titop, tjtop );

		if (   ter27_xor( ti, tj )
		    != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( xor( unpack( ti, tj ) ) )" );

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

		bter9_t titop = TER9_TER27_TOP( ti );
		bter9_t timid = TER9_TER27_MID( ti );
		bter9_t tilow = TER9_TER27_LOW( ti );

		bter9_t tjtop = TER9_TER27_TOP( tj );
		bter9_t tjmid = TER9_TER27_MID( tj );
		bter9_t tjlow = TER9_TER27_LOW( tj );

		bter9_t tklow = bter9_addc( tjlow, ter9_neg( tilow ),
					    BTER9_C_0 );
		bter9_t tkmid = bter9_addc( tjmid, ter9_neg( timid ),
					    bter9_carry );
		bter9_t tktop = bter9_addc( tjtop, ter9_neg( titop ),
					    bter9_carry );

		uint64_t k = j - i;
		
		if (tk != TER27_TER9_PACK( tktop, tkmid, tklow ))
			fail( "tk != PACK( subb( unpack( ti, tj ) ) )" );

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

void ut927muldiv() {
	uter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test uter27_t and uter9_t with 3n+1 (Collatz conjecture)\n" );
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
				/* in here, ti and tj vary over a wide range */
				uter27_t quoxti, quo, rem;

				uter9_t titop = TER9_TER27_TOP( ti );
				uter9_t timid = TER9_TER27_MID( ti );
				uter9_t tilow = TER9_TER27_LOW( ti );

				if (i != uint64_uter27( ti ))
					fail( "ternary != binary" );
				/* do real divide test, note, j >= i */
				void_uter27_div( tj, ti );
				quo = uter27_quo;
				rem = uter27_rem;

				uter9_t quotop = TER9_TER27_TOP( quo );
				uter9_t quomid = TER9_TER27_MID( quo );
				uter9_t quolow = TER9_TER27_LOW( quo );

				uter9_t remtop = TER9_TER27_TOP( rem );
				uter9_t remmid = TER9_TER27_MID( rem );
				uter9_t remlow = TER9_TER27_LOW( rem );

				quoxti = uter27_mul( quo, ti );

				void_uter9_mul( quolow, tilow );
				uter9_t quoxtilow = uter9_prod_low;
				uter9_t quoxtimid = uter9_prod_top;
				void_uter9_mul( quolow, timid );
				quoxtimid =
					uter9_addc( quoxtimid, uter9_prod_low,
						    UTER9_C_0 );
				uter9_t quoxtitop =
					uter9_add( uter9_prod_top,
						   uter9_carry );
					/* discard carry out of top */
				void_uter9_mul( quolow, titop );
				quoxtitop =
					uter9_add( quoxtitop, uter9_prod_low );
					/* discard carry out of top */
				void_uter9_mul( quomid, tilow );
				quoxtimid =
					uter9_addc( quoxtimid, uter9_prod_low,
						    UTER9_C_0 );
				quoxtitop =
					uter9_addc( quoxtitop, uter9_prod_top,
						   uter9_carry );
					/* discard carry out of top */
				void_uter9_mul( quomid, timid );
				quoxtitop =
					uter9_add( quoxtitop,
						   uter9_prod_low );
					/* discard carry out of top */
				void_uter9_mul( quotop, tilow );
				quoxtitop =
					uter9_add( quoxtitop,
						   uter9_prod_low );
					/* discard carry out of top */

				if (quoxti != TER27_TER9_PACK(
				    quoxtitop, quoxtimid, quoxtilow ))
					fail( "((j/i) * i)!=unpacked version" );

				uter9_t tjlow = uter9_addc( remlow, quoxtilow,
							    UTER9_C_0 );
				uter9_t tjmid = uter9_addc( remmid, quoxtimid,
							    uter9_carry );
				uter9_t tjtop = uter9_addc( remtop, quoxtitop,
							    uter9_carry );

				if (tj != TER27_TER9_PACK(
				    tjtop, tjmid, tjlow ))
					fail( "j != j%i + ((j/i) * i)" );
			}
		}
		ti = uter27_add( tj, UTER27_C_1 );
		i = j + 1;
	}
	if ( i <= UINT64_UTER27_C_MAX ) fail( "does not reach max" );
	printf( "  success\n" );
}

void bt927muldiv() {
	bter27_t ti, tj;
	uint64_t i, j;
	int count;

	printf( "Test bter27_t and bter9_t with 3n+1 (Collatz conjecture)\n" );
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
			if (  (void_bter27_div( ti, BTER27_C_2 ), bter27_rem)
			   == BTER27_C_0) { /* even case */
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
				/* in here, ti and tj vary over a wide range */
				bter27_t quoxti, quo, rem;

				bter9_t titop = TER9_TER27_TOP( ti );
				bter9_t timid = TER9_TER27_MID( ti );
				bter9_t tilow = TER9_TER27_LOW( ti );

				if (i != int64_bter27( ti ))
					fail( "ternary != binary" );
				/* do real divide test, note, j >= i */
				void_bter27_div( tj, ti );
				quo = bter27_quo;
				rem = bter27_rem;

				bter9_t quotop = TER9_TER27_TOP( quo );
				bter9_t quomid = TER9_TER27_MID( quo );
				bter9_t quolow = TER9_TER27_LOW( quo );

				bter9_t remtop = TER9_TER27_TOP( rem );
				bter9_t remmid = TER9_TER27_MID( rem );
				bter9_t remlow = TER9_TER27_LOW( rem );

				quoxti = bter27_mul( quo, ti );

				void_bter9_mul( quolow, tilow );
				bter9_t quoxtilow = bter9_prod_low;
				bter9_t quoxtimid = bter9_prod_top;
				void_bter9_mul( quolow, timid );
				quoxtimid =
					bter9_addc( quoxtimid, bter9_prod_low,
						    BTER9_C_0 );
				bter9_t quoxtitop =
					bter9_add( bter9_prod_top,
						   bter9_carry );
					/* discard carry out of top */
				void_bter9_mul( quolow, titop );
				quoxtitop =
					bter9_add( quoxtitop, bter9_prod_low );
					/* discard carry out of top */
				void_bter9_mul( quomid, tilow );
				quoxtimid =
					bter9_addc( quoxtimid, bter9_prod_low,
						    BTER9_C_0 );
				quoxtitop =
					bter9_addc( quoxtitop, bter9_prod_top,
						   bter9_carry );
					/* discard carry out of top */
				void_bter9_mul( quomid, timid );
				quoxtitop =
					bter9_add( quoxtitop,
						   bter9_prod_low );
					/* discard carry out of top */
				void_bter9_mul( quotop, tilow );
				quoxtitop =
					bter9_add( quoxtitop,
						   bter9_prod_low );
					/* discard carry out of top */

				if (quoxti != TER27_TER9_PACK(
				    quoxtitop, quoxtimid, quoxtilow ))
					fail( "((j/i) * i)!=unpacked version" );

				bter9_t tjlow = bter9_addc( remlow, quoxtilow,
							    BTER9_C_0 );
				bter9_t tjmid = bter9_addc( remmid, quoxtimid,
							    bter9_carry );
				bter9_t tjtop = bter9_addc( remtop, quoxtitop,
							    bter9_carry );

				if (tj != TER27_TER9_PACK(
				    tjtop, tjmid, tjlow ))
					fail( "j != j%i + ((j/i) * i)" );
			}
		}
		ti = bter27_add( tj, BTER27_C_1 );
		i = j + 1;
	}
	if ( i <= INT64_BTER27_C_MAX ) fail( "does not reach max" );
	printf( "  success\n" );
}

int main() {
	ut927arithtest();
        bt927arithtest();
	ut927muldiv();
	bt927muldiv();
	exit( EXIT_SUCCESS );
}
