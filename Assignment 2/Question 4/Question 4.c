/*
 * Course: Programming Fundamentals
 * Title: Bakery Festival Sales Management System
 * Description: Manages festival sales, computes statistics per day, summarizes total revenue, and plots a bar chart.
 * Date: 27/10/26
 */

#include <stdio.h>

// Function to input and validate festival days (1 to 7) //
int getValidDays() {
    int days = 0;
    while (days < 1 || days > 7) {
        printf("Number of days: ");
        scanf("%d", &days);
        if (days < 1 || days > 7) {
            printf("Invalid value! Please enter a value between 1 and 7.\n");
        }
    }
    return days; // Return valid number of days //
}

// Function to input daily orders, calculate sales, average, and highest order //
float calculateDailySales(int dayNumber) {
    int num_orders;
    printf("Day %d - Number of orders: ", dayNumber);
    scanf("%d", &num_orders);
    
    float total_sales = 0.0;
    float highest_order = 0.0;
    
    printf("Order amounts: ");
    for (int j = 0; j < num_orders; j++) {
        float amount;
        scanf("%f", &amount);
        
        // Validate that each amount is greater than zero //
        while (amount <= 0) {
            printf("Invalid amount! Enter amount greater than zero: ");
            scanf("%f", &amount);
        }
        
        total_sales += amount; // Accumulate daily sales //
        if (j == 0 || amount > highest_order) {
            highest_order = amount; // Track highest order amount //
        }
    }
    
    float avg_order = total_sales / num_orders; // Compute average order amount //
    
    // Display daily statistics //
    printf("Total sales: Rs. %.2f\n", total_sales);
    printf("Average order: Rs. %.2f\n", avg_order);
    printf("Highest order: Rs. %.2f\n", highest_order);
    
    return total_sales; // Return total sales for the day //
}

// Function to find the day with the highest total sales //
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int best_day = 1;
    float max_sales = dailySales[0];
    
    for (int i = 1; i < numberOfDays; i++) {
        if (dailySales[i] > max_sales) {
            max_sales = dailySales[i]; // Update maximum sales //
            best_day = i + 1; // Store 1-based day index //
        }
    }
    return best_day; // Return day number with highest sales //
}

// Function to display daily sales bar chart using asterisks //
void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (int i = 0; i < numberOfDays; i++) {
        int stars = (int)(dailySales[i] / 100); // One asterisk for every Rs. 100 //
        printf("Day %d: ", i + 1);
        for (int s = 0; s < stars; s++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    // Get valid number of festival days //
    int numberOfDays = getValidDays();
    
    float dailySales[numberOfDays]; // Array to store total sales for each day //
    float total_festival_sales = 0.0;
    
    // Process orders for each festival day //
    for (int i = 0; i < numberOfDays; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        total_festival_sales += dailySales[i]; // Accumulate overall festival sales //
    }
    
    // Find the day with the highest total sales //
    int best_day = findHighestSalesDay(dailySales, numberOfDays);
    float highest_daily_sales = dailySales[best_day - 1];
    
    // Display Festival Summary //
    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", total_festival_sales);
    printf("Day with highest sales: Day %d\n", best_day);
    printf("Highest daily sales: Rs. %.2f\n", highest_daily_sales);
    
    // Display Daily Sales Bar Chart //
    displayBarChart(dailySales, numberOfDays);
    
    return 0;
}
