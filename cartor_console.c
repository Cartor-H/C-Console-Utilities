#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "cartor_console.h"
// #include "strings.h"

int TRM_W = 64; // Default terminal width
int TRM_H = 128; // Default terminal height

/**
 * Gets the current width and height of the terminal
 * 
 * @param width Pointer to store the terminal width
 * @param height Pointer to store the terminal height
 * @return 0 on success, -1 on failure
 */
int get_terminal_size(int *width, int *height) {
    struct winsize w;
    
    // TIOCGWINSZ is a request for getting the window size
    // 0 is the file descriptor for standard input
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        // Try Using Env Vars As Fallback
        char *columns = getenv("COLUMNS");
        char *lines = getenv("LINES");
        
        if (columns != NULL && lines != NULL) {
            *width = atoi(columns);
            *height = atoi(lines);
            return 0;
        }
        
        return -1;
    }
    
    *width = w.ws_col;
    *height = w.ws_row;
    
    return 0;
}

/**
 * Initializes the state
 */
void cartor_init(){
    // Get the terminal size
    if (get_terminal_size(&TRM_W, &TRM_H) == -1) {
        fprintf(stderr, "Error getting terminal size\n");
        exit(EXIT_FAILURE);
    }
    
    // Set the terminal to raw mode
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Clear the screen
    printf("\033[H\033[J");
}

/**
 * Cleans up the state
 */
void cartor_exit(){
    // Reset the terminal to its original state
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    oldt.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    // Clear the screen
    // printf("\033[H\033[J");
    // Move the cursor to the top left corner
    // printf("\033[0;0H");
    // Reset the cursor color
    printf("\033[0m");
}

/**
 * Draws A Horizontal Line
 */
void draw_horizontal_line(int length, int offset, const char *start_type, const char *end_type, const char *line_type) {
    if (length <= 0) {
        return;
    }

    int start_len = start_type ? strlen(start_type) : 0;
    int end_len = end_type ? strlen(end_type) : 0;

    // Ensure the total length does not exceed the specified length
    int line_length = length - start_len - end_len;
    if (line_length < 0) {
        line_length = 0;
    }

    // Print the offset
    for (int i = 0; i < offset; i++) {
        putchar(' ');
    }

    // Print the starting type
    if (start_type) {
        printf("%s", start_type);
    }

    // Print the line
    for (int i = 0; i < line_length; i++) {
        printf("%s", line_type);
    }

    // Print the ending type
    if (end_type) {
        printf("%s", end_type);
    }

    // Move to the next line
    // putchar('\n');
}

void draw_hrz_line(int length) {
    draw_horizontal_line(length, 0, NULL, NULL, L_H);
}
void horizontal_repeat(int length, const char *line_type) {
    draw_horizontal_line(length, 0, NULL, NULL, line_type);
}

/**
 * Draws an oppen bubble
 * for each new line in content the bubble height will be extended.
 * The bubble will look something like this:
 * ╭{Title}──────────────────╌┄┈
 * │  CONTENT_LINE_0       ╌┄┈
 * │  CONTENT_LINE_1     ╌┄┈
 * │  CONTENT_LINE_2   ╌┄┈
 * ╰─────────────────╌┄┈
 */
void draw_open_bubble(const char *border_color, const char *title_color, String title, const char *content_color, String content){
    // Calculate the bubble width
    int bubble_width = strDispWidth(content) + strHeight(content) + 4; // Adjust for borders

    // Print the top border
    printf("%s╭{%s%s%s%s}", border_color, C_R, title_color, str2char(title), border_color);
    draw_hrz_line(bubble_width - strDispWidth(title));
    printf("%s%s\n", LE_HFD, C_R);

    // Print the content
    for (int i = 0; i < strHeight(content); i++) {
        printf("%s│%s%s  %s%s", border_color, C_R, content_color, str2char(getRow(content, i)), border_color);
        horizontal_repeat(bubble_width - strDispWidth(getRow(content, i)) - i*2 - 2, " ");
        printf("%s%s\n", LE_HFD, C_R);
    }


    // line = strtok(content_copy, "\n");
    // int i = 1;
    // while (line != NULL) {
    //     printf("%s│%s%s  %s%s", border_color, C_R, content_color, line, border_color);
    //     horizontal_repeat(bubble_width - strlen(line) - i*2, " ");
    //     printf("%s%s\n", LE_HFD, C_R);
    //     line = strtok(NULL, "\n");
    //     i++;
    // }

    // free(content_copy); // Free the allocated memory

    // Print the bottom border
    printf("%s╰", border_color);
    draw_hrz_line(bubble_width - strHeight(content)*2);
    printf("%s%s\n", LE_HFD, C_R);
}