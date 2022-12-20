/* libter27.c */
/**********
 * Ternary Data Types for C Programmers
 * 	27-trit Ternary Support
 * Version 1.0, Dec 29, 2015, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libter27.shtml for documentation
 *
 * Copyright 2015, distributed under the
 *	Creative Commons Attribution 4.0 International license
 *	See https://creativecommons.org/licenses/by/4.0/
 * Disclaimer: This is preliminary work,
 *      the author takes no responsibility for errors in this work
 *      but would appreciate being informed of such errors.
 * Acknowledgement: This work was partially supported by Jinn Labs.
 **********/

#include "libter27.h"

/* arithmetic support
 * we need at least 27+3 places of precision in intermediate results
 * because of use of base 27 in multiplication algorithm;
 * we would need just 1 trit of extra precision for base 3 multiply.
 */

/* masks and constants */
#define _T31_MASK UINT64_C(0x3FFFFFFFFFFFFFFF)
#define _UT31_C_0 UINT64_C(0x0000000000000000)
#define _BT31_C_NEGBIAS UINT64_C(0x1555555555555556)
#define _BT31_C_0 UINT64_C(0x1555555555555555)
#define _T3_MASK UINT64_C(0x000000000000003F)

/* to call _UT31_ADD, first declare uter27_t c, d, e */
#define _UT31_ADD( a, b ) (					\
     c = (a) + _BT31_C_0,			\
     d = (b) + c,						\
     e = (~((b) ^ c ^ d) & UINT64_C(0x5555555555555554)) >> 2,	\
     d - e							\
)

/* to call _BT31_ADD, first declare uter27_t c, d, e for _UT31_ADD */
#define _BT31_ADD( a, b ) (					\
	_UT31_ADD( _UT31_ADD( a, b ), _BT31_C_NEGBIAS )		\
)

#define _UT31_2S_COMP( a ) (UINT64_C(0x2AAAAAAAAAAAAAAA) - (a))

#define _UT31_SL_C( a, b ) ((a) << (2*(b)))
#define _UT31_SR_C( a, b ) ((a) >> (2*(b)))

#define _BT31_BT27( a ) (a | UINT64_C(0x1540000000000000))

#define _BT31_NEG( a ) _UT31_2S_COMP( a )

#define _BT31_SL_C( a, b ) (						    \
	((a) << (2*(b))) | (_BT31_C_0 >> (2*(31 - (b)))) \
)

#define _BT31_SR_C( a, b ) (						      \
	(((a) >> (2*(b))) | (_BT31_C_0 << (2*(31 - (b))))) \
	& _T31_MASK							      \
)

/* simple add and subtract */

uter27_t uter27_add( uter27_t a, uter27_t b ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	return _UT31_ADD( a, b ) & _TER27_MASK;
}

bter27_t bter27_add( bter27_t a, bter27_t b ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	return _BT31_ADD( a, b ) & _TER27_MASK;
}
	
uter27_t uter27_sub( uter27_t a, uter27_t b ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	b = _UT27_2S_COMP( b );
	b = _UT31_ADD( b, UTER27_C_1 );
	return _UT31_ADD( a, b ) & _TER27_MASK;
}

bter27_t bter27_neg( bter27_t a ) {
	return _UT27_2S_COMP( a );
}

bter27_t bter27_sub( bter27_t a, bter27_t b ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	return _BT31_ADD( a, _UT27_2S_COMP( b )) & _TER27_MASK;
}

/* special add and subtract */

uter27_t uter27_addsr_c( uter27_t a, uter27_t b, unsigned int s ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	return (_UT31_ADD( a, b ) >> (s << 1)) & _TER27_MASK;
}

bter27_t bter27_addsr_c( bter27_t a, bter27_t b, unsigned int s ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	return (_BT31_ADD( _BT31_BT27( a ), _BT31_BT27( b ) ) >> (s << 1))
		& _TER27_MASK;
}

uter27_t uter27_carry; /* must be either 0 or 1 */
uter27_t uter27_addc( uter27_t a, uter27_t b, uter27_t cin ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	b = b + cin; /* strange but true: safe to use binary add here */
	a = _UT31_ADD( a, b );
	uter27_carry = (a >> 54) & UINT64_C(3);
        return  a & _TER27_MASK;
}

bter27_t bter27_carry; /* must be either -1, 0 or 1 */
bter27_t bter27_addc( bter27_t a, bter27_t b, bter27_t cin ) {
	uter27_t c, d, e; /* used by _UT31_ADD() */
	a = _UT31_ADD( _BT31_BT27( a ), _BT31_BT27( b ) );
	a = _UT31_ADD( a, _BT31_BT27( cin + 1 ) );
	bter27_carry = ((a >> 54) & UINT64_C(3)) | BTER27_C_N1;
	return a & _TER27_MASK;
}

/* shift operations */

uter27_t uter27_sl_c( uter27_t a, unsigned int b ) {
	return UTER27_SL_C( a, b );
}

bter27_t bter27_sl_c( bter27_t a, unsigned int b ) {
	return BTER27_SL_C( a, b );
}

uter27_t uter27_sr_c( uter27_t a, unsigned int b ) {
	return UTER27_SR_C( a, b );
}

bter27_t bter27_sr_c( bter27_t a, unsigned int b ) {
	return BTER27_SR_C( a, b );
}

/* logic operations */

uter27_t ter27_min( uter27_t a, uter27_t b ) {
	return TER27_MIN( a, b );
}

uter27_t ter27_max( uter27_t a, uter27_t b ) {
	return TER27_MAX( a, b );
}

uter27_t ter27_neg( uter27_t a ) {
	return TER27_NEG( a );
}

uter27_t ter27_xor( uter27_t a, uter27_t b ) {
	uter27_t nega = _TER27_LOGIC( TER27_NEG( a ) );
	uter27_t negb = _TER27_LOGIC( TER27_NEG( b ) );
	a = _TER27_LOGIC( a );
	b = _TER27_LOGIC( b );
	a = (a & negb) | (b & nega);
	return _TER27_LOGIC( a );
}

uter27_t ter27_equ( uter27_t a, uter27_t b ) {
        uter27_t nega = _TER27_LOGIC( TER27_NEG( a ) );
        uter27_t negb = _TER27_LOGIC( TER27_NEG( b ) );
        a = _TER27_LOGIC( a );
        b = _TER27_LOGIC( b );
        a = (a & b) | (nega & negb);
        return _TER27_LOGIC( a );
}

/* multiply and divide: basic */

uter27_t uter27_mul( uter27_t a, uter27_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand left and the multiplier right
	   to accumulate the least significant 27 trits of the product;
	   the more significant trits of the product are discarded. */
	uter27_t prod = UTER27_C_0;
	uter27_t c, d, e; /* used by _UT31_ADD() */
	uter27_t p, q; /* the partial product and a rarely used temporary */
	while (a != UTER27_C_0) {
		switch (a & _T3_MASK) {
		case UTER27_C_0:
			p = UTER27_C_0;
			break;
		case UTER27_C_1:
			p = b;
			break;
		case UTER27_C_2:
			p = _UT31_ADD( b, b );
			break;
		case UTER27_C_3:
			p = _UT31_SL_C( b, 1 );
			break;
		case UTER27_C_4:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 3+1 */
			break;
		case UTER27_C_5:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			break;
		case UTER27_C_6:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 3*2 */
			break;
		case UTER27_C_7:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ), b );  /* *3+1 */
			break;
		case UTER27_C_8:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_9:
			p = _UT31_SL_C( b, 2 );
			break;
		case UTER27_C_10:
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , b ); /* 9+1 */
			break;
		case UTER27_C_11:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_12:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_13:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_14:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ), p );  /* 9+ */
			break;
		case UTER27_C_15:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT31_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER27_C_16:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_17:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_18:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 2 );  /* 2*7 */
			break;
		case UTER27_C_19:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 2 );  /* 2*9 */
			p = _UT31_ADD( p, b );			 /* +1 */
			break;
		case UTER27_C_20:
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , b ); /* 9+1 */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_21:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ), b );  /* *3+1 */
			p = _UT31_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER27_C_22:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_23:
			q = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , q ); /* 3+ */
			p = _UT31_ADD( _UT31_SL_C( q, 2 ) , p ); /* 18+ */
			break;
		case UTER27_C_24:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_25:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_26:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT31_ADD( p, p );			 /* *2 */
		}
		a = UTER27_SR_C( a, 3 );
		prod = _UT31_ADD( prod, p );
		b = _UT31_SL_C( b, 3 );
	}
	return prod & _TER27_MASK;
}

bter27_t bter27_mul( bter27_t a, bter27_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand left and the multiplier right
	   to accumulate the least significant 27 trits of the product;
	   the more significant trits of the product are discarded. */
	bter27_t prod = BTER27_C_0;
	uter27_t c, d, e; /* used by _BT31_ADD() */
	int i;
	b = _BT31_BT27( b );
	for (i = 9; i > 0; i--) { /* base 27 multiply */
		bter27_t p; /* partial product */
		switch (a & _T3_MASK) {
		case BTER27_C_N13 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), p ) );
			break;
		case BTER27_C_N12 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_SL_C( _BT31_ADD( p, p ), 1 ) );
			break;
		case BTER27_C_N11 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), p ) );
			break;
		case BTER27_C_N10 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), b ) );
			break;
		case BTER27_C_N9 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( b, 2 ) );
			break;
		case BTER27_C_N8 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( p, 1 ), p ) );
			break;
		case BTER27_C_N7 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( p, 1 ), b ) );
			break;
		case BTER27_C_N6 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( _BT31_ADD( b, b ), 1 ) );
			break;
		case BTER27_C_N5 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 1 ), p ) );
			break;
		case BTER27_C_N4 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 1 ), b ) );
			break;
		case BTER27_C_N3 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( b, 1 ) );
			break;
		case BTER27_C_N2 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( b, b ) );
			break;
		case BTER27_C_N1 & _T3_MASK:
			p = _BT31_NEG( b );
			break;
		case BTER27_C_0 & _T3_MASK:
			p = _BT31_C_0;
			break;
		case BTER27_C_1 & _T3_MASK:
			p = b;
			break;
		case BTER27_C_2 & _T3_MASK:
			p = _BT31_ADD( b, b );
			break;
		case BTER27_C_3 & _T3_MASK:
			p = _BT31_SL_C( b, 1 );
			break;
		case BTER27_C_4 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ) , b );
			break;
		case BTER27_C_5 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), p );
			break;
		case BTER27_C_6 & _T3_MASK:
			p = _BT31_SL_C( _BT31_ADD( b, b ), 1 );
			break;
		case BTER27_C_7 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( p, 1 ), b );
			break;
		case BTER27_C_8 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( p, 1 ), p );
			break;
		case BTER27_C_9 & _T3_MASK:
			p = _BT31_SL_C( b, 2 );
			break;
		case BTER27_C_10 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), b );
			break;
		case BTER27_C_11 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), p );
			break;
		case BTER27_C_12 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_SL_C( _BT31_ADD( p, p ), 1 );
			break;
		case BTER27_C_13 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), b );
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), p );
		}
		prod = _BT31_ADD( prod, p );
		a = BTER27_SR_C( a, 3 );
		b = _BT31_SL_C( b, 3 );
	}
	return prod & _TER27_MASK;
}

uter27_t uter27_rem, uter27_quo;
void void_uter27_div( uter27_t a, uter27_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter27_t c, d, e; /* used by _UT31_ADD() */
	uter27_t negb = _UT31_ADD( _UT31_2S_COMP( b ), UTER27_C_1 );

	uter27_quo = a; /* quo initially holds the dividend */
	uter27_rem = UTER27_C_0;

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 27; i++) { /* divide step */
		/* first, shift rem-quo double-register 1 trit left */
		uter27_rem = _UT31_SL_C( uter27_rem, 1 )
			   | _UT31_SR_C( uter27_quo, 26 );
		uter27_quo = UTER27_SL_C( uter27_quo, 1 );

		/* second, compute one trit of quotient */
		if (uter27_rem >= b) { /* mostly the same as binary division */
			uter27_quo++;
			uter27_rem = _UT31_ADD( uter27_rem, negb )
				   & _T31_MASK;
			if (uter27_rem >= b) { /* this step added for ternary */
				uter27_quo++;
				uter27_rem = _UT31_ADD( uter27_rem, negb )
					   & _T31_MASK;
			}
		}
	}
}

/* optimization done above with _BT31_ADD() not done below (balanced is ugly) */
bter27_t bter27_rem, bter27_quo;
void void_bter27_div( bter27_t a, bter27_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	bter27_t one = 1;	/* binary 1 (careful rule violation here) */
	bter27_t trem, nrem;	/* candidate for next remainder */

	if (b < BTER27_C_0) { /* take absolute value of divisor */
		b = bter27_neg( b );
		one = UINT64_C(0xFFFFFFFFFFFFFFFF); /* binary -1 (violation) */
	}

        bter27_rem = BTER27_C_0;
        bter27_quo = a;

	/* the simple, stupid algorithm for division */
	for (i = 0; i < 27; i++) { /* divide step */
		/* first, shift rem-quo balanced double-register 1 trit left */
		bter27_rem = ((bter27_rem << 2)+(bter27_quo >> 52))
			     & _TER27_MASK;
		bter27_quo = BTER27_SL_C( bter27_quo, 1 );

		/* second, compute one trit of quotient */
		if (bter27_rem > BTER27_C_0) {
                        trem = bter27_sub( bter27_rem, b );
                        nrem = bter27_neg( trem );
			if ( (nrem < bter27_rem)
			||   (  (nrem == bter27_rem)
                             && (bter27_quo > BTER27_C_0)  ) ) {
				bter27_quo = bter27_quo + one; /* violation */
				bter27_rem = trem;
			}
		} else if (bter27_rem < BTER27_C_0) {
                        trem = bter27_add( bter27_rem, b );
                        nrem = bter27_neg( trem );
			if ( (nrem > bter27_rem)
			||  (  (nrem == bter27_rem)
                            && (bter27_quo < BTER27_C_0)  ) ) {
				bter27_quo = bter27_quo - one; /* violation */
				bter27_rem = trem;
			}
		}
	}
}

/* bter27_t bter27_rem, bter27_quo; */
void void_bter27_div_down( bter27_t a, bter27_t b ) {
	void_bter27_div( a, b );
	if (bter27_rem < BTER27_C_0) {
		if (b > BTER27_C_0) {
			bter27_rem = bter27_add( bter27_rem, b );
			bter27_quo = bter27_sub( bter27_quo, BTER27_C_1 );
		} else {
			bter27_rem = bter27_sub( bter27_rem, b );
			bter27_quo = bter27_add( bter27_quo, BTER27_C_1 );
		}
	}
}

/* bter27_t bter27_rem, bter27_quo; */
void void_bter27_div_up( bter27_t a, bter27_t b ) {
	void_bter27_div( a, b );
	if (bter27_rem > BTER27_C_0) {
		if (b > BTER27_C_0) {
			bter27_rem = bter27_sub( bter27_rem, b );
			bter27_quo = bter27_add( bter27_quo, BTER27_C_1 );
		} else {
			bter27_rem = bter27_add( bter27_rem, b );
			bter27_quo = bter27_sub( bter27_quo, BTER27_C_1 );
		}
	}
}

/* multiply and divide: special */

uter27_t uter27_prod_top, uter27_prod_low; /* double register for product */
void void_uter27_mul( uter27_t a, uter27_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand and product left, giving a long result. */
	uter27_prod_top = _UT31_C_0;
	uter27_prod_low = a;
	uter27_t c, d, e; /* used by _UT31_ADD() */
	uter27_t p, q; /* the partial product and a rarely used temporary */
	int i;
	for (i = 9; i > 0; i--) { /* base 27 multiply */
		/* 27 cases based on least significant 3 trits of multiplier */
		switch (uter27_prod_low & _T3_MASK) {
		case UTER27_C_0:
			p = _UT31_C_0;
			break;
		case UTER27_C_1:
			p = b;
			break;
		case UTER27_C_2:
			p = _UT31_ADD( b, b );
			break;
		case UTER27_C_3:
			p = _UT31_SL_C( b, 1 );
			break;
		case UTER27_C_4:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 3+1 */
			break;
		case UTER27_C_5:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			break;
		case UTER27_C_6:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 3*2 */
			break;
		case UTER27_C_7:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ), b );  /* *3+1 */
			break;
		case UTER27_C_8:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_9:
			p = _UT31_SL_C( b, 2 );
			break;
		case UTER27_C_10:
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , b ); /* 9+1 */
			break;
		case UTER27_C_11:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_12:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_13:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_14:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ), p );  /* 9+ */
			break;
		case UTER27_C_15:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT31_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER27_C_16:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_17:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_18:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 2 );  /* 2*9 */
			break;
		case UTER27_C_19:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 2 );  /* 2*9 */
			p = _UT31_ADD( p, b );			 /* +1 */
			break;
		case UTER27_C_20:
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , b ); /* 9+1 */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_21:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ), b );  /* *3+1 */
			p = _UT31_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER27_C_22:
			p = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT31_ADD( p, p );			 /* *2 */
			break;
		case UTER27_C_23:
			q = _UT31_ADD( b, b );			 /* 2  */
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , q ); /* 3+ */
			p = _UT31_ADD( _UT31_SL_C( q, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_24:
			p = _UT31_SL_C( _UT31_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER27_C_25:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER27_C_26:
			p = _UT31_ADD( _UT31_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT31_ADD( _UT31_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT31_ADD( p, p );			 /* *2 */
		}
		uter27_prod_top = _UT31_ADD( uter27_prod_top, p );
		uter27_prod_low = UTER27_SR_C( uter27_prod_low, 3)
			       | UTER27_SL_C( uter27_prod_top, 24);
		uter27_prod_top = _UT31_SR_C( uter27_prod_top, 3);
	}
}

bter27_t bter27_prod_top, bter27_prod_low; /* double register for product */
void void_bter27_mul( bter27_t a, bter27_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand and product left, giving a long result. */
	bter27_prod_top = _BT31_C_0; 
	bter27_prod_low = a;
	uter27_t c, d, e; /* used by _BT31_ADD() */
	int i;
	b = _BT31_BT27( b );
	for (i = 9; i > 0; i--) { /* base 27 multiply */
		bter27_t p; /* partial product */
		switch (bter27_prod_low & _T3_MASK) {
		case BTER27_C_N13 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), p ) );
			break;
		case BTER27_C_N12 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_SL_C( _BT31_ADD( p, p ), 1 ) );
			break;
		case BTER27_C_N11 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), p ) );
			break;
		case BTER27_C_N10 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 2 ), b ) );
			break;
		case BTER27_C_N9 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( b, 2 ) );
			break;
		case BTER27_C_N8 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( p, 1 ), p ) );
			break;
		case BTER27_C_N7 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( p, 1 ), b ) );
			break;
		case BTER27_C_N6 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( _BT31_ADD( b, b ), 1 ) );
			break;
		case BTER27_C_N5 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 1 ), p ) );
			break;
		case BTER27_C_N4 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( _BT31_SL_C( b, 1 ), b ) );
			break;
		case BTER27_C_N3 & _T3_MASK:
			p = _BT31_NEG( _BT31_SL_C( b, 1 ) );
			break;
		case BTER27_C_N2 & _T3_MASK:
			p = _BT31_NEG( _BT31_ADD( b, b ) );
			break;
		case BTER27_C_N1 & _T3_MASK:
			p = _BT31_NEG( b );
			break;
		case BTER27_C_0 & _T3_MASK:
			p = _BT31_C_0;
			break;
		case BTER27_C_1 & _T3_MASK:
			p = b;
			break;
		case BTER27_C_2 & _T3_MASK:
			p = _BT31_ADD( b, b );
			break;
		case BTER27_C_3 & _T3_MASK:
			p = _BT31_SL_C( b, 1 );
			break;
		case BTER27_C_4 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ) , b );
			break;
		case BTER27_C_5 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), p );
			break;
		case BTER27_C_6 & _T3_MASK:
			p = _BT31_SL_C( _BT31_ADD( b, b ), 1 );
			break;
		case BTER27_C_7 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( p, 1 ), b );
			break;
		case BTER27_C_8 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( p, 1 ), p );
			break;
		case BTER27_C_9 & _T3_MASK:
			p = _BT31_SL_C( b, 2 );
			break;
		case BTER27_C_10 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), b );
			break;
		case BTER27_C_11 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), p );
			break;
		case BTER27_C_12 & _T3_MASK:
			p = _BT31_ADD( b, b );
			p = _BT31_SL_C( _BT31_ADD( p, p ), 1 );
			break;
		case BTER27_C_13 & _T3_MASK:
			p = _BT31_ADD( _BT31_SL_C( b, 1 ), b );
			p = _BT31_ADD( _BT31_SL_C( b, 2 ), p );
		}
		bter27_prod_top = _BT31_ADD( bter27_prod_top, p );
		/* regular shifts work because all trits are accounted for */
		bter27_prod_low = ( (bter27_prod_low >> 6)
				 | (bter27_prod_top << 48)
				 ) & _TER27_MASK;
		/* all the shifting above may have put junk into high bits */
		bter27_prod_top = _BT31_SR_C( bter27_prod_top & _T31_MASK, 3);
	}
	bter27_prod_top = bter27_prod_top & _TER27_MASK;
}

/* uter27_t uter27_rem, uter27_quo; */
void void_uter27_divl( uter27_t ah, uter27_t al, uter27_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter27_t c, d, e; /* used by _UT31_ADD() */
	uter27_t negb = _UT31_ADD( _UT31_2S_COMP( b ), UTER27_C_1 );

	uter27_quo = al; /* quo initially holds the dividend low half */
	uter27_rem = ah; /* rem initially holds the dividend high half */

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 27; i++) { /* divide step */
		/* first, shift rem-quo double-register 1 trit left */
		uter27_rem = _UT31_SL_C( uter27_rem, 1 )
			   | _UT31_SR_C( uter27_quo, 26 );
		uter27_quo = UTER27_SL_C( uter27_quo, 1 );

		/* second, compute one trit of quotient */
		if (uter27_rem >= b) { /* mostly the same as binary division */
			uter27_quo++;
			uter27_rem = _UT31_ADD( uter27_rem, negb )
				   & _T31_MASK;
			if (uter27_rem >= b) { /* this step added for ternary */
				uter27_quo++;
				uter27_rem = _UT31_ADD( uter27_rem, negb )
					   & _T31_MASK;
			}
		}
		/* BUG: need to mask uter27_rem? */
	}
}

/* bter27_t bter27_rem, bter27_quo; */
void void_bter27_divl( bter27_t ah, bter27_t al, bter27_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter27_t c, d, e; /* used by _UT31_ADD() */
	bter27_t one = 1; /* binary 1 (careful rule violation here) */
	bter27_t trem, nrem; /* tentative remainder and its negation */

        if (b < BTER27_C_0) { /* take absolute value of divisor */
                b = bter27_neg( b );
                one = UINT64_C(0xFFFFFFFFFFFFFFFF); /* binary -1 (violation) */
        }

	/* widen b and keep negative on hand, dividend similarly widened */
	b = _BT31_BT27( b );
	bter27_t negb = _BT31_NEG( b );

	bter27_rem = _BT31_BT27( ah ); /* rem starts as high half dividend */
	bter27_quo = al; /* quo initially holds the dividend low half */

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 27; i++) { /* divide step */
		/* first, shift rem-quo balanced double-register 1 trit left */
		bter27_rem = ((bter27_rem << 2) | (bter27_quo >> 52))
			     & _T31_MASK;
		bter27_quo = BTER27_SL_C( bter27_quo, 1 );

		/* second, compute one trit of quotient */
		if (bter27_rem >= _BT31_C_0) {
			trem = _BT31_ADD( bter27_rem, negb ) & _T31_MASK;
			nrem = _BT31_NEG( trem );
			if ( (nrem < bter27_rem)
			||   (  (nrem == bter27_rem)
			     && (bter27_quo > BTER27_C_0)  ) ) {
				bter27_quo = bter27_quo + one; /* violation */
				bter27_rem = trem;
			}
		} else if (bter27_rem < _BT31_C_0) {
			trem = _BT31_ADD( bter27_rem, b ) & _T31_MASK;
			nrem = _BT31_NEG( trem );
			if ( (nrem > bter27_rem)
			||   (  (nrem == bter27_rem)
			     && (bter27_quo < BTER27_C_0)  ) ) {
				bter27_quo = bter27_quo - one; /* violation */
				bter27_rem = trem;
			}
		}
	}
	bter27_rem = bter27_rem & _TER27_MASK;
}

/* conversion routines, between binary and ternary */

uint64_t uint64_uter27( uter27_t ta ) {
        /* note:  All possible values can be converted */
        /* for comments, see the 9-trit version */
        uint64_t high = (ta >> 2) & UINT64_C(0x0033333333333333);
        uint64_t acc =  ta        & UINT64_C(0x0033333333333333);
        acc = acc + (3 * high);
        high = (acc >> 4)         & UINT64_C(0x000F0F0F0F0F0F0F);
        acc =  acc                & UINT64_C(0x000F0F0F0F0F0F0F);
        acc = acc + (9 * high);
        high = (acc >> 8)         & UINT64_C(0x003F00FF00FF00FF);
        acc =  acc                & UINT64_C(0x003F00FF00FF00FF);
        acc = acc + (81 * high);
        high = (acc >> 16)        & UINT64_C(0x0000FFFF0000FFFF);
        acc =  acc                & UINT64_C(0x0000FFFF0000FFFF);
        acc = acc + (6561 * high);
        high = (acc >> 32)        & UINT64_C(0x00000000FFFFFFFF);
        acc =  acc                & UINT64_C(0x00000000FFFFFFFF);
        return (uint64_t) acc + (43046721 * high);
}

uter27_t uter27_uint64( uint64_t ba ) {
        /* note:  Numbers larger than 3**27-1 are illegal and convert wrong */
        /* BUG:  This should be fixed to raise an exception or something */
        uter27_t ta = UTER27_C_0;
	uter27_t c, d, e; /* used by _UT31_ADD() */
        int i;
        for ( i = 64; i != 0; i-- ) { /* for 64 bits, most sig first */
                ta = _UT31_ADD( ta, ta );
                ta = _UT31_ADD( ta, ((ba & UINT64_C(0x8000000000000000))>>63) );
                ba = ba << 1;
        }
        return ta & _TER27_MASK;
}

int64_t int64_bter27( bter27_t ta ) {
	/* note: INT64_BTER27_C_MAX is the bias */
	return uint64_uter27( ta ) - INT64_BTER27_C_MAX;
}

bter27_t bter27_int64( int64_t ba ) {
	/* note: INT64_BTER27_C_MAX is the bias */
	return uter27_uint64( ba + INT64_BTER27_C_MAX );
}

/* conversion routines, between biased and unsigned */

bter27_t bter27_uter27( uter27_t a ) {
	uter27_t c, d, e;
	/* note: BTER27_C_1 is the 2's comp of BTER27_C_0 which is the bias */
	return _UT31_ADD( a, BTER27_C_1 ) & _TER27_MASK;
	/* so this code subtracts the bias */
}

uter27_t uter27_bter27( uter27_t a ) {
	uter27_t c, d, e;
	/* note: BTER27_C_0 is the bias */
	return _UT31_ADD( a, BTER27_C_0 ) & _TER27_MASK;
}
