#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <regex.h>



#include "strings.h"

// Create String From StringLine
String lineToString(StringLine str) {
    String result;
    result.type = STRING_LINE;
    result.data.Line = str;
    return result;
}

// Create String From StringMtrx
String mtrxToString(StringMtrx str) {
    String result;
    result.type = STRING_MTRX;
    result.data.Mtrx = str;
    return result;
}


String chr2str(char *str) {
    return charToString(str);
}

// Create String From StringChar
String charToString(char *str) {
    String result;

    // Make A Copy Of The String So We Can Modify It
    char *content_copy = strdup(str);
    if (content_copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Count & Sepparate str Based On New Lines
    char *line = strtok(content_copy, "\n");
    // No new lines
    if (!line) {
        result.type = STRING_LINE;
        result.data.Line.val = strdup(str);
        result.data.Line.len = strlen(str);
    // New lines found
    } else {
        result.type = STRING_MTRX;
        result.data.Mtrx.height = 0;
        result.data.Mtrx.width  = 0;
        result.data.Mtrx.disp_width = 0;
        
        while (line != NULL) {
            // Calc Height
            result.data.Mtrx.height += 1;

            // Calc Width
            int line_length = strlen(line);
            if (line_length > result.data.Mtrx.width) {
                result.data.Mtrx.width = line_length;
            }

            // Calc Disp Width
            int disp_line_length = get_disp_len(line);
            if (disp_line_length > result.data.Mtrx.disp_width) {
                result.data.Mtrx.disp_width = disp_line_length;
            }

            line = strtok(NULL, "\n");
        }

        free(content_copy); // Free the allocated memory

        // Allocate Memory For The Rows
        result.data.Mtrx.rows = malloc(result.data.Mtrx.height * sizeof(StringLine));
        if (result.data.Mtrx.rows == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        // Make A Copy Of The String So We Can Modify It
        content_copy = strdup(str);
        if (content_copy == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        // Reset line to the start of the string
        line = strtok(content_copy, "\n");
        int i = 0;
        while (line != NULL) {
            // Allocate Memory For Each Row
            result.data.Mtrx.rows[i].val = strdup(line);
            if (result.data.Mtrx.rows[i].val == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            result.data.Mtrx.rows[i].len = strlen(line);
            result.data.Mtrx.rows[i].disp_len = get_disp_len(line);
            i++;
            line = strtok(NULL, "\n");
        }
        // Free the content_copy
        free(content_copy);
    }

    result.type = STRING_LINE;
    result.data.Line.val = str;
    result.data.Line.len = strlen(str);
    result.data.Line.disp_len = result.data.Line.len; // Assuming no special characters for now
    return result;
}



// Concatenate two Strings
String concat(String str1, String str2) {
    String result;

    if (str1.type != str2.type) {
        fprintf(stderr, "Error: Cannot concatenate Strings of different types.\n");
        exit(EXIT_FAILURE);
    }

    switch (str1.type) {
        case STRING_LINE: {
            size_t len1 = strlen(str1.data.Line.val);
            size_t len2 = strlen(str2.data.Line.val);
            char *newLine = malloc(len1 + len2 + 1);
            if (!newLine) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(newLine, str1.data.Line.val);
            strcat(newLine, str2.data.Line.val);
            StringLine line = { .val = newLine };
            result = lineToString(line);
            free(newLine);
            break;
        }
        case STRING_MTRX: {
            fprintf(stderr, "Error: Concatenation for STRING_MTRX is not supported.\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

// \033[38;5;201m
// regex`(^|[^\\])<([^>]*)>`

/**
 * Count Display Length (w/o special characters or tokens) 
 * 
 * Ignores anything of the format:
 *   regex`\033\[[;0-9]*m`
 * 
 * @param src The string to count the display length of
 * @return The display length of the string
 */
int get_disp_len(char *str) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\033\\[[;0-9]*m";
    int count = 0;

    // Compile the regex
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(EXIT_FAILURE);
    }

    char *current = str;
    while (*current != '\0') {
        // Check if the current part of the string matches the regex
        if (regexec(&regex, current, 1, &match, 0) == 0 && match.rm_so == 0) {
            // Skip the escape sequence
            current += match.rm_eo;
        } else {
            // Count the character and move to the next
            count++;
            current++;
        }
    }

    // Free the compiled regex
    regfree(&regex);

    return count;
}


void print(String str) {
    switch (str.type) {
        case STRING_LINE:
            printf("%s", str.data.Line.val);
            break;
        case STRING_MTRX:
            for (int i = 0; i < str.data.Mtrx.height-1; i++) {
                printf("%s\n", str.data.Mtrx.rows[i].val);
            }
            printf("%s", str.data.Mtrx.rows[str.data.Mtrx.height-1].val);
            break;
    }
}

void printnl(String str) {
    switch (str.type) {
        case STRING_LINE:
            printf("%s\n", str.data.Line.val);
            break;
        case STRING_MTRX:
            for (int i = 0; i < str.data.Mtrx.height; i++) {
                printf("%s\n", str.data.Mtrx.rows[i].val);
            }
            break;
    }
}