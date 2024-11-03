#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANGGOTA 20

struct Mahasiswa {
    char nama[50];
    char jenis_kelamin; // 'L' laki-laki, 'P' perempuan
    struct Mahasiswa* next;
};

// Fungsi untuk membuat node mahasiswa baru
struct Mahasiswa* buatMahasiswa(char nama[], char jenis_kelamin) {
    struct Mahasiswa* nodeBaru = (struct Mahasiswa*) malloc(sizeof(struct Mahasiswa));
    strcpy(nodeBaru->nama, nama);
    nodeBaru->jenis_kelamin = jenis_kelamin;
    nodeBaru->next = NULL;
    return nodeBaru;
}

// Fungsi untuk menambahkan mahasiswa ke lingkaran
void tambahKeLingkaran(struct Mahasiswa** head_ref, char nama[], char jenis_kelamin, int* count) {
    if (*count >= MAX_ANGGOTA) {
        printf("Lingkaran sudah penuh!\n");
        return;
    }

    struct Mahasiswa* nodeBaru = buatMahasiswa(nama, jenis_kelamin);
    struct Mahasiswa* temp = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = nodeBaru;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }

    (*count)++;
    printf("Mahasiswa %s telah ditambahkan ke lingkaran %c.\n", nama, jenis_kelamin);
}

// Fungsi untuk menghapus mahasiswa dari lingkaran
void hapusDariLingkaran(struct Mahasiswa** head_ref, char nama[], int* count) {
    struct Mahasiswa* temp = *head_ref;
    struct Mahasiswa* prev = NULL;

    // Jika head mengandung nama yang dihapus
    if (temp != NULL && strcmp(temp->nama, nama) == 0) {
        *head_ref = temp->next;
        free(temp);
        (*count)--;
        printf("Mahasiswa %s telah dihapus dari lingkaran.\n", nama);
        return;
    }

    // Mencari node yang mengandung nama
    while (temp != NULL && strcmp(temp->nama, nama) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Jika nama tidak ditemukan
    if (temp == NULL) {
        printf("Mahasiswa %s tidak ditemukan dalam lingkaran.\n", nama);
        return;
    }

    prev->next = temp->next;
    free(temp);
    (*count)--;
}

// Fungsi untuk menampilkan lingkaran
void tampilkanLingkaran(struct Mahasiswa* node) {
    if (node == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    printf("Daftar Mahasiswa:\n");
    while (node != NULL) {
        printf("%s (%c) -> ", node->nama, node->jenis_kelamin);
        node = node->next;
    }
    printf("NULL\n");
}

// Fungsi utama
int main() {
    struct Mahasiswa* lingkaranLakiLaki = NULL;
    struct Mahasiswa* lingkaranPerempuan = NULL;
    int countLakiLaki = 0;
    int countPerempuan = 0;

    int pilihan;
    char nama[50], jenis_kelamin;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Mahasiswa ke Lingkaran\n");
        printf("2. Hapus Mahasiswa dari Lingkaran\n");
        printf("3. Tampilkan Lingkaran\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan Nama Mahasiswa: ");
                scanf("%s", nama);
                printf("Masukkan Jenis Kelamin, Pilih (L/P): ");
                scanf(" %c", &jenis_kelamin);

                jenis_kelamin = toupper(jenis_kelamin);
                if (jenis_kelamin != 'L' && jenis_kelamin != 'P') {
                    printf("Jenis kelamin tidak valid! Harap masukkan 'L' atau 'P'.\n");
                    break;
                }

                // Cindy hanya ingin bergandengan dengan sesama mahasiswi
                if (strcmp(nama, "Cindy") == 0 && jenis_kelamin == 'L') {
                    printf("Cindy hanya mau bergandengan dengan sesama mahasiswi.\n");
                    break;
                }

                // Menambah mahasiswa ke lingkaran berdasarkan jenis kelamin
                if (jenis_kelamin == 'L') {
                    // Irsya dan Arsyad tidak boleh dipisahkan
                    if (strcmp(nama, "Irsyad") == 0 || strcmp(nama, "Arsyad") == 0) {
                        tambahKeLingkaran(&lingkaranLakiLaki, "Irsyad", 'L', &countLakiLaki);
                        tambahKeLingkaran(&lingkaranLakiLaki, "Arsyad", 'L', &countLakiLaki);
                    } else {
                        tambahKeLingkaran(&lingkaranLakiLaki, nama, 'L', &countLakiLaki);
                    }
                } else if (jenis_kelamin == 'P') {
                    tambahKeLingkaran(&lingkaranPerempuan, nama, 'P', &countPerempuan);
                } else {
                    printf("Jenis kelamin tidak valid!\n");
                }
                break;

            case 2:
                printf("Masukkan Nama Mahasiswa yang Ingin Dihapus: ");
                scanf("%s", nama);

                // Mencoba menghapus dari lingkaran laki-laki
                hapusDariLingkaran(&lingkaranLakiLaki, nama, &countLakiLaki);
                // Mencoba menghapus dari lingkaran perempuan
                hapusDariLingkaran(&lingkaranPerempuan, nama, &countPerempuan);
                break;

            case 3:
                printf("\n=== Lingkaran Laki-Laki ===\n");
                tampilkanLingkaran(lingkaranLakiLaki);

                printf("\n=== Lingkaran Perempuan ===\n");
                tampilkanLingkaran(lingkaranPerempuan);
                break;

            case 4:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid! Pilih antara 1-4!\n");
        }

    } while (pilihan != 4);

    return 0;
}
