// calculator.c

#include <stdio.h>
int main() {
    double a, b;
    int choice;
    printf("Basic Calculator\n");
    printf("Enter first number: "); if (scanf("%lf", &a)!=1) return 0;
    printf("Enter second number: "); if (scanf("%lf", &b)!=1) return 0;
    printf("Choose operation:\n1) +  2) -  3) *  4) /\nChoice: "); scanf("%d", &choice);
    switch(choice) {
        case 1: printf("Result: %.6g\n", a + b); break;
        case 2: printf("Result: %.6g\n", a - b); break;
        case 3: printf("Result: %.6g\n", a * b); break;
        case 4:
            if (b == 0) printf("Error: Division by zero!\n");
            else printf("Result: %.6g\n", a / b);
            break;
        default: printf("Invalid choice\n");
    }
    return 0;
}
