#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// structure for donor (Linked List Node)
struct Donor {
    int id;
    char name[50];
    char bg[5]; 
    int month;
    int year;
    struct Donor *next; 
};

struct Donor *head = NULL;
int total = 0; 

// simple queue using array
char queue[50][5];
int front = 0;
int back = 0;

// current date fixed for now
int curr_month = 8;
int curr_year = 2026;

// check if 4 months passed
int check_can_donate(int m, int y) {
    if (m == 0 && y == 0) {
        return 1; 
    }
    
    int total_months = (curr_year - y) * 12 + (curr_month - m);
    
    if (total_months >= 4) {
        return 1; 
    } else {
        return 0; 
    }
}

// add a new donor to the linked list
void add_donor() {
    printf("\n---------- ADD NEW DONOR ----------\n");
    struct Donor *new_donor = (struct Donor *)malloc(sizeof(struct Donor));
    
    total++;
    new_donor->id = total; 
    
    printf(" Enter name: ");
    scanf("%s", new_donor->name);
    
    printf(" Enter blood group (e.g. A+): ");
    scanf("%s", new_donor->bg);
    
    int choice;
    printf(" Did they donate before? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf(" Enter month (1-12): ");
        scanf("%d", &new_donor->month);
        printf(" Enter year: ");
        scanf("%d", &new_donor->year);
    } else {
        new_donor->month = 0;
        new_donor->year = 0;
    }
    
    new_donor->next = NULL; 

    if (head == NULL) {
        head = new_donor; 
    } else {
        struct Donor *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_donor; 
    }
    
    printf("\n -> SUCCESS: Donor added! ID is %d\n", new_donor->id);
    
    // check queue
    int q_size = back - front;
    int used = 0; 
    
    for (int i = 0; i < q_size; i++) {
        char temp_bg[5];
        strcpy(temp_bg, queue[front]); 
        front++; 
        
        if (used == 0 && strcmp(new_donor->bg, temp_bg) == 0 && check_can_donate(new_donor->month, new_donor->year) == 1) {
            printf(" -> GOOD NEWS: New donor gave blood to someone waiting for %s!\n", temp_bg);
            new_donor->month = curr_month;
            new_donor->year = curr_year;
            used = 1;
        } else {
            strcpy(queue[back], temp_bg);
            back++;
        }
    }
    printf("-----------------------------------\n");
}

// customer asks for blood
void get_blood() {
    printf("\n---------- REQUEST BLOOD ----------\n");
    char need_bg[5];
    printf(" What blood group do you need? ");
    scanf("%s", need_bg);
    
    struct Donor *temp = head;
    int found = 0;
    
    while (temp != NULL) {
        if (strcmp(temp->bg, need_bg) == 0) {
            if (check_can_donate(temp->month, temp->year) == 1) {
                printf("\n -> SUCCESS: We got blood from %s (ID: %d)\n", temp->name, temp->id);
                temp->month = curr_month;
                temp->year = curr_year;
                found = 1;
                break; 
            }
        }
        temp = temp->next; 
    }
    
    if (found == 0) {
        printf("\n -> NOTICE: No blood available right now. Putting you in the queue...\n");
        if (back < 50) {
            strcpy(queue[back], need_bg); 
            back++;
        } else {
            printf(" -> ERROR: Queue is full!\n");
        }
    }
    printf("-----------------------------------\n");
}

void print_queue() {
    printf("\n========== PEOPLE WAITING ==========\n");
    if (front == back) {
        printf(" Queue is currently empty.\n");
    } else {
        for (int i = front; i < back; i++) {
            printf(" [%d] Waiting for %s blood\n", (i - front) + 1, queue[i]);
        }
    }
    printf("====================================\n");
}

void print_donors() {
    printf("\n=========== ALL DONORS ===========\n");
    struct Donor *temp = head;
    
    if (temp == NULL) {
        printf(" No donors in the database yet.\n");
    }
    
    while (temp != NULL) {
        printf(" ID: %02d | Name: %-10s | BG: %-3s | Last Donated: %02d/%d\n", 
               temp->id, temp->name, temp->bg, temp->month, temp->year);
        temp = temp->next; 
    }
    printf("==================================\n");
}

int main() {
    int choice;
    
    while (1) {
        printf("\n=================================\n");
        printf("     BLOOD MANAGEMENT SYSTEM     \n");
        printf("=================================\n");
        printf("  [1] Add New Donor              \n");
        printf("  [2] Request Blood              \n");
        printf("  [3] View Waiting Queue         \n");
        printf("  [4] View All Donors            \n");
        printf("  [5] Exit Program               \n");
        printf("=================================\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            add_donor();
        } else if (choice == 2) {
            get_blood();
        } else if (choice == 3) {
            print_queue();
        } else if (choice == 4) {
            print_donors();
        } else if (choice == 5) {
            printf("\n Exiting System... Goodbye!\n\n");
            break;
        } else {
            printf("\n -> ERROR: Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}