#include <cstdio>

int mystrcmp(const char *str1, const char *str2) {
    const unsigned char *ustr1 = (const unsigned char *) str1;
    const unsigned char *ustr2 = (const unsigned char *) str2;
    int result;
    while (*ustr1 != 0 && *ustr2 != 0 && (result = *ustr1 - *ustr2) == 0) {
        *ustr1++;
        *ustr2++;
    }
    result = *ustr1 - *ustr2;
    return result;
}


int main() {
    char *str1 = "aba";
    char *str2 = "abaaa";
    int result = mystrcmp(str1, str2); // str1 < str2
    printf("%d\n", result);

    char *s1 = "abaa";
    char *s2 = "abaa";
    result = mystrcmp(s1, s2); // str1 == str2
    printf("%d\n", result);

    char *t1 = "abaaa";
    char *t2 = "aba";
    result = mystrcmp(t1, t2); // str1 > str2
    printf("%d\n", result);

    char *d1 = "abad";
    char *d2 = "abaa";
    result = mystrcmp(d1, d2); // str1 > str2
    printf("%d\n", result);

    char *f1 = "abaa";
    char *f2 = "abad";
    result = mystrcmp(f1, f2); // str1 < str2
    printf("%d\n", result);
    
    char *g1 = "abd";
    char *g2 = "abaaaa";
    result = mystrcmp(g1, g2); // str1 > str2
    printf("%d\n", result);

    char *l1 = "abad";
    char *l2 = "abd";
    result = mystrcmp(l1, l2); // str1 < str2
    printf("%d\n", result);
    
    
    result = mystrcmp("abc", "abc");
    printf("%d\n", result);

    result = mystrcmp("123", "123");
    printf("%d\n", result);

    result = mystrcmp("123", "124");
    printf("%d\n", result);

    result = mystrcmp("0999999", "123");
    printf("%d\n", result);

    result = mystrcmp("123", "3");
    printf("%d\n", result);

    result = mystrcmp("3", "123");
    printf("%d\n", result);

    result = mystrcmp("12", "123");
    printf("%d\n", result);

    result = mystrcmp("123", "1234");
    printf("%d\n", result);
  return 0;
}