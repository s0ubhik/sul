#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int print_help(){
    printf("Usage: sulock [COMMAND]\n");
    return 0;
}

int main(int argc, char* argv[]){
    if (argc < 2 || strcmp(argv[argc-1], "-h") == 0) return print_help();

    char* cmd = malloc(strlen(argv[1]) * sizeof(char));
    strcpy(cmd, argv[1]);
    for (int i = 3; i < argc; i++){
       int s = strlen(argv[i]) + strlen(cmd) + 1;
       if (s > 256) cmd = realloc(cmd, s*sizeof(char));
       strcat(cmd, " ");
       strcat(cmd, argv[i]);
    }

    setuid(0);
    system(cmd);
    return 0;
}
