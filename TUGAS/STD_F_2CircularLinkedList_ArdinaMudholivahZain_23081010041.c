#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahDataAwal(node **list);
void tambahDataTengah(node **list);
void tambahDataAkhir (node **list);
void hapusDataAwal(node **list);
void hapusDataTengah(node **list);
void hapusDataAkhir(node **list);
void pencarianData(node *list);
void hitungNode(node *list);
void hasilJumlahData(node *list);
void tranverse(node *list);

//========================================================

int main()
{
    node *list;
    char pilih;

    list = NULL;
    do{
        system("cls");
        printf("Masukkan pilihan\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Hapus data di awal list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir list\n");
        printf("7. Cari data dalam list\n");
        printf("8. Hitung informasi jumlah data\n");
        printf("9. Jumlah total semua data\n");
        printf("0. Cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan x untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        if (pilih == '1') {
            tambahDataAwal(&list);
        }
        else if (pilih == '2') {
            tambahDataTengah(&list);
        }
        else if (pilih == '3') {
            tambahDataAkhir(&list);
        }
        else if (pilih == '4') {
            hapusDataAwal(&list);
        }
        else if (pilih == '5') {
            hapusDataTengah(&list);
        }
        else if (pilih == '6') {
            hapusDataAkhir(&list);
        }
        else if (pilih == '7') {
            pencarianData(list);
        }
        else if (pilih == '8') {
            hitungNode(list);
        }
        else if (pilih == '9') {
            hasilJumlahData(list);
        }
        else if (pilih == '0'){
            tranverse(list);
            getch();
        }
    } while (pilih != 'x' && pilih != 'X');

    return 0;
}

//========================================================

// Fungsi untuk menambahkan data di awal linked list
void tambahDataAwal(node **list){
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL){
        pNew->data = bil;
        if (*list == NULL){
            *list = pNew;
            pNew->next = *list;
        }
        else{
            pCur = *list;
            while (pCur->next != *list){
                pCur = pCur->next;
            }
            pNew->next = *list;
            *list = pNew;
            pCur->next = *list;
        }
        printf("Data berhasil ditambahkan di awal.\n");
    }
    else{
        printf("Alokasi memori gagal.\n");
    }
    getch();
}

//========================================================
// Fungsi untuk menambahkan data di tengah linked list
void tambahDataTengah(node **list){
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*list);
    if (*list == NULL){
        printf("\nList kosong. Menambahkan data di awal.\n");
        tambahDataAwal(list);
        return;
    }
    printf("\nPosisi penyisipan setelah data bernilai: ");
    scanf("%d", &pos);
    printf("Bilangan: ");
    scanf("%d", &bil);

    pCur = *list;
    do{
        if (pCur->data == pos){
            break;
        }
        pCur = pCur->next;
    } while (pCur != *list);

    if (pCur->data != pos){
        printf("\nNode tidak ditemukan.\n");
        getch();
        return;
    }

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL){
        printf("\nAlokasi memori gagal.\n");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = pCur->next;
    pCur->next = pNew;
    printf("Data berhasil disisipkan setelah %d.\n", pos);
    getch();
}

//========================================================
// Fungsi untuk menambahkan data di akhir linked list
void tambahDataAkhir(node **list){
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL){
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }

    pNew->data = bil;

    if (*list == NULL){
        *list = pNew;
        pNew->next = *list;
    }
    else{
        pCur = *list;
        while (pCur->next != *list){
            pCur = pCur->next;
        }
        pCur->next = pNew;
        pNew->next = *list;
    }
    printf("Data berhasil ditambahkan di akhir.\n");
    getch();
}

//========================================================
// Fungsi untuk menghapus node di awal linked list
void hapusDataAwal(node **list){
    if (*list == NULL){
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    node *pCur = *list;
    if ((*list)->next == *list){

        free(pCur);
        *list = NULL;
    }
    else{
        node *pTail = *list;
        while (pTail->next != *list){
            pTail = pTail->next;
        }
        *list = (*list)->next;
        pTail->next = *list;
        free (pCur);
    }
    printf("Data %d berhasil dihapus dari awal.\n");
    getch();
}

//========================================================
// Fungsi untuk menghapus node di tengah linked list
void hapusDataTengah(node **list){
    int bil;
    node *pCur, *pPre;

    system("cls");
    tranverse(*list);
    if(*list == NULL){
        getch();
        return;
    }
    printf("\nMasukkan data yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *list;
    pPre = NULL;
    do{
        if (pCur->data == bil){
            break;
        }
        pPre = pCur;
        pCur = pCur->next;
    } while (pCur != *list);

    if (pCur->data != bil){
        printf("Data %d tidak ditemukan dalam linked list.\n", bil);
        getch();
        return;
    }

    if (pCur == *list){
        // Menghapus node pertama
        hapusDataAwal(list);
        return;
    }

    // Menghapus node selain node pertama
    pPre->next = pCur->next;
    printf("Data %d berhasil dihapus.\n", bil);
    free(pCur);
    getch();
}

//========================================================
// Fungsi untuk menghapus node di akhir linked list
void hapusDataAkhir(node **list){
    if (*list == NULL){
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    node *pCur = *list, *pPre = NULL;

    if (pCur->next == *list){
        printf("Data %d berhasil dihapus dari akhir.\n", pCur->data);
        free(pCur);
        *list = NULL;
        getch();
        return;
    }

    while (pCur->next != *list){
        pPre = pCur;
        pCur = pCur->next;
    }

    pPre->next = *list;
    printf("Data %d berhasil dihapus dari akhir.\n", pCur->data);
    free(pCur);
    getch();
}

//========================================================
// Fungsi untuk mencari data dalam list
void pencarianData(node *list){
    int bil;
    node *pCur;
    int urutan = 1;

    system("cls");
    if(list == NULL){
        printf("Linked list kosong.\n");
        return;
    }
    printf("Masukkan data yang dicari: ");
    scanf("%d", &bil);

    pCur = list;
    do{
        if (pCur->data == bil) {
            printf("Node dengan nilai %d ditemukan pada node %d.\n", bil, urutan);
            getch();
            return;
        }
        pCur = pCur->next;
        urutan++;
    } while (pCur != list);

    printf("Data %d tidak ditemukan dalam linked list.\n", bil);
    getch();
}

//========================================================
// Fungsi untuk menghitung informasi jumlah data dalam linked list
void hitungNode(node *list){
    int count = 0;
    node *pCur = list;

    if (list == NULL) {
        printf("List kosong, tidak ada data dalam list.\n");
        getch();
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != list);

    printf("Total data dalam list adalah: %d\n", count);
    getch();
}

//========================================================
// Fungsi untuk menjumlahkan semua data dalam linked list
void hasilJumlahData (node *list){
    int total = 0;
    node *pCur = list;

    if (list == NULL) {
        system("cls");
        printf("List kosong, tidak ada data dalam list.\n");
        getch();
        return;
    }

    do {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != list);

    printf("\nJumlah nilai data dalam list adalah: %d\n", total);
    getch();
}

//========================================================
// Fungsi untuk menampilkan isi linked list
void tranverse(node *list){
    node *pWalker;

    system("cls");

    if (list == NULL){
        printf("List kosong.\n");
        return;
    }

    pWalker = list;
    printf("Isi Linked List:\n");

    printf("%d -> ", pWalker->data);

    pWalker = pWalker->next;
    while (pWalker != list) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }

    printf("%d\n", list->data);
}

