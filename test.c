#include <stdio.h>

int main(){
    char x[] = "asdasdasdasdasdasdasdasd";
    int i = 0;
    while (x[i] != '\0'){
        i++;
    }
    printf("%d\n", i);
    return 0;
}