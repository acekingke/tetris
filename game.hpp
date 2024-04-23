#ifndef GAME_HPP
#define GAME_HPP
#define DEBUG 
const int WIDTH = 12;
const int HEIGHT = 18;
// board origin (0, 0) is at the top left (4,2)
const int BOARDX = 4;
const int BOARDY = 3;
const int NEXTX = BOARDX + WIDTH + 4;
const int NEXTY = BOARDY;
const int SCOREX = BOARDX + WIDTH + 4;
const int SCOREY = BOARDY + 4;
const int SPEED = 20;

class Game {
    public:
        Game();
        void run();
        void Test();
    private:
        void draw();
        void input();
        void update();
        void init();
        bool over();
        void end();
        int piece_index(int px, int py, int rotation);
        void draw_block(int x, int y, int shape, int rotation);
        bool fit_block(int x, int y, int shape, int rotation);
        void draw_board();
        void log(const std::string& message);
        bool is_bottom();
        void fill_bottom();
        void reset_xy();
        bool is_top();
        void clear_lines();
        void draw_next();
        void draw_score();
    private:
        bool is_over;
        int key;
        int board[WIDTH][HEIGHT];
        int x, y;
        int shape;
        int next_shape;
        int rotation;
        int speed_count;
        // score
        int score;

        const char* const shapes[7] = {
            "..X."
            "..X."
            "..X."
            "..X.", // I
            "..X."
            ".XX."
            "..X."
            "....",// T
            "....."
            "XX.."
            "XX.."
            "...", // O
            "..X."
            ".XX."
            ".X.."
            "....", // Z
            ".X.."
            ".XX."
            "..X."
            "....",// S
            ".X.."
            ".X.."
            ".XX."
            "....", // L
            "..X."
            "..X."
            ".XX."
            "...." // J
        };

};  // class Game
#endif