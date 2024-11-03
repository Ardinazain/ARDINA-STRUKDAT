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
void tambahDataAwal(node **head);
void tambahDataTengah(node **head);
void tambahDataAkhir (node **head);
void hapusDataAwal(node **head);
void hapusDataTengah(node **head);
void hapusDataAkhir(node **head);
void pencarianData(node *head);
int hitungNode(node *head);
int hasilJumlahData(node *head);
void tranverse(node *head);
void insertNode(node **head, node *pPre, node *pNew);

//========================================================

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
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
     printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);
     if (pilih == '1') {
        tambahDataAwal(&head);
     }
     else if (pilih == '2') {
        tambahDataTengah(&head);
     }
     else if (pilih == '3') {
        tambahDataAkhir(&head);
     }
     else if (pilih == '4') {
        hapusDataAwal(&head);
     }
     else if (pilih == '5') {
        hapusDataTengah(&head);
     }
     else if (pilih == '6') {
        hapusDataAkhir(&head);
     }
     else if (pilih == '7') {
        pencarianData(&head);
        getch();
     }
     else if (pilih == '8') {
        printf("Jumlah node: %d\n", hitungNode(head));
        getch();
     }
     else if (pilih == '9') {
        printf("Total penjumlahan dari semua node: %d\n", hasilJumlahData(head));
        getch();
     }
     else if (pilih == '0'){
     		tranverse(head);
         getch();
     }
  } while (pilih != 'q');

  return 0;
}

//========================================================

/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================
// Fungsi untuk menambahkan data di awal linked list

void tambahDataAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;
      //add before first logical node or to an empty list
	  pNew -> next = *head;
      *head = pNew;
  }
  else{
      printf("alokasi memori gagal");
      getch();
  }
}

//========================================================
// Fungsi untuk menambahkan data di tengah linked list

void tambahDataTengah(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
     printf("Data berhasil disisipkan setelah %d.\n", pos);
     getch();
  }
}

//========================================================
// Fungsi untuk menambahkan data di akhir linked list

void tambahDataAkhir(node **head){
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("===== TAMBAH DATA DI AKHIR =====\n");
    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL){
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->next = NULL;

    if (*head == NULL){
        *head = pNew;
    }
    else{
        pCur = *head;
        while (pCur->next != NULL){
            pCur = pCur->next;
        }
        pCur->next = pNew;
    }
    printf("Data berhasil ditambahkan di akhir.\n");
    getch();
}

//========================================================
// Fungsi untuk menghapus node di awal linked list

void hapusDataAwal(node **head){
    node *temp;

    if (*head == NULL){
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    temp = *head;
    *head = (*head)->next;
    printf("Data %d berhasil dihapus dari awal.\n", temp->data);
    free(temp);
    getch();
}

//========================================================
// Fungsi untuk menghapus node di tengah linked list

void hapusDataTengah(node **head){
    int bil;
    node *pCur, *pPrev;

    system("cls");
    printf("===== HAPUS DATA DI TENGAH =====\n");
    tranverse(*head);
    if(*head == NULL){
        getch();
        return;
    }
    printf("\nMasukkan data yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *head;
    pPrev = NULL;

    while (pCur != NULL && pCur->data != bil){
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL){
        printf("Data %d tidak ditemukan dalam linked list.\n", bil);
        getch();
        return;
    }

    if (pPrev == NULL){
        // Menghapus node pertama
        *head = pCur->next;
    }
    else{
        pPrev->next = pCur->next;
    }

    printf("Data %d berhasil dihapus.\n", bil);
    free(pCur);
    getch();
}

//========================================================
// Fungsi untuk menghapus node di akhir linked list

void hapusDataAkhir(node **head){
    node *pCur, *pPrev;

    if (*head == NULL){
        printf("Linked list kosong. Tidak ada yang dihapus.\n");
        getch();
        return;
    }

    if ((*head)->next == NULL){
        printf("Data %d berhasil dihapus dari akhir.\n", (*head)->data);
        free(*head);
        *head = NULL;
        getch();
        return;
    }

    pCur = *head;
    pPrev = NULL;
    while (pCur->next != NULL){
        pPrev = pCur;
        pCur = pCur->next;
    }

    pPrev->next = NULL;
    printf("Data %d berhasil dihapus dari akhir.\n", pCur->data);
    free(pCur);
    getch();
}

//========================================================
// Fungsi untuk mencari data dalam list

void pencarianData(node *head){
    int bil;
    node *pCur;
    int ditemukan = 0;

    system("cls");
    printf("===== CARI DATA =====\n");
    if(head == NULL){
        printf("Linked list kosong.\n");
        return;
    }
    printf("Masukkan data yang dicari: ");
    scanf("%d", &bil);

    pCur = head;
    while (pCur != NULL){
        if (pCur->data == bil){
            ditemukan = 1;
            break;
        }
        pCur = pCur->next;
    }

    if (ditemukan){
        printf("Data %d ditemukan dalam linked list.\n", bil);
    }
    else{
        printf("Data %d tidak ditemukan dalam linked list.\n", bil);
    }
}

//========================================================
// Fungsi untuk menghitung informasi jumlah data dalam linked list

int hitungNode (node *head){
    int count = 0;
    node *pCur = head;

    while (pCur != NULL){
        count++;
        pCur = pCur->next;
    }

    return count;
}

//========================================================
// Fungsi untuk menjumlahkan semua data dalam linked list

int hasilJumlahData (node *head){
    int sum = 0;
    node *pCur = head;

    while (pCur != NULL){
        sum += pCur->data;
        pCur = pCur->next;
    }

    return sum;
}

//========================================================
// Fungsi untuk menampilkan isi linked list

void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
}

//========================================================
// Fungsi untuk menyisipkan node

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
       //add before first logical node or to an empty list
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       //add in the middle or at the end
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

//========================================================

