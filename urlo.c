#include <stdio.h>
#include <unistd.h>

// Set maximum URL character length
#define MAX_LINE 200
// Name of the text file containing the URLs
#define FILE_NAME "urls.txt"

// Define the open-URL command based on OS
#ifdef _WIN32
#define OPEN_CMD "start "

#elif __APPLE__
#define OPEN_CMD "open "

#elif __linux__
#define OPEN_CMD "xdg-open "

#endif

int main(int argc, char **argv) {
    // Open the file specified by FILE_NAME
    FILE *fp = fopen(FILE_NAME, "r");
    // Check if the file was successfully opened, if not, exit program
    if (fp == NULL) {
        fprintf(stderr, "%s could find the file %s", argv[0], FILE_NAME);
        return 1;
    }

    char url[MAX_LINE];
    // Loop while there are still lines to read in the file
    while (*fgets(url, MAX_LINE, fp)) {
        // Add the OS-specific open-URL command before the URL
        char cmd[MAX_LINE + 6] = OPEN_CMD;
        strcat(cmd, url);

        // Open the URL. If it returns a failure status, exit program
        if (system(cmd)) {
            fprintf(stderr, "%s could not open the url %s", argv[0], url);
            return 2;
        }
    }

    // Close the file
    fclose(fp);
    return 0;
}