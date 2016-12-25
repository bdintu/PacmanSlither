int hit(OBJECT_POSTION object, char obj){

    if( getchar(object.x, object.y) == obj ){
        return obj;
    }

    return 0;
}

void warp(OBJECT_POSTION *object){
    if ( object->x==X_WARP_LEFT-1 && object->y==Y_WARP_LETT ){
        object->x = X_WARP_RIGHT;
    }else if( object->x==X_WARP_RIGHT+1 && object->y==Y_WARP_RIGHT ){
        object->x = X_WARP_LEFT;
    }
}

int set_pacman(OBJECT_POSTION *object){
    object->x = PACMAN_START_X;
    object->y = PACMAN_START_Y;
}

int set_monster(OBJECT_POSTION object[], int num){
    if(num==0){
        object[0].x = MONSTER_START_X;
        object[0].y = MONSTER_START_Y;
    }
    if(num==1){
        object[1].x = MONSTER_START_X-1;
        object[1].y = MONSTER_START_Y+2;
    }
    if(num==2){
        object[2].x = MONSTER_START_X;
        object[2].y = MONSTER_START_Y+2;
    }
    if(num==3){
        object[3].x = MONSTER_START_X+1;
        object[3].y = MONSTER_START_Y+2;
    }
}

void show_msg(char *msg){
    setcolor(WHITE, 0);
    gotoxy(X_MSG_START, Y_MSG);
    printf("%s",msg);
}

void show_scroe(PLAYER player){
    setcolor(RED, 0);
    gotoxy(X_SCORE, Y_SCORE);
    printf("%4d",player.score);
}

void show_live(PLAYER player){
    setcolor(RED, 0);
    gotoxy(X_LIVE, Y_LIVE);
    printf("%2d",player.live);
}

void rand_bigfood(int balance){
    if(balance < FOOD_LEN/4 ) return;
    int x, y;
    do{
        x = rand()% (X_GAME_END-X_GAME_START) + X_GAME_START;
        y = rand()% (Y_GAME_END-Y_GAME_START) + Y_GAME_START;
    } while( getchar(x, y) != FOOD );
    setcolor(BIGFOOD_COLOR, 0);
    gotoxy(x, y);
    printf("%c", BIGFOOD);
}

void draw_coin(){
    setcolor(COIN_COLOR, 0);
    gotoxy(X_COIN1, Y_COIN1);
    printf("%c", COIN);
    gotoxy(X_COIN2, Y_COIN2);
    printf("%c", COIN);
    gotoxy(X_COIN3, Y_COIN3);
    printf("%c", COIN);
    gotoxy(X_COIN4, Y_COIN4);
    printf("%c", COIN);
}

void draw_monster(OBJECT_POSTION *monster_pos, int iseat){
    gotoxy(monster_pos->x_old, monster_pos->y_old);
    setcolor(monster_pos->fg, 0);
    if(  !(monster_pos->ch == MONSTER)  )
        printf("%c", monster_pos->ch);

    //if(  !getchar(monster_pos->x, monster_pos->y)=='M'    ){
        monster_pos->ch = getchar(monster_pos->x, monster_pos->y);
        monster_pos->fg = getfgcolor(monster_pos->x, monster_pos->y);
    //}

    gotoxy( monster_pos->x, monster_pos->y );
    if(iseat)
        setcolor(MONSTER_EAT_COLOR, 0);
    else
        setcolor(MONSTER_COLOR, 0);
    printf("%c", MONSTER);
}

void *draw_pacman(void *arg){
    OBJECT_POSTION *pacman_pos;
    pacman_pos = (OBJECT_POSTION *) arg;

    pthread_mutex_lock( &mutex );
    gotoxy(pacman_pos->x_old, pacman_pos->y_old);
    printf(" ");
    setcolor(PACMAN_COLOR, 0);
    gotoxy(pacman_pos->x, pacman_pos->y);
    printf("P");
    pthread_mutex_unlock( &mutex );


    pthread_exit(NULL);

    /*while(1){

        pthread_mutex_lock( &mutex );

        gotoxy(pacman_pos->x, pacman_pos->y);
        printf("%c",pacman_anima[pacman_pos->movement]);
        Sleep(500);

        gotoxy(pacman_pos->x, pacman_pos->y);
        printf("=");
        Sleep(500);

        pthread_mutex_unlock( &mutex );

    }*/
}

void whitefood(){

    setcolor(FOOD_COLOR, BLACK);

    for(int y=2; y<=20; y++){
        for(int x=24; x<=47; x++){

            if( getchar(x, y) == FOOD ){
                gotoxy(x,y);
                printf("%c",FOOD);
            }

        }
    }

}

int lenfood(){

    int num = 0;


    for(int y=2; y<=20; y++){
        for(int x=24; x<=47; x++){

            if( getchar(x, y) == FOOD ){
                num++;
            }

        }
    }
    return num;

}
