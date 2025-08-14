// fs_sim.c
#include <stdio.h>
#include <stdlib.h>

void create_file() {
    char name[256];
    printf("Filename to create: "); scanf("%s", name);
    FILE *f = fopen(name, "wx"); // fail if exists (POSIX). If not supported, fallback handled below.
    if (!f) {
        // fallback to not overwriting
        f = fopen(name, "r");
        if (f) { fclose(f); printf("File exists already.\n"); return; }
        f = fopen(name, "w");
        if (!f) { perror("fopen"); return; }
    }
    fprintf(f, ""); fclose(f);
    printf("Created %s\n", name);
}

void write_file() {
    char name[256];
    printf("Filename to write: "); scanf("%s", name);
    printf("Enter text (single line, no spaces allowed) : ");
    // To keep simple, read rest of line
    getchar();
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin)) return;
    FILE *f = fopen(name, "a");
    if (!f) { perror("fopen"); return; }
    fputs(buf, f);
    fclose(f);
    printf("Appended to %s\n", name);
}

void read_file() {
    char name[256];
    printf("Filename to read: "); scanf("%s", name);
    FILE *f = fopen(name, "r");
    if (!f) { perror("fopen"); return; }
    int c;
    while ((c = fgetc(f)) != EOF) putchar(c);
    fclose(f);
    printf("\n--- EOF ---\n");
}

void delete_file() {
    char name[256];
    printf("Filename to delete: "); scanf("%s", name);
    if (remove(name) == 0) printf("Deleted %s\n", name);
    else perror("remove");
}

int main() {
    int ch;
    while (1) {
        printf("\nFile System Simulator\n1) Create 2) Write (append) 3) Read 4) Delete 5) Exit\nChoice: ");
        if (scanf("%d",&ch)!=1) break;
        switch(ch) {
            case 1: create_file(); break;
            case 2: write_file(); break;
            case 3: read_file(); break;
            case 4: delete_file(); break;
            case 5: exit(0);
            default: printf("Invalid\n");
        }
    }
    return 0;
}
