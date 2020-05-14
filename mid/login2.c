#include<time.h>
#include<signal.h>
#include<setjmp.h>
#include<ncurses.h>
#include<syslog.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#define TAB 9
#define ENT 0x0d
#define DEL 0x7f

#define BUFLEN_MAX 256

#define TRY_MAX 5

#define INIT_X (0)
#define INIT_Y (0)

#define ID_X (INIT_X + 10)
#define ID_Y (INIT_Y + 3)

#define PASSWORD_X (ID_X)
#define PASSWORD_Y (ID_Y + 1)

#define RESULT_X (0)
#define RESULT_Y (PASSWORD_Y + 2)

#define MODE_PASSWORD 1
#define MODE_ID 2

#define EXPIRE_TIME 30
#define BASIC_TIME 5

int g_remain;
int g_timer_param;

jmp_buf checkpoint;

int n_try = 0;

const char *userID = "dondon";
const char *userPWD = "dondon0107";

void sig_handler(int signum){
    if(signum != SIGALRM) exit(0);

    if(g_timer_param == EXPIRE_TIME){
        clear();
        move(INIT_Y, INIT_X);
        printw("TIMER EXPIRED...(%d seconds)", EXPIRE_TIME);
        refresh();
        getch();
        endwin();
        exit(0);
    }
    else if(g_timer_param == BASIC_TIME){
        g_timer_param = EXPIRE_TIME;
        g_remain -= BASIC_TIME;
        alarm(g_remain);
    }
    else{
        clear();
        move(0,0);
        printw("ILLEGAL PARAMETER...");
        refresh();
        getch();
        exit(0);
    }
}

void draw_interface(void){
    clear();
    move(INIT_Y, INIT_X);
    printw("#####################################");
    printw("\n############login program############");
    printw("\n#####################################");
    printw("\nID      : ");
    printw("\nPASSWORD: ");
    refresh();
}

int get_string(int mode, char* buf){
    
    int n, res;
    char ch;

    if(mode != MODE_PASSWORD && mode != MODE_ID) return -1;

    memset(buf, 0, BUFLEN_MAX);

    noecho();

    mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X) : move(ID_Y, ID_X);
    
    refresh();

    n = 0;
    while((res = read(0, &ch, 1))){
        if(res < 0) return -1;
        if(ch == ENT || ch == TAB) break;
        if(g_remain < BASIC_TIME){
            g_timer_param = EXPIRE_TIME;
            alarm(g_remain);
            g_remain = 0;
        }
        else{
            g_timer_param = BASIC_TIME;
            alarm(BASIC_TIME);
        }

        if(ch == DEL){
            if(n > 0){
                n--;
                mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);

                printw(" ");
                mode == MODE_PASSWORD ? move(PASSWORD_Y, PASSWORD_X + n) : move(ID_Y, ID_X + n);
                refresh();
            }
        }
        else{
            mode == MODE_PASSWORD ? printw("*") : printw("%c", ch);
            refresh();

            buf[n++] = ch;
            if(n >= BUFLEN_MAX) return -1;
        }
    }
    buf[n] = '\0';

    return n;
}

int checkuser(char *inid, char *inpwd){
    if(!strcmp(inid, userID) && !strcmp(inpwd, userPWD)) return 1;
    else {
        n_try++;
        longjmp(checkpoint, 1);
    }
}
int main(int argc, char** argv){

    if(setjmp(checkpoint) > 0){
        printw("hello");
        refresh();
    }
    
  //  int n_try;
    char buf_login[BUFLEN_MAX];
    char buf_password[BUFLEN_MAX];

    struct sigaction sa;


    initscr();
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_flags = 0;
    sa.sa_handler = sig_handler;
    sigfillset(&sa.sa_mask);

    sigaction(SIGALRM, &sa, NULL);

    g_remain = EXPIRE_TIME;
    g_timer_param = EXPIRE_TIME;

    alarm(0);
    alarm(EXPIRE_TIME);

  //  n_try = 0;
    while(n_try < TRY_MAX){
        draw_interface();
        if(get_string(MODE_ID, buf_login) <= 0) n_try++;
        else{
            if(get_string(MODE_PASSWORD, buf_password) <= 0) n_try++;
            else{
                //if(!strcmp(buf_login, userID) && !strcmp(buf_password, userPWD)) break;
                checkuser(buf_login, buf_password);
                //else n_try++;
            }
        }
    }

    clear();
    move(INIT_Y, INIT_X);
    n_try < TRY_MAX ? printw("LOGIN SUCCESS!\n") : printw("LOGIN FAILED...(You tried %d times)\n", n_try);
    
    refresh();
    getch();
    endwin();
    return 0;
}