#include <avr/io.h>
#include "DEL.h"

int main(){
    DEL(0x01, 'a', 4);

    return 0;
}

