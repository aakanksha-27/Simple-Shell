#include shell.h

static void my_handler(int signum) {
    static int counter = 0;
    if (signum == SIGINT) {
        char buff1[23] = "\nCaught SIGINT signal\n";
        write(STDOUT_FILENO, buff1, 23);
        if (counter++ == 1) {
            char buff2[20] = "Cannot handle more\n";
            write(STDOUT_FILENO, buff2, 20);
            exit(0);
        }
    }
}

void setupSignalHandler(){
    struct sigaction sig;
    memset(&sig, 0, sizeof(sig));
    sig.sa_handler = my_handler;

    sigaction(SIGINT, &sig, NULL);
}

void shell_loop() {
     int status;
     char input[MAX_SIZE];
     do {
         printf("group_48@aakanksha_palak:~$ ");
         read_user_input();
         char* pipe_ptr = find_pipe(input);

         if (pipe_ptr != NULL) {
            status = pipe_command(input);
         } else {
            status = launch(input,status);
        }
     } while(status);
 }

void read_user_input() {
    if (fgets(input,MAX_SIZE, stdin) != NULL) {
        int length = strlen(input);
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }
    }else{
         perror("Error: ");
         exit(1);
    }
}

char* find_pipe(char input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '|') {
            return (char* )&input[i];
        }
    }
    return NULL;
}

int main(){
    setupSignalHandler();
    shell_loop();
}
