
#include <stdio.h>
#include <string.h>

#define MAX 100

struct DownloadRequest {
    int id;
    char fileName[100];
    char url[200];
    int priority;
    int completed;
    int order;
};

struct DownloadRequest requests[MAX];
int count = 0;
int nextId = 1001;
int orderNumber = 0;

void addRequest() {
    if (count >= MAX) {
        printf("\nRequest list is full!\n");
        return;
    }

    struct DownloadRequest r;

    r.id = nextId++;
    r.completed = 0;
    r.order = orderNumber++;

    printf("\nEnter file name: ");
    scanf(" %99[^\n]", r.fileName);

    printf("Enter download URL: ");
    scanf(" %199[^\n]", r.url);

    printf("Enter priority (1 = Highest, 5 = Lowest): ");

    if (scanf("%d", &r.priority) != 1) {
        printf("Invalid priority input!\n");
        while (getchar() != '\n');
        return;
    }

    if (r.priority < 1 || r.priority > 5) {
        printf("Invalid priority. Setting priority to 3.\n");
        r.priority = 3;
    }

    requests[count++] = r;

    printf("\nRequest added successfully!\n");
    printf("Request ID: %d\n", r.id);
}

void displayRequests() {
    if (count == 0) {
        printf("\nNo download requests found.\n");
        return;
    }

    printf("\n========== ALL REQUESTS ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nRequest ID: %d\n", requests[i].id);
        printf("File Name: %s\n", requests[i].fileName);
        printf("URL: %s\n", requests[i].url);
        printf("Priority: %d\n", requests[i].priority);
        printf("Status: %s\n",
               requests[i].completed ? "Processed" : "Pending");
    }
}

void processRequest() {
    int selected = -1;

    for (int i = 0; i < count; i++) {
        if (!requests[i].completed) {
            if (selected == -1 ||
                requests[i].priority < requests[selected].priority ||
                (requests[i].priority == requests[selected].priority &&
                 requests[i].order < requests[selected].order)) {
                selected = i;
            }
        }
    }

    if (selected == -1) {
        printf("\nNo pending requests to process.\n");
        return;
    }

    printf("\n========== PROCESSING REQUEST ==========\n");
    printf("Request ID: %d\n", requests[selected].id);
    printf("File Name: %s\n", requests[selected].fileName);
    printf("URL: %s\n", requests[selected].url);

    requests[selected].completed = 1;

    printf("Status: Processed successfully (simulation)\n");
}

void searchRequest() {
    int id;

    printf("\nEnter Request ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input!\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < count; i++) {
        if (requests[i].id == id) {
            printf("\nRequest Found!\n");
            printf("Request ID: %d\n", requests[i].id);
            printf("File Name: %s\n", requests[i].fileName);
            printf("URL: %s\n", requests[i].url);
            printf("Priority: %d\n", requests[i].priority);
            printf("Status: %s\n",
                   requests[i].completed ? "Processed" : "Pending");
            return;
        }
    }

    printf("\nRequest ID not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf(" DOWNLOAD REQUEST SCHEDULER SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Download Request\n");
        printf("2. Display All Requests\n");
        printf("3. Process Next Request\n");
        printf("4. Search Request by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting program.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addRequest();
                break;
            case 2:
                displayRequests();
                break;
            case 3:
                processRequest();
                break;
            case 4:
                searchRequest();
                break;
            case 5:
                printf("\nThank you for using the system!\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
