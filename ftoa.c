#include <inc/ftoa.h>

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
int intToStr(int x, char str[], int d, int isNegative)
{
    int i = 0;
    if(x<0)
    {
        x=-x;
    }
    if(x==0)
    {
        str[i++] = '0';
    }
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    if(isNegative)
        str[i++] = '-';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    float fpart = 0.0;
    int isNegative = 0;

    // Extract integer part
    int ipart = (int)n;


    if(n<0.0)
    {
        // Extract floating part
        fpart = -(n - (float)ipart);
        isNegative = 1;
    }
    else
    {
        // Extract floating part
        fpart = n - (float)ipart;
    }
    // convert integer part to string
    int i = intToStr(ipart, res, 0, isNegative);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint,0);
    }
}
