// Tim Asisten Sister 19 - Test case generator milestone 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMA_IMAGE "system.img"

typedef unsigned char byte;

// Link dengan tc_lib
// insert_file & create_folder menerima relative pathing
extern void insert_file(byte buf[2880][512], char *fname, byte parent_idx);
extern void create_folder(byte buf[2880][512], char *fname, byte parent_idx);



void tc_A(byte buf[2880][512]) {
    create_folder(buf, "folder1", 0xFF);
    create_folder(buf, "folder2", 0);
    create_folder(buf, "folder3", 0);
    insert_file(buf, "file_src/tc_a/hehe", 2);
    insert_file(buf, "file_src/tc_a/haha", 2);
    insert_file(buf, "file_src/tc_a/hoho", 2);
    create_folder(buf, "folder4", 0);
    create_folder(buf, "folder5", 6);
    insert_file(buf, "file_src/tc_a/keos", 6);
    insert_file(buf, "file_src/tc_a/keoskeos", 6);

    insert_file(buf, "file_src/tc_a/file3", 0);
    insert_file(buf, "file_src/tc_a/file1", 0);
    insert_file(buf, "file_src/tc_a/file2", 0);
    insert_file(buf, "file_src/tc_a/file_luar", 0xFF);
}

void tc_B(byte buf[2880][512]) {
    insert_file(buf, "file_src/tc_b/file_idx_0", 0xFF);
    create_folder(buf, "folder1", 0xFF);
    for (int i = 1; i < 62; i++) {
        char str_buf[16];
        sprintf(str_buf, "folder%d", i + 1);
        create_folder(buf, str_buf, i);
    }
    insert_file(buf, "file_src/tc_b/file_idx_63", 0xFF);
}

void tc_C(byte buf[2880][512]) {
    create_folder(buf, "A", 0xFF);
    create_folder(buf, "test", 0);
    create_folder(buf, "A11", 1);
    create_folder(buf, "B", 0xFF);

    create_folder(buf, "A2", 0);
    create_folder(buf, "test", 4);
    create_folder(buf, "C", 0xFF);
    create_folder(buf, "C1", 6);
    create_folder(buf, "C11", 7);
    create_folder(buf, "test", 8);
}

void tc_D(byte buf[2880][512]) {
    insert_file(buf, "file_src/tc_d/512", 0xFF);
    insert_file(buf, "file_src/tc_d/1024", 0xFF);
    for (int i = 0; i < 14; i++) {
        char str_buf[32];
        sprintf(str_buf, "file_src/tc_d/8192_%d", i + 1);
        insert_file(buf, str_buf, 0xFF);
    }
}



int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage : tester <test case>\n");
        exit(1);
    }

    // Load entire file and save to buffer
    FILE *image = fopen(NAMA_IMAGE, "rb");

    if (image == NULL) {
        fprintf(stderr, "Error : File image <%s> not found\n", NAMA_IMAGE);
        exit(1);
    }

    byte imagebuffer[2880][512];
    for (int i = 0; i < 2880; i++)
        fread(imagebuffer[i], 512, 1, image);

    // Close file descriptor and overwrite
    fclose(image);
    image = fopen(NAMA_IMAGE, "wb");

    switch (argv[1][0]) {
        case 'A':
            tc_A(imagebuffer);
            break;
        case 'B':
            tc_B(imagebuffer);
            break;
        case 'C':
            tc_C(imagebuffer);
            break;
        case 'D':
            tc_D(imagebuffer);
            break;
    }

    // Overwrite old file
    for (int i = 0; i < 2880; i++)
        fwrite(imagebuffer[i], 512, 1, image);

    fclose(image);
    return 0;
}
