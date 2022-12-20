/* libter9.h */
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

#ifndef _LIBTER9_H
#define _LIBTER9_H

#include <stdint.h>

#ifndef _TER9_MASK
/* exact width data types (definition suppressed if done in libter27.h) */
typedef uint32_t uter9_t;  /* 9-trit unsigned ternary in 32-bit binary */
typedef uint32_t bter9_t;  /* 9-trit balanced ... */

/* special implementation constants */
#define _TER9_MASK	UINT32_C(0x0003FFFF)
#endif

/* limits on exact-width data types expressed in that data type */
#define UTER9_C_MAX	UINT32_C(0x0002AAAA)
#define BTER9_C_MAX	UTER9_C_MAX

/* Binary equivalents of above limits */
#define UINT16_UTER9_C_MAX	UINT16_C(19682)
#define INT16_BTER9_C_MAX	INT16_C(9841)

/* small unsigned ternary constants */
#define UTER9_C_0	UINT32_C(0x00000000)
#define UTER9_C_1	UINT32_C(0x00000001)
#define UTER9_C_2	UINT32_C(0x00000002)
#define UTER9_C_3	UINT32_C(0x00000004)
#define UTER9_C_4	UINT32_C(0x00000005)
#define UTER9_C_5	UINT32_C(0x00000006)
#define UTER9_C_6	UINT32_C(0x00000008)
#define UTER9_C_7	UINT32_C(0x00000009)
#define UTER9_C_8	UINT32_C(0x0000000A)
#define UTER9_C_9	UINT32_C(0x00000010)
#define UTER9_C_10	UINT32_C(0x00000011)
#define UTER9_C_11	UINT32_C(0x00000012)
#define UTER9_C_12	UINT32_C(0x00000014)
#define UTER9_C_13	UINT32_C(0x00000015)
#define UTER9_C_14	UINT32_C(0x00000016)
#define UTER9_C_15	UINT32_C(0x00000018)
#define UTER9_C_16	UINT32_C(0x00000019)
#define UTER9_C_17	UINT32_C(0x0000001a)
#define UTER9_C_18	UINT32_C(0x00000020)
#define UTER9_C_19	UINT32_C(0x00000021)
#define UTER9_C_20	UINT32_C(0x00000022)
#define UTER9_C_21	UINT32_C(0x00000024)
#define UTER9_C_22	UINT32_C(0x00000025)
#define UTER9_C_23	UINT32_C(0x00000026)
#define UTER9_C_24	UINT32_C(0x00000028)
#define UTER9_C_25	UINT32_C(0x00000029)
#define UTER9_C_26	UINT32_C(0x0000002a)

/* small balanced positive ternary constants */
#define BTER9_C_0	UINT32_C(0x00015555)
#define BTER9_C_1	UINT32_C(0x00015556)
#define BTER9_C_2	UINT32_C(0x00015558)
#define BTER9_C_3	UINT32_C(0x00015559)
#define BTER9_C_4	UINT32_C(0x0001555A)
#define BTER9_C_5	UINT32_C(0x00015560)
#define BTER9_C_6	UINT32_C(0x00015561)
#define BTER9_C_7	UINT32_C(0x00015562)
#define BTER9_C_8	UINT32_C(0x00015564)
#define BTER9_C_9	UINT32_C(0x00015565)
#define BTER9_C_10	UINT32_C(0x00015566)
#define BTER9_C_11	UINT32_C(0x00015568)
#define BTER9_C_12	UINT32_C(0x00015569)
#define BTER9_C_13	UINT32_C(0x0001556A)

/* small balanced negative ternary constants */
#define BTER9_C_N13	UINT32_C(0x00015540)
#define BTER9_C_N12	UINT32_C(0x00015541)
#define BTER9_C_N11	UINT32_C(0x00015542)
#define BTER9_C_N10	UINT32_C(0x00015544)
#define BTER9_C_N9	UINT32_C(0x00015545)
#define BTER9_C_N8	UINT32_C(0x00015546)
#define BTER9_C_N7	UINT32_C(0x00015548)
#define BTER9_C_N6	UINT32_C(0x00015549)
#define BTER9_C_N5	UINT32_C(0x0001554A)
#define BTER9_C_N4	UINT32_C(0x00015550)
#define BTER9_C_N3	UINT32_C(0x00015551)
#define BTER9_C_N2	UINT32_C(0x00015552)
#define BTER9_C_N1	UINT32_C(0x00015554)

/* arithmetic support */
#define _UT9_2S_COMP( a ) (UTER9_C_MAX - (a))

/* simple add and subtract */

uter9_t uter9_add( uter9_t a, uter9_t b );
bter9_t bter9_add( bter9_t a, bter9_t b );

uter9_t uter9_sub( uter9_t a, uter9_t b );

bter9_t bter9_neg( bter9_t a );
bter9_t bter9_sub( bter9_t a, bter9_t b );

/* special add and subtract */

uter9_t uter9_addsr_c( uter9_t a, uter9_t b, unsigned int s );
bter9_t bter9_addsr_c( bter9_t a, bter9_t b, unsigned int s );

uter9_t uter9_carry;
uter9_t uter9_addc( uter9_t a, uter9_t b, uter9_t cin );

bter9_t bter9_carry;
bter9_t bter9_addc( bter9_t a, bter9_t b, bter9_t cin );

/* shift operations */

uter9_t uter9_sl_c( uter9_t a, unsigned int b );
#define UTER9_SL_C( a, b ) (((a) << (2*(b))) & _TER9_MASK)

bter9_t bter9_sl_c( bter9_t a, unsigned int b );
#define BTER9_SL_C( a, b ) (( ((a) << (2*(b)))		    \
			    | (BTER9_C_0 >> (18-(2*(b))))   \
			    ) & _TER9_MASK)

uter9_t uter9_sr_c( uter9_t a, unsigned int b );
#define UTER9_SR_C( a, b ) ((a) >> (2*(b)))

bter9_t bter9_sr_c( bter9_t a, unsigned int b );
#define BTER9_SR_C( a, b ) (( ((a) >> (2*(b)))		     \
			    | (BTER9_C_0 << (18-(2*(b))))    \
			    ) & _TER9_MASK)

/* logic operations */

#define _TER9_LOGIC( a ) ((a) ^ (((a) >> 1) & BTER9_C_0))

uter9_t ter9_min( uter9_t a, uter9_t b );
#define TER9_MIN( a, b ) _TER9_LOGIC(_TER9_LOGIC( a ) & _TER9_LOGIC( b ))

uter9_t ter9_max( uter9_t a, uter9_t b );
#define TER9_MAX( a, b ) _TER9_LOGIC(_TER9_LOGIC( a ) | _TER9_LOGIC( b ))

uter9_t ter9_neg( uter9_t a );
#define TER9_NEG( a ) (_UT9_2S_COMP( a ))

uter9_t ter9_xor( uter9_t a, uter9_t b );

uter9_t ter9_equ( uter9_t a, uter9_t b );

/* multiply and divide: basic */

uter9_t uter9_mul( uter9_t a, uter9_t b );
bter9_t bter9_mul( bter9_t a, bter9_t b );

extern uter9_t uter9_rem, uter9_quo;
void void_uter9_div( uter9_t a, uter9_t b );

extern bter9_t bter9_rem, bter9_quo;
void void_bter9_div( bter9_t a, bter9_t b );
void void_bter9_div_down( bter9_t a, bter9_t b );
void void_bter9_div_up( bter9_t a, bter9_t b );

/* multiply and divide: special */

uter9_t uter9_prod_top, uter9_prod_low;
void void_uter9_mul( uter9_t a, uter9_t b );
bter9_t bter9_prod_top, bter9_prod_low;
void void_bter9_mul( bter9_t a, bter9_t b );

void void_uter9_divl( uter9_t ah, uter9_t al, uter9_t b );
void void_bter9_divl( bter9_t ah, bter9_t al, bter9_t b );

/* conversion routines: between binary and ternary */

uint16_t uint16_uter9( uter9_t ta );
uter9_t uter9_uint16( uint16_t ba );
int16_t int16_bter9( bter9_t ta );
bter9_t bter9_int16( int16_t ba );

/* conversion routines: between biased and unsigned */

bter9_t bter9_uter9( uter9_t a );
uter9_t uter9_bter9( uter9_t a );

#endif
