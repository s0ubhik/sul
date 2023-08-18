#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "md5-c/md5.h"

int print_help(){
    printf("Usage: sulock [PASSWORD] [COMMAND]\n");
    return 0;
}

int check_pswd(uint8_t pswd[16]){
    
    uint8_t password[16] = {0x81, 0xdc, 0x9b, 0xdb, 0x52, 0xd0, 0x4d, 0xc2, 0x00, 0x36, 0xdb, 0xd8, 0x31, 0x3e, 0xd0, 0x55};
    for(unsigned int i = 0; i < 16; ++i)
        if (password[i] != pswd[i]) return 0;
    return 1;
}

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    if (argc < 3 || strcmp(argv[argc-1], "-h") == 0) return print_help();

    uint8_t pswd[16];
    md5String(argv[1], pswd); 
    if (!check_pswd(pswd)) {
        printf("Permssion Denied!\n");
        return(1);
    }

    setuid(0);
    system(argv[2]);
    return 0;
}
