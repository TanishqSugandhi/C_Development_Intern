// sorting_search.c
#include <stdio.h>
#include <stdlib.h>

void print_arr(int *a, int n) {
    for (int i=0;i<n;i++) printf("%d ", a[i]);
    printf("\n");
}

void bubble_sort(int *a, int n) {
    for (int i=0;i<n-1;i++)
        for (int j=0;j<n-1-i;j++)
            if (a[j] > a[j+1]) { int t=a[j]; a[j]=a[j+1]; a[j+1]=t; }
}

int partition(int *a, int l, int r) {
    int pivot = a[r];
    int i = l-1;
    for (int j=l;j<r;j++) if (a[j] <= pivot) { i++; int t=a[i]; a[i]=a[j]; a[j]=t; }
    int t=a[i+1]; a[i+1]=a[r]; a[r]=t;
    return i+1;
}
void quicksort(int *a, int l, int r) {
    if (l<r) {
        int p = partition(a,l,r);
        quicksort(a,l,p-1);
        quicksort(a,p+1,r);
    }
}

int linear_search(int *a, int n, int key) {
    for (int i=0;i<n;i++) if (a[i]==key) return i;
    return -1;
}

int binary_search(int *a, int n, int key) {
    int l=0, r=n-1;
    while (l<=r) {
        int m = l + (r-l)/2;
        if (a[m]==key) return m;
        else if (a[m] < key) l = m+1;
        else r = m-1;
    }
    return -1;
}

int main() {
    int n, choice, key;
    printf("Enter array size: "); if (scanf("%d",&n)!=1) return 0;
    int *a = malloc(sizeof(int)*n);
    for (int i=0;i<n;i++){ printf("a[%d]: ", i); scanf("%d", &a[i]); }
    printf("Array: "); print_arr(a,n);
    printf("\n1) Bubble sort\n2) Quicksort\n3) Linear search\n4) Binary search (requires sorted arr)\nChoice: ");
    if (scanf("%d",&choice)!=1) return 0;
    if (choice==1) { bubble_sort(a,n); printf("After bubble sort: "); print_arr(a,n); }
    else if (choice==2) { quicksort(a,0,n-1); printf("After quicksort: "); print_arr(a,n); }
    else if (choice==3) {
        printf("Key to search: "); scanf("%d",&key);
        int idx = linear_search(a,n,key);
        printf(idx>=0 ? "Found at index %d\n" : "Not found\n", idx);
    } else if (choice==4) {
        quicksort(a,0,n-1);
        printf("Sorted: "); print_arr(a,n);
        printf("Key to search: "); scanf("%d",&key);
        int idx = binary_search(a,n,key);
        printf(idx>=0 ? "Found at index %d\n" : "Not found\n", idx);
    } else printf("Invalid\n");
    free(a);
    return 0;
}
