/* terconst.c */
/**********
 * Utility to create ternary constants for users of libter.h and libter27.h
 * Version 1.0, Dec 29, 2015, Douglas W. Jones, jones@cs.uiowa.edu
 * See http://homepage.cs.uiowa.edu/~dwjones/ternary/libtern.shtml for documentation
 *
 * Copyright 2015, distributed under the
 *	Creative Commons Attribution 4.0 International license
 *	See https://creativecommons.org/licenses/by/4.0/
 * Disclaimer: This is preliminary work,
 *      the author takes no responsibility for errors in this work
 *      but would appreciate being informed of such errors.
 * Acknowledgement: This work was partially supported by Jinn Labs.
 **********/

/* utility to create ternary constants for users of libtern.h
   usage -- see the help function below for usage
 */

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "libter9io.h"
#include "libter27io.h"

void help( char * name ) {
	printf( "%s: ternary constant conversion function\n"
		" usage: %s -XterY [-base Z|-hept] {NNN}\n"
		"   -XterY is one of {-uter9 -bter9}, a type\n"
		"   -XterY is one of {-uter9 -uter27 -bter9 -bter27}, a type\n"
		"   -XterY may be abbreviated as {-u9 -u27 -b9 -b27}.\n"
		"   -XterY may be abbreviated as {-u9 -u27 -b9 -b27}.\n"
		"   -base Z, optional, Z, the input base, default is base 10\n"
		"   -base Z may be abbreviated as -b Z.\n"
		"   -hept, optional, abbreviated -h, use heptavintimal input.\n"
		"   {NNN} one or more numbers in the indicated base.\n"
		, name, name );
	exit( EXIT_SUCCESS );
}

void error( char * name, char * msg, char * more ) {
	printf( "%s: %s%s\n"
		" usage:  %s -XterY [-base Z|-hept] {NNN}\n"
		" for more details: %s -help\n"
	      , name, msg, more
	      , name
	      , name );
	exit( EXIT_FAILURE );
}

uint64_t hepttoll( char * str, char ** endptr ) {
	/* convert string s, a heptavintimal number, to an integer;
	   return the value,
	   set endptr following the same conventions used by strtoll() */
	static const char digits[128] = { /* digit conversion table */
                99,99,99,99, 99,99,99,99, 99,99,99,99, 99,99,99,99,
                99,99,99,99, 99,99,99,99, 99,99,99,99, 99,99,99,99,
                99,99,99,99, 99,99,99,99, 99,99,99,99, 99,99,99,99,
                 0, 1, 2, 3,  4, 5, 6, 7,  8, 9,99,99, 99,99,99,99,
                99,10,11,12, 13,14,15,16, 17, 1, 1,18,  1,19,20, 0,
                21, 0,22, 5, 23,24,24,24, 25, 1,26,99, 99,99,99,99,
                99,10,11,12, 13,14,15,16, 17, 1, 1,18,  1,19,20, 0,
                21, 0,22, 5, 23,24,24,24, 25, 1,26,99, 99,99,99,99
        };
	uint64_t acc = 0; /* the accumulator */
	for (;;) {
		int digit = 99;
		int ch = (int) *str;
		if ((ch >= 0) && (ch <= 127)) digit = digits[ch];
		if (digit >= 27) {
			*endptr = str;
			return acc;
		}
		acc = (acc * 27) + digit;
		str++;
	}
}

int main (int argc, char ** argv) {
	enum { U9, U27, B9, B27 } mytype; /* summary type */
	int arg;              /* the command line argument number */
	char * prefix = NULL; /* the prefix on the type name; NULL if none */
	long long int max;    /* the maximum permitted value */
	long long int min;    /* the minimum permitted value */
	int base = 0;  	      /* number base for input number */
	long long int value;  /* the input number, converted to binary */
	int bits;             /* number of bits in the binary coded ternary */

	arg = 1;
	while (arg < argc) { /* for each command line arg */
		if ( (!strcmp( argv[arg], "-help" ))
	        ||   (!strcmp( argv[arg], "-?" ))    ) {
			help( argv[0] );
		} else if ( (!strcmp( argv[arg], "-uter9" ))
		       ||   (!strcmp( argv[arg], "-u9" ))    ) {
			if (prefix != NULL)
				error( argv[0], "Extra type ", argv[arg] );
			max = 19682LL; /* this is 3**9 - 1 */
			min = 0;
			mytype = U9;
			bits = 32;
			prefix = "UTER9";
		} else if ( (!strcmp( argv[arg], "-uter27" ))
		       ||   (!strcmp( argv[arg], "-u27" ))    ) {
			if (prefix != NULL)
				error( argv[0], "Extra type ", argv[arg] );
			max = 7625597484096LL; /* this is 3**27 - 1 */
			min = 0;
			mytype = U27;
			bits = 64;
			prefix = "UTER27";
		} else if ( (!strcmp( argv[arg], "-bter9" ))
		       ||   (!strcmp( argv[arg], "-b9" ))    ) {
			if (prefix != NULL)
				error( argv[0], "Extra type ", argv[arg] );
			max =  9841LL; /* this is (3**9 - 1)/2 */
			min = -9841LL;
			mytype = B9;
			bits = 32;
			prefix = "BTER9";
		} else if ( (!strcmp( argv[arg], "-bter27" ))
		       ||   (!strcmp( argv[arg], "-b27" ))    ) {
			if (prefix != NULL)
				error( argv[0], "Extra type ", argv[arg] );
			max =  3182798742493LL; /* this is (3**27 - 1)/2 */
			min = -3182798742493LL;
			mytype = B27;
			bits = 64;
			prefix = "BTER27";
		} else if ( (!strcmp( argv[arg], "-base" ))
		       ||   (!strcmp( argv[arg], "-b" ))    )   {
			char * end; /* return value set by strtoll */
			if (base != 0)
				error( argv[0], "Extra base", "" );
			arg = arg + 1;
			if (arg >= argc)
				error( argv[0], "No base", "" );
			base = (int) strtoll( argv[arg], &end, 10 );
			if ( *end != '\0' )
				error( argv[0], "Bad base ", argv[arg] );
			if ((base <= 1) || (base > 36))
				error( argv[0], "Bad base ", argv[arg] );
		} else if ( (!strcmp( argv[arg], "-hept" ))
		       ||   (!strcmp( argv[arg], "-h" ))    )   {
			if (base != 0)
				error( argv[0], "Extra base ", argv[arg] );
			base = -27;
		} else { /* assume all else is the number to convert */
			break; /* note, arg has not been incremented */
		}
		arg = arg + 1;
	}
	if (arg >= argc)
		error( argv[0], "No values to convert", "" );
	if (prefix == NULL)
		error( argv[0], "No type specified", "" );

	if (base == -27) { /* heptavintimal */
		if (mytype == B9) {
			mytype = U9;
			min = 0LL;
			max = 19682LL; /* this is 3**9 - 1 */
		} else if (mytype == B27) {
			mytype = U27;
			min = 0LL;
			max = 7625597484096LL; /* this is 3**27 - 1 */
		}
	}

	/* all set to convert a collection of numbers */
	while (arg < argc) { /* for each remaining command line line arg */
		char * end; /* return value set by strtoll */
		char * number = argv[arg]; /* a string giving a number */
		uint64_t bct; /* the binary coded ternary representation */

		if (base == -27) { /* heptavintimal */
			value = hepttoll( number, &end );
		} else { /* normal number bases */
			value = strtoll( number, &end, base );
		}
		if ( *end != '\0' )
			error( argv[0], "Corrupt value ", argv[arg] );
		if ((value < min) || (value > max))
			error( argv[0], "Value out of bounds ", argv[arg] );

		/* value is now validated, ready to make ternary */
		switch (mytype) {
		case U9:
			bct = (uint64_t) uter9_uint16( (uint16_t)value );
			break;
		case U27:
			bct = (uint64_t) uter27_uint64( (uint64_t)value );
			break;
		case B9:
			bct = (uint64_t) bter9_int16( (int16_t)value );
			break;
		case B27:
			bct = (uint64_t) bter27_int64( (int64_t)value );
			break;
		}

		/* now, compose the output */
		printf( "#define %s_C_", prefix );
		if (*number != '-') {
			printf( "%s	", number );
		} else { /* must avoid output of negative sign */
			printf( "N%s	", number+1 );
		}
		if (bits == 32) {
			printf( "UINT32_C(0x%08" PRIX64 ")\n", bct );
		} else { /* bits == 64 */
			printf( "UINT64_C(0x%016" PRIX64 ")\n", bct );
		}

		arg = arg + 1;
	}
	exit( EXIT_SUCCESS );
}
