#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[]) {
    for (int i = 1; i <= 10; i ++) {
        sleep(100);
        printf(1, "Teste %d\n", i);
    }
    
    exit();
}