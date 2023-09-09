#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef PASSWORD
    #define ARG_CMD 2
    #include "md5-c/md5.h"
#else
    #define ARG_CMD 1
#endif

int print_help(){
#ifdef PASSWORD
    printf("Usage: sulock [PASSWORD] [COMMAND]\n");
#else
    printf("Usage: sulock [COMMAND]\n");
#endif
    return 0;
}

#ifdef PASSWORD
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
#endif

int main(int argc, char* argv[]){
    if (argc < ARG_CMD+1 || strcmp(argv[argc-1], "-h") == 0) return print_help();

    /* check password */
#ifdef PASSWORD
    uint8_t pswd[16];
    md5String(argv[1], pswd);
    if (!check_pswd(pswd)) {
        printf("Permssion Denied!\n");
        return(1);
    }
#endif

    /* make command string */
    char* cmd = malloc(strlen(argv[ARG_CMD]) * sizeof(char));
    strcpy(cmd, argv[ARG_CMD]);
    for (int i = ARG_CMD+1; i < argc; i++){
       int s = strlen(argv[i]) + strlen(cmd) + 1;
       if (s > 256) cmd = realloc(cmd, s*sizeof(char));
       strcat(cmd, " ");
       strcat(cmd, argv[i]);
    }

    setuid(0);
    system(cmd);
    return 0;
}
