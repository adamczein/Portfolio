#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "../lib_dir/LectureByteCode.h"
#include "../lib_dir/memoire_24.h"
#include "../lib_dir/AffichageMemoire.h"

//main qui effectue la lecture du UART et qui �crit le contennu dans la m�moire externe
int main(){
    ByteCode code;
    code.LectureByteCode();
}