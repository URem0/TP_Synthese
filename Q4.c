#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


#define message "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n"
#define messageFortune "Today is what happened to yesterday.\n"
#define messageAurevoir "Bye Bye .. \n"
#define BUFSIZE 128

int main(){
    write(STDOUT_FILENO,message,strlen(message));   //Message de bienvenue
    while(1){                                       // Pour rester dans le Shell
        int n;
        char buf[BUFSIZE];                          // Pour stocker la commande
        int status;
        pid_t pid;
        n=read(STDIN_FILENO,buf,BUFSIZE);           //Lecture de ce qu'on écrit 
        buf[n-1]=0;                                 //Mettre un 0 à la fin pour indiquer la fin du message
        
        if ( (strcmp(buf,"exit")==0) || (n==0) ){   // Pour sortir du shell avec la commande exit ou Ctrl+D, quand on fait un Ctrl+D on indique le "end of file"
                                                    //et quand read renvoie la valeur 0 cela indique le "end of file"
            write(STDOUT_FILENO,messageAurevoir,strlen(messageAurevoir)); // Message d'aurevoir
            break;
        }

        pid = fork();                       // Creation processus fils

        if (pid!=0){
            wait(&status);
        }else{                              // Ce que le fils va faire
            if (strcmp(buf,"fortune")==0){
                        write(STDOUT_FILENO,messageFortune,strlen(messageFortune)); // Message de fortune
            }
            break;                          // Necessaire sinon on créer un fils à l'intérieur du fils et ainsi de suite à chaque nouvelle commande
        }

        if (WIFEXITED(status)){                                  //si le fils s’est terminé normalement
            printf("enseah [exit:%d] %% \n",WEXITSTATUS(status));//renvoie dans ce cas la valeur de sortie du fils
        }else if (WIFSIGNALED(status)){                          //si le fils s’est terminé à cause d’un signal, par un kill par exemple
            printf("enseah [signal:%d] %% \n",WTERMSIG(status)); //renvoie le numéro du signal qui a causé la fin du fils
        }
        
    }
    return 0;
}
        
