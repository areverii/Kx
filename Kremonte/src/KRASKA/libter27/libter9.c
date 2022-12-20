/* libter9.c */
/**********
 * Ternary Data Types for C Programmers
 *      9-trit Ternary Support
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

#include "libter9.h"

/* arithmetic support
 * we need at least 9+3 places of precision in intermediate results
 * because of use of base 27 in multiplication algorithm;
 * we would need just 1 trit of extra precision for base 3 multiply.
 */

/* masks and constants */
#define _T15_MASK UINT32_C(0x3FFFFFFF)
#define _UT15_C_0 UINT64_C(0x00000000)
#define _BT15_C_NEGBIAS UINT32_C(0x15555556)
#define _BT15_C_0 UINT32_C(0x15555555)
#define _T3_MASK UINT32_C(0x0000003F)

/* to call _UT15_ADD, first declare uter9_t c, d, e */
#define _UT15_ADD( a, b ) (					\
     c = (a) + _BT15_C_0,				\
     d = (b) + c,						\
     e = (~((b) ^ c ^ d) & UINT32_C(0x55555554)) >> 2,		\
     d - e							\
)

/* to call _BT15_ADD, first declare uter9_t c, d, e for _UT15_ADD */
#define _BT15_ADD( a, b ) (					\
	_UT15_ADD( _UT15_ADD( a, b ), _BT15_C_NEGBIAS )		\
)

#define _UT15_2S_COMP( a ) (UINT32_C(0x2AAAAAAA) - (a))

#define _UT15_SL_C( a, b ) ((a) << (2*(b)))
#define _UT15_SR_C( a, b ) ((a) >> (2*(b)))

#define _BT15_BT9( a ) (a | UINT32_C(0x15540000))

#define _BT15_NEG( a ) _UT15_2S_COMP( a )

#define _BT15_SL_C( a, b ) (						\
	((a) << (2*(b))) | (_BT15_C_0 >> (2*(15 - (b))))	\
)

#define _BT15_SR_C( a, b ) (						\
	(((a) >> (2*(b))) | (_BT15_C_0 << (2*(15 - (b)))))	\
	& _T15_MASK							\
)

/* simple add and subtract */

uter9_t uter9_add( uter9_t a, uter9_t b ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	return _UT15_ADD( a, b ) & _TER9_MASK;
}

bter9_t bter9_add( bter9_t a, bter9_t b ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	return _BT15_ADD( a, b ) & _TER9_MASK;
}
	
uter9_t uter9_sub( uter9_t a, uter9_t b ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	b = _UT9_2S_COMP( b );
	b = _UT15_ADD( b, UTER9_C_1 );
	return _UT15_ADD( a, b ) & _TER9_MASK;
}

bter9_t bter9_neg( bter9_t a ) {
	return _UT9_2S_COMP( a );
}

bter9_t bter9_sub( bter9_t a, bter9_t b ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	return _BT15_ADD( a, _UT9_2S_COMP( b )) & _TER9_MASK;
}

/* special add and subtract */

uter9_t uter9_addsr_c( uter9_t a, uter9_t b, unsigned int s ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	return (_UT15_ADD( a, b ) >> (s << 1)) & _TER9_MASK;
}

bter9_t bter9_addsr_c( bter9_t a, bter9_t b, unsigned int s ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	return (_BT15_ADD( _BT15_BT9( a ), _BT15_BT9( b ) ) >> (s << 1))
		& _TER9_MASK;
}

uter9_t uter9_carry; /* must be either 0 or 1 */
uter9_t uter9_addc( uter9_t a, uter9_t b, uter9_t cin ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	b = b + cin; /* strange but true: safe to use binary add here */
	a = _UT15_ADD( a, b );
	uter9_carry = (a >> 18) & UINT32_C(3);
        return  a & _TER9_MASK;
}

bter9_t bter9_carry; /* must be either -1, 0 or 1 */
bter9_t bter9_addc( bter9_t a, bter9_t b, bter9_t cin ) {
	uter9_t c, d, e; /* used by _UT15_ADD() */
	a = _UT15_ADD( _BT15_BT9( a ), _BT15_BT9( b ) );
	a = _UT15_ADD( a, _BT15_BT9( cin + 1 ) );
	bter9_carry = ((a >> 18) & UINT32_C(3)) | BTER9_C_N1;
	return a & _TER9_MASK;
}

/* shift operations */

uter9_t uter9_sl_c( uter9_t a, unsigned int b ) {
	return UTER9_SL_C( a, b );
}

bter9_t bter9_sl_c( bter9_t a, unsigned int b ) {
	return BTER9_SL_C( a, b );
}

uter9_t uter9_sr_c( uter9_t a, unsigned int b ) {
	return UTER9_SR_C( a, b );
}

bter9_t bter9_sr_c( bter9_t a, unsigned int b ) {
	return BTER9_SR_C( a, b );
}

/* logic operations */

uter9_t ter9_min( uter9_t a, uter9_t b ) {
	return TER9_MIN( a, b );
}

uter9_t ter9_max( uter9_t a, uter9_t b ) {
	return TER9_MAX( a, b );
}

uter9_t ter9_neg( uter9_t a ) {
	return TER9_NEG( a );
}

uter9_t ter9_xor( uter9_t a, uter9_t b ) {
	uter9_t nega = _TER9_LOGIC( TER9_NEG( a ) );
	uter9_t negb = _TER9_LOGIC( TER9_NEG( b ) );
	a = _TER9_LOGIC( a );
	b = _TER9_LOGIC( b );
	a = (a & negb) | (b & nega);
	return _TER9_LOGIC( a );
}

uter9_t ter9_equ( uter9_t a, uter9_t b ) {
        uter9_t nega = _TER9_LOGIC( TER9_NEG( a ) );
        uter9_t negb = _TER9_LOGIC( TER9_NEG( b ) );
        a = _TER9_LOGIC( a );
        b = _TER9_LOGIC( b );
        a = (a & b) | (nega & negb);
        return _TER9_LOGIC( a );
}

/* multiply and divide: basic */

uter9_t uter9_mul( uter9_t a, uter9_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand left and the multiplier right
	   to accumulate the least significant 9 trits of the product;
	   the more significant trits of the product are discarded. */
	uter9_t prod = UTER9_C_0;
	uter9_t c, d, e; /* used by _UT15_ADD() */
	uter9_t p, q; /* the partial product and a rarely used temporary */
	while (a != UTER9_C_0) {
		switch (a & _T3_MASK) { /* compute partial prod */
		case UTER9_C_0:
			p = UTER9_C_0;
			break;
		case UTER9_C_1:
			p = b;
			break;
		case UTER9_C_2:
			p = _UT15_ADD( b, b );
			break;
		case UTER9_C_3:
			p = _UT15_SL_C( b, 1 );
			break;
		case UTER9_C_4:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 3+1 */
			break;
		case UTER9_C_5:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			break;
		case UTER9_C_6:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 3*2 */
			break;
		case UTER9_C_7:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ), b );  /* *3+1 */
			break;
		case UTER9_C_8:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_9:
			p = _UT15_SL_C( b, 2 );
			break;
		case UTER9_C_10:
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , b ); /* 9+1 */
			break;
		case UTER9_C_11:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_12:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_13:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_14:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ), p );  /* 9+ */
			break;
		case UTER9_C_15:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT15_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER9_C_16:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_17:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_18:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 2 );  /* 2*9 */
			break;
		case UTER9_C_19:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 2 );  /* 2*9 */
			p = _UT15_ADD( p, b );			 /* +1 */
			break;
		case UTER9_C_20:
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , b ); /* 9+1 */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_21:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ), b );  /* *3+1 */
			p = _UT15_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER9_C_22:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_23:
			q = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , q ); /* 3+ */
			p = _UT15_ADD( _UT15_SL_C( q, 2 ) , p ); /* 18+ */
			break;
		case UTER9_C_24:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_25:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_26:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT15_ADD( p, p );			 /* *2 */
		}
		a = UTER9_SR_C( a, 3 );
		prod = _UT15_ADD( prod, p );
		b = _UT15_SL_C( b, 3 );
	}
	return prod & _TER9_MASK;
}

bter9_t bter9_mul( bter9_t a, bter9_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand left and the multiplier right
	   to accumulate the least significant 9 trits of the product;
	   the more significant trits of the product are discarded. */
	bter9_t prod = BTER9_C_0;
	uter9_t c, d, e; /* used by _BT15_ADD() */
	int i;
	b = _BT15_BT9( b );
	for (i = 3; i > 0; i--) { /* base 27 multiply */
		bter9_t p; /* partial product */
		switch (a & _T3_MASK) {
		case BTER9_C_N13 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), p ) );
			break;
		case BTER9_C_N12 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_SL_C( _BT15_ADD( p, p ), 1 ) );
			break;
		case BTER9_C_N11 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), p ) );
			break;
		case BTER9_C_N10 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), b ) );
			break;
		case BTER9_C_N9 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( b, 2 ) );
			break;
		case BTER9_C_N8 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( p, 1 ), p ) );
			break;
		case BTER9_C_N7 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( p, 1 ), b ) );
			break;
		case BTER9_C_N6 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( _BT15_ADD( b, b ), 1 ) );
			break;
		case BTER9_C_N5 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 1 ), p ) );
			break;
		case BTER9_C_N4 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 1 ), b ) );
			break;
		case BTER9_C_N3 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( b, 1 ) );
			break;
		case BTER9_C_N2 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( b, b ) );
			break;
		case BTER9_C_N1 & _T3_MASK:
			p = _BT15_NEG( b );
			break;
		case BTER9_C_0 & _T3_MASK:
			p = _BT15_C_0;
			break;
		case BTER9_C_1 & _T3_MASK:
			p = b;
			break;
		case BTER9_C_2 & _T3_MASK:
			p = _BT15_ADD( b, b );
			break;
		case BTER9_C_3 & _T3_MASK:
			p = _BT15_SL_C( b, 1 );
			break;
		case BTER9_C_4 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ) , b );
			break;
		case BTER9_C_5 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), p );
			break;
		case BTER9_C_6 & _T3_MASK:
			p = _BT15_SL_C( _BT15_ADD( b, b ), 1 );
			break;
		case BTER9_C_7 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( p, 1 ), b );
			break;
		case BTER9_C_8 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( p, 1 ), p );
			break;
		case BTER9_C_9 & _T3_MASK:
			p = _BT15_SL_C( b, 2 );
			break;
		case BTER9_C_10 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), b );
			break;
		case BTER9_C_11 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), p );
			break;
		case BTER9_C_12 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_SL_C( _BT15_ADD( p, p ), 1 );
			break;
		case BTER9_C_13 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), b );
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), p );
		}
		prod = _BT15_ADD( prod, p );
		a = BTER9_SR_C( a, 3 );
		b = _BT15_SL_C( b, 3 );
	}
	return prod & _TER9_MASK;
}

uter9_t uter9_rem, uter9_quo;
void void_uter9_div( uter9_t a, uter9_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter9_t c, d, e; /* used by _UT15_ADD() */
	uter9_t negb = _UT15_ADD( _UT15_2S_COMP( b ), UTER9_C_1 );

	uter9_quo = a; /* quo initially holds the dividend */
	uter9_rem = UTER9_C_0;

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 9; i++) { /* divide step */
		/* first, shift rem-quo double-register 1 trit left */
		uter9_rem = _UT15_SL_C( uter9_rem, 1 )
			  | _UT15_SR_C( uter9_quo, 8 );
		uter9_quo = UTER9_SL_C( uter9_quo, 1 );

		/* second, compute one trit of quotient */
		if (uter9_rem >= b) { /* mostly the same as binary division */
			uter9_quo++;
			uter9_rem = _UT15_ADD( uter9_rem, negb ) & _T15_MASK;
			if (uter9_rem >= b) { /* this step added for ternary */
				uter9_quo++;
				uter9_rem = _UT15_ADD( uter9_rem, negb )
					  & _T15_MASK;
			}
		}
	}
}

/* optimization done above with _BT15_ADD() not done below (balanced is ugly) */
bter9_t bter9_rem, bter9_quo;
void void_bter9_div( bter9_t a, bter9_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	bter9_t one = 1;	/* binary 1 (careful rule violation here) */
	bter9_t trem, nrem;	/* candidate for next remainder */

	if (b < BTER9_C_0) { /* take absolute value of divisor */
		b = bter9_neg( b );
		one = UINT32_C(0xFFFFFFFF); /* binary -1 (rule violation) */
	}

        bter9_rem = BTER9_C_0;
        bter9_quo = a;

	/* the simple, stupid algorithm for division */
	for (i = 0; i < 9; i++) { /* divide step */
		/* first, shift rem-quo balanced double-register 1 trit left */
		bter9_rem = ((bter9_rem << 2)+(bter9_quo >> 16)) & _TER9_MASK;
		bter9_quo = BTER9_SL_C( bter9_quo, 1 );

		/* second, compute one trit of quotient */
		if (bter9_rem > BTER9_C_0) {
                        trem = bter9_sub( bter9_rem, b );
                        nrem = bter9_neg( trem );
			if ( (nrem < bter9_rem)
			||   (  (nrem == bter9_rem)
                             && (bter9_quo > BTER9_C_0)  ) ) {
				bter9_quo = bter9_quo + one; /* violation */
				bter9_rem = trem;
			}
		} else if (bter9_rem < BTER9_C_0) {
                        trem = bter9_add( bter9_rem, b );
                        nrem = bter9_neg( trem );
			if ( (nrem > bter9_rem)
			||  (  (nrem == bter9_rem)
                            && (bter9_quo < BTER9_C_0)  ) ) {
				bter9_quo = bter9_quo - one; /* violation */
				bter9_rem = trem;
			}
		}
	}
}

/* bter9_t bter9_rem, bter9_quo; */
void void_bter9_div_down( bter9_t a, bter9_t b ) {
	void_bter9_div( a, b );
	if (bter9_rem < BTER9_C_0) {
		if (b > BTER9_C_0) {
			bter9_rem = bter9_add( bter9_rem, b );
			bter9_quo = bter9_sub( bter9_quo, BTER9_C_1 );
		} else {
			bter9_rem = bter9_sub( bter9_rem, b );
			bter9_quo = bter9_add( bter9_quo, BTER9_C_1 );
		}
	}
}

/* bter9_t bter9_rem, bter9_quo; */
void void_bter9_div_up( bter9_t a, bter9_t b ) {
	void_bter9_div( a, b );
	if (bter9_rem > BTER9_C_0) {
		if (b > BTER9_C_0) {
			bter9_rem = bter9_sub( bter9_rem, b );
			bter9_quo = bter9_add( bter9_quo, BTER9_C_1 );
		} else {
			bter9_rem = bter9_add( bter9_rem, b );
			bter9_quo = bter9_sub( bter9_quo, BTER9_C_1 );
		}
	}
}

/* multiply and divide: special */

uter9_t uter9_prod_top, uter9_prod_low; /* double register for product */
void void_uter9_mul( uter9_t a, uter9_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand and product left, giving a long result. */
	uter9_prod_top = _UT15_C_0;
	uter9_prod_low = a;
	uter9_t c, d, e; /* used by _UT15_ADD() */
	uter9_t p, q; /* the partial product and a rarely used temporary */
	int i;
	for (i = 3; i > 0; i--) { /* base 27 multiply */
		/* 27 cases based on least significant 3 trits of multiplier */
		switch (uter9_prod_low & _T3_MASK) {
		case UTER9_C_0:
			p = UTER9_C_0;
			break;
		case UTER9_C_1:
			p = b;
			break;
		case UTER9_C_2:
			p = _UT15_ADD( b, b );
			break;
		case UTER9_C_3:
			p = _UT15_SL_C( b, 1 );
			break;
		case UTER9_C_4:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 3+1 */
			break;
		case UTER9_C_5:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			break;
		case UTER9_C_6:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 3*2 */
			break;
		case UTER9_C_7:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ), b );  /* *3+1 */
			break;
		case UTER9_C_8:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_9:
			p = _UT15_SL_C( b, 2 );
			break;
		case UTER9_C_10:
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , b ); /* 9+1 */
			break;
		case UTER9_C_11:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_12:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_13:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_14:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ), p );  /* 9+ */
			break;
		case UTER9_C_15:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ), p );  /* 3+ */
			p = _UT15_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER9_C_16:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_17:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_18:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 2 );  /* 2*9 */
			break;
		case UTER9_C_19:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 2 );  /* 2*9 */
			p = _UT15_ADD( p, b );			 /* +1 */
			break;
		case UTER9_C_20:
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , b ); /* 9+1 */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_21:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ), b );  /* *3+1 */
			p = _UT15_SL_C( p, 1 );			 /* *3 */
			break;
		case UTER9_C_22:
			p = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT15_ADD( p, p );			 /* *2 */
			break;
		case UTER9_C_23:
			q = _UT15_ADD( b, b );			 /* 2  */
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , q ); /* 3+ */
			p = _UT15_ADD( _UT15_SL_C( q, 2 ) , p ); /* 18+ */
			break;
		case UTER9_C_24:
			p = _UT15_SL_C( _UT15_ADD( b, b ), 1 );  /* 2*3 */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			break;
		case UTER9_C_25:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( p, 1 ) , p ); /* *4 */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			break;
		case UTER9_C_26:
			p = _UT15_ADD( _UT15_SL_C( b, 1 ) , b ); /* 4  */
			p = _UT15_ADD( _UT15_SL_C( b, 2 ) , p ); /* 9+ */
			p = _UT15_ADD( p, p );			 /* *2 */
		}
		uter9_prod_top = _UT15_ADD( uter9_prod_top, p );
		uter9_prod_low = UTER9_SR_C( uter9_prod_low, 3)
			       | UTER9_SL_C( uter9_prod_top, 6);
		uter9_prod_top = _UT15_SR_C( uter9_prod_top, 3);
	}
}

bter9_t bter9_prod_top, bter9_prod_low; /* double register for product */
void void_bter9_mul( bter9_t a, bter9_t b ) {
	/* this is a base 27 (three trits at a time) multiply,
	   it adds the least significant partial product first,
	   shifting the multiplicand and product left, giving a long result. */
	bter9_prod_top = _BT15_C_0; 
	bter9_prod_low = a;
	uter9_t c, d, e; /* used by _BT15_ADD() */
	int i;
	b = _BT15_BT9( b );
	for (i = 3; i > 0; i--) { /* base 27 multiply */
		bter9_t p; /* partial product */
		switch (bter9_prod_low & _T3_MASK) {
		case BTER9_C_N13 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), p ) );
			break;
		case BTER9_C_N12 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_SL_C( _BT15_ADD( p, p ), 1 ) );
			break;
		case BTER9_C_N11 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), p ) );
			break;
		case BTER9_C_N10 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 2 ), b ) );
			break;
		case BTER9_C_N9 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( b, 2 ) );
			break;
		case BTER9_C_N8 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( p, 1 ), p ) );
			break;
		case BTER9_C_N7 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( p, 1 ), b ) );
			break;
		case BTER9_C_N6 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( _BT15_ADD( b, b ), 1 ) );
			break;
		case BTER9_C_N5 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 1 ), p ) );
			break;
		case BTER9_C_N4 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( _BT15_SL_C( b, 1 ), b ) );
			break;
		case BTER9_C_N3 & _T3_MASK:
			p = _BT15_NEG( _BT15_SL_C( b, 1 ) );
			break;
		case BTER9_C_N2 & _T3_MASK:
			p = _BT15_NEG( _BT15_ADD( b, b ) );
			break;
		case BTER9_C_N1 & _T3_MASK:
			p = _BT15_NEG( b );
			break;
		case BTER9_C_0 & _T3_MASK:
			p = _BT15_C_0;
			break;
		case BTER9_C_1 & _T3_MASK:
			p = b;
			break;
		case BTER9_C_2 & _T3_MASK:
			p = _BT15_ADD( b, b );
			break;
		case BTER9_C_3 & _T3_MASK:
			p = _BT15_SL_C( b, 1 );
			break;
		case BTER9_C_4 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ) , b );
			break;
		case BTER9_C_5 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), p );
			break;
		case BTER9_C_6 & _T3_MASK:
			p = _BT15_SL_C( _BT15_ADD( b, b ), 1 );
			break;
		case BTER9_C_7 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( p, 1 ), b );
			break;
		case BTER9_C_8 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( p, 1 ), p );
			break;
		case BTER9_C_9 & _T3_MASK:
			p = _BT15_SL_C( b, 2 );
			break;
		case BTER9_C_10 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), b );
			break;
		case BTER9_C_11 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), p );
			break;
		case BTER9_C_12 & _T3_MASK:
			p = _BT15_ADD( b, b );
			p = _BT15_SL_C( _BT15_ADD( p, p ), 1 );
			break;
		case BTER9_C_13 & _T3_MASK:
			p = _BT15_ADD( _BT15_SL_C( b, 1 ), b );
			p = _BT15_ADD( _BT15_SL_C( b, 2 ), p );
		}
		bter9_prod_top = _BT15_ADD( bter9_prod_top, p );
		/* regular shifts work because all trits are accounted for */
		bter9_prod_low = ( (bter9_prod_low >> 6)
				 | (bter9_prod_top << 12)
				 ) & _TER9_MASK;
		/* all the shifting above may have put junk into high bits */
		bter9_prod_top = _BT15_SR_C( bter9_prod_top & _T15_MASK, 3);
	}
	bter9_prod_top = bter9_prod_top & _TER9_MASK;
}

/* uter9_t uter9_rem, uter9_quo; */
void void_uter9_divl( uter9_t ah, uter9_t al, uter9_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter9_t c, d, e; /* used by _UT15_ADD() */
	uter9_t negb = _UT15_ADD( _UT15_2S_COMP( b ), UTER9_C_1 );

	uter9_quo = al; /* quo initially holds the dividend low half */
	uter9_rem = ah; /* rem initially holds the dividend high half */

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 9; i++) { /* divide step */
		/* first, shift rem-quo double-register 1 trit left */
		uter9_rem = _UT15_SL_C( uter9_rem, 1 )
			  | _UT15_SR_C( uter9_quo, 8 );
		uter9_quo = UTER9_SL_C( uter9_quo, 1 );

		/* second, compute one trit of quotient */
		if (uter9_rem >= b) { /* mostly the same as binary division */
			uter9_quo++;
			uter9_rem = _UT15_ADD( uter9_rem, negb ) & _T15_MASK;
			if (uter9_rem >= b) { /* this step added for ternary */
				uter9_quo++;
				uter9_rem = _UT15_ADD( uter9_rem, negb )
					    & _T15_MASK;
			}
		}
		/* BUG: need to mask uter9_rem? */
	}
}

/* bter9_t bter9_rem, bter9_quo; */
void void_bter9_divl( bter9_t ah, bter9_t al, bter9_t b ) {
        /* BUG:  This should do something about division by zero */
	int i;
	uter9_t c, d, e; /* used by _UT15_ADD() */
	bter9_t one = 1; /* binary 1 (careful rule violation here) */
	bter9_t trem, nrem; /* tentative remainder and its negation */

        if (b < BTER9_C_0) { /* take absolute value of divisor */
                b = bter9_neg( b );
                one = UINT32_C(0xFFFFFFFF); /* binary -1 (rule violation) */
        }

	/* widen b and keep negative on hand, dividend similarly widened */
	b = _BT15_BT9( b );
	bter9_t negb = _BT15_NEG( b );

	bter9_rem = _BT15_BT9( ah ); /* rem initially the high half dividend */
	bter9_quo = al; /* quo initially holds the dividend low half */

	/* the simple, stupid algorithm for division, do better later */
	for (i = 0; i < 9; i++) { /* divide step */
		/* first, shift rem-quo balanced double-register 1 trit left */
		bter9_rem = ((bter9_rem << 2)|(bter9_quo >> 16)) & _T15_MASK;
		bter9_quo = BTER9_SL_C( bter9_quo, 1 );

		/* second, compute one trit of quotient */
		if (bter9_rem >= _BT15_C_0) {
			trem = _BT15_ADD( bter9_rem, negb ) & _T15_MASK;
			nrem = _BT15_NEG( trem );
			if ( (nrem < bter9_rem)
			||   (  (nrem == bter9_rem)
			     && (bter9_quo > BTER9_C_0)  ) ) {
				bter9_quo = bter9_quo + one; /* violation */
				bter9_rem = trem;
			}
		} else if (bter9_rem < _BT15_C_0) {
			trem = _BT15_ADD( bter9_rem, b ) & _T15_MASK;
			nrem = _BT15_NEG( trem );
			if ( (nrem > bter9_rem)
			||   (  (nrem == bter9_rem)
			     && (bter9_quo < BTER9_C_0)  ) ) {
				bter9_quo = bter9_quo - one; /* violation */
				bter9_rem = trem;
			}
		}
	}
	bter9_rem = bter9_rem & _TER9_MASK;
}

/* conversion routines, between binary and ternary */

uint16_t uint16_uter9( uter9_t ta ) {
        /* note:  All possible values can be converted */
	uint32_t high = (ta >> 2) & UINT32_C(0x00033333); /* high trits */
	uint32_t acc =  ta        & UINT32_C(0x00033333); /* low trits */
	acc = acc + (3 * high); /* acc is now binary-coded base 9 */
	high = (acc >> 4)         & UINT32_C(0x00030F0F); /* high digits */
	acc =  acc                & UINT32_C(0x00030F0F); /* low digits */
        acc = acc + (9 * high); /* acc is now binary-coded base 81 */
	high = (acc >> 8)         & UINT32_C(0x000300FF); /* high digits */
	acc =  acc                & UINT32_C(0x000300FF); /* low digits */
        acc = acc + (81 * high); /* acc is now binary-coded base 6561 */
        high = (acc >> 16)        & UINT32_C(0x0000FFFF); /* high digits */
        acc =  acc                & UINT32_C(0x0000FFFF); /* low digits */
        return (uint16_t) acc + (6561 * high);

	/* the above code replaces this trivial iterative code
	uint16_t ba = 0;
        int i;
        for ( i = 9; i != 0; i-- ) {
                ba = (ba * 3) + ((ta & UINT32_C(0x00030000)) >> 16);
                ta = ta << 2;
        }
        return ba;
	*/
}

uter9_t uter9_uint16( uint16_t ba ) {
        /* note:  Numbers larger than 3**9-1 are illegal and convert wrong */
        /* BUG:  This should be fixed to raise an exception or something */
        uter9_t ta = UTER9_C_0;
	uter9_t c, d, e; /* used by _UT15_ADD() */
        int i;
        for ( i = 16; i != 0; i-- ) { /* for 16 bits, most sig first */
                ta = _UT15_ADD( ta, ta );
                ta = _UT15_ADD( ta, ((ba & UINT16_C(0x8000)) >> 15) );
                ba = ba << 1;
        }
        return ta & _TER9_MASK;
}

int16_t int16_bter9( bter9_t ta ) {
	/* note: INT16_BTER9_C_MAX is the bias */
	return uint16_uter9( ta ) - INT16_BTER9_C_MAX;
}

bter9_t bter9_int16( int16_t ba ) {
	/* note: INT16_BTER9_C_MAX is the bias */
	return uter9_uint16( ba + INT16_BTER9_C_MAX );
}

/* conversion routines, between biased and unsigned */

bter9_t bter9_uter9( uter9_t a ) {
	uter9_t c, d, e;
	/* note: BTER9_C_1 is the 2's comp of BTER9_C_0 which is the bias */
	return _UT15_ADD( a, BTER9_C_1 ) & _TER9_MASK;
	/* so this code subtracts the bias */
}

uter9_t uter9_bter9( uter9_t a ) {
	uter9_t c, d, e;
	/* note: BTER9_C_0 is the bias */
	return _UT15_ADD( a, BTER9_C_0 ) & _TER9_MASK;
}
