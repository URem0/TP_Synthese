#include <string.h>
#include <unistd.h>

#define message "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n"

int main(){
    write(STDOUT_FILENO,message,strlen(message)); //On va afficher le message de bienvenue avec la fonction write
    return 0;
}