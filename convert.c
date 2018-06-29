#include <string.h>
#include <inc/convert.h>



const unsigned CheckIfSigned[33]=
{0x00000000,
0x00000001,0x00000002,0x00000004,0x00000008,
0x00000010,0x00000020,0x00000040,0x00000080,
0x00000100,0x00000200,0x00000400,0x00000800,
0x00001000,0x00002000,0x00004000,0x00008000,
0x00010000,0x00020000,0x00040000,0x00080000,
0x00100000,0x00200000,0x00400000,0x00800000,
0x01000000,0x02000000,0x04000000,0x08000000,
0x10000000,0x20000000,0x40000000,0x80000000};
const unsigned ConvertToSigned[32]=
{0xffffffff,
0xfffffffe,0xfffffffc,0xfffffff8,0xfffffff0,
0xffffffe0,0xffffffc0,0xffffff80,0xffffff00,
0xfffffe00,0xfffffc00,0xfffff800,0xfffff000,
0xffffe000,0xffffc000,0xffff8000,0xffff0000,
0xfffe0000,0xfffc0000,0xfff80000,0xfff00000,
0xffe00000,0xffc00000,0xff800000,0xff000000,
0xfe000000,0xfc000000,0xf8000000,0xf0000000,
0xe0000000,0xc0000000,0x80000000};
const unsigned digits2bits[33]=
{0x00000000,
0x00000001,0x00000003,0x00000007,0x0000000f,
0x0000001f,0x0000003f,0x0000007f,0x000000ff,
0x000001ff,0x000003ff,0x000007ff,0x00000fff,
0x00001fff,0x00003fff,0x00007fff,0x0000ffff,
0x0001ffff,0x0003ffff,0x0007ffff,0x000fffff,
0x001fffff,0x003fffff,0x007fffff,0x00ffffff,
0x01ffffff,0x03ffffff,0x07ffffff,0x0fffffff,
0x1fffffff,0x3fffffff,0x7fffffff,0xffffffff};


int convert_raw_to_integer (const unsigned source,
							const unsigned digits,
							BOOL * validation,
							int LowRange,
							int HighRange,
							const int scale,
							const int offset)
{
	int tempInt;
	unsigned temp;
	temp = source & CheckIfSigned[digits];
	if (temp != 0) 
		temp = source | ConvertToSigned[digits-1];
	else
		temp= source;
	memcpy (&tempInt, &temp, sizeof (unsigned));
	tempInt=tempInt*scale + offset;
	if (tempInt >= LowRange && tempInt <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempInt;
}

float convert_raw_to_floatsn (const unsigned source,
							  const unsigned digits,
							  BOOL * validation,
							  float LowRange,
							  float HighRange,
							  const float scale,
							  const float offset)
{
	int tempInt;
	float tempFloat;
	unsigned temp;
	int signFactor;

	temp = source & CheckIfSigned[digits];
	if (temp != 0)
	{
		temp = (source | ConvertToSigned[digits-1]);
		signFactor = -1;
	}
	else
	{
		temp=source;
		signFactor = 1;
	}
	memcpy (&tempInt, &temp, sizeof (unsigned));
	tempFloat= (float) tempInt;
	tempFloat=(tempFloat*scale + offset) * signFactor;
	if (tempFloat >= LowRange && tempFloat <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempFloat;
}

float convert_raw_to_floatun (const unsigned source,
							  const unsigned digits,
							  BOOL * validation,
							  float LowRange,
							  float HighRange,
							  const float scale,
							  const float offset)
{
	float tempFloat;
	unsigned temp;

	temp = source & digits2bits[digits];
	tempFloat= (float) temp;
	tempFloat=tempFloat*scale + offset;
	if (tempFloat >= LowRange && tempFloat <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempFloat;
}

float convert_raw_to_float (const unsigned source,
							const unsigned digits,
							BOOL * validation,
							float LowRange,
							float HighRange,
							const float scale,
							const float offset)
{
	int tempInt;
	float tempFloat;
	unsigned temp;
	temp = source & CheckIfSigned[digits];
	if (temp != 0) 
		temp = (source | ConvertToSigned[digits-1]);
	else
		temp=source;
	memcpy (&tempInt, &temp, sizeof (unsigned));
	tempFloat= (float) tempInt;
	tempFloat=tempFloat*scale + offset;
	if (tempFloat >= LowRange && tempFloat <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempFloat;
}

unsigned convert_raw_to_unsigned (const unsigned source,
								  const unsigned digits,
								  BOOL * validation,
								  unsigned LowRange,
								  unsigned HighRange,
								  const unsigned scale,
								  const unsigned offset)
{
	unsigned UStemp;
	UStemp= source;
	UStemp=UStemp*scale + offset;
	if (UStemp >= LowRange && UStemp <= HighRange) 
	*validation= TRUE;
	else
	*validation = FALSE;
	return UStemp;
}

double convert_raw_to_double(
							 const long unsigned source,
							 const long unsigned digits,
							 BOOL* validation,
							 double LowRange,
							 double HighRange,
							 const double scale,
							 const double offset)
{
	long int tempInt;
	double tempFloat;
	long unsigned temp;
	temp = source & CheckIfSigned[digits];
	if (temp != 0) 
		temp = (source | ConvertToSigned[digits-1]);
	else
		temp=source;
	memcpy (&tempInt, &temp, sizeof (long unsigned));
	tempFloat= (double) tempInt;
	tempFloat=tempFloat*scale + offset;
	if (tempFloat >= LowRange && tempFloat <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempFloat;
} /* convert_Raw_to_DOUBLE */

long convert_raw_to_long(
						 const long unsigned source,
						 const long unsigned digits,
						 BOOL* validation,
						 long LowRange,
						 long HighRange,
						 const long scale,
						 const long offset)
{
	long int tempInt;
	long tempFloat;
	long unsigned temp;
	temp = source & CheckIfSigned[digits];
	if (temp != 0) 
		temp = (source | ConvertToSigned[digits-1]);
	else
		temp=source;
	memcpy (&tempInt, &temp, sizeof (long unsigned));
	tempFloat= (long) tempInt;
	tempFloat=tempFloat*scale + offset;
	if (tempFloat >= LowRange && tempFloat <= HighRange) 
		*validation= TRUE;
	else
		*validation = FALSE;
	return tempFloat;
} /* convert_Raw_to_LONG */

/****CONVERSION OF DIFFERENT TYPES TO RAW*******/

unsigned convert_FLOATSN_to_Raw (float source,
								 const unsigned digits,
								 const float scale,
								 const float offset)
{
	unsigned tempUInt;
	unsigned signBit;

	if (source < 0.0)
	{
		signBit = CheckIfSigned[digits] ;
		source = -source ;
	}
	else
	{
		signBit = 0 ;
	}
	source=(source-offset)/scale;
	tempUInt=(unsigned)source;
	tempUInt= (tempUInt & digits2bits[digits-1]) | signBit ; 

	return tempUInt;
} /* convertfloat2Raw */

unsigned convert_FLOAT_to_Raw (float source,
							   const unsigned digits,
							   const float scale,
							   const float offset)
{
	unsigned tempUInt;
	int tempInt;
	source=(source-offset)/scale;
	tempInt=(int)source;
	memcpy (&tempUInt, &tempInt, sizeof (int));
	tempUInt= tempUInt & digits2bits[digits]; 
	return tempUInt;
};/* convertfloat2Raw */

unsigned convert_FLOATUN_to_Raw (float source,
								 const unsigned digits,
								 const float scale,
								 const float offset)
{
	unsigned tempUInt;

	source=(source-offset)/scale;
	tempUInt=(unsigned)source;
	tempUInt= tempUInt & digits2bits[digits]; 
	return tempUInt;
};/* convertfloatun2Raw */

unsigned convert_INTEGER_to_Raw (int source,
								 const unsigned digits,
								 const int scale,
								 const int offset )
{
	unsigned tempUInt;
	source=(source-offset)/scale;
	memcpy (&tempUInt, &source, sizeof (int));
	tempUInt= tempUInt & digits2bits[digits]; 
	return tempUInt;
}; /* convertInt2Raw */


unsigned convert_UNSIGNED_to_Raw (unsigned source,
								  const unsigned digits)
{
	unsigned UStemp;
	UStemp = source;
	return UStemp;
}

long unsigned convert_DOUBLE_to_Raw(const double source,
									const long unsigned digits,
									const double scale,
									const double offset)
{
	long unsigned tempUInt;
	long int tempInt;
	double tempDouble;
	tempDouble=(source-offset)/scale;
	tempInt=(int)tempDouble;
	memcpy (&tempUInt, &tempInt, sizeof (int));
	tempUInt= tempUInt & digits2bits[digits]; 
	return tempUInt;
};/* convert_DOUBLE_to_Raw */

long unsigned convert_LONG_to_Raw(const long source,
								  const long unsigned digits,
								  const long scale,
								  const long offset)
{
	long unsigned tempUInt;
	long int tempInt;
	long tempLong;
	tempLong=(source-offset)/scale;
	tempInt=(int)tempLong;
	memcpy (&tempUInt, &tempInt, sizeof (int));
	tempUInt= tempUInt & digits2bits[digits]; 
	return tempUInt;
};/* convert_LONG_to_Raw */

void convert_LongUInt_to_2_UInt
(const long unsigned source,
 unsigned * LsPart, unsigned * MsPart, int LsPart_bits)
{
	const long unsigned LSW_mask=0x0000FFFF;

	*LsPart=(unsigned)(source & LSW_mask);
	*MsPart=(unsigned)(source >> LsPart_bits);
} /* convert_LongUInt_to_2_UInt */

long unsigned convert_2_UInt_to_LongUInt
(const unsigned LsPart, const unsigned MsPart,
 int LsPart_bits)
{
	long unsigned result;
	result = (long unsigned)MsPart;
	result = result << LsPart_bits;
	result = result | (long unsigned)LsPart;
	return result;
} /* convert_2_UInt_to_LongUInt */

void convertBCD2Array(	const float		Data,
						const float		Resolution,
						const unsigned	NumberDigits,
						unsigned		pArray[])
{
	float InvResolution;
	int   DecimalData;
	div_t tempDiv;
	int i = 0;


     
    InvResolution = 1 / Resolution ;

    DecimalData = (int)floor( (double)((Data + 0.005) * InvResolution) ) ;

    for ( i = NumberDigits - 1 ; i >= 0 ; i-- )
    {
        tempDiv = div( DecimalData , (int)pow( (double)10 , (double)i )) ;
        pArray[i] = tempDiv.quot ;

        DecimalData = tempDiv.rem ;
    }
}

void convertArray2BCD(	float			*pData,
						const float		Resolution,
						const unsigned	NumberDigits,
						const unsigned	Array[])
{
    int i = 0 ;
	int digit = 0;
	float delta = 0.0;
	double mult = 0.0;
	
    *pData = 0.0 ;

    for ( i = 0 ; i < NumberDigits ; i++ )
    {
		digit = Array[i];
		mult = pow( (double)10 , (double)i);
		delta = digit * mult;
		*pData = *pData + delta;
    }

    *pData *= Resolution ;
}
