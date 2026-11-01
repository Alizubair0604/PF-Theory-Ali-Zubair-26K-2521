/*
 * Course: Programming Fundamentals
 * Title: University Library Management System
 * Description: Menu-driven application to manage library books, member registration, borrowing, returns, and late return fines with waivers.
 * Date: 27/10/26
 */

#include <stdio.h>
#include <string.h>

// Function to display menu options //
void displayMenu() {
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
}

// Function to register a member //
void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter member name: ");
    scanf(" %[^\n]s", name); // Read string with spaces //
    printf("Enter Student/Member ID: ");
    scanf("%d", studentID);
    
    *memberType = 0;
    while (*memberType != 1 && *memberType != 2) {
        printf("Enter membership type (1 for Student, 2 for Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Invalid membership type! Please enter 1 or 2.\n");
        }
    }
    printf("Member registered successfully!\n");
}

// Function to display all books and their available copies //
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n--------------------------------------------------\n");
    printf(" ID \t\t Title \t\t\t Copies\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        printf(" %d \t %-20s \t %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
    printf("--------------------------------------------------\n");
}

// Function to handle book borrowing //
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("Error: You have reached the maximum limit of 3 borrowed books!\n");
        return;
    }
    
    int b_id;
    printf("Enter book ID to borrow: ");
    scanf("%d", &b_id);
    
    int index = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == b_id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Error: Invalid book ID!\n");
    } else if (availableCopies[index] <= 0) {
        printf("Error: Book is currently out of stock!\n");
    } else {
        // Check if member already has this book //
        int already_has = 0;
        for (int i = 0; i < *borrowedCount; i++) {
            if (borrowedBookIDs[i] == b_id) {
                already_has = 1;
                break;
            }
        }
        
        if (already_has) {
            printf("Error: You have already borrowed this book!\n");
        } else {
            borrowedBookIDs[*borrowedCount] = b_id;
            (*borrowedCount)++;
            availableCopies[index]--; // Decrease available copies by one //
            printf("Book successfully borrowed!\n");
        }
    }
}

// Function to handle book returns, fine calculations, and waivers //
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    if (*borrowedCount == 0) {
        printf("Error: You have no books currently borrowed!\n");
        return 0.0;
    }
    
    int b_id;
    printf("Enter book ID to return: ");
    scanf("%d", &b_id);
    
    int pos = -1;
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == b_id) {
            pos = i;
            break;
        }
    }
    
    if (pos == -1) {
        printf("Error: You have not borrowed a book with this ID!\n");
        return 0.0;
    }
    
    int days_kept;
    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &days_kept);
    
    while (days_kept <= 0) {
        printf("Invalid number of days! Enter a positive value: ");
        scanf("%d", &days_kept);
    }
    
    // Allowed period: Student = 14 days, Faculty = 30 days //
    int allowed_days = (memberType == 1) ? 14 : 30;
    float current_fine = 0.0;
    
    if (days_kept > allowed_days) {
        int extra_days = days_kept - allowed_days;
        if (memberType == 1) {
            current_fine = extra_days * 20.0; // Student: Rs. 20 per extra day //
        } else {
            current_fine = extra_days * 10.0; // Faculty: Rs. 10 per extra day //
        }
    }
    
    *totalFine += current_fine; // Add to cumulative fine before waiver //
    float payable_fine = current_fine;
    
    // Check for membership code waiver //
    char code[20];
    printf("Enter membership code for waiver (enter 'NONE' if none): ");
    scanf("%s", code);
    
    if (strcmp(code, "LIB2026") == 0) {
        payable_fine *= 0.5; // Apply 50% waiver //
        printf("50%% waiver successfully applied to this return's fine!\n");
    }
    
    // Restore available copies in inventory //
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == b_id) {
            availableCopies[i]++;
            break;
        }
    }
    
    // Remove book from borrowed list //
    for (int i = pos; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;
    
    printf("Book returned successfully! Fine payable for this return: Rs. %.2f\n", payable_fine);
    return payable_fine;
}

// Function to display member record and current status //
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n===== MEMBER RECORD =====\n");
    printf("Name            : %s\n", name);
    printf("Student/ID      : %d\n", studentID);
    printf("Membership Type : %s\n", (memberType == 1) ? "Student" : "Faculty");
    
    printf("Borrowed Books  : ");
    if (borrowedCount == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < borrowedCount; i++) {
            printf("%d ", borrowedBookIDs[i]);
        }
        printf("\n");
    }
    printf("Total Fine (Pre-waiver)  : Rs. %.2f\n", totalFine);
    printf("Fine Payable (Post-waiver): Rs. %.2f\n", totalFine * 0.5); // Simplified display representation for active balance //
}

int main() {
    // Initialize Book Inventory //
    int totalBooks = 4;
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    
    // Initialize Member Record Variables //
    char name[50];
    int studentID = 0;
    int memberType = 1; // Default to Student //
    int borrowedBookIDs[3] = {0};
    int borrowedCount = 0;
    float totalFine = 0.0;
    float fineAfterWaiver = 0.0;
    
    // Perform initial member registration as part of startup //
    printf("Welcome to the University Library System. Please register first.\n");
    registerMember(name, &studentID, &memberType);
    
    int choice;
    do {
        displayMenu();
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                {
                    float ret_fine = returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                    fineAfterWaiver += ret_fine;
                }
                break;
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Exiting application. Goodbye!\n");
                break;
            default:
                printf("Invalid menu choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);
    
    return 0;
}
