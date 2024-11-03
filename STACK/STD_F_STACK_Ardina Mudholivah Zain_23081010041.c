#include <stdio.h>
#include <stdlib.h>
#define MAX 15

typedef struct node {
    int data;
    struct node *next;
} node;

void pushStack(node **top, int data, int *stackCount, int maxSize);
int popStack(node **top, int *stackCount, int *success);
int stackTop(node *top);
int isEmptyStack(node *top);
int isFullStack(int stackCountValue, int maxSize);
void destroyStack(node **top, int *stackCount);
void printStack(node *top);

int main() {
    node *top = NULL;
    char pilih;
    int data;
    int maxSize = MAX;
    int stackCountValue = 0;
    int success;

    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("1. tambah data di paling atas (Push Stack)\n");
        printf("2. hapus data di paling atas (Pop Stack)\n");
        printf("3. tampilkan data paling atas (Stack Top)\n");
        printf("4. cek stack kosong atau terisi (Empty Stack)\n");
        printf("5. cek stack penuh atau belum (Full Stack)\n");
        printf("6. hitung jumlah data (Stack Count)\n");
        printf("7. kosongkan semua data (Destroy Stack)\n");
        printf("0. cetak isi stack!\n");
        printf("MASUKKAN PILIHAN (tekan x untuk keluar) : ");

        scanf(" %c", &pilih);

        switch (pilih) {
            case '1':
                printf("Masukkan data ke atas: ");
                scanf("%d", &data);
                pushStack(&top, data, &stackCountValue, maxSize);
                break;
            case '2':
                data = popStack(&top, &stackCountValue, &success);
                if (success) printf("Data yang dihapus: %d\n", data);
                else printf("Pop stack gagal!\n");
                break;
            case '3':
                data = stackTop(top);
                if (data != -1) printf("Data teratas: %d\n", data);
                break;
            case '4':
                printf(isEmptyStack(top) ? "Stack kosong\n" : "Stack tidak kosong\n");
                break;
            case '5':
                printf(isFullStack(stackCountValue, maxSize) ? "Stack penuh\n" : "Stack belum penuh\n");
                break;
            case '6':
                printf("Jumlah data dalam stack: %d\n", stackCountValue);
                break;
            case '7':
                destroyStack(&top, &stackCountValue);
                printf("Semua data dalam stack telah dikosongkan\n");
                break;
            case '0':
                printStack(top);
                break;
            case 'x':
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
        printf("Tekan enter untuk melanjutkan...");
        while (getchar() != '\n'); // membersihkan buffer
        getchar(); // menunggu input untuk melanjutkan
    } while (pilih != 'x');

    return 0;
}

// Fungsi untuk push data ke stack
void pushStack(node **top, int data, int *stackCountValue, int maxSize) {
    if (*stackCountValue >= maxSize) {
        printf("Stack penuh!\n");
        return;
    }
    node *newNode = (node*)malloc(sizeof(node));
    if (!newNode){
        printf("Gagal mengalokasikan memori!\n");
        return;
    }

    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
    (*stackCountValue)++;
    printf("%d telah ditambahkan ke stack.\n", data);
}

// Fungsi untuk pop data dari stack
int popStack(node **top, int *stackCountValue, int *success) {
    if (isEmptyStack(*top)) {
        printf("Stack kosong!\n");
        *success = 0;
        return -1;
    }
    node *temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    (*stackCountValue)--;
    *success = 1;
    return data;
}

// Melihat data teratas
int stackTop(node *top) {
    if (isEmptyStack(top)) {
        printf("Stack kosong!\n");
        return -1;
    }
    return top->data;
}

// Cek apakah stack kosong
int isEmptyStack(node *top) {
    return top == NULL;
}

// Cek apakah stack penuh
int isFullStack(int stackCountValue, int maxSize) {
    return stackCountValue >= maxSize;
}

// Hitung jumlah elemen dalam stack
int stackCount(node *top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->next;
    }
    return count;
}

// Kosongkan stack
void destroyStack(node **top, int *stackCountValue) {
    int success;
    while (!isEmptyStack(*top)) {
        popStack(top, stackCountValue, &success);
    }
    *stackCountValue = 0;
}

// Tampilkan seluruh isi stack
void printStack(node *top) {
    if (isEmptyStack(top)) {
        printf("Stack kosong\n");
    } else {
        printf("Isi stack:\n");
        while (top != NULL) {
            printf("%d\n", top->data);
            top = top->next;
        }
    }
}
