#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #include "cartor_console.h"

#define UNUSED(x) (void)(x)

// typedef char* StringChar;

typedef struct {
    char *val;
    int disp_len; // length of string w/o special characters
    int len;
} StringLine;

typedef struct {
    StringLine *rows;
    int height; // num rows
    int width;  // max width
    int disp_width; // max width w/o special characters
} StringMtrx;

// Enum to distinguish between the types
typedef enum {
    // STRING_CHAR,
    STRING_LINE,
    STRING_MTRX 
} StringType;

// Union that can hold any of the three types
typedef union {
    // StringChar Char;
    StringLine Line;
    StringMtrx Mtrx;
} StringUnion;

// Create a tagged union that combines the type tag with the union
typedef struct {
    StringType type;
    StringUnion data;
} String;

// Factory functions to create the different types

// Create Strings
// String charToString(StringChar);
String lineToString(StringLine);
String mtrxToString(StringMtrx);

// Create String From char *
String charToString(char *str);
String chr2str(char *str);
String int2str(int num);
String flt2str(float num);

char*  str2char(String str);

/**
 * Get Properties From String
 */
int    strWidth(String str);
int    strHeight(String str);
int    strDispWidth(String str);
String getRow(String str, int row);


int get_disp_len(char *str);

String concat(String str1, String str2);

void print(String str);
void printnl(String str);


typedef struct {
    char *val;
} ColorNode;

typedef struct {
    ColorNode *nodes;
    int size;
} ColorList;

typedef struct {
    int r;
    int g;
    int b;
} ColorRGB;


String rainbow(String str);
String colorLoop(String str, ColorList colors);

// Gradient
String strGrad(String str, ColorRGB start, ColorRGB end);

ColorList getGrad(int num_colors, ColorRGB start, ColorRGB end);
ColorRGB  getRGB(int r, int g, int b);
char*     getColor(int r, int g, int b);

// Parsing:

/*
<function: color1, color2, color3, ...>
    <name_of_text_param_1>
        TEXT_1
    </name_of_text_param_1>
    <name_of_text_param_2>
        TEXT_2
    </name_of_text_param_2>
</function>

*/


#endif // STRINGS_H