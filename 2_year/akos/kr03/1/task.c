#include <stdio.h>
#include <math.h>

void discrim(float, float, float, float *);

int main() {
    float a, b, c;
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    float res = 0;
    discrim(a, b, c, &res);
    printf("%f\n", res);
    return 0;
}