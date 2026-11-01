/*
 * Course: Programming Fundamentals
 * Title: Cinema Hall Seat Booking Management System
 * Description: Manages cinema seat availability and allocates consecutive seats prioritizing the middle row.
 * Date: 27/10/26
 */

#include <stdio.h>

int main() {
    int rows, cols;
    
    // Prompt and input number of rows and columns //
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &cols);
    
    int seats[rows][cols];
    
    // Input current seating status (0 for available, 1 for booked) //
    printf("Enter the seating status (%d rows by %d cols):\n", rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &seats[i][j]);
        }
    }
    
    // Display Seating Arrangement (_ for available, X for booked) //
    printf("\nSeating Arrangement:\n  ");
    for(int j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for(int i = 0; i < rows; i++) {
        printf("R%d ", i);
        for(int j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
    
    // Seat Availability Report //
    int total_free = 0;
    printf("\nFree seats per row: ");
    for(int i = 0; i < rows; i++) {
        int row_free = 0;
        for(int j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                row_free++;
            }
        }
        printf("%d ", row_free);
        total_free += row_free;
    }
    printf(" Total free: %d\n", total_free);
    
    // Group Booking Input & Validation //
    int k;
    printf("\nEnter number of customers (k) who want to sit together: ");
    scanf("%d", &k);
    
    if(k <= 0 || k > cols) {
        // Validation check for group size //
        printf("Error: Invalid group size! Must be greater than 0 and less than or equal to the number of seats in a row.\n");
    } else {
        int found = 0;
        int alloc_row = -1, alloc_start = -1;
        int mid = rows / 2; // Calculate middle row using integer division //
        
        // Search rows starting from the middle row outwards //
        for(int d = 0; d < rows && !found; d++) {
            for(int i = 0; i < 2 && !found; i++) {
                int r = (i == 0) ? (mid - d) : (mid + d);
                
                // Ensure row index is valid and avoid duplicate check when d == 0 //
                if((d > 0 || i == 0) && (r >= 0 && r < rows)) {
                    int current_consecutive = 0;
                    int start_seat = -1;
                    
                    // Within each row, find the first available block of k consecutive seats //
                    for(int c = 0; c < cols; c++) {
                        if(seats[r][c] == 0) {
                            if(current_consecutive == 0) {
                                start_seat = c;
                            }
                            current_consecutive++;
                            
                            if(current_consecutive == k) {
                                alloc_row = r;
                                alloc_start = start_seat;
                                found = 1;
                                break; // Stop searching once a suitable block is found //
                            }
                        } else {
                            current_consecutive = 0;
                            start_seat = -1;
                        }
                    }
                }
            }
        }
        
        // Confirm Booking or Handle Unsuccessful Booking //
        if(found) {
            // Update seating plan by marking allocated seats as 1 //
            for(int c = alloc_start; c < alloc_start + k; c++) {
                seats[alloc_row][c] = 1;
            }
            
            printf("\nGroup of %d seated in Row %d, Seats %d to %d\n\n", k, alloc_row, alloc_start, alloc_start + k - 1);
            
            // Display updated seating arrangement //
            printf("  ");
            for(int j = 0; j < cols; j++) {
                printf("%d ", j);
            }
            printf("\n");
            
            total_free = 0;
            for(int i = 0; i < rows; i++) {
                printf("R%d ", i);
                int row_free = 0;
                for(int j = 0; j < cols; j++) {
                    if(seats[i][j] == 0) {
                        printf("_ ");
                        row_free++;
                    } else {
                        printf("X ");
                    }
                }
                total_free += row_free;
                printf("\n");
            }
            printf("\nRemaining free seats: %d\n", total_free);
            
        } else {
            // Handle unsuccessful booking: leave plan unchanged //
            printf("\nSorry! No consecutive seats available for a group of %d. Seating plan remains unchanged.\n", k);
        }
    }
    
    return 0;
}
