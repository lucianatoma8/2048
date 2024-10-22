#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// functie care afiseaza aspectul vizual al jocului
void draw_board(int board[4][4]) {
    attron(COLOR_PAIR(1) | A_BOLD);
    printw(
        "                      ,---.           ,---.\n"
        "                    / /\"`.--\"\"\"\"\"\"\"-`\"\"\\ \\\n"
        "                    \\ \\    _       _    / /\n"
        "                     `./  / __   __ \\  \\,'\n"
        "                      /    /_O)_(_O\\    \\\n"
        "                      |  .-'  ___  `-.  |\n"
        "                   .--|       \\_/       |--.\n"
        "                 ,'    \\   \\   |   /   /    `.\n"
        "                /       `.  `--^--'  ,'       \\\n"
        "             .-\"\"\"\"\"-.    `--.___.--'     .-\"\"\"\"\"-.\n"
        ".-----------/         \\------------------/         "
        "\\--------------.\n"
        "| .---------\\         /----------------- \\         /------------. "
        "|\n"
        "| |          `-`--`--'                    `--'--'-'             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |                                                             | |\n"
        "| |_____________________________________________________________| |\n"
        "|_________________________________________________________________|\n"
        "                   )__________|__|__________\n"
        "                  |            ||            |\n"
        "                  |____________||____________|\n"
        "                    ),-----.(      ),-----.(\n"
        "                  ,'   ==.   \\    /  .==    `.\n"
        "                 /            )  (            \\\n"
        "                 `==========='    `==========='\n");
    attroff(COLOR_PAIR(1) | A_BOLD);

    int startx = 75, starty = 8, width = 8, height = 4, color_pair, i, j, x, y;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int box = board[i][j];
            // desenam marginile casutelor
            for (y = 0; y <= height; y++) {
                for (x = 0; x <= width; x++) {
                    if (y == 0 || y == height || x == 0 || x == width) {
                        mvaddch(starty + i * (height + 1) + y,
                                startx + j * (width + 1) + x, ACS_CKBOARD);
                    }
                }
            }
            
            if (box == 2)
                color_pair = 3;
            else if (box == 4)
                color_pair = 9;
            else if (box == 8)
                color_pair = 4;
            else if (box == 16)
                color_pair = 10;
            else if (box == 32)
                color_pair = 5;
            else if (box == 64)
                color_pair = 11;
            else if (box == 128)
                color_pair = 6;
            else if (box == 256)
                color_pair = 12;
            else if (box == 512)
                color_pair = 7;
            else if (box == 1024)
                color_pair = 13;
            else if (box == 2048)
                color_pair = 8;
            else
                color_pair = 1;

            // coloram si afisam valoarea din interiorul casutei
            if (box != 0) {
                attron(COLOR_PAIR(color_pair) | A_BOLD);
                // umplem interiorul casutei cu spatii
                // de aceea plecam de la 1, trecem peste boarder
                for (y = 1; y < height; y++) {
                    for (x = 1; x < width; x++) {
                        mvaddch(starty + i * (height + 1) + y,
                                startx + j * (width + 1) + x, ' ');
                    }
                }
                // convertim valoarea casutei intr-un sir de caractere
                // luam 4 + 1 pt terminatorul de sir
                char num_str[5];
                sprintf(num_str, "%d", box);
                int num_len = strlen(num_str);
                // calculam gap-urile pentru a centra numarul in casuta
                int gap_x = (width - num_len) / 2 + 1;
                int gap_y = height / 2;
                // afisam numarul in centrul casutei
                mvprintw(starty + i * (height + 1) + gap_y,
                         startx + j * (width + 1) + gap_x, "%s", num_str);
                attroff(COLOR_PAIR(color_pair) | A_BOLD);
            }
        }
    }
}

// functie care genereaza automat o casuta cu valoarea 2 sau 4
void add_random_box(int board[4][4]) {
    int i, j;
    do {
        i = rand() % 4;
        j = rand() % 4;
    } while (board[i][j] != 0);
    board[i][j] = (rand() % 2 == 0) ? 2 : 4;
}

// functie care initializeaza noul joc
void start_new_game(int board[4][4], int new, int* score) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    int i, j;
    // initializam jocul si tabla de joc
    if (new) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                board[i][j] = 0;
            }
        }
        srand(time(NULL));
        // adaugam doua numere aleatoare pe tabla
        add_random_box(board);
        add_random_box(board);
        // resetam scorul la 0 cand incepe un joc nou
        *score = 0;
    }
    draw_board(board);
}

// functie care afiseaza panoul de control
void display_control_panel(int score) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    attron(A_BOLD);
    mvprintw(13, 5, "Date: %02d.%02d.%04d", t->tm_mday, t->tm_mon + 1,
             t->tm_year + 1900);
    mvprintw(14, 5, "Time: %02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
    mvprintw(15, 5, "Score: %d", score);
    mvprintw(16, 5, "Commands: arrow keys to move");
    mvprintw(17, 15, "'q' to go to Menu");
    mvprintw(18, 15, "'u' to undo (once per move)");
    attroff(A_BOLD);
}

// functie care muta toate casutele in sus
int move_boxes_up(int board[4][4]) {
    int moved = 0, row, col;
    for (col = 0; col < 4; col++) {
        // incepem de sus, unde va fi mutata casuta
        int write_row = 0;
        for (row = 0; row < 4; row++) {
            // verificam daca exista vreo casuta in pozitia curenta
            if (board[row][col] != 0) {
                // ne asiguram ca putem muta casuta
                if (write_row != row) {
                    board[write_row][col] = board[row][col];
                    board[row][col] = 0;
                    moved = 1;
                }
                write_row++;
            }
        }
    }
    return moved;
}

// functie care muta toate casutele in jos
int move_boxes_down(int board[4][4]) {
    int moved = 0, row, col;
    for (col = 0; col < 4; col++) {
        // incepem de jos, unde va fi mutata casuta
        int write_row = 3;
        for (row = 3; row >= 0; row--) {
            // verificam daca exista vreo casuta in pozitia curenta
            if (board[row][col] != 0) {
                // ne asiguram ca putem muta casuta
                if (write_row != row) {
                    board[write_row][col] = board[row][col];
                    board[row][col] = 0;
                    moved = 1;
                }
                write_row--;
            }
        }
    }
    return moved;
}

// functie care muta toate casutele la stanga
int move_boxes_left(int board[4][4]) {
    int moved = 0, row, col;
    for (row = 0; row < 4; row++) {
        // incepem din stanga, unde va fi mutata casuta
        int write_col = 0;
        for (col = 0; col < 4; col++) {
            // verificam daca exista vreo casuta in pozitia curenta
            if (board[row][col] != 0) {
                // ne asiguram ca putem muta casuta
                if (write_col != col) {
                    board[row][write_col] = board[row][col];
                    board[row][col] = 0;
                    moved = 1;
                }
                write_col++;
            }
        }
    }
    return moved;
}

// functie care muta toate casutele la dreapta
int move_boxes_right(int board[4][4]) {
    int moved = 0, row, col;
    for (row = 0; row < 4; row++) {
        // incepem din dreapta, unde va fi mutata casuta
        int write_col = 3;
        for (col = 3; col >= 0; col--) {
            // verificam daca exista vreo casuta in pozitia curenta
            if (board[row][col] != 0) {
                // ne asiguram ca putem muta casuta
                if (write_col != col) {
                    board[row][write_col] = board[row][col];
                    board[row][col] = 0;
                    moved = 1;
                }
                write_col--;
            }
        }
    }
    return moved;
}

// functie care combina casutele identice cand se muta in sus
int combine_boxes_up(int board[4][4], int* score) {
    int combined = 0, row, col;
    for (col = 0; col < 4; col++) {
        // pornim de sus in jos
        for (row = 0; row < 3; row++) {
            if (board[row][col] != 0 &&
                board[row][col] == board[row + 1][col]) {
                board[row][col] *= 2;
                board[row + 1][col] = 0;
                *score += board[row][col];
                combined = 1;
                // trecem la casuta urmatoare pt a evita combinari multiple
                row++;
            }
        }
    }
    return combined;
}

// functie care combina casutele identice cand se muta in jos
int combine_boxes_down(int board[4][4], int* score) {
    int combined = 0, row, col;
    for (col = 0; col < 4; col++) {
        // pornim de jos in sus
        for (row = 3; row > 0; row--) {
            if (board[row][col] != 0 &&
                board[row][col] == board[row - 1][col]) {
                board[row][col] *= 2;
                board[row - 1][col] = 0;
                *score += board[row][col];
                combined = 1;
                // trecem la casuta urmatoare pt a evita combinari multiple
                row--;
            }
        }
    }
    return combined;
}

// functie care combina casutele identice cand se muta la stanga
int combine_boxes_left(int board[4][4], int* score) {
    int combined = 0, row, col;
    for (row = 0; row < 4; row++) {
        // pornim de la stanga la dreapta
        for (col = 0; col < 3; col++) {
            if (board[row][col] != 0 &&
                board[row][col] == board[row][col + 1]) {
                board[row][col] *= 2;
                board[row][col + 1] = 0;
                *score += board[row][col];
                combined = 1;
                // trecem la casuta urmatoare pt a evita combinari multiple
                col++;
            }
        }
    }
    return combined;
}

// functie care combina casutele identice cand se muta la dreapta
int combine_boxes_right(int board[4][4], int* score) {
    int combined = 0, row, col;
    for (row = 0; row < 4; row++) {
        // pornim de la dreapta la stanga
        for (col = 3; col > 0; col--) {
            if (board[row][col] != 0 &&
                board[row][col] == board[row][col - 1]) {
                board[row][col] *= 2;
                board[row][col - 1] = 0;
                *score += board[row][col];
                combined = 1;
                // trecem la casuta urmatoare pt a evita combinari multiple
                col--;
            }
        }
    }
    return combined;
}

// functie pt mutarea efectiva a casutelor in sus (mutare + combinare)
int moveup(int board[4][4], int* score) {
    int moved = move_boxes_up(board), combined = combine_boxes_up(board, score);
    // verificam daca a avut loc vreo mutare sau combinare
    if (moved || combined) {
        // executam o mutare suplimentara cand e nevoie
        moved += move_boxes_up(board);
        return 1;
    }
    return 0;
}

// functie pt mutarea efectiva a casutelor in jos (mutare + combinare)
int movedown(int board[4][4], int* score) {
    int moved = move_boxes_down(board),
        combined = combine_boxes_down(board, score);
    // verificam daca a avut loc vreo mutare sau combinare
    if (moved || combined) {
        // executam o mutare suplimentara cand e nevoie
        moved += move_boxes_down(board);
        return 1;
    }
    return 0;
}

// functie pt mutarea efectiva a casutelor la dreapta (mutare + combinare)
int moveright(int board[4][4], int* score) {
    int moved = move_boxes_right(board),
        combined = combine_boxes_right(board, score);
    // verificam daca a avut loc vreo mutare sau combinare
    if (moved || combined) {
        // executam o mutare suplimentara cand e nevoie
        moved += move_boxes_right(board);
        return 1;
    }
    return 0;
}

// functie pt mutarea efectiva a casutelor la stanga (mutare + combinare)
int moveleft(int board[4][4], int* score) {
    int moved = move_boxes_left(board),
        combined = combine_boxes_left(board, score);
    // verificam daca a avut loc vreo mutare sau combinare
    if (moved || combined) {
        // executam o mutare suplimentara cand e nevoie
        moved += move_boxes_left(board);
        return 1;
    }
    return 0;
}

// functie care verifica daca putem efectua mutari pe tabla
// daca exista casute libere sau exista 2 casute alaturate cu aceeasi valoare
int can_move(int board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] == 0) return 1;
            if (j < 3 && board[i][j] == board[i][j + 1]) return 1;
            if (i < 3 && board[i][j] == board[i + 1][j]) return 1;
        }
    }
    return 0;
}

// functie care calculeaza numarul casutelor libere
int count_free_cells(int board[4][4]) {
    int free_cells = 0, i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                free_cells++;
            }
        }
    }
    return free_cells;
}

// functie pentru mutarea automata a casutelor
int auto_move(int board[4][4]) {
    int best_move = -1, max_free_cells = -1, backup_board[4][4], backup_score,
        directions[4] = {0, 1, 2, 3}, i, j, k, confusing_position_up = 0,
        confusing_position_down = 0, confusing_position_left = 0,
        confusing_position_right = 0;
    // luam in considerare cazurile in care daca s-ar efectua anumite mutari,
    // tabla de joc ar ramane la fel, ca sa le putem evita mai apoi
    if ((board[0][0] != 0 && board[0][1] != 0 && board[0][0] != board[0][1]) ||
        (board[0][0] != 0 && board[0][2] != 0 && board[0][0] != board[0][2]) ||
        (board[0][0] != 0 && board[0][3] != 0 && board[0][0] != board[0][3]) ||
        (board[0][1] != 0 && board[0][2] != 0 && board[0][1] != board[0][2]) ||
        (board[0][1] != 0 && board[0][3] != 0 && board[0][1] != board[0][3]) ||
        (board[0][2] != 0 && board[0][3] != 0 && board[0][2] != board[0][3]) ||
        (board[0][0] != 0 && board[1][0] != 0 && board[0][0] != board[1][0]) ||
        (board[0][1] != 0 && board[1][1] != 0 && board[0][1] != board[1][1]) ||
        (board[0][2] != 0 && board[1][2] != 0 && board[0][2] != board[1][2]) ||
        (board[0][3] != 0 && board[1][3] != 0 && board[0][3] != board[1][3])) {
        confusing_position_up = 1;
    } else if ((board[3][0] != 0 && board[3][1] != 0 &&
                board[3][0] != board[3][1]) ||
               (board[3][0] != 0 && board[3][2] != 0 &&
                board[3][0] != board[3][2]) ||
               (board[3][0] != 0 && board[3][3] != 0 &&
                board[3][0] != board[3][3]) ||
               (board[3][1] != 0 && board[3][2] != 0 &&
                board[3][1] != board[3][2]) ||
               (board[3][1] != 0 && board[3][3] != 0 &&
                board[3][1] != board[3][3]) ||
               (board[3][2] != 0 && board[3][3] != 0 &&
                board[3][2] != board[3][3]) ||
               (board[3][0] != 0 && board[2][0] != 0 &&
                board[3][0] != board[2][0]) ||
               (board[3][1] != 0 && board[2][1] != 0 &&
                board[3][1] != board[2][1]) ||
               (board[3][2] != 0 && board[2][2] != 0 &&
                board[3][2] != board[2][2]) ||
               (board[3][3] != 0 && board[2][3] != 0 &&
                board[3][3] != board[2][3])) {
        confusing_position_down = 1;
    } else if ((board[0][0] != 0 && board[0][1] != 0 &&
                board[0][0] != board[0][1]) ||
               (board[1][0] != 0 && board[1][1] != 0 &&
                board[1][0] != board[1][1]) ||
               (board[2][0] != 0 && board[2][1] != 0 &&
                board[2][0] != board[2][1]) ||
               (board[3][0] != 0 && board[3][1] != 0 &&
                board[3][0] != board[3][1])) {
        confusing_position_left = 1;
    } else if ((board[0][2] != 0 && board[0][3] != 0 &&
                board[0][2] != board[0][3]) ||
               (board[1][2] != 0 && board[1][3] != 0 &&
                board[1][2] != board[1][3]) ||
               (board[2][2] != 0 && board[2][3] != 0 &&
                board[2][2] != board[2][3]) ||
               (board[3][2] != 0 && board[3][3] != 0 &&
                board[2][2] != board[3][3])) {
        confusing_position_right = 1;
    }
    // parcurgem fiecare directie posibila si
    // copiem tabla originala in cea de rezerva
    for (k = 0; k < 4; k++) {
        int direction = directions[k];
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                backup_board[i][j] = board[i][j];
            }
        }
        // am ales 0/1/2/3 pt sus/jos/stanga/dreapta
        // sarim peste cazurile in care casutele sunt asezate deja cat mai
        // in sus/jos sau la stanga/dreapta, ca sa nu se poata efectua o
        // miscare automata in sus/jos/stanga/dreapta in aceste cazuri
        switch (direction) {
            case 0:
                if (confusing_position_up == 1 && direction == 0) {
                    continue;
                }
                moveup(backup_board, &backup_score);
                break;
            case 1:
                if (confusing_position_down == 1 && direction == 1) {
                    continue;
                }
                movedown(backup_board, &backup_score);
                break;
            case 2:
                if (confusing_position_left == 1 && direction == 2) {
                    continue;
                }
                moveleft(backup_board, &backup_score);
                break;
            case 3:
                if (confusing_position_right == 1 && direction == 3) {
                    continue;
                }
                moveright(backup_board, &backup_score);
                break;
        }

        int free_cells = count_free_cells(backup_board);
        // mutarea aleasa va fi aceea care elibereaza cat mai multe casute
        if (free_cells > max_free_cells) {
            max_free_cells = free_cells;
            best_move = direction;
        }
    }
    // daca oricare ar fi directia, avem acelasi nr de casute libere,
    // alegem o diectie la intamplare
    if (best_move == -1) {
        best_move = directions[rand() % 4];
    }
    return best_move;
}

// functie care salveaza starea jocului pt resume
void copy_saved_board(int board[4][4], int saved_board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            saved_board[i][j] = board[i][j];
        }
    }
} 

// functie care salveaza starea jocului pt UNDO
void copy_undo_board(int board[4][4], int undo_board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            undo_board[i][j] = board[i][j];
        }
    }
} 

int main() {
    initscr();
    start_color();
    // initializam perechile de culori pt fundal, highlight si casute astfel:
    // 1 - fundal, 2 - '2', 3 - '8', 4 - '32', 5 - '128', 6 - '512', 7 - '2048'
    // 8 - highlight, 9 - '4', 10 - '16', 11 - '64', 12 - '256', 13 - '1024'
    init_color(1, 1000, 780, 820);
    init_color(2, 905, 625, 770);
    init_color(3, 900, 560, 675);
    init_color(4, 850, 445, 630);
    init_color(5, 785, 400, 510);
    init_color(6, 700, 265, 420);
    init_color(7, 625, 270, 460);
    init_color(8, 410, 160, 375);
    init_color(9, 830, 605, 800);
    init_color(10, 590, 470, 715);
    init_color(11, 525, 375, 555);
    init_color(12, 555, 270, 520);
    init_color(13, 345, 260, 485);

    init_pair(1, COLOR_BLACK, 1);
    init_pair(2, 1, 8);
    init_pair(3, COLOR_WHITE, 2);
    init_pair(4, COLOR_WHITE, 3);
    init_pair(5, COLOR_WHITE, 4);
    init_pair(6, COLOR_WHITE, 5);
    init_pair(7, COLOR_WHITE, 6);
    init_pair(8, COLOR_WHITE, 7);
    init_pair(9, COLOR_WHITE, 9);
    init_pair(10, COLOR_WHITE, 10);
    init_pair(11, COLOR_WHITE, 11);
    init_pair(12, COLOR_WHITE, 12);
    init_pair(13, COLOR_WHITE, 13);

    bkgd(COLOR_PAIR(1));
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    char* options[] = {"New Game", "Resume", "Quit"};
    int choice, highlight = 0, in_menu = 1, score = 0, saved_game = 0,
                game_over = 0, game_won = 0, board[4][4], saved_board[4][4],
                saved_score = 0, can_undo = 0, undo_board[4][4], undo_score = 0;

    while (1) {
        erase();
        if (in_menu) {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(0, 55,
                     "(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/"
                     ")(\\o/)(\\o/)");
            mvprintw(1, 55,
                     "(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/"
                     "|\\)(/|\\)");
            mvprintw(
                2, 55,
                "(\\o/)    ______     ____      _   _       _____   (\\o/)");
            mvprintw(3, 55,
                     "(/|\\)   (____  \\   / __ \\    / / / \\     /  _  \\  "
                     "(/|\\)");
            mvprintw(
                4, 55,
                "(\\o/)        ) /  ( (  ) )  ( (__) (___ (  (_)  ) (\\o/)");
            mvprintw(
                5, 55,
                "(/|\\)   __  / /   ( (  ) )   \\___   __(  \\  _  /  (/|\\)");
            mvprintw(
                6, 55,
                "(\\o/)  /  \\/ / __ ( (  ) )      ) (      / / \\ \\  (\\o/)");
            mvprintw(
                7, 55,
                "(/|\\) ( () \\__/ / ( (__) )      ) (     ( (___) ) (/|\\)");
            mvprintw(8, 55,
                     "(\\o/)  \\__\\____(   \\____/      /___\\     \\_____/  "
                     "(\\o/)");
            mvprintw(
                9, 55,
                "(/|\\)                                             (/|\\)");
            mvprintw(10, 55,
                     "(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/)(\\o/"
                     ")(\\o/)(\\o/)");
            mvprintw(11, 55,
                     "(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/|\\)(/"
                     "|\\)(/|\\)");

            mvprintw(15, 70, "  (¯`·.¸¸.·´¯`·.¸¸.·´¯)");
            mvprintw(16, 70, "  ( \\                 / )");
            mvprintw(17, 70, " ( \\ )               ( / )");
            mvprintw(18, 70, "( ) (                 ) ( )");
            mvprintw(19, 70, " ( / )               ( \\ )");
            mvprintw(20, 70, "  ( /                 \\ )");
            mvprintw(21, 70, "   (_.·´¯`·.¸¸.·´¯`·.¸_)");
            attroff(COLOR_PAIR(1) | A_BOLD);

            // afisam un highlight pe text pt a marca optiunea pe care o alegem
            int i;
            for (i = 0; i < 3; ++i) {
                if (i == highlight) {
                    attron(COLOR_PAIR(2) | A_BOLD);
                } else {
                    attron(COLOR_PAIR(1) | A_BOLD);
                }
                mvprintw(i + 17, 80, "%s", options[i]);
                attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | A_BOLD);
            }
            choice = getch();
            switch (choice) {
                case KEY_UP:
                    highlight = (highlight - 1 + 3) % 3;
                    break;
                case KEY_DOWN:
                    highlight = (highlight + 1) % 3;
                    break;
                case 10:
                    if (highlight == 0) {
                        // new game:
                        in_menu = 0;
                        start_new_game(board, 1, &score);
                        can_undo = 0;
                    } else if (highlight == 1) {
                        // resume:
                        if (saved_game) {
                            in_menu = 0;
                            // afisam tabla de joc in starea anterioara "q"/"Q"
                            copy_saved_board(board, saved_board);
                            score = saved_score;
                            start_new_game(board, 0, &score);
                            display_control_panel(score);
                            can_undo = 1;
                        }
                    } else if (highlight == 2) {
                        // quit:
                        endwin();
                        return 0;
                    }
                    break;
            }
        } else if (game_over) {
            // afisam mesajul corespunzator
            draw_board(board);
            display_control_panel(score);
            attron(COLOR_PAIR(2) | A_BOLD);
            mvprintw(21, 28, "GAME OVER");
            mvprintw(23, 6,
                     "Press 'n' for New Game, 'm' to go to Menu, 'q' to Quit");
            attroff(COLOR_PAIR(2) | A_BOLD);
            refresh();
            while (1) {
                choice = getch();
                switch (choice) {
                    case 'n':
                    case 'N':
                        // incepem un joc nou
                        game_won = 0;
                        game_over = 0;
                        in_menu = 0;
                        start_new_game(board, 1, &score);
                        break;
                    case 'm':
                    case 'M':
                        // revenim la meniu
                        game_won = 0;
                        game_over = 0;
                        in_menu = 1;
                        break;
                    case 'q':
                    case 'Q':
                        // iesim de tot din joc
                        endwin();
                        return 0;
                    case 'u':
                    case 'U':
                        // anulam mutarea facuta
                        if (can_undo) {
                            copy_undo_board(undo_board, board);
                            score = undo_score;
                            game_over = 0;
                            game_won = 0;
                            can_undo = 0;
                            clear();
                            draw_board(board);
                            display_control_panel(score);
                            break;
                        }
                }
                if (choice == 'n' || choice == 'N' || choice == 'm' ||
                    choice == 'M' || choice == 'q' || choice == 'Q' ||
                    choice == 'u' || choice == 'U') {
                    break;
                }
            }

        } else if (game_won) {
            // afisam mesajul corespunzator
            draw_board(board);
            display_control_panel(score);
            attron(COLOR_PAIR(2) | A_BOLD);
            mvprintw(21, 28, "YOU WON !!");
            mvprintw(23, 6,
                     "Press 'n' for New Game, 'm' to go to Menu, 'q' to Quit");
            attroff(COLOR_PAIR(2) | A_BOLD);
            refresh();
            while (1) {
                choice = getch();
                switch (choice) {
                    case 'n':
                    case 'N':
                        // incepem un joc nou
                        game_won = 0;
                        game_over = 0;
                        in_menu = 0;
                        start_new_game(board, 1, &score);
                        break;
                    case 'm':
                    case 'M':
                        // revenim la meniu
                        game_won = 0;
                        game_over = 0;
                        in_menu = 1;
                        break;
                    case 'q':
                    case 'Q':
                        // iesim de tot din joc
                        endwin();
                        return 0;
                    case 'u':
                    case 'U':
                        // anulam mutarea facuta
                        if (can_undo) {
                            copy_undo_board(undo_board, board);
                            score = undo_score;
                            game_over = 0;
                            game_won = 0;
                            can_undo = 0;
                            clear();
                            draw_board(board);
                            display_control_panel(score);
                            break;
                        }
                }
                if (choice == 'n' || choice == 'N' || choice == 'm' ||
                    choice == 'M' || choice == 'q' || choice == 'Q' ||
                    choice == 'u' || choice == 'U') {
                    break;
                }
            }
        } else {
            // optiuni posibile in timpul jocului:
            start_new_game(board, 0, &score);
            display_control_panel(score);
            timeout(15000);
            choice = getch();
            if (choice == 'q' || choice == 'Q') {
                // salvam starea jocului si revenim la meniu
                copy_saved_board(board, saved_board);
                saved_score = score;
                saved_game = 1;
                can_undo = 1;
                in_menu = 1;
            } else if (can_undo && (choice == 'u' || choice == 'U')) {
                // anulam mutarea facuta
                copy_undo_board(undo_board, board);
                score = undo_score;
                clear();
                draw_board(board);
                game_over = 0;
                can_undo = 0;
            } else if (choice == ERR) {
                // daca nu s-a apasat nicio tasta timp de 15s, mutam
                // automat casutele
                int auto_direction = auto_move(board);
                copy_undo_board(board, undo_board);
                undo_score = score;
                can_undo = 1;
                switch (auto_direction) {
                    case 0:
                        moveup(board, &score);
                        break;
                    case 1:
                        movedown(board, &score);
                        break;
                    case 2:
                        moveleft(board, &score);
                        break;
                    case 3:
                        moveright(board, &score);
                        break;
                }
                add_random_box(board);
                erase();
                draw_board(board);
                display_control_panel(score);
                // verificam daca jocul a fost pierdut / castigat
                // daca da, jocul se termina
                if (!can_move(board)) {
                    game_over = 1;
                }
                int i, j;
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        if (board[i][j] == 2048) {
                            game_won = 1;
                            break;
                        }
                    }
                    if (game_won) {
                        break;
                    }
                }
            } else {
                // in joc:
                copy_undo_board(board, undo_board);
                undo_score = score;
                switch (choice) {
                    // dupa fiecare mutare, salvam tabla de joc si permitem
                    // optiunea de undo
                    case KEY_UP:
                        copy_saved_board(board, saved_board);
                        saved_score = score;
                        if (moveup(board, &score)) {
                            add_random_box(board);
                            can_undo = 1;
                        }
                        break;
                    case KEY_DOWN:
                        copy_saved_board(board, saved_board);
                        saved_score = score;
                        if (movedown(board, &score)) {
                            add_random_box(board);
                            can_undo = 1;
                        }
                        break;
                    case KEY_LEFT:
                        copy_saved_board(board, saved_board);
                        saved_score = score;
                        if (moveleft(board, &score)) {
                            add_random_box(board);
                            can_undo = 1;
                        }
                        break;
                    case KEY_RIGHT:
                        copy_saved_board(board, saved_board);
                        saved_score = score;
                        if (moveright(board, &score)) {
                            add_random_box(board);
                            can_undo = 1;
                        }
                        break;
                }
                if (!can_move(board) && !game_over) {
                    // atunci, jocul e pierdut, afisam mesajul corespunzator
                    draw_board(board);
                    display_control_panel(score);
                    attron(COLOR_PAIR(2) | A_BOLD);
                    mvprintw(21, 28, "GAME OVER");
                    mvprintw(23, 6,
                             "Press 'n' for New Game, 'm' to go to Menu, 'q' "
                             "to Quit");
                    attroff(COLOR_PAIR(2) | A_BOLD);
                    refresh();
                    game_over = 1;
                    saved_game = 0;
                }
                // daca se ajunge la valoarea 2048, jocul e castigat,
                // afisam mesajul corespunzator
                int i, j;
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        if (board[i][j] == 2048) {
                            draw_board(board);
                            display_control_panel(score);
                            attron(COLOR_PAIR(2) | A_BOLD);
                            mvprintw(21, 28, "YOU WON !!");
                            mvprintw(23, 6,
                                     "Press 'n' for New Game, 'm' to go to "
                                     "Menu, 'q' to Quit");
                            attroff(COLOR_PAIR(2) | A_BOLD);
                            refresh();
                            game_won = 1;
                            saved_game = 0;
                        }
                    }
                }
            }
        }
    }
    endwin();
    return 0;
}