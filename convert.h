#ifndef convert_H
#define convert_H

#include <stdlib.h>
#include <math.h>

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef __cplusplus
extern "C"{
#endif


	/****************example of usage ***********************************
	*																	*
	*int convert_raw_to_integer(const unsigned source,					*
	*							-- The raw data							*
	*						   const unsigned digits,					*
	*							-- Num of bits of the element			*
	*						   BOOL * validation,						*
	*							-- the validation value - TRUE/FALSE	*
	*						   int HighRange,							*
	*							-- highest Eng value possible			*
	*						   int LowRange,							*
	*							-- lowest Eng value possible			*
	*						   const int scale,							*
	*						   const int offset);						*
	*																	*
	*********************************************************************/

	/*conversion of Raw to different types*/

	float convert_raw_to_float(const unsigned source,
		const unsigned digits,
		BOOL* validation,
		float LowRange,
		float HighRange,
		const float scale,
		const float offset);

	float convert_raw_to_floatsn(const unsigned source,
		const unsigned digits,
		BOOL* validation,
		float LowRange,
		float HighRange,
		const float scale,
		const float offset);

	float convert_raw_to_floatun(const unsigned source,
		const unsigned digits,
		BOOL* validation,
		float LowRange,
		float HighRange,
		const float scale,
		const float offset);

	int convert_raw_to_integer(const unsigned source,
		const unsigned digits,
		BOOL * validation,
		int LowRange,
		int HighRange,
		const int scale,
		const int offset);

	unsigned convert_raw_to_unsigned (const unsigned source,
		const unsigned digits,
		BOOL* validation,
		unsigned LowRange,
		unsigned HighRange,
		const unsigned scale,
		const unsigned offset);

	double convert_raw_to_double(
		const long unsigned source,
		const long unsigned digits,
		BOOL* validation,
		double LowRange,
		double HighRange,
		const double scale,
		const double offset);

	long convert_raw_to_long(
		const long unsigned source,
		const long unsigned digits,
		BOOL* validation,
		long LowRange,
		long HighRange,
		const long scale,
		const long offset);
	/*convertion of different types to raw*/

	unsigned convert_UNSIGNED_to_Raw (unsigned source,
		const unsigned digits);

	unsigned convert_FLOAT_to_Raw (float source,
		const unsigned digits,
		const float scale,
		const float offset);

	unsigned convert_FLOATSN_to_Raw (float source,
		const unsigned digits,
		const float scale,
		const float offset);

	unsigned convert_FLOATUN_to_Raw (float source,
		const unsigned digits,
		const float scale,
		const float offset);

	unsigned convert_INTEGER_to_Raw (int source,
		const unsigned digits,
		const int scale,
		const int offset);

	long unsigned convert_DOUBLE_to_Raw(const double source,
		const long unsigned digits,
		const double scale,
		const double offset);

	long unsigned convert_LONG_to_Raw(const long source,
		const long unsigned digits,
		const long scale,
		const long offset);

	void convert_LongUInt_to_2_UInt (const long unsigned source,
		unsigned * LsPart, unsigned * MsPart, int LsPart_bits);

	long unsigned convert_2_UInt_to_LongUInt
		(const unsigned LsPart, const unsigned MsPart,
		int LsPart_bits);
		
	void convertBCD2Array ( const float       Data,
							const float       Resolution,
							const unsigned    NumberDigits ,
							unsigned          pArray[]) ;
	
	void convertArray2BCD ( float *pData ,
							const float Resolution ,
							const unsigned NumberDigits ,
							const unsigned Array[] );



#ifdef __cplusplus
}
#endif

#endif
