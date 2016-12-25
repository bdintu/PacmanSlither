const char *getdir() {
    char cur_part[PART_LENGHT];
    _getcwd(cur_part, sizeof(cur_part));
    cur_part[sizeof(cur_part) - 1] = '\0';

    char *cpy = (char *)malloc(PART_LENGHT);
    strcpy(cpy, cur_part);
	strcat(cpy, "\\");
    return cpy;
}

char getchar(short x, short y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2];
	COORD c = {x, y};
	DWORD num_read;
	if( !ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0];
}

short getfgcolor(short x, short y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD buf[2]; COORD c = {x,y}; DWORD num_read;
	if( !ReadConsoleOutputAttribute(hStd,(LPWORD)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0]%16;
}

short getbgcolor(short x, short y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD buf[2]; COORD c = {x,y}; DWORD num_read;
	if( !ReadConsoleOutputAttribute(hStd,(LPWORD)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0]/16;
}

void gotoxy(short x, short y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(short fg, short bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16 + fg);
}

void setconsolesize(short x, short y){
	SMALL_RECT r = {0, 0, x, y};
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);
}

void setfont(short x, short y){
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize       = sizeof(info);
	info.dwFontSize.X = x;
	info.dwFontSize.Y = y;
	info.FontWeight   = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

void hiddencursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void removescrollbar(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO infox;
	GetConsoleScreenBufferInfo(handle, &infox);
	COORD new_size = {
		infox.srWindow.Right - infox.srWindow.Left + 1,
		infox.srWindow.Bottom - infox.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void cls(){
    system("cls");
}

void clean(int x1, int y1, int x2, int y2){
    setcolor(WHITE, BLACK);

    for(int y=y1; y<=y2; y++){
        for(int x=x1; x<=x2; x++){
            gotoxy(x,y);
            printf(" ");
        }
    }

    gotoxy(x1, y1);
}
