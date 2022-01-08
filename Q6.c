#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>


#define message "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n"
#define messageFortune "Today is what happened to yesterday.\n"
#define messageAurevoir "Bye Bye .. \n"
#define messageS "C'est toi ma fortune :* \n"
#define messageOS "HAHAHA pranked \n"
#define messageIP "127.0.0.1 \n"
#define BUFSIZE 128

int main(){
    struct timespec start, stop;
    int n;
    char buf[BUFSIZE];                          // Pour stocker la commande
    int status;
    pid_t pid;
    const char * separators = " -";             // Les séparateurs
    write(STDOUT_FILENO,message,strlen(message));   //Message de bienvenue
    while(1){   
        n=read(STDIN_FILENO,buf,BUFSIZE-1);           //Lecture de ce qu'on écrit 
        buf[n-1]=0;                                 //Mettre un 0 à la fin pour indiquer la fin du message
        if ( (strcmp(buf,"exit")==0) || (n==0) ){   // Pour sortir du shell avec la commande exit ou Ctrl+D, quand on fait un Ctrl+D on indique le "end of file"
                                                    //et quand read renvoie la valeur 0 cela indique le "end of file"
            write(STDOUT_FILENO,messageAurevoir,strlen(messageAurevoir)); // Message d'aurevoir
            break;
        }

        pid = fork();                       // Creation processus fils
        clock_gettime(CLOCK_REALTIME,&start);
        if (pid!=0){
            wait(&status);
       }else{                              // Ce que le fils va faire
            char* p =strtok(buf,separators);         // On va découper la commande rentrée en plusieurs morceaux et on va identifier les arguments                    
            if (strcmp(p,"fortune")==0){             // Commande fortune
                write(STDOUT_FILENO,messageFortune,strlen(messageFortune)); // Message de fortune   
                while(p!=NULL){                    
                    if (strcmp(p,"s")==0){          // Argument s
                        write(STDOUT_FILENO,messageS,strlen(messageS));
                    }
                    if (strcmp(p,"osfortune")==0){ // Argument osfortune
                        write(STDOUT_FILENO,messageOS,strlen(messageOS));
                    }
                    p=strtok(NULL,separators);     // Pour passer à l'argument suivant
                }
            }
             if (strcmp(p,"hostname")==0){          // Commande hostname
                 while(p!=NULL){                    
                    if (strcmp(p,"i")==0){          // Argument s
                        write(STDOUT_FILENO,messageIP,strlen(messageIP));
                    }
                    p=strtok(NULL,separators);     // Pour passer à l'argument suivant
                }
             }
            break;              // Necessaire sinon on créer un fils à l'intérieur du fils et ainsi de suite à chaque nouvelle commande
            
        }                   
        clock_gettime(CLOCK_REALTIME,&stop);
        if (WIFEXITED(status)){                                //si le fils s’est terminé normalement
            printf("enseah [exit:%d|%ldms] %% \n",WEXITSTATUS(status),(stop.tv_nsec-start.tv_nsec)/(1000));//renvoie dans ce cas la valeur de sortie du fils
        }else if (WIFSIGNALED(status)){                        //si le fils s’est terminé à cause d’un signal, par un kill par exemple   
            printf("enseah [signal:%d|%ldms] %% \n",WTERMSIG(status),(stop.tv_nsec-start.tv_nsec)/(1000)); //renvoie le numéro du signal qui a causé la fin du fils
        }
        
    }
    return 0;
}