#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

void tambahDataAwal(node **head);
void tambahDataTengah(node **head);
void tambahDataAkhir(node **head);
void hapusDataAwal(node **head);
void hapusDataTengah(node **head);
void hapusDataAkhir(node **head);
void pencarianData(node *head);
int hitungNode(node *head);
int hasilJumlahData(node *head);
void tranverse(node *head, int reverse);

//========================================================

int main()
{
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir list\n");
        printf("4. hapus data di awal list\n");
        printf("5. hapus data di tengah list\n");
        printf("6. hapus data di akhir list\n");
        printf("7. cari data dalam list\n");
        printf("8. hitung informasi jumlah data\n");
        printf("9. jumlah total semua data\n");
        printf("0. cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan x untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1') {
            tambahDataAwal(&head);
        } else if (pilih == '2') {
            tambahDataTengah(&head);
        } else if (pilih == '3') {
            tambahDataAkhir(&head);
        } else if (pilih == '4') {
            hapusDataAwal(&head);
        } else if (pilih == '5') {
            hapusDataTengah(&head);
        } else if (pilih == '6') {
            hapusDataAkhir(&head);
        } else if (pilih == '7') {
            pencarianData(head);
            getch();
        } else if (pilih == '8') {
            printf("Jumlah node: %d\n", hitungNode(head));
            getch();
        } else if (pilih == '9') {
            printf("Total penjumlahan dari semua node: %d\n", hasilJumlahData(head));
            getch();
        } else if (pilih == '0') {
            tranverse(head, 0);
            getch();
        }
    } while (pilih != 'x');

    return 0;
}

//========================================================

void tambahDataAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;
        if (*head != NULL) {
            (*head)->prev = pNew;
        }
        *head = pNew;
    } else {
        printf("alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahDataTengah(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head, 0);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("\nalokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = pCur->next;
    pNew->prev = pCur;
    if (pCur->next != NULL) {
        pCur->next->prev = pNew;
    }
    pCur->next = pNew;

    printf("Data berhasil disisipkan setelah %d.\n", pos);
    getch();
}

//========================================================

void tambahDataAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("===== TAMBAH DATA DI AKHIR =====\n");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = NULL;

    if (*head == NULL) {
        pNew->prev = NULL;
        *head = pNew;
    } else {
        pCur = *head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        pCur->next = pNew;
        pNew->prev = pCur;
    }
    printf("Data berhasil ditambahkan di akhir.\n");
    getch();
}

//========================================================

void hapusDataAwal(node **head) {
    node *temp;

    if (*head == NULL) {
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    printf("Data %d berhasil dihapus dari awal.\n", temp->data);
    free(temp);
    getch();
}

//========================================================

void hapusDataTengah(node **head) {
    int bil;
    node *pCur;

    system("cls");
    printf("===== HAPUS DATA DI TENGAH =====\n");
    tranverse(*head, 0);
    if (*head == NULL) {
        getch();
        return;
    }
    printf("\nMasukkan data yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != bil) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data %d tidak ditemukan dalam linked list.\n", bil);
        getch();
        return;
    }

    if (pCur->prev != NULL) {
        pCur->prev->next = pCur->next;
    } else {
        *head = pCur->next;
    }

    if (pCur->next != NULL) {
        pCur->next->prev = pCur->prev;
    }

    printf("Data %d berhasil dihapus.\n", bil);
    free(pCur);
    getch();
}

//========================================================

void hapusDataAkhir(node **head) {
    node *pCur;

    if (*head == NULL) {
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    pCur = *head;
    while (pCur->next != NULL) {
        pCur = pCur->next;
    }

    if (pCur->prev != NULL) {
        pCur->prev->next = NULL;
    } else {
        *head = NULL;
    }

    printf("Data %d berhasil dihapus dari akhir.\n", pCur->data);
    free(pCur);
    getch();
}

//========================================================

void pencarianData(node *head) {
    int bil;
    node *pCur;
    int ditemukan = 0;
    int urutan = 1;

    system("cls");
    printf("===== CARI DATA =====\n");
    if (head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }
    printf("Masukkan data yang dicari: ");
    scanf("%d", &bil);

    pCur = head;
    while (pCur != NULL) {
        if (pCur->data == bil) {
            ditemukan = 1;
            break;
        }
        pCur = pCur->next;
        urutan++;
    }

    if (ditemukan) {
        printf("Data dengan nilai %d ditemukan pada node %d.\n", bil, urutan);
    } else {
        printf("Data %d tidak ditemukan dalam linked list.\n", bil);
    }
}

//========================================================

int hitungNode(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    return count;
}

//========================================================

int hasilJumlahData(node *head) {
    int sum = 0;
    node *pCur = head;

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }

    return sum;
}

//========================================================

void tranverse(node *head, int reverse) {
    node *pWalker = head;
    system("cls");

    if (head == NULL){
        printf("List kosong.\n");
        return;
    }

    if (reverse == 0) {
        printf("NULL <- ");
        while(pWalker != NULL){
            printf("%d", pWalker->data);
            if (pWalker->next != NULL) {
                printf(" <-> ");
            }
            pWalker = pWalker->next;
        }
        printf(" -> NULL\n");
    }

}

//========================================================

