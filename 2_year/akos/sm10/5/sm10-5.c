#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) {
    void * handle;
    void * func;
    double (*d_func)(double);
    double number;
    handle = dlopen("libm.so.6", RTLD_LAZY);
    func = dlsym(handle, argv[1]);
    if (!handle || !func) {
        return 1;
    } 
    d_func = (double (*)(double)) func;
    while (scanf("%lf", &number) == 1) {
        printf("%.10g\n", d_func(number));
    }
    dlclose(handle);
    return 0;
}