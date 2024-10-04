// Пример 2: Перемещение текста по экрану
#include <pdcurses.h>

int main() {
    initscr();
    keypad(stdscr, TRUE);           // Включение режима клавиатуры для работы со стрелками
    noecho();                       // Отключение отображения символов ввода
    curs_set(0);                    // Скрываем курсор

    int x = 10, y = 5;              // Начальная позиция текста
    mvprintw(y, x, "Move me!");     // Вывод начального текста
    refresh();

    int ch;
    while ((ch = getch()) != 'q') { // Нажатие 'q' завершает программу
        switch (ch) {
            case KEY_UP:
                y = (y > 0) ? y - 1 : y;
                break;
            case KEY_DOWN:
                y = (y < LINES - 1) ? y + 1 : y;
                break;
            case KEY_LEFT:
                x = (x > 0) ? x - 1 : x;
                break;
            case KEY_RIGHT:
                x = (x < COLS - 1) ? x + 1 : x;
                break;
        }
        clear();                    // Очистка экрана
        mvprintw(y, x, "Move me!"); // Перемещение текста
        refresh();
    }

    endwin();
    return 0;
}
