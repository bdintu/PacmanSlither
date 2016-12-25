typedef struct {
    char menu;
    char cursor;
    char button;
    char buffer;
} CH;

typedef struct{
    char id[10];
    char name[64];
    unsigned int live;
    unsigned int score;
} PLAYER;

typedef struct {
    short x;
    short y;
    short x_old;
    short y_old;
    // Next is the only monster.
    char ch;
    short fg;
} OBJECT_POSTION;
