
void drawSnake();
void drawField();
void appleTime();
int returnLastKeyInput();
void movement();
void updateTail();
void HighScore(int score);
void LeaderBoard();
void reset();
void MainMenu();

struct score {
	char name[32];
	int score;
	struct score* next;
};

#define WIDTH 30
#define HEIGHT 20


using namespace std;

extern int field[WIDTH][HEIGHT], x, y, tempx, head, tail, length, dir, ch, apple, applex, appley, difficulty, score, game;

