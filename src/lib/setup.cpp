void setcmd(){
    SetConsoleCP(DECODE);
    SetConsoleOutputCP(DECODE);
    setconsolesize(CONSOLE_SIZE_X, CONSOLE_SIZE_Y);
    setfont(FONT_SIZE_X, FONT_SIZE_Y);
    hiddencursor(0);
    removescrollbar();
}
