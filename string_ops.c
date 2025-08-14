// string_ops.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse_str(char *s) {
    int i=0, j=strlen(s)-1;
    while(i<j){ char t=s[i]; s[i]=s[j]; s[j]=t; i++; j--; }
}

int count_vowels(const char *s) {
    int cnt=0;
    for (; *s; s++) {
        char c = tolower((unsigned char)*s);
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') cnt++;
    }
    return cnt;
}

int is_palindrome(const char *s) {
    int i=0, j=strlen(s)-1;
    while(i<j){
        while(i<j && !isalnum((unsigned char)s[i])) i++;
        while(i<j && !isalnum((unsigned char)s[j])) j--;
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j])) return 0;
        i++; j--;
    }
    return 1;
}

int main() {
    char buf[1024];
    printf("Enter a string (max 1023 chars):\n");
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    // remove newline
    size_t len = strlen(buf);
    if (len && buf[len-1]=='\n') buf[len-1]=0;

    char tmp[1024];
    strcpy(tmp, buf);
    reverse_str(tmp);
    printf("Reversed: %s\n", tmp);
    printf("Vowel count: %d\n", count_vowels(buf));
    printf("Palindrome (ignoring non-alnum & case): %s\n", is_palindrome(buf) ? "YES" : "NO");
    return 0;
}
