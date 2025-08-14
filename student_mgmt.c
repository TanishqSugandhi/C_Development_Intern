// student_mgmt.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[64];
    float marks[3];
} Student;

const char *DB = "students.dat";

void add_student() {
    Student s;
    printf("Enter ID: "); if (scanf("%d", &s.id)!=1) return;
    printf("Enter name: "); getchar(); fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name,"\n")] = 0;
    for (int i=0;i<3;i++){ printf("Mark %d: ", i+1); scanf("%f",&s.marks[i]); }
    FILE *f = fopen(DB,"ab");
    if (!f) { perror("fopen"); return; }
    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("Saved.\n");
}

void list_students() {
    FILE *f = fopen(DB,"rb");
    if (!f) { printf("No records.\n"); return; }
    Student s;
    printf("Students:\n");
    while (fread(&s,sizeof(s),1,f)==1) {
        float avg = (s.marks[0]+s.marks[1]+s.marks[2])/3.0f;
        printf("ID:%d Name:%s Marks:%.1f,%.1f,%.1f Avg:%.2f\n", s.id, s.name, s.marks[0], s.marks[1], s.marks[2], avg);
    }
    fclose(f);
}

void delete_student() {
    int id; printf("Enter ID to delete: "); if (scanf("%d",&id)!=1) return;
    FILE *f = fopen(DB,"rb"); if (!f){ printf("No records.\n"); return; }
    FILE *t = fopen("tmp.dat","wb"); if (!t){ perror("tmp"); fclose(f); return; }
    Student s; int found=0;
    while (fread(&s,sizeof(s),1,f)==1) {
        if (s.id==id) { found=1; continue; }
        fwrite(&s,sizeof(s),1,t);
    }
    fclose(f); fclose(t);
    remove(DB); rename("tmp.dat", DB);
    printf(found ? "Deleted.\n" : "ID not found.\n");
}

void update_student() {
    int id; printf("Enter ID to update: "); if (scanf("%d",&id)!=1) return;
    FILE *f = fopen(DB,"r+b"); if (!f){ printf("No records.\n"); return; }
    Student s;
    int found=0;
    while (fread(&s,sizeof(s),1,f)==1) {
        if (s.id==id) {
            found=1;
            printf("Current name: %s\n", s.name);
            printf("Enter new name: "); getchar(); fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name,"\n")] = 0;
            for (int i=0;i<3;i++){ printf("New mark %d: ", i+1); scanf("%f",&s.marks[i]); }
            fseek(f, -((long)sizeof(s)), SEEK_CUR);
            fwrite(&s,sizeof(s),1,f);
            printf("Updated.\n");
            break;
        }
    }
    if (!found) printf("ID not found.\n");
    fclose(f);
}

int main() {
    int choice;
    while (1) {
        printf("\nStudent Management\n1) Add 2) List 3) Delete 4) Update 5) Exit\nChoice: ");
        if (scanf("%d",&choice)!=1) break;
        switch(choice){
            case 1: add_student(); break;
            case 2: list_students(); break;
            case 3: delete_student(); break;
            case 4: update_student(); break;
            case 5: exit(0);
            default: printf("Invalid\n");
        }
    }
    return 0;
}
