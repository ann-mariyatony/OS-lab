#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, head, req[100];

void sort(int arr[], int n) {
    int i, j, temp;
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// ✅ Check if selected head exists in request list
int isValidHead(int value) {
    for(int i = 0; i < n; i++) {
        if(req[i] == value)
            return 1;
    }
    return 0;
}

// ✅ Remove head from request list (prevents duplication)
void removeHeadFromRequests() {
    int i, j;
    for(i = 0; i < n; i++) {
        if(req[i] == head) {
            for(j = i; j < n - 1; j++) {
                req[j] = req[j + 1];
            }
            n--;  // reduce size
            break;
        }
    }
}

void SSTF() {
    int visited[100] = {0};
    int total = 0, i, j, pos, min, dist;

    pos = head;
    printf("\nSeek Sequence: %d", pos);

    for(i = 0; i < n; i++) {
        min = 9999;
        int index = -1;

        for(j = 0; j < n; j++) {
            if(!visited[j]) {
                dist = abs(pos - req[j]);
                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        if(index == -1) break;

        visited[index] = 1;
        total += min;
        pos = req[index];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

void LOOK() {
    int total = 0, i;
    int left[100], right[100];
    int l = 0, r = 0;
    int pos = head;

    for(i = 0; i < n; i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nSeek Sequence: %d", pos);

    // Move right first
    for(i = 0; i < r; i++) {
        total += abs(pos - right[i]);
        pos = right[i];
        printf(" -> %d", pos);
    }

    // Then left
    for(i = l - 1; i >= 0; i--) {
        total += abs(pos - left[i]);
        pos = left[i];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

void CSCAN() {
    int total = 0, i;
    int left[100], right[100];
    int l = 0, r = 0;
    int disk_size = 5000;
    int pos = head;

    for(i = 0; i < n; i++) {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nSeek Sequence: %d", pos);

    // Move right
    for(i = 0; i < r; i++) {
        total += abs(pos - right[i]);
        pos = right[i];
        printf(" -> %d", pos);
    }

    // Go to end
    total += abs(pos - (disk_size - 1));
    pos = disk_size - 1;
    printf(" -> %d", pos);

    // Jump to start
    total += abs(pos - 0);
    pos = 0;
    printf(" -> %d", pos);

    // Continue left side
    for(i = 0; i < l; i++) {
        total += abs(pos - left[i]);
        pos = left[i];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

int main() {
    int choice, i;

    srand(time(0));

    printf("Enter number of requests: ");
    scanf("%d", &n);

    // Generate random requests
    printf("Generated request sequence:\n");
    for(i = 0; i < n; i++) {
        req[i] = rand() % 5000;
        printf("%d ", req[i]);
    }
    printf("\n");

    // Select head from generated list
    do {
        printf("Select initial head position from above sequence: ");
        scanf("%d", &head);

        if(!isValidHead(head)) {
            printf("Invalid choice! Try again.\n");
        }

    } while(!isValidHead(head));

    // Remove head to avoid duplication
    removeHeadFromRequests();

    
        printf("\n--- Disk Scheduling ---\n");
        printf("1. SSTF\n2. LOOK\n3. C-SCAN\n4. Exit\n");
         while(1) {
        printf("\n Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: SSTF(); break;
            case 2: LOOK(); break;
            case 3: CSCAN(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
