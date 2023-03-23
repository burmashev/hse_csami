#include <stdio.h>
#include <math.h>

void myexp(double, double *);

int main() {
    double x;
    scanf("%lf", &x);

    double res = 0;
    myexp(x, &res);
    printf("%lf\n", res);
    return 0;
}