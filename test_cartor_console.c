#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "cartor_console.h"
#include "strings.h"



int main() {
    cartor_init();
    printf("Terminal size: %d x %d\n", TRM_W, TRM_H);

    draw_horizontal_line(TRM_W, 0, LS_HFD, LE_BKT, L_H);

    printf("\n\n");

    draw_open_bubble(
        C_WHT,
        C_RED,
        "Title",
        C_LRED,
        "This is a "C_VAR C_U"test"C_R C_LRED" of the open bubble\n"
        "It should be able to handle "C_I"multiple"C_R C_LRED" lines\n"
        "And it should look nice\n"
    );

    print(charToString("This is a test"));
    printnl(charToString("}-- This is a SECOND test"));

    print(chr2str(
        "HELLO\n"
        "WORLD\n"
        "THIS IS A TEST\n"
        "OF THE CARTOR CONSOLE\n"
        "AND THE STRING LIBRARY\n"
    ));

    printnl(chr2str(""));

    printnl(charToString(
        "There are " C_NUM "4" C_R " lines here\n"
        "And this is a " C_VAR "test" C_R "\n"
        "Of the " C_I "cartor" C_R " console\n"
        "And the " C_U "string" C_R " library\n"
    ));

    cartor_exit();
}