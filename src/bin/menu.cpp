void menu(CH *ch){
    unsigned int row = 4;
    unsigned int menu_row[row] = {7, 9, 11, 13};
    char menu[row][10] = {"New Game", "Last 10", "Control", "Quit"};

    //Draw File
    cls();
    setcolor(LIGHTGREEN, 0);
    draw_file("menu.txt",0 ,0);

    setcolor(LIGHTMAGENTA, 0);
    draw_file("1.txt", X_GAME_START, Y_GAME_START);
    whitefood();

    //Write Menu
    setcolor(WHITE, 0);
    for(unsigned int i=0; i<row; i++){
        gotoxy( X_MENU_CENTER - strlen( menu[i] ) /2, menu_row[i]);
        printf("%s", menu[i]);
    }

    //Seek Cursor
    setcolor(RED, 0);
	gotoxy(X_MENU_CURSOR, menu_row[ch->cursor]);
	printf(">");

	ch->button = getch();
    switch( ch->button ){
        case 13:
            ch->menu = ch->cursor+1;
        break;
        case 'q':
            printf(" ");
            ch->cursor = ch->cursor = 3;
        break;
        case 'w':
            printf(" ");
            ch->cursor = (ch->cursor-1)%row;
        break;
        case 's':
            printf(" ");
            ch->cursor = (ch->cursor+1)%row;
        break;
    }


    gotoxy(X_MENU_CURSOR, menu_row[ch->cursor]);
    printf(">");
}

void draw_newgame(CH *ch){
    unsigned int num_menu = 2;
    unsigned int menu[num_menu] = {7, 11};
    unsigned int cursor[num_menu] = {9, 13};
    char txt_menu[num_menu][10] = {"ID", "Name"};

    clean(X_MENU_START, Y_MENU_START, X_MENU_END, Y_MENU_END);
    setcolor(WHITE, 0);

    for(unsigned int i=0; i<num_menu; i++){
        gotoxy( X_MENU_CENTER - strlen( txt_menu[i] ) /2, menu[i]);
        puts( txt_menu[i] );
    }

    hiddencursor(1);
    gotoxy(X_MENU_CURSOR, cursor[0]);
    gets(player.id);
    gotoxy(X_MENU_CURSOR, cursor[1]);
    gets(player.name);
    hiddencursor(0);

    ch->menu = 7;
}

void level(CH *ch){
    unsigned int row = 3;
    unsigned int menu_row[row] = {7, 9, 11};
    char menu[row][10] = {"Hard", "Normal", "Easy"};

    //Draw File
    cls();
    setcolor(LIGHTGREEN, 0);
    draw_file("menu.txt",0 ,0);

    setcolor(LIGHTMAGENTA, 0);
    draw_file("1.txt", X_GAME_START, Y_GAME_START);
    whitefood();

    //Write Menu
    setcolor(WHITE, 0);
    for(unsigned int i=0; i<row; i++){
        gotoxy( X_MENU_CENTER - strlen( menu[i] ) /2, menu_row[i]);
        printf("%s", menu[i]);
    }

    gotoxy(7, 14);
    printf("%d live.",player.live);

    //Seek Cursor
    setcolor(RED, 0);
	gotoxy(X_MENU_CURSOR, menu_row[ch->cursor]);
	printf(">");

	ch->button = getch();
    switch( ch->button ){
        case 13:
            ch->menu = 5;
        break;
        case 'q':
            printf(" ");
            ch->cursor = ch->cursor = 3;
        break;
        case 'w':
            printf(" ");
            player.live = (player.live-1)%4;
            ch->cursor = (ch->cursor-1)%row;
        break;
        case 's':
            printf(" ");
            player.live = (player.live+1)%4;
            ch->cursor = (ch->cursor+1)%row;
        break;
    }

    if(player.live==0) player.live = 1;


    gotoxy(X_MENU_CURSOR, menu_row[ch->cursor]);
    printf(">");
}

void draw_rank(CH *ch){
    clean(X_MENU_START, Y_MENU_START, X_MENU_END, Y_MENU_END);
    setcolor(WHITE, 0);
    gotoxy(X_MENU_CURSOR, 7);
    read_struct();

    gotoxy(2, 16);
    printf("Press any key to menu");
    ch->button = getch();
    ch->menu = 0;
}

void draw_control(CH *ch){
    clean(X_MENU_START, Y_MENU_START, X_MENU_END, Y_MENU_END);
    setcolor(WHITE, 0);
    draw_file("control.txt", 6, 5);

    gotoxy(2, 16);
    printf("Press any key to menu");
    ch->button = getch();
    ch->menu = 0;
}

void draw_quit(CH *ch){
    clean(X_MENU_START, Y_MENU_START, X_MENU_END, Y_MENU_END);
    setcolor(WHITE, 0);
    gotoxy(1, 10);
    ch->menu = 6;
}
