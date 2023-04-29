#include "./../include/testprogram.h" 

int waitexample1() {
    pid_t cpid;
    
    if (fork()== 0)
        exit(0);           
    else
        cpid = wait(NULL); 

    
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);

    return 0;
}

int waitexample2() {
    int stat;
 
    // This status 1 is reported by WEXITSTATUS
    if(fork() == 0) {
        puts("child");
        exit(1);
    } else {
        wait(&stat);
        puts("parent");
    }

    if(WIFEXITED(stat))
        printf("Exit status: %d\n", WEXITSTATUS(stat));
    else if (WIFSIGNALED(stat))
        psignal(WTERMSIG(stat), "Exit signal");

    return 0;
}

int waitexample3() {
    int i, stat;
    pid_t pid[5];
    
    for(i=0; i<5; i++) {
        if((pid[i] = fork()) == 0) {
            sleep(1);
            exit(100 + i);
        }
    }

    // Using waitpid() and printing exit status
    // of children.
    for(i=0; i<5; i++) {
        pid_t cpid = waitpid(pid[i], &stat, 0);
        if(WIFEXITED(stat))
            printf("Child %d terminated with status: %d\n",
                cpid, WEXITSTATUS(stat));
    }

    return 0;
}

int test_wait() {
    //waitexample1();
    waitexample2();
    //waitexample3();
    return 0;
}