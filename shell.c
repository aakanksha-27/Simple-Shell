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

bool find_background(const char *command) {
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '&') {
            return true; 
        }
    }return false; 
}

int launch (char *command , int status) {
    if(command == "exit"){
        showHistory();
        printf("Shell ended");
        return 0;
    }
    else if(find_background(command)){
        
    }else{
        status = create_process_and_run(command,false);
        if(status == -1){
            perror("Error: ")
            return 1;
        }
    }
    return status;
}

void trimWhiteSpace(char *str){
    int len = strlen(str);
    int s = 0;
    int e = len - 1;

    while(isspace(str[s]) && s < len) s++;
    while(isspace(str[e]) && e >= 0) e--;

    char* st;
    int j = 0;
    for (int i = s; i <= e; i++){
        st[j++] = str[i];
    }
    st[j] = '\0';
    strcpy(str,st);
}

int main(){
    setupSignalHandler();
    shell_loop();
}
