PLAYER player;

int draw_file(char const *file, int x, int y){
    char path[256];
    char buffer[256];
    FILE *p;

    strcpy( path, getdir() );
    strcat( path, "map/");
    strcat( path, file);

    p = fopen(path, "r");
    if(!p){
        gotoxy( 0, Y_ERROR );
        printf("%s, %s\n", path, strerror(errno));
        return -1;
    }

    while(fgets(buffer, 256, (FILE*)p)){
        gotoxy(x,y++);
        printf("%s", buffer);
    }

    if(fclose(p)){
        gotoxy( 0, Y_ERROR );
        printf("%s\n", strerror(errno));
        return -1;
    }

    return 0;
}

int read_struct(){
    char path[256];
    PLAYER player;
    FILE *p;

    strcpy( path, getdir() );
    strcat( path, "save.bin");

    p = fopen(path,"rb");
    if (!p){
        gotoxy( 0, Y_ERROR );
        printf("%s, %s\n", path, strerror(errno));
        return -1;
    }

    int line = 5;
    gotoxy(X_MENU_CURSOR, line++);
    printf("   ID    score");
    while(fread(&player, sizeof(PLAYER), 1, p)){
        gotoxy(X_MENU_CURSOR, line++);
        printf("%08s %4d\n", player.id, player.score);
        if(line==17){
            break;
        }
    }

    if(fclose(p)){
        gotoxy( 0, Y_ERROR );
        printf("%s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int write_struct(PLAYER player){
    char path[256];
    FILE *p;

    strcpy( path, getdir() );
    strcat( path, "save.bin");

    p = fopen(path,"ab");
    if (!p){
        gotoxy( 0, Y_ERROR );
        printf("%s, %s\n", path, strerror(errno));
        return -1;
    }

    /*while(fread(&buffer, sizeof(PLAYER), 1, p)){
        if( buffer.player >= player.player){
            break;
        }
    }*/

    fwrite(&player, sizeof(PLAYER), 1, p);

    if(fclose(p)){
        gotoxy( 0, Y_ERROR );
        printf("%s\n", strerror(errno));
        return -1;
    }
    return 0;
}
