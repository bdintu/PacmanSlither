OBJECT_POSTION pacman_pos, monster_pos[4];

void game_main(CH *ch){
    clean(X_MENU_START, Y_MENU_START, X_MENU_END, Y_MENU_END);
    setcolor(WHITE, 0);

    char id[255];
    strcpy(id,"ID: ");
    strcat(id, player.id);

    char name[255];
    strcpy(name,"Name: ");
    strcat(name, player.name);

    gotoxy( X_MENU_CENTER - strlen( id ) /2, 5);
    puts( id );
    gotoxy( X_MENU_CENTER - strlen( name ) /2, 7);
    puts( name );

    setcolor(FOOD_COLOR, 0);
    gotoxy( X_MENU_CENTER - strlen( name ) /2, 9);
    puts(". 10P");
    setcolor(BIGFOOD_COLOR, 0);
    gotoxy( X_MENU_CENTER - strlen( name ) /2, 10);
    puts("$ 100P (RANDOM)");
    gotoxy( X_MENU_CENTER - strlen( name ) /2, 11);
    setcolor(MONSTER_EAT_COLOR, 0);
    puts("M 200P (DOUBLE)");
    setcolor(MONSTER_COLOR, 0);
    gotoxy( X_MENU_CENTER - strlen( name ) /2, 12);
    puts("M DEAD!");

    pthread_t thread_pacman, thread_monster;
    pthread_attr_t attr;
    pthread_mutex_init( &mutex, NULL );
    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE);

    unsigned int len_food = 0;
    unsigned int show_msg_time = 0;
    unsigned int ran, ran_old;
    char ispause = 0;
    char iseat = 0;
    unsigned int eat_time = 0;
    ch->buffer = 'a';

    clean(X_GAME_START, Y_GAME_START, X_GAME_END, Y_GAME_END);
    setcolor(LIGHTMAGENTA, 0);
    draw_file("1.txt", X_GAME_START, Y_GAME_START);

    for(unsigned int i=0; i<MONSTER_LEN; i++) rand_bigfood(FOOD_LEN);
    draw_coin();
    show_scroe(player);
    show_live(player);

    set_pacman(&pacman_pos);
    for(unsigned int i=0; i<MONSTER_LEN; i++) set_monster(monster_pos, i);
    show_msg("READY");
    show_msg_time = 10;
    whitefood();

    while(1){

        //Input key

        if( kbhit() ){
            ispause = ch->button;
            ch->buffer = '\0';
        }

        if( ch->buffer == '\0'){
            ch->button = getch();
            ch->buffer = ch->button;
        }

        //monster direct

        pacman_pos.x_old = pacman_pos.x;
        pacman_pos.y_old = pacman_pos.y;

        for(unsigned int i=0; i<MONSTER_LEN; i++){
            monster_pos[i].x_old = monster_pos[i].x;
            monster_pos[i].y_old = monster_pos[i].y;

            do{
                ran_old = ran;
                ran = rand()%4;

                monster_pos[i].x = monster_pos[i].x_old;
                monster_pos[i].y = monster_pos[i].y_old;

                switch( ran ){
                    case 0: monster_pos[i].y--;    break;
                    case 1: monster_pos[i].y++;    break;
                    case 2: monster_pos[i].x--;    break;
                    case 3: monster_pos[i].x++;    break;
                }

            }while ( hit( monster_pos[i], WALL ) );

        }

        switch( ch->button ){
            case 'q':
                write_struct(player);
                player.live = 1;
                show_msg("Quit?");
                Sleep(1000);
                ch->menu = 0;
                return;
            break;
            case 'p':
                show_msg("Pause");
                ch->button = '\0';
                while(ch->button != 'p'){
                    ch->button = getch();
                }
                ch->button = ispause;
                clean(X_MSG_START, Y_MSG, X_MSG_END, Y_MSG);
            break;
        }

        switch( ch->buffer ){
            case 'w':
                pacman_pos.y--;
            break;
            case 's':
                pacman_pos.y++;
            break;
            case 'a':
                pacman_pos.x--;
            break;
            case 'd':
                pacman_pos.x++;
            break;
        }

        //hit monster

        for(unsigned int i=0; i<MONSTER_LEN; i++){
            if(  hit( monster_pos[i], PACMAN )
                //far 1 point
                || (int)sqrt(  (int)pow(pacman_pos.x - monster_pos[i].x, 2)  + (int)pow(pacman_pos.y - monster_pos[i].y, 2) ) == 0
                && ( (pacman_pos.x == monster_pos[i].x) || (pacman_pos.y == monster_pos[i].y) )
            ){
                if(iseat==1){
                    set_monster(monster_pos, i);
                    player.score += 200;
                    show_msg("YEH!!");
                    show_msg_time = 10;
                    Sleep(1000);
                }else{
                    player.live--;
                    show_live(player);
                    for(unsigned int i=0; i<MONSTER_LEN; i++) set_monster(monster_pos, i);
                    set_pacman(&pacman_pos);
                    show_msg("READY");
                    show_msg_time = 10;
                    Sleep(1000);
                    break;
                }

            }
        }

        //MONSTER
        for(unsigned int i=0; i<MONSTER_LEN; i++){
            if ( hit( monster_pos[i], WALL ) ){
                monster_pos[i].x = monster_pos[i].x_old;
                monster_pos[i].y = monster_pos[i].y_old;
            }
        }

        //PACMAN
        if( hit( pacman_pos, FOOD ) ){
            pthread_mutex_lock( &mutex );
            len_food++;
            pthread_mutex_unlock( &mutex );
            player.score += SCORE_FOOD;
        }

        if( hit( pacman_pos, COIN ) ){
            iseat = 1;
            eat_time = 30;
            #if DEBUG
            eat_time = 65535;
            #endif
        }

        if(iseat && eat_time==1){
            iseat = 0;
            eat_time = 0;
        }

        if( hit( pacman_pos, BIGFOOD ) ){
            rand_bigfood(FOOD_LEN-len_food);
            player.score += SCORE_BIGFOOD;
        }

        if ( hit( pacman_pos, WALL ) ){
            pacman_pos.x = pacman_pos.x_old;
            pacman_pos.y = pacman_pos.y_old;
        }

        if(len_food == FOOD_LEN){
            show_msg("WIN!!");
            write_struct(player);
            player.live = 1;
            Sleep(1000);
            ch->menu = 0;
            return;
        }
        #if BUG
        if(len_food > 130 && !lenfood()){
            show_msg("WIN!!");
            write_struct(player);
            player.live = 1;
            Sleep(1000);
            ch->menu = 0;
            return;
        }
        #endif

        if(player.live == 0){
            show_msg("LOSE!");
            write_struct(player);
            player.live = 1;
            Sleep(1000);
            ch->menu = 0;
            return;
        }

        //WARP
        warp(&pacman_pos);
        for(unsigned int i=0; i<MONSTER_LEN; i++)    warp(&monster_pos[i]);

        //Draw Obj

        pthread_create(&thread_pacman, &attr, draw_pacman, (void *)&pacman_pos);
        //START MUTEX
        pthread_mutex_lock( &mutex );

        for(unsigned int i=0; i<MONSTER_LEN; i++)    draw_monster(&monster_pos[i], iseat);
        show_scroe(player);

        #if DEBUG
        gotoxy(30,23);
        printf("%4d",len_food);
        #endif

        //Del MSG
        show_msg_time--;
        eat_time--;
        if(show_msg_time == 1){
            show_msg_time = 0;
            show_msg("     ");
        }

        pthread_mutex_unlock( &mutex );
        //END MUTEX

        srand( time( NULL ) );
        Sleep(200);
    }

    pthread_mutex_destroy( &mutex );
    pthread_attr_destroy( &attr);
    pthread_exit(NULL);
}
