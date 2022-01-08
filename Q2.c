#include <string.h>
#include <unistd.h>

#define message "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n"
#define messageFortune "Today is what happened to yesterday.\n"
#define BUFSIZE 128

int main(){
    write(STDOUT_FILENO,message,strlen(message));   //Message de bienvenue
    while(1){                                       // Pour rester dans le Shell
        int n;
        char buf[BUFSIZE];                          //Pour stocker la commande
        n=read(STDIN_FILENO,buf,BUFSIZE);           //Lecture de ce qu'on écrit 
        buf[n-1]=0;                                 //Mettre un 0 à la fin pour indiquer la fin du message
        if (strcmp(buf,"fortune")==0){
            write(STDOUT_FILENO,messageFortune,strlen(messageFortune)); //Message de fortune
        }
    }
    return 0;
}