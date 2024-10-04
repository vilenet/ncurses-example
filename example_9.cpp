// Пример 9: Простая таблица с вводом данных
#include <pdcurses.h>
#include <sstream>
#include <string>

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int table[3][3] = {0};       // Таблица 3x3
    int x = 1, y = 1;            // Текущие координаты ячейки
    int ch;
    std::string input = "";      // Строка для ввода чисел

    mvprintw(0, 0, "Simple Table Editor (Use arrows to navigate, Enter to edit, q to quit)");
    refresh();

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_LEFT:
                if (x > 0) x--;
                break;
            case KEY_RIGHT:
                if (x < 2) x++;
                break;
            case KEY_UP:
                if (y > 0) y--;
                break;
            case KEY_DOWN:
                if (y < 2) y++;
                break;
            case 10: // Enter для редактирования ячейки
                move(2 + y * 2, 4 + x * 4); // Переход на нужную ячейку
                echo();
                input = "";
                char c;
                while ((c = getch()) != 10) {
                    if (isdigit(c)) {
                        input += c;
                        printw("%c", c);
                    }
                }
                noecho();
                table[y][x] = std::stoi(input); // Преобразование строки в число
                break;
        }
        clear();
        mvprintw(0, 0, "Simple Table Editor (Use arrows to navigate, Enter to edit, q to quit)");

        // Отображение таблицы
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mvprintw(2 + i * 2, 4 + j * 4, "%d", table[i][j]);
            }
        }
        move(2 + y * 2, 4 + x * 4); // Перемещение курсора в активную ячейку
        refresh();
    }

    endwin();
    return 0;
}
