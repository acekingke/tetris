#include <iostream>
#include <ncurses.h>
#include <random>
#include <time.h>
 #include <unistd.h>
#include <fstream>
#include "game.hpp"

Game::Game(): is_over(false), key(0), x(WIDTH / 2), y(-3), shape(0), rotation(0) {
    srand(time(NULL));
    
}

void Game::run() {
    init();
    unsigned int microseconds = 50000;
    while (!this->over()) {
        speed_count++;
        input();
        update();
        draw();
        usleep(microseconds);
    }
    end();
}
void Game::draw() {
    // clear screen
    clear();
    mvprintw(0, 4, "Press 'q' to quit");
    static bool flag  = false;
    draw_board();
    draw_block(this->x, this->y, shape, this->rotation);
    // draw next block
    draw_next();
    // draw scores
    draw_score();
}

void Game::draw_board() {
    // draw a line
    mvprintw(BOARDY - 1, BOARDX - 1, "/");
    mvprintw(BOARDY + HEIGHT, BOARDX - 1, "\\");
    for (int i = 0; i < WIDTH; i++)
    {
        mvprintw(BOARDY - 1, BOARDX  + i, "-");
        mvprintw(BOARDY + HEIGHT, BOARDX + i, "-");
    }
    mvprintw(BOARDY - 1, BOARDX + WIDTH, "\\");
    mvprintw(BOARDY + HEIGHT, BOARDX + WIDTH, "/");
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(BOARDY + i, BOARDX - 1, "|");
        mvprintw(BOARDY + i, BOARDX + WIDTH, "|");
    }
    // draw board
    for (int py = 0; py < HEIGHT; py++) {
        for (int px = 0; px < WIDTH; px++) {
            if (board[px][py] == 'X') {
                mvprintw(BOARDY + py, BOARDX + px, "X");
            }
        }
    }
}
bool Game::fit_block(int x, int y, int shape, int rotation) {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            int pi = piece_index(px, py, rotation);
           if (shapes[shape][pi] == 'X') { 
                // if one not fits, return false
                // but it may be y + py < 0
                if (x + px < 0 || x + px >= WIDTH || y + py >= HEIGHT) {
                    return false;
                }
                if (y + py >= 0 && board[x + px][y + py] == 'X') {
                    return false;
                }
            }
        }
    }

    return true;
}
void Game::input() {
    // get input
    this->key = getch();
}
void Game::update() {
    if (this->key == 'q') {
       is_over = true;
    }
    shape = next_shape;
    bool is_force = (speed_count == SPEED);
    if (is_top()) {
        is_over = true;
    }
    switch (key) {
        case KEY_UP:
            if (fit_block(x, y, shape, (rotation + 1) % 4)) {
                rotation = (rotation + 1) % 4;
            }
            break;
        case KEY_LEFT:
            if (fit_block(x - 1, y, shape, rotation)) {
                
                x--;
            }
            //log("x is " + std::to_string(x) + " y is " + std::to_string(y) + " shape is " + std::to_string(shape) + " rotation is " + std::to_string(rotation));
            break;
        case KEY_RIGHT:

            if (fit_block(x + 1, y, shape, rotation)) {
                 x++;
            }
            break;
        case KEY_DOWN:
        //mvprintw(0, 0, "press down");
            if (fit_block(x, y + 1, shape, rotation)) {
                y++;
            }
            break;
        default:
           break;
    }
    if (speed_count == SPEED) { // force down
        if (fit_block(x, y + 1, shape, rotation)) {
                    y++;
        }
            
        speed_count = 0;
    }   
    fill_bottom(); // fill the bottom, if is_bottom is true
    clear_lines(); // clear lines
    this->key = 0;
    refresh();
}
void Game::init() {
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // set getch is non-blocking
    curs_set(0); // hide cursor
	start_color();
    use_default_colors();
    next_shape = rand() % 7;
}
void Game::end() {
     clear();
     mvprintw(1, 0, "Game is over");
     mvprintw(2, 0, "press any key to exit");
     refresh();
     nodelay(stdscr, FALSE);
     getch();
    // end game
    endwin();
}

bool Game::over() {
    // check if game is over
   
    return this->is_over;
}

int Game::piece_index(int px, int py, int rotation) {
    // rotate piece
    switch (rotation) {
        case 0:
            return py *4 + px; // no rotation
        case 1:
            return 12 + py - 4 * px; // 90 degree rotation
        case 2:
            return 15 - px - 4 * py; // 180 degree rotation
        case 3:
            return 3 - py + 4 * px; // 270 degree rotation
        default:
            return -1;
    }
    return 0;
}

void Game::draw_block(int x, int y, int shape, int rotation) {
    // draw block
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            int pi = piece_index(px, py, rotation);
            if (shapes[shape][pi] == 'X' && y + py >= 0) {
                mvprintw(BOARDY + y + py, BOARDX + x + px, "X");
            }
        }
    }
}
void Game::Test() {
    x = -2;
    y = 1;
    shape = 3;
    
    std::cout<<fit_block(x, y, shape, rotation)<<std::endl;
}

void Game::log(const std::string& message) {
     std::string filePath = "tetris.log";
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app );
     ofs << message << '\n';
     ofs.close();
}

bool Game::is_bottom() {
    return !fit_block(x, y + 1, shape, rotation);
}

void Game::fill_bottom() {
    if (is_bottom()) {
        for (int py = 0; py < 4; py++) {
            for (int px = 0; px < 4; px++) {
                int pi = piece_index(px, py, rotation);
                if (shapes[shape][pi] == 'X' && y + py >= 0) {
                    board[x + px][y + py] = 'X';
                }
            }
        }
        reset_xy();
        next_shape = rand() % 7;
    }
}

void Game::reset_xy() {
    x = WIDTH / 2;
    y = -3;
}

bool Game::is_top() {
    for (int px = 0; px < WIDTH; px++) {
        if (board[px][0] == 'X') {
            return true;
        }
    }
    return false;
}
void Game::clear_lines() {
    for (int py = 0; py < HEIGHT; py++) {
        bool is_full = true;
        for (int px = 0; px < WIDTH; px++) {
            if (board[px][py] != 'X') {
                is_full = false;
                break;
            }
        }
        if (is_full) {
            score += 1;
            for (int y = py; y > 0; y--) {
                for (int x = 0; x < WIDTH; x++) {
                    board[x][y] = board[x][y - 1];
                }
            }
        }
    }
}


void Game::draw_next() {
    // draw next block
    mvprintw(NEXTY -1 , NEXTX, "next block:");
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            int pi = piece_index(px, py, 0);
            if (shapes[shape][pi] == 'X') {     
                mvprintw(NEXTY + py, NEXTX + px, "X");
            }
        }
    }
}

void Game::draw_score() {
    // draw scores
    mvprintw(SCOREY , SCOREX, "score: %d",score);
    
}