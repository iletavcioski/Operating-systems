#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
struct proces {
    int pid;
    char ime[1001];
    char stanje;
    int ppid;
    int niti;
    int fajlojproc;
} procesi[10001];

int swapi(int a, int b) {
    return a;
}
char swapc(char a, int b) {
    return a;
}

int brojprocesi = 0;
int n = 0;
int drevo[100001];
int dlabocina[100001];
int maxidep = 0;

void dfs1(int x, int d) {
    int brojac = 0;
    if (d > maxidep)
    maxidep = d;
     for (int j = 0; j < x; j++) 
        brojac += drevo[j];
    for (int i = brojac + 1; i < brojac + 1 + drevo[x]; i++) {
        dfs1(i, d + 1);
    }
}
void dfs(int x, int d) {
    int brojac = 0;
    //printf("%d-%d\n",x,d);
    for (int j = 0; j < x; j++) 
        brojac += drevo[j];
    for (int i = brojac + 1; i < brojac + 1 + drevo[x]; i++) {
        int pid = fork();
        
        
        //printf("%d %d\n",x,i);
        
        if (pid < 0) {
            perror("zgresitev\n");
            exit(1);
        } else if (pid == 0) {
            
            //printf("%d da\n",x);
            //pause();
            dfs(i, d + 1);
            pause();
            //exit(0);
            //printf("%d %d\n",x,dlabocina[x + 1] + brojac);
            
        } else {
           // sleep(3*(maxidep - d));
           // exit(0);
           //exit(0);
           //pause();
        }
        
        
    }
}
int main(int argc, char* argv[]) {
    brojprocesi = 0;
    if (strcmp(argv[1], "pids") == 0 || strcmp(argv[1],"names") == 0 || strcmp(argv[1],"ps") == 0 || strcmp(argv[1],"psext") == 0) {
        char * pat = malloc(sizeof(char) * 1000001);
        strcpy(pat, argv[2]);
        struct dirent * dat;
        DIR * d = opendir(pat);
        //printf("da\n");
        while (dat = readdir(d)) {
            //printf("%s\n",dat->d_name);
            char * vnatrepat = malloc(sizeof(char) * 101);
            strcpy(vnatrepat, dat->d_name);
            int mn = 1;
            int brojac = 0;
            int nemozi = 0;
            for (int i = strlen(vnatrepat) - 1; i >= 0; i--) {
                //printf("da\n");
                if (vnatrepat[i] >= '0' && vnatrepat[i] <= '9') {
                    brojac += mn*(vnatrepat[i]-'0');
                    mn *= 10;
                } else {
                    nemozi = 1;
                    break;
                }
            }
            if (nemozi == 0) {
                char * vlezidat = malloc(sizeof(char) * 101);
                strcpy(vlezidat,pat);
                strcat(vlezidat,"/");
                strcat(vlezidat,vnatrepat);
                char * vlezistat = malloc(sizeof(char) * 101);
                strcpy(vlezistat, vlezidat);
                strcat(vlezistat,"/stat");
                char * vlezistatus = malloc(sizeof(char) * 101);
                strcpy(vlezistatus, vlezidat);
                strcat(vlezistatus, "/status");
                char * vlezifd = malloc(sizeof(char) * 101);
                strcpy(vlezifd, vlezidat);
                strcat(vlezifd, "/fd");
                FILE * f = fopen(vlezistatus, "r");
                char * statuss = malloc(sizeof(char) * 1000001);
                int imaniti = 0;
                //printf("da\n");
                while (fscanf(f,"%s",statuss) != -1) {
                    if (imaniti == 1) {
                        int brojce = 0;
                        int mn = 1;
                        for (int i = strlen(statuss) - 1; i >= 0; i--) {
                            brojce += mn*(statuss[i]-'0');
                            mn*=10;
                        }
                        procesi[brojprocesi].niti = brojce;
                        imaniti = 0;
                    }
                    if (strcmp(statuss, "Threads:") == 0) {
                        imaniti = 1;
                    }
                }
                //printf("da\n");
                fclose(f);
                //printf("da\n");
                //printf("%s\n",vlezifd);
                DIR * dfd = opendir(vlezifd);
                
                struct durent * dd;
                int brojci = 0;
                while (readdir(dfd)) {
                    brojci++;
                }
                closedir(dfd);
                //printf("da\n");
                brojci-=2;
                procesi[brojprocesi].fajlojproc = brojci;
                //printf("%s\n", vlezistat);
                f = fopen(vlezistat,"r");
                char * ss = malloc(sizeof(char) * 101);
                fscanf(f, "%d %s %c %d",&procesi[brojprocesi].pid,ss,&procesi[brojprocesi].stanje,&procesi[brojprocesi].ppid);
                //printf("da\n");
                
                int nn = strlen(ss) - 2;
                char *ad = malloc(sizeof(char) * nn);
                //printf("%d\n",nn);
                for (int i = 1; i <= nn; i++) {
                    ad[i-1] = ss[i];
                }
                //printf("%s\n",ad);
                ad[nn] = 0;
                strcpy(procesi[brojprocesi].ime,ad);
                //printf("%s\n",procesi[brojprocesi].ime);
                free(ad);
                brojprocesi++;
                //print
                fclose(f);
            }
        }
        closedir(d);
        //printf("da\n");wddw
        for (int i = 0; i < brojprocesi; i++) {
                for (int j = i + 1; j < brojprocesi; j++) {
                    if (procesi[i].pid > procesi[j].pid) {
                        int t2 = procesi[i].pid;
                        procesi[i].pid = procesi[j].pid;
                        procesi[j].pid = t2; 
                        t2 = procesi[i].ppid;
                        procesi[i].ppid = procesi[j].ppid;
                        procesi[j].ppid = t2; 
                        char t1 = procesi[i].stanje;
                        procesi[i].stanje = procesi[j].stanje;
                        procesi[j].stanje = t1; 
                        char *t = malloc(sizeof(char) * 101);
                        strcpy(t, procesi[i].ime);
                        strcpy(procesi[i].ime, procesi[j].ime);
                        strcpy(procesi[j].ime, t);
                        t2 = procesi[i].niti;
                        procesi[i].niti = procesi[j].niti;
                        procesi[j].niti = t2; 
                        t2 = procesi[i].fajlojproc;
                        procesi[i].fajlojproc = procesi[j].fajlojproc;
                        procesi[j].fajlojproc = t2; 
                        //printf("da\n");
                    }
                }
            }
        if (strcmp(argv[1], "pids") == 0 ) {
            for (int i = 0; i < brojprocesi; i++) {
                printf("%d\n", procesi[i].pid);
            }
        } else if (strcmp(argv[1],"names") == 0) {
            for (int i = 0; i < brojprocesi; i++) {
                for (int j = i + 1; j < brojprocesi; j++) {
                    char a[101];
                    char b[101];
                    strcpy(a,procesi[i].ime);
                    strcpy(b,procesi[j].ime);
                    for (int ii = 0; ii < strlen(a); ii++) {
                    if (a[ii] >= 'A' && a[ii] <= 'Z')
                        a[ii] += 32;
                    }
                    for (int ii = 0; ii < strlen(b); ii++) {
                    if (b[ii] >= 'A' && b[ii] <= 'Z')
                        b[ii] += 32;
                    }                           
                    if (strcmp(a,b) > 0) {
                        int t2 = procesi[i].pid;
                        procesi[i].pid = procesi[j].pid;
                        procesi[j].pid = t2; 
                        t2 = procesi[i].ppid;
                        procesi[i].ppid = procesi[j].ppid;
                        procesi[j].ppid = t2; 
                        char t1 = procesi[i].stanje;
                        procesi[i].stanje = procesi[j].stanje;
                        procesi[j].stanje = t1; 
                        char tt[101];
                        strcpy(tt, procesi[i].ime);
                        strcpy(procesi[i].ime, procesi[j].ime);
                        strcpy(procesi[j].ime, tt);
                        t2 = procesi[i].niti;
                        procesi[i].niti = procesi[j].niti;
                        procesi[j].niti = t2; 
                        t2 = procesi[i].fajlojproc;
                        procesi[i].fajlojproc = procesi[j].fajlojproc;
                        procesi[j].fajlojproc = t2; 
                        //printf("da\n");
                    } 
                }
            }
            for (int i = 0; i < brojprocesi; i++) {
                for (int j = i + 1; j < brojprocesi; j++) {
                    char a[101];
                    char b[101];
                    strcpy(a,procesi[i].ime);
                    strcpy(b,procesi[j].ime);
                                
                    if (strcmp(a,b) == 0 && procesi[i].pid > procesi[j].pid) {
                        int t2 = procesi[i].pid;
                        procesi[i].pid = procesi[j].pid;
                        procesi[j].pid = t2; 
                        t2 = procesi[i].ppid;
                        procesi[i].ppid = procesi[j].ppid;
                        procesi[j].ppid = t2; 
                        char t1 = procesi[i].stanje;
                        procesi[i].stanje = procesi[j].stanje;
                        procesi[j].stanje = t1; 
                        char tt[101];
                        strcpy(tt, procesi[i].ime);
                        strcpy(procesi[i].ime, procesi[j].ime);
                        strcpy(procesi[j].ime, tt);
                        t2 = procesi[i].niti;
                        procesi[i].niti = procesi[j].niti;
                        procesi[j].niti = t2; 
                        t2 = procesi[i].fajlojproc;
                        procesi[i].fajlojproc = procesi[j].fajlojproc;
                        procesi[j].fajlojproc = t2; 
                        //printf("da\n");
                    } 
                }
            }
            for (int i = 0; i < brojprocesi; i++) {
                printf("%d %s\n", procesi[i].pid, procesi[i].ime);
            }
        } else if (strcmp(argv[1],"ps") == 0) {
            //printf("da\n");
            if (argc == 3) {
                printf("%5s %5s %6s %s\n", "PID", "PPID", "STANJE", "IME");
                for (int i = 0; i < brojprocesi; i++) {
                    printf("%5d %5d %6c %s\n", procesi[i].pid, procesi[i].ppid, procesi[i].stanje, procesi[i].ime);
                }
            } else {
                //printf("da\n");
                printf("%5s %5s %6s %s\n", "PID", "PPID", "STANJE", "IME");
                char * s1 = malloc(sizeof(char) * 1001);
                //printf("da\n");
                strcpy(s1,argv[3]);
                //printf("da\n");
                int mn = 1;
                int br = 0;
                for (int i = strlen(s1) - 1; i >= 0; i--) {
                    br += mn*(s1[i]-'0');
                    mn*=10;
                }
                int niza[brojprocesi];
                for (int i = 0; i < brojprocesi; i++)
                    niza[i] = 0;
                int najde = 0;
                //printf("da\n");
                for (int i = 0; i < brojprocesi; i++) {
                    najde = 0;
                    int y = procesi[i].pid;
                    int kk = 1;
                    while (kk == 1) {
                        //printf("%d %d\n",y,br);
                        if (y == br) {
                            najde = 1;
                            break;
                        }
                        int ima = 0;
                        for (int j = 0; j < brojprocesi; j++) {
                            if (procesi[j].pid == y) {
                                y = procesi[j].ppid;
                                ima = 1;
                                //printf("najde %d %d\n",procesi[j].pid,procesi[j].ppid);
                                break;
                            }
                        }
                        if (ima == 0) {
                            break;
                        }
                    }
                    if (najde == 1) {
                        //printf("da\n");
                        printf("%5d %5d %6c %s\n", procesi[i].pid, procesi[i].ppid, procesi[i].stanje, procesi[i].ime);
                    }
                }
            } 
        } else if (strcmp(argv[1],"psext") == 0) {
            //printf("da\n");
            if (argc == 3) {
                printf("%5s %5s %6s %6s %6s %s\n", "PID", "PPID", "STANJE", "#NITI", "#DAT.", "IME");
                for (int i = 0; i < brojprocesi; i++) {
                    printf("%5d %5d %6c %6d %6d %s\n", procesi[i].pid, procesi[i].ppid, procesi[i].stanje,procesi[i].niti,procesi[i].fajlojproc, procesi[i].ime);
                }
            }
            else {
                printf("%5s %5s %6s %6s %6s %s\n", "PID", "PPID", "STANJE", "#NITI", "#DAT.", "IME");
                char * s1 = malloc(sizeof(char) * 1001);
                //printf("da\n");
                strcpy(s1,argv[3]);
                //printf("da\n");
                int mn = 1;
                int br = 0;
                for (int i = strlen(s1) - 1; i >= 0; i--) {
                    br += mn*(s1[i]-'0');
                    mn*=10;
                }
                int niza[brojprocesi];
                for (int i = 0; i < brojprocesi; i++)
                    niza[i] = 0;
                int najde = 0;
                //printf("da\n");
                for (int i = 0; i < brojprocesi; i++) {
                    najde = 0;
                    int y = procesi[i].pid;
                    int kk = 1;
                    while (kk == 1) {
                        //printf("%d %d\n",y,br);
                        if (y == br) {
                            najde = 1;
                            break;
                        }
                        int ima = 0;
                        for (int j = 0; j < brojprocesi; j++) {
                            if (procesi[j].pid == y) {
                                y = procesi[j].ppid;
                                ima = 1;
                                //printf("najde %d %d\n",procesi[j].pid,procesi[j].ppid);
                                break;
                            }
                        }
                        if (ima == 0) {
                            break;
                        }
                    }
                    if (najde == 1) {
                        //printf("da\n");
                        //printf("%5s %5s %6s %6s %6s %s\n", "PID", "PPID", "STANJE", "#NITI", "#DAT.", "IME");
                        printf("%5d %5d %6c %6d %6d %s\n", procesi[i].pid, procesi[i].ppid, procesi[i].stanje,procesi[i].niti,procesi[i].fajlojproc, procesi[i].ime);
                    }
                }
            } 
        }
    }
    else if (strcmp(argv[1],"sys") == 0) {
        char * pat = malloc(sizeof(char) * 1000001);
        strcpy(pat, argv[2]);
        pat=strcat(pat,"/version");
        FILE * f;
        f = fopen(pat,"r");
        char * ss = malloc(sizeof(char) * 1000001);
        int lin = 0;
        int linver = 0;
        int gcc = 0;
        int gccver = 0;
        while (fscanf(f,"%s",ss) != -1) {
            if (gcc && gccver) {
                printf("gcc: %s\n",ss);
                gcc = 0;
                gccver = 0;
            }
            if (strcmp(ss,"(gcc") == 0) { 
                gcc = 1;
            }
            if (strcmp(ss,"version") == 0 && gcc == 1) {
                gccver = 1;
            }
            if (lin && linver) {
                printf("Linux: %s\n",ss);
                lin = 0;
                linver = 0;
            }
            if (strcmp(ss,"Linux") == 0) { 
                lin = 1;
            }
            if (strcmp(ss,"version") == 0 && lin == 1) {
                linver = 1;
            }
        } 
        fclose(f);
        char * pat1 = malloc(sizeof(char) * 1000001);
        strcpy(pat1, argv[2]);
        pat1=strcat(pat1,"/swaps");
        f = fopen(pat1,"r");
        ss = malloc(sizeof(char) * 1000001);
        int br = 0;
        printf("Swap:");
        while (fscanf(f,"%s",ss) != -1) {
            if (br > 0 && br % 5 == 0) {
                printf(" %s", ss);
            }
            br++;
        }
        printf("\n");
        fclose(f);
        char * pat2 = malloc(sizeof(char) * 1000001);
        strcpy(pat2, argv[2]);
        pat2=strcat(pat2,"/modules");
        f = fopen(pat2,"r");
        ss = malloc(sizeof(char) * 1000001);
        br = 0;
        printf("Modules: ");
        while (fscanf(f,"%s",ss) != -1) {
            //printf("%c\n",ss[0]);
            //printf("%c\n",ss[1]);
            if (ss[0] == '0' && ss[1] == 'x') {
                br++;
            }
        }
        printf("%d\n", br);
        fclose(f);
    } else if (strcmp(argv[1],"forktree") == 0) {
        char * s2 = malloc(sizeof(char) * 1001);
        for (int i = 0; i < 100001; i++) {
            drevo[i] = 0;
        }
        n = 0;
        //drevo[0] = 0;
        while (scanf("%s",s2) != EOF) {
            int brojka = 0;
            int mn = 1;
            if (strcmp(s2,"-1") == 0) 
                break;
            for (int i = strlen(s2) - 1; i >= 0; i--) {
                brojka += mn*(s2[i] - '0');
                mn *= 10;
            }
            drevo[n] = brojka;
            n++;
        }
        dfs1(0,0);
        //return 0;
        int pocetok = getpid();
        dfs(0, 0);

        char pocstr[1001];
        sprintf(pocstr,"%d",pocetok);
        //printf("%s\n",argv[0]);
        for (int i = 0; i < 100001; i++) {
            dlabocina[i] = 0;
        }
        char * arg[4];
        for (int i = 0; i < 4; i++) {
            arg[i] = malloc(sizeof(char) * 101);
            arg[i][0] = 0;
        }
        strcpy(arg[0],argv[0]);
        strcpy(arg[1],"-c");
        strcpy(arg[2],pocstr);
        int brok = 100;;
        char ase[20];
        sprintf(ase,"%d",brok);
        arg[3] = NULL;
        //printf("da\n");
        
        pid_t  ppd = fork();
        int status;
        //wait(NULL);
        if (ppd == 0) {
            //wait(NULL);
            //dfs(0,0);
            
            execvp("pstree",arg);
            //printf("da\n");
        //execlp("pstree","pstree","-c",pocstr,NULL);
        //pause();
        //kill(pocetok,SIGTERM);
        //printf("da\n");
       // sleep(20);
         //   kill(pocetok,SIGTERM);
            exit(0);
        
        } else {
            int kkk = 0;
            while (kkk < 51000000) {
                kkk++;
            }
           wait(&ppd);
            //wait(NULL);
            while (kkk < 80000000) 
            {
                kkk++;
            }
           exit(0);
        }
        //wait(NULL);
        sleep(2);
        return 0;
    }
    return 0;
}