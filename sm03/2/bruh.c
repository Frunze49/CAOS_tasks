void print_tb();    
void bar();
void foo();

void foo() {
    bar();
 }
void bar() {
    print_tb();
}
int main() {
    print_tb();
    bar();
}
