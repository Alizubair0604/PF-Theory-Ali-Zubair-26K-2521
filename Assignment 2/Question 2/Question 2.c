/*
 * Course: Programming Fundamentals
 * Title: Amicable Pair Finder
 * Description: Finds and displays all amicable pairs where both numbers are less than or equal to n.
 * Date: 27/10/26
 */

#include <stdio.h>

// Function that returns the sum of the proper divisors of a number //
int sumOfProperDivisors(int num) {
    int sum = 0;
    
    // Test divisors up to half of num as per hint //
    for(int i = 1; i <= num / 2; i++) {
        if(num % i == 0) {
            sum += i; // Add divisor to running sum //
        }
    }
    
    return sum; // Return total sum of proper divisors //
}

int main() {
    int n;
    int total_pairs = 0;
    
    // Input upper limit n from user //
    printf("Enter the upper limit n: ");
    scanf("%d", &n);
    
    printf("\nAmicable pairs up to %d:\n", n);
    
    // Loop through numbers to find amicable pairs //
    for(int a = 1; a <= n; a++) {
        int b = sumOfProperDivisors(a); // Calculate sum of proper divisors for a //
        
        // Ensure b > a, b <= n (avoids duplicates and out-of-bound checks) //
        // Also implicitly ensures a and b are different and not perfect numbers //
        if(b > a && b <= n) {
            // Check if the sum of proper divisors of b equals a //
            if(sumOfProperDivisors(b) == a) {
                printf("(%d, %d)\n", a, b); // Display the amicable pair //
                total_pairs++; // Increment pair counter //
            }
        }
    }
    
    // Display total number of pairs found, or a message if none found //
    if(total_pairs > 0) {
        printf("Total pairs: %d\n", total_pairs);
    } else {
        printf("No amicable pairs found up to %d.\n", n);
    }
    
    return 0;
}
