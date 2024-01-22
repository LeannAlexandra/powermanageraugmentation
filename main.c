#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <time.h>


#define MAX_PATH 256
#define INACTIVITY_THRESHOLD 300 // 5 minutes in seconds
#define CHECK_INTERVAL 10 //10 seconds
#define TRUE 1
#define FALSE 0

int verboseLogging = FALSE;
int logging = TRUE;

// MANJARO SPECIFIC Function to check if the laptop is plugged into AC power
int isPluggedIn() {
    // Platform-specific code for Linux
    // You may need to adjust this based on your Linux distribution
    FILE* fp = popen("acpi -a | grep -c on-line", "r");
    if (!fp) {
        perror("Failed to execute command");
        exit(EXIT_FAILURE);
    }

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    return result;
}

// MANJARO SPECIFIC: Function to check if the lid is closed
int isLidClosed() {
    // Platform-specific code for Linux
    // You may need to adjust this based on your Linux distribution
    FILE* fp = popen("cat /proc/acpi/button/lid/LID/state | grep -c closed", "r");
    if (!fp) {
        perror("Failed to execute command");
        exit(EXIT_FAILURE);
    }

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    return result;
}

// LINUX SPECIFIC Function to force the computer into sleep mode
void forceSleep() {
    system("systemctl suspend");
}


// MANJARO Platform-specific implementation for getting inactive time
// Function to get the time since the last user activity in seconds
unsigned int getInactiveTime() {
    Display* display = XOpenDisplay(NULL);

    if (!display) {
        fprintf(stderr, "Unable to open X display\n");
        exit(EXIT_FAILURE);
    }

    XScreenSaverInfo info;
    XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);

    unsigned int idleTime = info.idle / 1000;  // Convert milliseconds to seconds

    XCloseDisplay(display);

    return idleTime;
}

// Function to get the current timestamp
void printTimestamp() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", 
           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}


int main() {
    while (1) {
        // Check if the lid is closed
        if (isLidClosed()) {
            // If the lid is closed, check power status
            if(logging||verboseLogging)
                printTimestamp(); // Print timestamp
            if(verboseLogging){
                printf("Lid is closed. ");
            }
            if (!isPluggedIn()) {
                if(verboseLogging)
                    printf("Not Plugged In. ");
                // If not connected to AC power, check inactivity time
                //sleep(CHECK_INTERVAL); // Simulating a 10-second interval, replace with your code
                // Check if inactivity time exceeds the threshold
                if (getInactiveTime() > INACTIVITY_THRESHOLD) {
                    if(verboseLogging||logging)
                        printf("Idle Time exceeds Threshold. - GOING TO SLEEP\n");
                    // printf("TODO: TIME FOR NIGHTY NIGHT NIGHT");
                    forceSleep();
                }else if( verboseLogging){
                    printf("Inactive time within threshold. %d\n",getInactiveTime());
                }
            }else if (verboseLogging){
                printf("Plugged In. Skipping inactivity check.\n");
            }
        }

        // Adjust the sleep duration based on your needs
        // This is just a sample code, you might need to refine it based on your system's behavior
        sleep(CHECK_INTERVAL); // Adjust as needed
    }

    return 0;
}
