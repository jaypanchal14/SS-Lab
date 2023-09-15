#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

//Objective : 

int main() {
    time_t time_now;
    struct tm exec_time;
    
    printf("Enter the execution time (HH:MM): ");
    scanf("%d:%d", &exec_time.tm_hour, &exec_time.tm_min);
    exec_time.tm_sec = 0;
    
    // Clear the input buffer
    while (getchar() != '\n');

    // Validate user input
    if (exec_time.tm_hour < 0 || exec_time.tm_hour > 23 || exec_time.tm_min < 0 || exec_time.tm_min > 59) {
        printf("Invalid time format. Please enter a valid time (HH:MM).\n");
        return 1;
    }

    char script_path[256];
    printf("Enter the script path or name(without any option): ");
    fgets(script_path, sizeof(script_path), stdin);
    script_path[strcspn(script_path, "\n")] = '\0'; // Remove trailing newline character
    
    // Fork into a daemon process
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid > 0) {
        // Parent process exits
        exit(0);
    }
    
    // Child process becomes the daemon
    // So it will come out of the current process's interactive mode, and whenever the scheduled time will come
    // it will print the output directly on the console. 
    setsid();
    
    while (1) {
        time(&time_now);
        struct tm* curr_time = localtime(&time_now);
        
        if (curr_time->tm_hour == exec_time.tm_hour && curr_time->tm_min == exec_time.tm_min) {
            pid_t script_pid = fork();
            
            if (script_pid == 0) {
                execlp(script_path, script_path, NULL);
                perror("Script execution failed");
                exit(1);
            } else if (script_pid > 0) {
                int status;
                waitpid(script_pid, &status, 0);
                
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    printf("Script executed successfully.\n");
                } else {
                    printf("Script execution failed.\n");
                }
                
                exit(0);
            }
        } else {
        
        	// Uncomment if you want to print the remaining time
            // Calculate and display the countdown timer
            /*int remaining_seconds = (exec_time.tm_hour - curr_time->tm_hour) * 3600 +
                                    (exec_time.tm_min - curr_time->tm_min) * 60 -
                                    curr_time->tm_sec;
            printf("Script will run in %d seconds.", remaining_seconds);
            fflush(stdout);
            */ 
        }
        
        sleep(1); // Sleep to check time again
    }
    
    return 0;
}

