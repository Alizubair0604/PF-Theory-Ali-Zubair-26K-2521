/*
 * Course: Programming Fundamentals
 * Title: Greenhouse Temperature Monitoring System
 * Description: Analyzes greenhouse sensor readings to track statistics, critical temperatures, and hot streaks.
 * Date: 27/10/26
 */

#include <stdio.h>

// Function to input all temperature readings into the two-dimensional array //
void inputReadings(int sensors, int hours, int temp[sensors][hours]) {
    for(int i = 0; i < sensors; i++) {
        printf("Enter readings for Sensor %d (%d hourly values): ", i + 1, hours);
        for(int j = 0; j < hours; j++) {
            scanf("%d", &temp[i][j]); // Input reading for sensor i at hour j //
        }
    }
}

// Function to analyze a single sensor's readings and compute statistics //
void analyzeSensor(int hours, int row_data[], int *total, float *avg, int *max_t, int *min_t, int *critical, int *warning, int *max_streak) {
    *total = 0;
    *max_t = row_data[0];
    *min_t = row_data[0];
    *critical = 0;
    *warning = 0;
    *max_streak = 0;
    int current_streak = 0;

    for(int j = 0; j < hours; j++) {
        int val = row_data[j]; // Current hourly temperature reading //
        *total += val; // Accumulate running total //

        if(val > *max_t) *max_t = val; // Update maximum temperature //
        if(val < *min_t) *min_t = val; // Update minimum temperature //

        if(val >= 40) {
            (*critical)++; // Count critical readings (40C or above) //
        }
        if(val >= 35 && val <= 39) {
            (*warning)++; // Count warning readings (between 35C and 39C inclusive) //
        }

        if(val >= 35) {
            current_streak++; // Track consecutive hot hours //
            if(current_streak > *max_streak) {
                *max_streak = current_streak; // Store longest hot streak //
            }
        } else {
            current_streak = 0; // Reset streak if temperature drops below 35C //
        }
    }
    *avg = (float)(*total) / hours; // Compute average temperature //
}

// Function to determine and return the sensor number with the highest average temperature //
int highestAverageSensor(int sensors, int hours, int temp[sensors][hours]) {
    int best_sensor = 0;
    float max_avg = -1.0;

    for(int i = 0; i < sensors; i++) {
        int total = 0;
        for(int j = 0; j < hours; j++) {
            total += temp[i][j]; // Sum readings for current sensor //
        }
        float avg = (float)total / hours; // Calculate average for current sensor //
        
        if(i == 0 || avg > max_avg) {
            max_avg = avg; // Update maximum average found //
            best_sensor = i; // Store sensor index //
        }
    }
    return best_sensor; // Return the index of the best sensor //
}

int main() {
    int sensors, hours;
    
    // Input number of sensors and hourly readings //
    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings per sensor: ");
    scanf("%d", &hours);
    
    int temp[sensors][hours]; // Declare 2D array for temperature readings //
    
    // Call input function to populate the array //
    inputReadings(sensors, hours, temp);
    
    printf("\n--- Individual Sensor Reports ---\n");
    
    // Process and display individual reports for each sensor //
    for(int i = 0; i < sensors; i++) {
        int total, max_t, min_t, critical, warning, max_streak;
        float avg;
        
        // Pass individual sensor row to the analysis function //
        analyzeSensor(hours, temp[i], &total, &avg, &max_t, &min_t, &critical, &warning, &max_streak);
        
        // Display formatted individual reports //
        printf("Sensor %d: Total=%d   Avg=%.2f   Max=%d   Min=%d\n", i + 1, total, avg, max_t, min_t);
        printf("           Critical=%d   Warning=%d   Longest hot streak=%d\n", critical, warning, max_streak);
    }
    
    // Call function to find the sensor with the highest average temperature //
    int best_sensor = highestAverageSensor(sensors, hours, temp);
    
    // Calculate average for the best sensor to display in final report //
    int best_total = 0;
    for(int j = 0; j < hours; j++) {
        best_total += temp[best_sensor][j];
    }
    float best_avg = (float)best_total / hours;
    
    // Display final report //
    printf("\nHighest average: Sensor %d (%.2f)\n", best_sensor + 1, best_avg);
    
    return 0;
}
