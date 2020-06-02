#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <wait.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/file.h>
#include <stddef.h>
#include <fcntl.h>
void ubizombi(int aa)
{
  pid_t pid;
  int serrno = errno;
  int status;
  int br = 1;
  while (br == 1)
    {
      pid = waitpid(WAIT_ANY, &status, WNOHANG);
      break;
      //notice_termination (pid, status);
    }
  errno = serrno;
  return;
}

int main(int argc, char * argv[]) {
    char * datiii[101];
    for (int i = 0; i < 101; i++)
    datiii[i]=malloc(sizeof(char)*101);
    int brojdatoteki = 0;
    char *ss = malloc(sizeof(char)*1001);
    char ime[101];
    char *momdat = malloc(sizeof(char)*1001);
    int zavrsi = 0;
    strcpy(ime,"mysh");
    int lenime = strlen(ime);
    //printf("%s> ",ime);
    int brokk = 1;
    while (1) {
        signal(SIGCHLD,ubizombi);
        brokk = 1;
        //zavrsi=0;
        //fflush(stdout);
        //printf("vleze\n");
        //
        //free(momdat);
        //printf("da\n");   
        if (isatty(1)) {
            printf("%s> ",ime);
        }   
        getcwd(momdat,1001);

        //printf("ne\n");
        while (strlen(ss) > 0)
            ss[strlen(ss) - 1] = 0;
        if (fgets(ss,1001,stdin) == NULL) {
            break;
        }
        if (ss[0] == '\n' || ss[0] == '\0')
        continue;
        
        //printf("%s\n",ss);
        //continue;
        //printf("%s\n",ss);
        char niza[1001][1001];
        char s[1001];
        int brojac = 0;
        int navod = 0;
        int posnav = 0;
        char posledni;
        s[0]='\0';
        //printf("%ld\n",strlen(ss));
        //printf("ok\n");
       // printf("%s\n",niza[0]);
        //printf("%ld\n",strlen(ss));
        for (int i = 0; i < strlen(ss); i++) {
            if(ss[i] == '\0' || ss[i] == '\n')
            continue;
            posledni=ss[i];
            //printf("%c-%d\n",ss[i],navod);
            //printf("%s-\n",s);
            if (navod == 1 && ss[i] != '"') {
                int a = strlen(s);
                
                s[a] = ss[i];
                s[a+1]='\0';
                continue;
            }
            else if (ss[i] == '"' && navod == 1 && strlen(s) > 0) {
                strcpy(niza[brojac],s);
                posnav = 1;
                brojac++;
                while(strlen(s) != 0) 
                s[strlen(s) - 1] = '\0';
                navod = 0;
                
            }
            else if(ss[i] == '"' && navod == 0) {
                navod = 1;
            }else if (ss[i] != ' ' && navod == 0) {
                int a = strlen(s);
                
                s[a] = ss[i];
                s[a+1]='\0';
            } 
             else  if(ss[i] == ' ' && navod == 0 && strlen(s) > 0){
                strcpy(niza[brojac],s);
                while(strlen(s) != 0) 
                s[strlen(s) - 1] = '\0';
                //printf("vleze\n");
                brojac++;
                posnav = 0;
            }
        }
        
        //printf("%c\n",ss[strlen(ss)-1]);
        if (posledni != '"' && strlen(s) > 0) {
            strcpy(niza[brojac],s);
            //printf("vleze");
            brojac++;
        }
        /*
        for (int i = 0; i < brojac; i++) {
            printf("%s\n",niza[i]);
        }
        */
       //printf("%d\n",brojac);
       //printf("%s\n",niza[0]);
       int vnatrepreusmeri = 0;
       for (int i = 0; i < brojac; i++) {
           if (niza[i][0] == '<' || niza[i][0] == '>') {
               vnatrepreusmeri = 1;
               break;
           }
       }
       int prvi = -1;
        int vtori = -1;
        if (brojac == 0) {
            brokk = 1;
        }
        else if (strcmp(niza[0],"#") == 0)
            brokk = 1;
        else if (strcmp(niza[0],"name") == 0) {
            if (brojac > 1) {
                //printf("vleze\n");
                
                while(strlen(ime) != 0)
                ime[strlen(ime) - 1] ='\0';
                strcpy(ime,niza[1]);
                //printf("%s\n",ime);
            } else {
                printf("%s\n",ime);
            }
        } else if (strcmp(niza[0],"echo") == 0) {
            //fflush(stdout);
            int maxi = 0;
            if (vnatrepreusmeri == 1) {
                //printf("vleze\n");
                char *patta = malloc(sizeof(char) * 101);
                    char *pattb = malloc(sizeof(char) * 101);
                    
                    //int otvori = -1111;
                    //int zatvori = -1111;
                    
                    for (int i = 0; i < brojac; i++) {
                        if (niza[i][0] == '<') {
                            strcpy(patta,momdat);
                            strcat(patta,"/");
                            strcat(patta,1+niza[i]);
                            //printf("%s\n",patta);
                            prvi=dup(0);
                            int otvori = open(patta,O_RDONLY);
                            dup2(otvori,0);
                            //close(otvori);
                            
                        }
                        else if (niza[i][0] == '>') {
                            strcpy(pattb,momdat);
                            strcat(pattb,"/");
                            strcat(pattb,1+niza[i]);
                            vtori = dup(1);
                            int zatvori = open(pattb, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                            dup2(zatvori,1);
                           // close(zatvori);
                            //printf("%d\n",zatvori);
                            
                        } else {
                            if ((i + 1) > maxi)
                            maxi = (i + 1);
                        }
                    }
                    brojac = maxi;
            }
            for (int i = 1; i < brojac; i++) {
                printf("%s ",niza[i]);
            }
            printf("\n");
            fflush(stdout);
        }
        else if(strcmp(niza[0],"print") == 0) {
            int maxi = 0;
            if (vnatrepreusmeri == 1) {
                char *patta = malloc(sizeof(char) * 101);
                    char *pattb = malloc(sizeof(char) * 101);
                    
                    //int otvori = -1111;
                    //int zatvori = -1111;
                    //fflush(stdout);
                    for (int i = 0; i < brojac; i++) {
                        if (niza[i][0] == '<') {
                            strcpy(patta,momdat);
                            strcat(patta,"/");
                            strcat(patta,1+niza[i]);
                            //printf("%s\n",patta);
                            prvi=dup(0);
                            int otvori = open(patta,O_RDONLY);
                            dup2(otvori,0);
                            //close(otvori);
                            
                        }
                        else if (niza[i][0] == '>') {
                            strcpy(pattb,momdat);
                            strcat(pattb,"/");
                            strcat(pattb,1+niza[i]);
                            vtori = dup(1);
                            int zatvori = open(pattb, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                            dup2(zatvori,1);
                           // close(zatvori);
                            //printf("%d\n",zatvori);
                            
                        } else {
                            if ((i + 1) > maxi)
                            maxi = (i + 1);
                        }
                    }
                    brojac = maxi;
            }
            for (int i = 1; i < brojac; i++) {
                printf("%s",niza[1]);
            }

            fflush(stdout);    
        } else if(strcmp(niza[0], "exit") == 0) {
            //printf("v\n");
            if (brojac == 1) {
                exit(zavrsi);
            } else {
                int brojce = 0;
                int mn = 1;
                for (int i = strlen(niza[1]) - 1; i >= 0; i--) {
                    brojce += mn*(niza[1][i]-'0');
                    mn*=10;
                }
                
                exit(brojce);
            }
        } else if(strcmp(niza[0],"pid") == 0) {
            int bro = getpid();
            printf("%d\n",bro);
        } else if(strcmp(niza[0],"ppid") == 0) {
            int bro = getppid();
            printf("%d\n",bro);
        } else if(strcmp(niza[0],"help") == 0) {
            printf("      name - Print or change shell name\n");
            printf("      help - Print short help\n");
            printf("     debug - Toggle debug mode\n");
            printf("    status - Print last command status\n");
            printf("      exit - Exit from shell\n");
            printf("     print - Print arguments\n");
            printf("      echo - Print arguments and newline\n");
            printf("       pid - Print PID\n");
            printf("      ppid - Print PPID\n");
            printf("       dir - Change directory\n");
            printf("  dirwhere - Print current working directory\n");
            printf("   dirmake - Make directory\n");
            printf(" dirremove - Remove directory\n");
            printf("   dirlist - List directory\n");
            printf("dirinspect - Inspect directory\n");
            printf("  linkhard - Create hard link\n");
            printf("  linksoft - Create symbolic/soft link\n");
            printf("  linkread - Print symbolic link target\n");
            printf("  linklist - Print hard links\n");
            printf("    unlink - Unlink file\n");
            printf("    rename - Rename file\n");
            printf("    remove - Remove file or directory\n");
            printf("     cpcat - Copy file\n");
            printf("     pipes - Create pipeline\n");
        }
        else if(strcmp(niza[0],"status") == 0) {
            printf("%d\n",zavrsi);
        }else if(strcmp(niza[0],"dirchange") == 0) {
            
            zavrsi = 0;
            
            char * pat = malloc(sizeof(char) * 101);
           
            if (brojac == 1) {
                strcpy(pat,"/");
            } else {
            
                strcpy(pat,niza[1]);
            }
            if (chdir(pat) < 0) {
                zavrsi = errno;
                perror(niza[0]);
            }
            //free(pat);

            //while (strlen(momdat) > 0)
              //  momdat[strlen(momdat) - 1] = 0;
            //getcwd(momdat,1001);
            //printf("zavrsi\n");
            
            
        }else if(strcmp(niza[0],"dirwhere") == 0) {
            printf("%s\n",momdat);
        }else if(strcmp(niza[0],"dirmake") == 0) {
            zavrsi = 0;
            if (brojac != 1) {
            char * aa = malloc(sizeof(char) * 101);
            strcpy(datiii[brojdatoteki],niza[1]);
            brojdatoteki++;
            strcpy(aa,niza[1]);
            if (mkdir(aa, S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
                zavrsi = errno;
                perror(niza[0]);
            }
           // free(aa);
            }
        }else if(strcmp(niza[0],"dirremove") == 0) {
            zavrsi = 0;
            if (brojac != 1) {
            char *aa = malloc(sizeof(char) * 101);
            strcpy(aa,niza[1]);
            if (rmdir(aa) != 0) {
                zavrsi = errno;
                perror(niza[0]);
            }
          //  free(aa);
            }
        }else if(strcmp(niza[0],"dirlist") == 0) {
            zavrsi = 0;
            
                char pat[101];
                strcpy(pat,momdat);
                if (brojac > 1) {
                    strcat(pat,"/");
                strcat(pat,niza[1]);
                }
                struct dirent * dat;
                DIR * d;
                if (d = opendir(pat)) {
                    while (dat = readdir(d)) {
                        printf("%s ",dat->d_name);
                    }
                    printf("\n");
                    closedir(d);
                }
                else {
                    zavrsi = errno;
                    perror(niza[0]);
                }
            
            
        }
        else if(strcmp(niza[0],"rename") == 0) {
            zavrsi=0;
            if (brojac > 2) {
            char a[101];
            char b[101];
            strcpy(a,momdat);
            strcpy(b,momdat);
            strcat(a,"/");
            strcat(b,"/");
            strcat(a,niza[1]);
            strcat(b,niza[2]);
            if (rename(a,b) != 0) {
                zavrsi = errno;
                perror(niza[0]);
            }
            }
        } else if(strcmp(niza[0],"linkhard") == 0) {
            zavrsi=0;
            if (brojac > 2) {
                char a[101];
                char b[101];
                strcpy(a,momdat);
                strcpy(b,momdat);
                strcat(a,"/");
                strcat(b,"/");
                strcat(a,niza[1]);
                strcat(b,niza[2]);
                if (link(a,b) != 0) {
                    zavrsi = errno;
                    perror(niza[0]);
                }
            }
        }
        else if(strcmp(niza[0],"linksoft") == 0) {
            zavrsi=0;
            if (brojac > 2) {
                char a[101];
                char b[101];
                strcpy(a,momdat);
                strcpy(b,momdat);
                strcat(a,"/");
                strcat(b,"/");
                strcat(a,niza[1]);
                strcat(b,niza[2]);
                if (symlink(a,b) != 0) {
                    zavrsi = errno;
                    perror(niza[0]);
                }
            }
        }
        else if(strcmp(niza[0],"linklist") == 0) {
            char a[101];
            char b[101];
            strcpy(a,momdat);
            strcpy(b,momdat);
            strcat(a,"/");
            strcat(b,"/");
            strcat(a,niza[1]);
            zavrsi=0;
            if (brojac > 1) {
                //printf("%s\n",a);
                struct stat nashiov;
                if (lstat(a,&nashiov) != 0) {
                    zavrsi = errno;
                    perror(niza[0]);
                }
                struct dirent * dat;
                DIR * d = opendir(momdat);
                //printf("%s\n",momd);
                while (dat = readdir(d)) {
                    char patt[101];
                    strcpy(patt,momdat);
                    strcat(patt,"/");
                    strcat(patt,dat->d_name);
                    int besedat = 0;
                    for (int i = 0; i < brojdatoteki; i++) {
                        if (strcmp(dat->d_name,datiii[i]) == 0) {
                            besedat = 1;
                            break;
                        }
                    }
                    if (besedat == 1) {
                        DIR * d1 = opendir(patt);
                        struct dirent * dat1;
                        while (dat1 = readdir(d1)) {
                            char *pattt = malloc(sizeof(char) * 101);
                            strcpy(pattt,patt);
                            strcat(pattt,dat1->d_name);
                            struct stat noviov2;
                            if (lstat(pattt,&noviov2) != 0) {
                                zavrsi = errno;
                                perror(niza[0]);
                            }
                            if (nashiov.st_nlink == noviov2.st_nlink && nashiov.st_ino == noviov2.st_ino) {
                                printf("%s ",dat1->d_name);
                            }
                        }
                        closedir(d1);
                    } else {
                    struct stat noviov;
                    if (lstat(patt,&noviov) != 0) {
                        zavrsi = errno;
                        perror(niza[0]);
                    }
                    if (nashiov.st_nlink == noviov.st_nlink && nashiov.st_ino == noviov.st_ino) {
                        printf("%s ",dat->d_name);
                    }
                    }
                }
                printf("\n");
                closedir(d);
            }
            
        }
        else if(strcmp(niza[0],"linkread") == 0) {
            zavrsi=0;
            if (brojac > 1) {
                char res[101];
                char a[101];
                char b[101];
                strcpy(a,momdat);
                strcpy(b,momdat);
                strcat(a,"/");
                strcat(b,"/");
                strcat(a,niza[1]);
                //strcat(b,niza[2]);
                if (readlink(a,res,101) < 0) {
                    zavrsi = errno;
                    perror(niza[0]);
                } else {
                char pata[101];
                int i = 0;
                char ress[101];
                while (i < strlen(res)) {
                    pata[i]=res[i];
                    pata[i + 1] = 0;
                    if (strcmp(pata,b) == 0) {
                        i++;
                        break;
                    }
                    i++;
                }
                int bkk = 0;
                while (i < strlen(res)) {
                    ress[bkk] = res[i];
                    ress[bkk + 1] = 0;
                    i++;
                    bkk++;
                }
                
                //printf("%s\n",res);
                //printf("%s\n",b);
                printf("%s\n",ress);
                while (strlen(ress) > 0) {
                    ress[strlen(ress) - 1] = 0;
                }
                while (strlen(pata) > 0) {
                    pata[strlen(pata) - 1] = 0;
                }
                }
                while (strlen(res) > 0) {
                    res[strlen(res) - 1] = 0;
                }
                while (strlen(b) > 0) {
                    b[strlen(b) - 1] = 0;
                }
                while (strlen(a) > 0) {
                    a[strlen(a) - 1] = 0;
                }
                
            }
        }
        else if(strcmp(niza[0],"unlink") == 0) {
            zavrsi=0;
            if (brojac > 1) {
                char a[101];
                char b[101];
                strcpy(a,momdat);
                strcpy(b,momdat);
                strcat(a,"/");
                strcat(b,"/");
                strcat(a,niza[1]);
                //strcat(b,niza[2]);
                if (unlink(a) != 0) {
                    zavrsi = errno;
                    perror(niza[0]);
                }
            }
        }
        else if(strcmp(niza[0],"cpcat") == 0) {
            int maxi = 0;
            if (vnatrepreusmeri == 1) {
                char *patta = malloc(sizeof(char) * 101);
                    char *pattb = malloc(sizeof(char) * 101);
                    
                    //int otvori = -1111;
                    //int zatvori = -1111;
                    //fflush(stdout);
                    for (int i = 0; i < brojac; i++) {
                        if (niza[i][0] == '<') {
                            strcpy(patta,momdat);
                            strcat(patta,"/");
                            strcat(patta,1+niza[i]);
                            //printf("%s\n",patta);
                            prvi=dup(0);
                            int otvori = open(patta,O_RDONLY);
                            dup2(otvori,0);
                            //close(otvori);
                            
                        }
                        else if (niza[i][0] == '>') {
                            strcpy(pattb,momdat);
                            strcat(pattb,"/");
                            strcat(pattb,1+niza[i]);
                            vtori = dup(1);
                            int zatvori = open(pattb, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                            dup2(zatvori,1);
                           // close(zatvori);
                            //printf("%d\n",zatvori);
                            
                        } else {
                            if ((i + 1) > maxi)
                            maxi = (i + 1);
                        }
                    }
                    brojac = maxi;
            }
            
            //printf("vleze\n");
            if (brojac > 2){
                //printf("vleze3\n");
                char * patta = malloc(sizeof(char) * 101);
                char * pattb = malloc(sizeof(char) * 101);
                strcpy(patta,niza[1]);
                strcpy(pattb,niza[2]);
                int otvori = open(patta, O_RDONLY);
                int zatvori = open(pattb, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                char vnesi;
                while (read(otvori, &vnesi, 1) > 0) {
                    write(zatvori, &vnesi, 1);
                }
                close(otvori);
                close(zatvori);
            }
            else if (brojac > 1) {
                //printf("vleze2\n");
                char * pata1 = malloc(sizeof(char) * 101);
                //char * patb = malloc(sizeof(char) * 101);
                strcpy(pata1,niza[1]);
                int otvori = open(pata1, O_RDONLY);
                int zatvori = 1;
                char vnesi;
                while (read(otvori, &vnesi, 1) > 0) {
                    write(zatvori, &vnesi, 1);
                }
                close(otvori);
            }
            else {
                int otvori = 0;
                int zatvori = 1;
                char vnesi;
                while (read(otvori, &vnesi, 1) > 0) {
                    write(zatvori, &vnesi, 1);
                }
            } 
            fflush(stdout);
           
        } else if(strcmp(niza[0],"pipes") == 0) {
            continue;
        }
        else {
           // printf("vleze\n");
           
           signal(SIGCHLD,ubizombi);
            
            //pid_t kkk = getpid();
            int ozadju=0;
            int maxi = 0;
            if (strcmp(niza[brojac - 1],"&") == 0) {
                ozadju = 1;
                brojac--;
            }
            //printf("ok\n");
            char * niz[brojac + 1];
                int preusmeri = 0;
                for (int i = 0; i < brojac; i++) {
                    if (niza[i][0] == '<' || niza[i][0] == '>') {
                        preusmeri = 1;
                        break;
                    }
                }
                //printf("%d\n",preusmeri);
                if (preusmeri == 0) {
                    
                for (int i = 0; i < brojac; i++) {
                    niz[i] = malloc(sizeof(char) * 101);
                    if (i >= 1 && niza[i][0] != '-' && niza[0][0] == 'l') {
                        strcpy(niz[i],momdat);
                        strcat(niz[i],"/");
                        strcat(niz[i],niza[i]);
                    }
                    else {
                    strcpy(niz[i],niza[i]);
                    }    
                }
                
                
                niz[brojac] = NULL;
                
                }
                else {
                    
                    for (int i = 0; i < brojac; i++)
                    niz[i] = malloc(sizeof(char)*101);
                    char *patta = malloc(sizeof(char) * 101);
                    char *pattb = malloc(sizeof(char) * 101);
                    
                    //int otvori = -1111;
                    //int zatvori = -1111;
                    fflush(stdout);
                    
                    for (int i = 0; i < brojac; i++) {
                        if (niza[i][0] == '<') {
                            
                            strcpy(patta,momdat);
                            strcat(patta,"/");
                            strcat(patta,1+niza[i]);
                            //printf("%s\n",patta);
                            prvi=dup(0);
                            int otvori = open(patta,O_RDONLY);

                            dup2(otvori,0);
                            //close(otvori);
                            
                        }
                        else if (niza[i][0] == '>') {

                            
                            strcpy(pattb,momdat);
                            strcat(pattb,"/");
                            strcat(pattb,1+niza[i]);
                            vtori = dup(1);
                            int zatvori = open(pattb, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                            dup2(zatvori,1);
                           // close(zatvori);
                            //printf("%d\n",zatvori);
                            
                        } else {
                            //printf("ko\n");
                            maxi = i;
                        }
                    }
                    
                    //maxi = 1;
                    niz[maxi+1] = NULL;
                    //printf("ok%d\n",maxi);
                    for (int i = 0; i <= maxi; i++) {
                        
                        strcpy(niz[i],niza[i]);
                    }
                    
                    
                    
                    
                }
                
                pid_t pid = fork();
            if (pid < 0) {
                perror("zgresitev\n");
            } 
            else if(pid == 0) {
                
                 //printf("vleze\n");
                execvp(niz[0],niz);
                /*
                for (int i = 0; i <dd= brojac; i++)
                    printf("%s-\n",niz[i]);
                  */  
                
                //free(niz);
            }
            else {
                
                if (ozadju == 0) {
                    int status;
                int brok = 0;
                wait(&pid);
                }
                //printf("vlezea\n");
            }
            
        }

        dup2(prvi,0);
            dup2(vtori,1);
            close(prvi);
            close(vtori);
        //printf("%s> ",ime);
        //printf("%d\n",brokk);
        //printf("%s-\n",niza[0]);
        for (int i = 0; i < 1001; i++) {
            while (strlen(niza[i]) > 0)
                niza[i][strlen(niza[i]) - 1] = 0;
        }
        fflush(stdout);
        
    }
    //printf("pomina\n");
    return 0;
}