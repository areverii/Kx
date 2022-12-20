/* libter27.h */
/**********
 * Ternary Data Types for C Programmers
 *      27-trit Ternary Support
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
#define _LIBTER27_H

#include <stdint.h>

/* exact width data types */
typedef uint64_t uter27_t;  /* 27-trit unsigned ternary in 64-bit binary */
typedef uint64_t bter27_t;  /* 27-trit balanced ... */

/* limits on exact-width data types expressed in that data type */
#define UTER27_C_MAX	UINT64_C(0x002AAAAAAAAAAAAA)
#define BTER27_C_MAX	UTER27_C_MAX

/* Binary equivalents of above limits */
#define UINT64_UTER27_C_MAX	UINT64_C(7625597484986)
#define INT64_BTER27_C_MAX	INT64_C(3812798742493)

/* small unsigned ternary constants */
#define UTER27_C_0      UINT64_C(0x0000000000000000)
#define UTER27_C_1      UINT64_C(0x0000000000000001)
#define UTER27_C_2      UINT64_C(0x0000000000000002)
#define UTER27_C_3      UINT64_C(0x0000000000000004)
#define UTER27_C_4      UINT64_C(0x0000000000000005)
#define UTER27_C_5      UINT64_C(0x0000000000000006)
#define UTER27_C_6      UINT64_C(0x0000000000000008)
#define UTER27_C_7      UINT64_C(0x0000000000000009)
#define UTER27_C_8      UINT64_C(0x000000000000000A)
#define UTER27_C_9      UINT64_C(0x0000000000000010)
#define UTER27_C_10     UINT64_C(0x0000000000000011)
#define UTER27_C_11     UINT64_C(0x0000000000000012)
#define UTER27_C_12     UINT64_C(0x0000000000000014)
#define UTER27_C_13     UINT64_C(0x0000000000000015)
#define UTER27_C_14     UINT64_C(0x0000000000000016)
#define UTER27_C_15     UINT64_C(0x0000000000000018)
#define UTER27_C_16     UINT64_C(0x0000000000000019)
#define UTER27_C_17     UINT64_C(0x000000000000001A)
#define UTER27_C_18     UINT64_C(0x0000000000000020)
#define UTER27_C_19     UINT64_C(0x0000000000000021)
#define UTER27_C_20     UINT64_C(0x0000000000000022)
#define UTER27_C_21     UINT64_C(0x0000000000000024)
#define UTER27_C_22     UINT64_C(0x0000000000000025)
#define UTER27_C_23     UINT64_C(0x0000000000000026)
#define UTER27_C_24     UINT64_C(0x0000000000000028)
#define UTER27_C_25     UINT64_C(0x0000000000000029)
#define UTER27_C_26     UINT64_C(0x000000000000002A)

/* small balanced positive ternary constants */
#define BTER27_C_0      UINT64_C(0x0015555555555555)
#define BTER27_C_1      UINT64_C(0x0015555555555556)
#define BTER27_C_2      UINT64_C(0x0015555555555558)
#define BTER27_C_3      UINT64_C(0x0015555555555559)
#define BTER27_C_4      UINT64_C(0x001555555555555A)
#define BTER27_C_5      UINT64_C(0x0015555555555560)
#define BTER27_C_6      UINT64_C(0x0015555555555561)
#define BTER27_C_7      UINT64_C(0x0015555555555562)
#define BTER27_C_8      UINT64_C(0x0015555555555564)
#define BTER27_C_9      UINT64_C(0x0015555555555565)
#define BTER27_C_10     UINT64_C(0x0015555555555566)
#define BTER27_C_11     UINT64_C(0x0015555555555568)
#define BTER27_C_12     UINT64_C(0x0015555555555569)
#define BTER27_C_13     UINT64_C(0x001555555555556A)

/* small balanced negative ternary constants */
#define BTER27_C_N13    UINT64_C(0x0015555555555540)
#define BTER27_C_N12    UINT64_C(0x0015555555555541)
#define BTER27_C_N11    UINT64_C(0x0015555555555542)
#define BTER27_C_N10    UINT64_C(0x0015555555555544)
#define BTER27_C_N9     UINT64_C(0x0015555555555545)
#define BTER27_C_N8     UINT64_C(0x0015555555555546)
#define BTER27_C_N7     UINT64_C(0x0015555555555548)
#define BTER27_C_N6     UINT64_C(0x0015555555555549)
#define BTER27_C_N5     UINT64_C(0x001555555555554A)
#define BTER27_C_N4     UINT64_C(0x0015555555555550)
#define BTER27_C_N3     UINT64_C(0x0015555555555551)
#define BTER27_C_N2     UINT64_C(0x0015555555555552)
#define BTER27_C_N1     UINT64_C(0x0015555555555554)

/* special implementation constants */

#define _TER27_MASK	UINT64_C(0x003FFFFFFFFFFFFF)

/* arithmetic support */

#define _UT27_2S_COMP( a ) (UTER27_C_MAX - (a))

/* simple add and subtract */

uter27_t uter27_add( uter27_t a, uter27_t b );
bter27_t bter27_add( bter27_t a, bter27_t b );

uter27_t uter27_sub( uter27_t a, uter27_t b );

bter27_t bter27_neg( bter27_t a );
bter27_t bter27_sub( bter27_t a, bter27_t b );

/* special add and subtract */

uter27_t uter27_addsr_c( uter27_t a, uter27_t b, unsigned int s );
bter27_t bter27_addsr_c( bter27_t a, bter27_t b, unsigned int s );

uter27_t uter27_carry;
uter27_t uter27_addc( uter27_t a, uter27_t b, uter27_t cin );

bter27_t bter27_carry;
bter27_t bter27_addc( bter27_t a, bter27_t b, bter27_t cin );

/* shift operations */

uter27_t uter27_sl_c( uter27_t a, unsigned int b );
#define UTER27_SL_C( a, b ) (((a) << (2*(b))) & _TER27_MASK)

bter27_t bter27_sl_c( bter27_t a, unsigned int b );
#define BTER27_SL_C( a, b ) (( ((a) << (2*(b)))		    \
			    | (BTER27_C_0 >> (54-(2*(b))))  \
			    ) & _TER27_MASK)

uter27_t uter27_sr_c( uter27_t a, unsigned int b );
#define UTER27_SR_C( a, b ) ((a) >> (2*(b)))

bter27_t bter27_sr_c( bter27_t a, unsigned int b );
#define BTER27_SR_C( a, b ) (( ((a) >> (2*(b)))		     \
			    | (BTER27_C_0 << (54-(2*(b))))   \
			    ) & _TER27_MASK)

/* logic operations */

#define _TER27_LOGIC( a ) ((a) ^ (((a) >> 1) & BTER27_C_0))

uter27_t ter27_min( uter27_t a, uter27_t b );
#define TER27_MIN( a, b ) _TER27_LOGIC(_TER27_LOGIC( a ) & _TER27_LOGIC( b ))

uter27_t ter27_max( uter27_t a, uter27_t b );
#define TER27_MAX( a, b ) _TER27_LOGIC(_TER27_LOGIC( a ) | _TER27_LOGIC( b ))

uter27_t ter27_neg( uter27_t a );
#define TER27_NEG( a ) (_UT27_2S_COMP( a ))

uter27_t ter27_xor( uter27_t a, uter27_t b );

uter27_t ter27_equ( uter27_t a, uter27_t b );

/* multiply and divide: basic */

uter27_t uter27_mul( uter27_t a, uter27_t b );
bter27_t bter27_mul( bter27_t a, bter27_t b );

extern uter27_t uter27_rem, uter27_quo;
void void_uter27_div( uter27_t a, uter27_t b );

extern bter27_t bter27_rem, bter27_quo;
void void_bter27_div( bter27_t a, bter27_t b );
void void_bter27_div_down( bter27_t a, bter27_t b );
void void_bter27_div_up( bter27_t a, bter27_t b );

/* multiply and divide: special */

uter27_t uter27_prod_top, uter27_prod_low;
void void_uter27_mul( uter27_t a, uter27_t b );
bter27_t bter27_prod_top, bter27_prod_low;
void void_bter27_mul( bter27_t a, bter27_t b );

void void_uter27_divl( uter27_t ah, uter27_t al, uter27_t b );
void void_bter27_divl( bter27_t ah, bter27_t al, bter27_t b );

/* conversion routines: between binary and ternary */

uint64_t uint64_uter27( uter27_t ta );
uter27_t uter27_uint64( uint64_t ba );
int64_t int64_bter27( bter27_t ta );
bter27_t bter27_int64( int64_t ba );

/* conversion routines: between biased and unsigned */

bter27_t bter27_uter27( uter27_t a );
uter27_t uter27_bter27( uter27_t a );

/* conversion routines: between 27-trit and 9-trit ternary */

#ifndef _LIBTER9_H
/* exact width data types needed only if libter9.h not already included */
typedef uint32_t uter9_t;  /* 9-trit unsigned ternary in 32-bit binary */
typedef uint32_t bter9_t;  /* 9-trit balanced ... */
#define _TER9_MASK      UINT32_C(0x0003FFFF)
#endif

/* conversion routines: widening */

#define UTER27_UTER9( a ) ((uter27_t) a)
#define BTER27_BTER9( a ) ((uter27_t)((a) | UINT64_C(0x0015555555540000)))

/* conversion routines: narrowing */

#define TER9_TER27( a ) (((uter9_t) a) & _TER9_MASK)

/* conversion routines: packing and unpacking */

#define TER9_TER27_TOP( a ) ((uter9_t)  ((a) >> 36)              )
#define TER9_TER27_MID( a ) ((uter9_t) (((a) >> 18) & _TER9_MASK))
#define TER9_TER27_LOW( a ) ((uter9_t) ( (a)        & _TER9_MASK))

#define TER27_TER9_PACK( a, b, c ) (            \
          ( ((uter27_t)(a)) << 36)              \
        | ( ((uter27_t)(b)) << 18)              \
        | ( ((uter27_t)(c))      )              \
)

#endif
