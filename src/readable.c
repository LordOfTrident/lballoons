/*
 *  lballoons - A terminal "screensaver" written in C
 *  Version 1.2.1
 *  Github: https://github.com/LordOfTrident/lballoons
 *
 *  This is the formatted source code NOT used by the
 *  makefile. If you want to see the "art" one, look
 *  at main.c
 */

#include <stdlib.h> // malloc, realloc, free, rand
#include <time.h> // usleep
#include <ncurses.h> // Terminal i/o
#include <stdbool.h> // bool, true, false

#define LB_VERSION_MAJOR 1
#define LB_VERSION_MINOR 2
#define LB_VERSION_PATCH 1

int usleep(unsigned p_uSeconds);

typedef struct {
	int x, y;
	char color;
} Balloon;

typedef struct {
	char ch, color;
} Pixel;

// Offset for the balloon lines so i
// dont need to draw spaces which may
// overlay other balloons and cut them
// off
const char offset[6] = {1, 0, 0, 1, 1, 1};
const char balloon_ascii[6][4] = {
	"_",
	"/#\\",
	"\\_/",
	"\\",
	"/",
	"\\"
};

Pixel *screen;
int screen_SizeX;
int screen_SizeY;
int screen_Size1D = 0;
int screen_Size1DPrevious;

Balloon *balloons;
int balloons_SizeX;
int balloons_SizeY;
int balloons_Size1D;
int balloons_SpawnPosition;

bool running;

void screen_WriteAt(
	const char *p_text,
	int p_posX,
	int p_posY,
	char p_color
) {
	if (p_posY < 0 || p_posY >= screen_SizeY)
		return;

	int pos = p_posY * screen_SizeX + p_posX;

	for (int i = 0; p_text[i] != 0; ++ i) {
		if (
			(p_posX + i) >= screen_SizeX ||
			(p_posX + i) < 0
		)
			break;

		screen[pos + i].ch = p_text[i];
		screen[pos + i].color = p_color;
	};
};

void balloon_Draw(const Balloon *p_balloon) {
	for (int i = 0; i < 6; ++ i) {
		screen_WriteAt(
			balloon_ascii[i],
			p_balloon->x + offset[i],
			p_balloon->y + i,
			i < 3? p_balloon->color : 1 // Color the balloon,
			                            // not the rope
		);
	};
};

void ballons_SetDefaults() {
	int x = 0, y = 0;
	for (int i = 0; i < balloons_Size1D; ++ i) {
		balloons[i].x = x * 6 + rand() % 4; // Offset the balloon position
		balloons[i].y = y * 7 + rand() % 4;
		balloons[i].color = rand() % 7 + 1;

		if (x >= balloons_SizeX) {
			x = 0;
			++ y;
		} else
			++ x;
	};
};

void balloons_Init() {
	balloons = (Balloon*)malloc(sizeof(Balloon) * balloons_Size1D);

	ballons_SetDefaults();
};

void screen_Init() {
	screen = (Pixel*)malloc(sizeof(Pixel) * screen_Size1D);

	for (int i = 0; i < screen_Size1D; ++ i) {
		screen[i].ch = ' ';
		screen[i].color = 1;
	};
};

void balloons_Refresh() {
	// I had alot of pain when using 2D arrays
	// and realloc, so it led to me switching
	// to 1D arrays which also turned out to
	// be a much better and easier fit
	void *temp = realloc(
		balloons,
		sizeof(Balloon) * balloons_Size1D
	);

	if (temp == NULL) {
		free(balloons);
		balloons_Init();
	} else {
		balloons = (Balloon*)temp;

		ballons_SetDefaults();
	};
};

void screen_Refresh() {
	void *temp = realloc(
		screen,
		sizeof(Pixel) * screen_Size1D
	);

	if (temp == NULL) {
		free(screen);
		screen_Init();
	} else {
		screen = (Pixel*)temp;

		if (screen_Size1DPrevious < screen_Size1D) {
			for (
				int i = screen_Size1DPrevious;
				i < screen_Size1D;
				++ i
			) {
				screen[i].ch = ' ';
				screen[i].color = 1;
			};
		};
	};
};

void screen_SetSize() {
	screen_SizeX = getmaxx(stdscr);
	screen_SizeY = getmaxy(stdscr);

	screen_Size1DPrevious = screen_Size1D;
	screen_Size1D = screen_SizeX * screen_SizeY;
};

void balloons_SetSize() {
	balloons_SizeX = screen_SizeX / 6;
	int balloons_TempSizeY = screen_SizeY / 7;
	balloons_SizeY = balloons_TempSizeY + 2;

	balloons_SpawnPosition = 7 * (balloons_TempSizeY + 1);
	balloons_Size1D = balloons_SizeY * (balloons_SizeX + 1);
};

void Init() {
	initscr();

	noecho();
	start_color();
	use_default_colors();
	curs_set(0); // Invisible cursor

	timeout(0); // Make getch not pause the program
	raw();
	cbreak(); // CTRL+C will exit the program, but
	          // the coded-in way is CTRL+Q

	init_pair(1, COLOR_WHITE,   COLOR_BLACK);
	init_pair(2, COLOR_BLUE,    COLOR_BLACK);
	init_pair(3, COLOR_RED,     COLOR_BLACK);
	init_pair(4, COLOR_GREEN,   COLOR_BLACK);
	init_pair(5, COLOR_YELLOW,  COLOR_BLACK);
	init_pair(6, COLOR_CYAN,    COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	screen_SetSize();
	screen_Init();

	balloons_SetSize();
	balloons_Init();
};

void Finish() {
	free(balloons);
	free(screen);

	endwin();
};

void Render() {
	move(0, 0);
	for (int i = 0; i < screen_Size1D; ++ i) {
		attron(COLOR_PAIR(screen[i].color));
		addch(screen[i].ch);
		attroff(COLOR_PAIR(screen[i].color));

		screen[i].ch = ' ';
		screen[i].color = 1;
	};

	refresh();
};

void Events() {
	int in = wgetch(stdscr);
	switch (in) {
	case KEY_RESIZE:
		screen_SetSize();
		screen_Refresh();

		balloons_SetSize();
		balloons_Refresh();

		break;

	case 'q' & 31:
		running = false;

		break;
	};
};

void MainLoop() {
	running = true;
	while (running) {
		int x = 0;
		for (int i = 0; i < balloons_Size1D; ++ i) {
			-- balloons[i].y;

			if (balloons[i].y < -6) {
				balloons[i].x = x * 6 + rand() % 4; // Re-randomize the X offset,
				                                    // not the Y offset
				balloons[i].y = balloons_SpawnPosition;
				balloons[i].color = rand() % 7 + 1;
			};

			balloon_Draw(&balloons[i]);

			if (x >= balloons_SizeX)
				x = 0;
			else
				++ x;
		};

		Render();
		Events();

		usleep(100000);
	};
};

int main(void) {
	Init();
	MainLoop();
	Finish();

	return 0;
};
