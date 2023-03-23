extern "C" void print_tb();
extern "C" void foo();
extern "C" void bar();
void foo() {
    print_tb();
}
void bar() {
    foo();
}
int main() {
    bar();
}
