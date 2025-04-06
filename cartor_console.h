#ifndef CARTOR_CONSOLE_H
#define CARTOR_CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "strings.h"

// Colors
#define C_R "\033[0m"
#define C_B "\033[1m"
#define C_I "\033[3m"
#define C_U "\033[4m"

#define C_RVRS "\033[7m"

#define C_PNK "\033[38;5;201m"  // Pink
#define C_RED "\033[31m"        // Red
#define C_YLW "\033[33m"        // Yellow
#define C_ORG "\033[38;5;208m"  // Orange
#define C_GRN "\033[32m"        // Green
#define C_TEL "\033[38;5;37m"   // Teal
#define C_CYN "\033[36m"        // Cyan
#define C_BLU "\033[34m"        // Blue
#define C_MGT "\033[35m"        // Magenta
#define C_WHT "\033[37m"        // White
#define C_GRY "\033[90m"        // Gray
#define C_DGR "\033[90m"        // Dark Gray

#define C_LRED "\033[91m"       // Light Red
#define C_LYEL "\033[93m"       // Light Yellow
#define C_LGRN "\033[92m"       // Light Green
#define C_LTEL "\033[38;5;45m"  // Light Teal
#define C_LCYN "\033[96m"       // Light Cyan
#define C_LBLU "\033[94m"       // Light Blue
#define C_LMGT "\033[95m"       // Light Magenta
#define C_LWHT "\033[97m"       // Light White
#define C_LGRY "\033[37m"       // Light Gray

#define C_BRED "\033[41m"       // Background Red
#define C_BYLW "\033[43m"       // Background Yellow
#define C_BORG "\033[48;5;208m" // Background Orange
#define C_BGRN "\033[42m"       // Background Green
#define C_BTEL "\033[48;5;37m"  // Background Teal
#define C_BCYN "\033[46m"       // Background Cyan
#define C_BBLU "\033[44m"       // Background Blue
#define C_BMGT "\033[45m"       // Background Magenta
#define C_BWHT "\033[47m"       // Background White
#define C_BGRY "\033[100m"      // Background Gray
#define C_BDGR "\033[100m"      // Background Dark Gray

#define C_NUM  C_B C_PNK
#define C_VAR      C_GRN
#define C_LN       C_WHT
#define C_BLN  C_B C_LN

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

// Characters (CH=K)
#define K_RCUR "╰"      // Round Corner Up Right
#define K_RCUL "╯"      // Round Corner Up Left
#define K_RCDR "╭"      // Round Corner Down Right
#define K_RCDL "╮"      // Round Corner Down Left

#define K_CUR "└"       // Corner Up Right
#define K_CUL "┘"       // Corner Up Left
#define K_CDR "┌"       // Corner Down Right
#define K_CDL "┐"       // Corner Down Left

#define K_THU "┴"       // T-Shape Horizontal Up
#define K_THD "┬"       // T-Shape Horizontal Down
#define K_TVR "├"       // T-Shape Vertical Right
#define K_TVL "┤"       // T-Shape Vertical Left
#define K_THV "┼"       // T-Shape Cross (Horizontal and Vertical)

#define K_B_THU   "┻"   // Bold            | T-Shape Horizontal Up
#define K_BU_THU  "┸"   // Bold Up         | T-Shape Horizontal Up
#define K_BH_THU  "┷"   // Bold Horizontal | T-Shape Horizontal Up
#define K_BR_THU  "┶"   // Bold Right      | T-Shape Horizontal Up
#define K_BL_THU  "┵"   // Bold Left       | T-Shape Horizontal Up
#define K_BUR_THU "┺"   // Bold Up Right   | T-Shape Horizontal Up
#define K_BUL_THU "┹"   // Bold Up Left    | T-Shape Horizontal Up

#define K_B_THD   "┳"   // Bold            | T-Shape Horizontal Down
#define K_BD_THD  "┰"   // Bold Down       | T-Shape Horizontal Down
#define K_BH_THD  "┯"   // Bold Horizontal | T-Shape Horizontal Down
#define K_BR_THD  "┮"   // Bold Right      | T-Shape Horizontal Down
#define K_BL_THD  "┭"   // Bold Left       | T-Shape Horizontal Down
#define K_BDR_THD "┲"   // Bold Down Right | T-Shape Horizontal Down
#define K_BDL_THD "┱"   // Bold Down Left  | T-Shape Horizontal Down

#define K_SLU "╵"       // Short Line Up
#define K_SLD "╷"       // Short Line Down
#define K_SVR "╶"       // Short Line Right
#define K_SVL "╴"       // Short Line Left

#define K_BSLU "╸"      // Bold Short Line Up
#define K_BSLD "╹"      // Bold Short Line Down
#define K_BSVR "╺"      // Bold Short Line Right
#define K_BSVL "╻"      // Bold Short Line Left

#define K_HL "─"        // Horizontal Line
#define K_VL "│"        // Vertical Line


// Line Types
#define LE_HFD "╌┄┈"    // Line Ending | Horizontal Fade
#define LS_HFD "┄┈╌"    // Line Start  | Horizontal Fade

#define LE_BKT "{"      // Line Ending | Bracket
#define LS_BKT "}"      // Line Start  | Bracket

#define LE_CIR "◯"      // Line Ending | Circle
#define LS_CIR "◯"      // Line Start  | Circle
#define LE_SQR "□"      // Line Ending | Square
#define LS_SQR "□"      // Line Start  | Square
#define LE_DIA "◇"      // Line Ending | Diamond
#define LS_DIA "◇"      // Line Start  | Diamond
#define LE_ARW "◁"      // Line Ending | Arrow
#define LS_ARW "▷"      // Line Start  | Arrow

#define LE_SQR_R "▢"    // Line Ending | Square
#define LS_SQR_R "▢"    // Line Start  | Square
#define LE_SQR_F "■"    // Line Ending | Square
#define LS_SQR_F "■"    // Line Start  | Square


#define L_H "─"         // Line Horizontal
#define L_V "│"         // Line Vertical

#define L_H_P "═"       // Line Horizontal Pipe
#define L_V_P "║"       // Line Vertical Pipe
#define L_H_R "╶"
#define L_H_F "╴"
#define L_V_U "╵"
#define L_V_B "╷"

#define L_H_D2 "╌"      // Line Horizontal Dotted 2
#define L_H_D3 "┄"      // Line Horizontal Dotted 3
#define L_H_D4 "┈"      // Line Horizontal Dotted 4

#define L_V_D2 "╎"      // Line Vertical Dotted 2
#define L_V_D3 "┆"      // Line Vertical Dotted 3
#define L_V_D4 "┊"      // Line Vertical Dotted 4


#define L_B_H "─"       // Bold Line Horizontal
#define L_B_V "│"       // Bold Line Vertical

#define L_B_H_P "═"     // Bold Line Horizontal Pipe
#define L_B_V_P "║"     // Bold Line Vertical Pipe
#define L_B_H_R "╶"
#define L_B_H_F "╴"
#define L_B_V_U "╵"
#define L_B_V_B "╷"

#define L_B_H_D2 "╌"    // Bold Line Horizontal Dotted 2
#define L_B_H_D3 "┄"    // Bold Line Horizontal Dotted 3
#define L_B_H_D4 "┈"    // Bold Line Horizontal Dotted 4

#define L_B_V_D2 "╎"    // Bold Line Vertical Dotted 2
#define L_B_V_D3 "┆"    // Bold Line Vertical Dotted 3
#define L_B_V_D4 "┊"    // Bold Line Vertical Dotted 4

//──────────────────────────────╌┄┈


extern int TRM_W;
extern int TRM_H;


void cartor_init();
void cartor_exit();
int  get_terminal_size(int *width, int *height);
void draw_horizontal_line(int length, int offset, const char *start_type, const char *end_type, const char *line_type);
void draw_open_bubble(const char *border_color, const char *title_color, String title, const char *content_color, String content);


#endif // CARTOR_CONSOLE_H