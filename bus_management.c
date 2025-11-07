#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 180
#define MAX_BUSES 4
#define MAX_NAME_LENGTH 50
#define MAX_AREA_LENGTH 50
#define MAX_PHONE_LENGTH 15

typedef struct {
    int busNumber;
    char driverName[MAX_NAME_LENGTH];
    char driverPhone[MAX_PHONE_LENGTH];
} Bus;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char area[MAX_AREA_LENGTH];
    char board[MAX_NAME_LENGTH];
    char depart[MAX_NAME_LENGTH];
    float fees;
    char pickupTime[10];
    char departTime[10];
    char parentPhone[MAX_PHONE_LENGTH];
    int busNumber;
} Student;

Bus buses[MAX_BUSES];
Student students[MAX_STUDENTS];
int studentCount = 0;

void initializeData();
void displayMainMenu();
void displayAllRecordsTable();
void searchRecords();
void editRecord();
void deleteRecord();
void saveToFile();
void displayBusDetails();
void addNewStudent();
void clearInputBuffer();
int askToContinue();
void updateFile();

int main() {
    initializeData();
    int choice;
    
    printf("=== COLLEGE BUS MANAGEMENT SYSTEM ===\n");
    printf("Initialized with %d students\n\n", studentCount);
    
    do {
        displayMainMenu();
        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1: 
                displayAllRecordsTable(); 
                break;
            case 2: 
                searchRecords(); 
                break;
            case 3: 
                editRecord(); 
                break;
            case 4: 
                deleteRecord(); 
                break;
            case 5: 
                addNewStudent();
                break;
            case 6: 
                saveToFile(); 
                break;
            case 7: 
                displayBusDetails(); 
                break;
            case 8: 
                printf("Exiting program. Goodbye!\n"); 
                break;
            default: 
                printf("Invalid choice! Please try again.\n");
        }
        
        // Ask to continue after each operation (except exit)
        if(choice != 8) {
            if(!askToContinue()) {
                break;
            }
        }
        
    } while(choice != 8);
    
    return 0;
}

int askToContinue() {
    char response;
    printf("\nDo you want to continue to main menu? (y/n): ");
    scanf("%c", &response);
    clearInputBuffer();
    
    if(response == 'y' || response == 'Y') {
        return 1;
    } else if(response == 'n' || response == 'N') {
        printf("Exiting program. Goodbye!\n");
        return 0;
    } else {
        printf("Invalid input! Returning to main menu.\n");
        return 1;
    }
}

void initializeData() {
    // Initialize buses with driver details
    buses[0].busNumber = 101; 
    strcpy(buses[0].driverName, "Rajesh Kumar"); 
    strcpy(buses[0].driverPhone, "9876543210");
    
    buses[1].busNumber = 102; 
    strcpy(buses[1].driverName, "Suresh Reddy"); 
    strcpy(buses[1].driverPhone, "9876543211");
    
    buses[2].busNumber = 103; 
    strcpy(buses[2].driverName, "Anil Naidu"); 
    strcpy(buses[2].driverPhone, "9876543212");
    
    buses[3].busNumber = 104; 
    strcpy(buses[3].driverName, "Praveen Chowdary"); 
    strcpy(buses[3].driverPhone, "9876543213");
    
    // Guntur District areas
    char firstNames[][20] = {
        "Aarav", "Aditi", "Akash", "Ananya", "Arjun", "Bhavana", "Chaitanya", "Divya", 
        "Esha", "Farhan", "Gaurav", "Harika", "Ishan", "Jahnavi", "Kiran", "Lakshmi",
        "Madhav", "Neha", "Omkar", "Pooja", "Rahul", "Sneha", "Tarun", "Usha",
        "Vikram", "Yamini", "Zubair", "Sai", "Krishna", "Venkat", "Rama", "Surya",
        "Lakshmi", "Parvati", "Saraswati", "Gayatri", "Anjali", "Priya", "Divya", "Swathi",
        "Ravi", "Teja", "Manisha", "Pavan", "Sravani", "Naveen", "Supriya", "Kiran",
        "Vishal", "Suman", "Raj", "Latha", "Mahesh", "Anusha", "Sandeep", "Kavitha"
    };
    
    char lastNames[][20] = {
        "Rao", "Reddy", "Naidu", "Chowdary", "Sharma", "Kumar", "Patel", "Joshi",
        "Das", "Yadav", "Mishra", "Pandey", "Gupta", "Verma", "Malhotra", "Iyer"
    };
    
    // Guntur District areas only
    char areas[][30] = {
        "Guntur City", "Amaravathi", "Mangalagiri", "Tadepalli", "Tenali",
        "Ponnur", "Bapatla", "Chilakaluripet", "Narasaraopet", "Vinukonda",
        "Macherla", "Sattenapalli", "Piduguralla", "Repalle", "Veldurthi"
    };
    
    char boardLocations[][30] = {
        "Main Gate", "RTC Bus Stand", "Highway Stop", "College Front", "Temple Road",
        "Police Station", "Bank Colony", "Market Center"
    };
    
    char departLocations[][30] = {
        "College", "Hostel", "Campus", "Main Building", "Library"
    };
    
    char pickupTimes[][10] = {"06:30 AM", "06:45 AM", "07:00 AM", "07:15 AM", "07:30 AM"};
    char departTimes[][10] = {"03:30 PM", "03:45 PM", "04:00 PM", "04:15 PM", "04:30 PM"};
    
    // Generate 150 unique students
    for(int i = 0; i < 150; i++) {
        students[i].id = i + 1;
        
        // Create unique name
        char fullName[MAX_NAME_LENGTH];
        strcpy(fullName, firstNames[i % 56]); // Using 56 first names
        strcat(fullName, " ");
        strcat(fullName, lastNames[i % 16]); // Using 16 last names
        strcpy(students[i].name, fullName);
        
        // Assign other details
        strcpy(students[i].area, areas[i % 15]);
        strcpy(students[i].board, boardLocations[i % 8]);
        strcpy(students[i].depart, departLocations[i % 5]);
        students[i].fees = 2500 + (rand() % 6) * 50; // 2500-2950 in steps of 50
        strcpy(students[i].pickupTime, pickupTimes[i % 5]);
        strcpy(students[i].departTime, departTimes[i % 5]);
        students[i].busNumber = 101 + (i % 4);
        
        // Generate unique phone number
        char phone[MAX_PHONE_LENGTH];
        sprintf(phone, "98765%05d", 10000 + i);
        strcpy(students[i].parentPhone, phone);
        
        studentCount++;
    }
}

void displayMainMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Display All Student Records\n");
    printf("2. Search Students\n");
    printf("3. Edit Student Record\n");
    printf("4. Delete Student Record\n");
    printf("5. Add New Student\n");
    printf("6. Save Records to File\n");
    printf("7. Display Bus Details\n");
    printf("8. Exit\n");
}

void updateFile() {
    FILE *file = fopen("bus_records.txt", "w");
    if(file == NULL) {
        printf("Error updating file!\n");
        return;
    }
    
    fprintf(file, "================================================================================================================================================================\n");
    fprintf(file, "| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    fprintf(file, "================================================================================================================================================================\n");
    
    for(int i = 0; i < studentCount; i++) {
        // Find driver details for this student's bus
        char driverName[MAX_NAME_LENGTH] = "";
        
        for(int j = 0; j < 4; j++) {
            if(buses[j].busNumber == students[i].busNumber) {
                strcpy(driverName, buses[j].driverName);
                break;
            }
        }
        
        fprintf(file, "| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
               students[i].id, students[i].busNumber, driverName,
               students[i].name, students[i].area, students[i].fees, 
               students[i].board, students[i].pickupTime, students[i].depart, students[i].departTime, students[i].parentPhone);
    }
    
    fprintf(file, "================================================================================================================================================================\n");
    fprintf(file, "Total Records: %d\n", studentCount);
    
    fclose(file);
    printf("File updated successfully!\n");
}

void addNewStudent() {
    if(studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students! Maximum limit (%d) reached.\n", MAX_STUDENTS);
        return;
    }
    
    printf("\n=== ADD NEW STUDENT ===\n");
    
    // Get student details from user
    students[studentCount].id = studentCount + 1;
    
    printf("Enter Student Name: ");
    fgets(students[studentCount].name, MAX_NAME_LENGTH, stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = 0;
    
    printf("Enter Area: ");
    fgets(students[studentCount].area, MAX_AREA_LENGTH, stdin);
    students[studentCount].area[strcspn(students[studentCount].area, "\n")] = 0;
    
    printf("Enter Board Location: ");
    fgets(students[studentCount].board, MAX_NAME_LENGTH, stdin);
    students[studentCount].board[strcspn(students[studentCount].board, "\n")] = 0;
    
    printf("Enter Depart Location: ");
    fgets(students[studentCount].depart, MAX_NAME_LENGTH, stdin);
    students[studentCount].depart[strcspn(students[studentCount].depart, "\n")] = 0;
    
    printf("Enter Bus Fees: ");
    scanf("%f", &students[studentCount].fees);
    clearInputBuffer();
    
    printf("Enter Pickup Time (e.g., 07:30 AM): ");
    fgets(students[studentCount].pickupTime, 10, stdin);
    students[studentCount].pickupTime[strcspn(students[studentCount].pickupTime, "\n")] = 0;
    
    printf("Enter Depart Time (e.g., 04:30 PM): ");
    fgets(students[studentCount].departTime, 10, stdin);
    students[studentCount].departTime[strcspn(students[studentCount].departTime, "\n")] = 0;
    
    printf("Enter Parent Phone Number: ");
    fgets(students[studentCount].parentPhone, MAX_PHONE_LENGTH, stdin);
    students[studentCount].parentPhone[strcspn(students[studentCount].parentPhone, "\n")] = 0;
    
    printf("Enter Bus Number (101-104): ");
    scanf("%d", &students[studentCount].busNumber);
    clearInputBuffer();
    
    studentCount++;
    printf("\nNew student added successfully! Student ID: %d\n", studentCount);
    
    // Display the added record
    printf("\n=== ADDED STUDENT RECORD ===\n");
    printf("================================================================================================================================================================\n");
    printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    printf("================================================================================================================================================================\n");
    
    // Find driver details
    char driverName[MAX_NAME_LENGTH] = "";
    for(int j = 0; j < 4; j++) {
        if(buses[j].busNumber == students[studentCount-1].busNumber) {
            strcpy(driverName, buses[j].driverName);
            break;
        }
    }
    
    printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
           students[studentCount-1].id, students[studentCount-1].busNumber, driverName,
           students[studentCount-1].name, students[studentCount-1].area, students[studentCount-1].fees, 
           students[studentCount-1].board, students[studentCount-1].pickupTime, students[studentCount-1].depart, 
           students[studentCount-1].departTime, students[studentCount-1].parentPhone);
    printf("================================================================================================================================================================\n");
    
    // Update file immediately
    updateFile();
}

void displayAllRecordsTable() {
    if(studentCount == 0) {
        printf("No student records found!\n");
        return;
    }
    
    printf("\n");
    printf("================================================================================================================================================================\n");
    printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    printf("================================================================================================================================================================\n");
    
    for(int i = 0; i < studentCount; i++) {
        // Find driver details for this student's bus
        char driverName[MAX_NAME_LENGTH] = "";
        
        for(int j = 0; j < 4; j++) {
            if(buses[j].busNumber == students[i].busNumber) {
                strcpy(driverName, buses[j].driverName);
                break;
            }
        }
        
        printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
               students[i].id,
               students[i].busNumber,
               driverName,
               students[i].name,
               students[i].area,
               students[i].fees,
               students[i].board,
               students[i].pickupTime,
               students[i].depart,
               students[i].departTime,
               students[i].parentPhone);
    }
    
    printf("================================================================================================================================================================\n");
    printf("Total Records: %d\n", studentCount);
}

void searchRecords() {
    int choice;
    char searchTerm[MAX_NAME_LENGTH];
    
    printf("\n=== SEARCH OPTIONS ===\n");
    printf("1. Search by Name\n");
    printf("2. Search by Area\n");
    printf("Enter choice (1 or 2): ");
    
    if(scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter 1 or 2.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if(choice == 1) {
        printf("Enter student name to search: ");
        if(fgets(searchTerm, MAX_NAME_LENGTH, stdin) == NULL) {
            printf("Error reading input!\n");
            return;
        }
        searchTerm[strcspn(searchTerm, "\n")] = 0;
        
        printf("\nSearch Results for '%s':\n", searchTerm);
        printf("================================================================================================================================================================\n");
        printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
        printf("================================================================================================================================================================\n");
        
        int found = 0;
        for(int i = 0; i < studentCount; i++) {
            if(strstr(students[i].name, searchTerm) != NULL) {
                // Find driver details
                char driverName[MAX_NAME_LENGTH] = "";
                
                for(int j = 0; j < 4; j++) {
                    if(buses[j].busNumber == students[i].busNumber) {
                        strcpy(driverName, buses[j].driverName);
                        break;
                    }
                }
                
                printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
                       students[i].id, students[i].busNumber, driverName,
                       students[i].name, students[i].area, students[i].fees, 
                       students[i].board, students[i].pickupTime, students[i].depart, students[i].departTime, students[i].parentPhone);
                found = 1;
            }
        }
        
        printf("================================================================================================================================================================\n");
        if(!found) {
            printf("No students found with name containing '%s'!\n", searchTerm);
        }
        
    } else if(choice == 2) {
        printf("Enter area to search: ");
        if(fgets(searchTerm, MAX_NAME_LENGTH, stdin) == NULL) {
            printf("Error reading input!\n");
            return;
        }
        searchTerm[strcspn(searchTerm, "\n")] = 0;
        
        printf("\nStudents in area '%s':\n", searchTerm);
        printf("================================================================================================================================================================\n");
        printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
        printf("================================================================================================================================================================\n");
        
        int found = 0;
        for(int i = 0; i < studentCount; i++) {
            if(strstr(students[i].area, searchTerm) != NULL) {
                // Find driver details
                char driverName[MAX_NAME_LENGTH] = "";
                
                for(int j = 0; j < 4; j++) {
                    if(buses[j].busNumber == students[i].busNumber) {
                        strcpy(driverName, buses[j].driverName);
                        break;
                    }
                }
                
                printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
                       students[i].id, students[i].busNumber, driverName,
                       students[i].name, students[i].area, students[i].fees, 
                       students[i].board, students[i].pickupTime, students[i].depart, students[i].departTime, students[i].parentPhone);
                found = 1;
            }
        }
        
        printf("================================================================================================================================================================\n");
        if(!found) {
            printf("No students found in area '%s'!\n", searchTerm);
        }
    } else {
        printf("Invalid choice! Please enter 1 or 2.\n");
    }
}

void editRecord() {
    int id;
    printf("Enter Student ID to edit: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    int foundIndex = -1;
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    if(foundIndex == -1) {
        printf("Student with ID %d not found!\n", id);
        return;
    }
    
    printf("\nCurrent Record:\n");
    printf("================================================================================================================================================================\n");
    printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    printf("================================================================================================================================================================\n");
    
    // Find driver details
    char driverName[MAX_NAME_LENGTH] = "";
    
    for(int j = 0; j < 4; j++) {
        if(buses[j].busNumber == students[foundIndex].busNumber) {
            strcpy(driverName, buses[j].driverName);
            break;
        }
    }
    
    printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
           students[foundIndex].id, students[foundIndex].busNumber, driverName,
           students[foundIndex].name, students[foundIndex].area, students[foundIndex].fees, 
           students[foundIndex].board, students[foundIndex].pickupTime, students[foundIndex].depart, students[foundIndex].departTime, students[foundIndex].parentPhone);
    printf("================================================================================================================================================================\n");
    
    printf("\nEnter field to edit:\n");
    printf("1. Name\n2. Area\n3. Fees\n4. Board Location\n5. Depart Location\n6. Pickup Time\n7. Depart Time\n8. Parent Phone\n9. Bus Number\n");
    printf("Choice: ");
    int field;
    if(scanf("%d", &field) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    switch(field) {
        case 1:
            printf("Enter new name: ");
            fgets(students[foundIndex].name, MAX_NAME_LENGTH, stdin);
            students[foundIndex].name[strcspn(students[foundIndex].name, "\n")] = 0;
            break;
        case 2:
            printf("Enter new area: ");
            fgets(students[foundIndex].area, MAX_AREA_LENGTH, stdin);
            students[foundIndex].area[strcspn(students[foundIndex].area, "\n")] = 0;
            break;
        case 3:
            printf("Enter new fees: ");
            scanf("%f", &students[foundIndex].fees);
            clearInputBuffer();
            break;
        case 4:
            printf("Enter new board location: ");
            fgets(students[foundIndex].board, MAX_NAME_LENGTH, stdin);
            students[foundIndex].board[strcspn(students[foundIndex].board, "\n")] = 0;
            break;
        case 5:
            printf("Enter new depart location: ");
            fgets(students[foundIndex].depart, MAX_NAME_LENGTH, stdin);
            students[foundIndex].depart[strcspn(students[foundIndex].depart, "\n")] = 0;
            break;
        case 6:
            printf("Enter new pickup time: ");
            fgets(students[foundIndex].pickupTime, 10, stdin);
            students[foundIndex].pickupTime[strcspn(students[foundIndex].pickupTime, "\n")] = 0;
            break;
        case 7:
            printf("Enter new depart time: ");
            fgets(students[foundIndex].departTime, 10, stdin);
            students[foundIndex].departTime[strcspn(students[foundIndex].departTime, "\n")] = 0;
            break;
        case 8:
            printf("Enter new parent phone: ");
            fgets(students[foundIndex].parentPhone, MAX_PHONE_LENGTH, stdin);
            students[foundIndex].parentPhone[strcspn(students[foundIndex].parentPhone, "\n")] = 0;
            break;
        case 9:
            printf("Enter new bus number: ");
            scanf("%d", &students[foundIndex].busNumber);
            clearInputBuffer();
            break;
        default:
            printf("Invalid field!\n");
            return;
    }
    
    printf("Record updated successfully!\n");
    
    // Display updated record
    printf("\n=== UPDATED STUDENT RECORD ===\n");
    printf("================================================================================================================================================================\n");
    printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    printf("================================================================================================================================================================\n");
    
    // Find updated driver details
    char updatedDriverName[MAX_NAME_LENGTH] = "";
    for(int j = 0; j < 4; j++) {
        if(buses[j].busNumber == students[foundIndex].busNumber) {
            strcpy(updatedDriverName, buses[j].driverName);
            break;
        }
    }
    
    printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
           students[foundIndex].id, students[foundIndex].busNumber, updatedDriverName,
           students[foundIndex].name, students[foundIndex].area, students[foundIndex].fees, 
           students[foundIndex].board, students[foundIndex].pickupTime, students[foundIndex].depart, 
           students[foundIndex].departTime, students[foundIndex].parentPhone);
    printf("================================================================================================================================================================\n");
    
    // Update file immediately
    updateFile();
}

void deleteRecord() {
    int id;
    printf("Enter Student ID to delete: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    int foundIndex = -1;
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    if(foundIndex == -1) {
        printf("Student with ID %d not found!\n", id);
        return;
    }
    
    printf("\nRecord to Delete:\n");
    printf("================================================================================================================================================================\n");
    printf("| ID  | BusNo | Driver Name       | StudentName        | Area           | Fees     | Board           | Pickup Time | Depart    | Depart Time | Parent Phone  |\n");
    printf("================================================================================================================================================================\n");
    
    // Find driver details
    char driverName[MAX_NAME_LENGTH] = "";
    
    for(int j = 0; j < 4; j++) {
        if(buses[j].busNumber == students[foundIndex].busNumber) {
            strcpy(driverName, buses[j].driverName);
            break;
        }
    }
    
    printf("| %-3d | %-5d | %-16s | %-18s | %-14s | %-8.2f | %-15s | %-11s | %-9s | %-11s | %-13s |\n",
           students[foundIndex].id, students[foundIndex].busNumber, driverName,
           students[foundIndex].name, students[foundIndex].area, students[foundIndex].fees, 
           students[foundIndex].board, students[foundIndex].pickupTime, students[foundIndex].depart, students[foundIndex].departTime, students[foundIndex].parentPhone);
    printf("================================================================================================================================================================\n");
    
    printf("\nConfirm deletion? (y/n): ");
    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();
    
    if(confirm == 'y' || confirm == 'Y') {
        // Store deleted record info before deletion
        int deletedId = students[foundIndex].id;
        char deletedName[MAX_NAME_LENGTH];
        strcpy(deletedName, students[foundIndex].name);
        
        for(int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
            students[i].id = i + 1; // Update IDs after deletion
        }
        studentCount--;
        
        printf("Record deleted successfully! (ID: %d, Name: %s)\n", deletedId, deletedName);
        
        // Update file immediately
        updateFile();
    } else {
        printf("Deletion cancelled.\n");
    }
}

void saveToFile() {
    updateFile(); // Reuse the updateFile function
    printf("Records saved to 'bus_records.txt' successfully!\n");
}

void displayBusDetails() {
    printf("\n=== BUS DETAILS ===\n");
    for(int i = 0; i < 4; i++) {
        printf("\nBus %d:\n", buses[i].busNumber);
        printf("Driver: %s\n", buses[i].driverName);
        printf("Driver Phone: %s\n", buses[i].driverPhone);
        
        int count = 0;
        for(int j = 0; j < studentCount; j++) {
            if(students[j].busNumber == buses[i].busNumber) {
                count++;
            }
        }
        printf("Students: %d\n", count);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}