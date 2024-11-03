#include <stdio.h>

// membuat struct
struct Users {
    char *nama;
    int nomor_id;
    char *email;
};

int main () {

    // menggunakan struct
    struct Users user_1, user_2;

    // mengisi nilai ke struct
    user_1.nama = "Lee Jeno";
    user_1.nomor_id = "23";
    user_1.email = "jenojam@gmail.com";

    // mengisi nilai ke struct
    user_2.nama = "Na Jaemin";
    user_2.nomor_id = "13";
    user_2.email = "najaem@gmail.com";

    // mencetak isi struct
    printf("## User 1 ##\n");
    printf("nama: %s\n", user_1.nama);
    printf("nomor_id: %d\n", user_1.nomor_id);
    printf("email: %s\n", user_1.email);

    printf("## User 2 ##\n");
    printf("nama: %s\n", user_2.nama);
    printf("nomor_id: %d\n", user_2.nomor_id);
    printf("email: %s\n", user_2.email);

    return 0;
}
