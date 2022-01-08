#include <string.h>
#include <unistd.h>

#define message "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n"
#define messageFortune "Today is what happened to yesterday.\n"
#define messageAurevoir "Bye Bye .. \n"
#define BUFSIZE 128

int main(){
    write(STDOUT_FILENO,message,strlen(message));   //Message de bienvenue
    while(1){                                       // Pour rester dans le Shell
        int n;
        char buf[BUFSIZE];                          // Pour stocker la commande
        n=read(STDIN_FILENO,buf,BUFSIZE);           //Lecture de ce qu'on écrit 
        buf[n-1]=0;                                 //Mettre un 0 à la fin pour indiquer la fin du message
        if (strcmp(buf,"fortune")==0){
            write(STDOUT_FILENO,messageFortune,strlen(messageFortune)); // Message de fortune
        }
        if ( (strcmp(buf,"exit")==0) || (n==0) ){   // Pour sortir du shell avec la commande exit ou Ctrl+D, quand on fait un Ctrl+D on indique le "end of file"
                                                    //et quand read renvoie la valeur 0 cela indique le "end of file"
            write(STDOUT_FILENO,messageAurevoir,strlen(messageAurevoir)); // Message d'aurevoir
            break;
        }  
    }
    return 0;
}
        
