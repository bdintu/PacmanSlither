#define DEBUG 0
#define BUG 1

#include <stdio.h>
#include <conio.h>
#include <direct.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#include "inc/cmd.h"
#include "inc/color.h"
#include "inc/struct.h"
#include "inc/1.h"

#include "lib/cmd.cpp"
#include "lib/setup.cpp"

#include "bin/file.cpp"
#include "bin/hit.cpp"
#include "bin/menu.cpp"
#include "bin/game.cpp"

int main(int argc, char *argv[]){

    setcmd();
    CH ch;
    ch.menu = 0;
    ch.cursor = 0;
    ch.button = '\0';
    ch.buffer = '\0';
    player.live = 1;

    while(1){
        srand( time( NULL ) );
        fflush(stdin);

        player.score = 0;

        switch( ch.menu ){
            case 0: menu(&ch);          break;
            case 1: draw_newgame(&ch);  break;
            case 7: level(&ch);         break;
            case 2: draw_rank(&ch);     break;
            case 3: draw_control(&ch);  break;
            case 4: draw_quit(&ch);     break;
            case 5: game_main(&ch);     break;
            case 6: return 0;           break;
        }
    }

    return 0;
}
