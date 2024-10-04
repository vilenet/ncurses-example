// Пример 4: Работа с цветами
#include <pdcurses.h>

int main() {
    initscr();
    start_color();                   // Включаем поддержку цветов

    if (!has_colors()) {             // Проверка поддержки цветов
        endwin();
        printf("Your terminal does not support colors\n");
        return 1;
    }

    // Определяем цветовые пары
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(1, 1, "Red Text");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(2, 1, "Green Text");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    mvprintw(3, 1, "Blue Text");
    attroff(COLOR_PAIR(3));

    refresh();
    getch();
    endwin();
    return 0;
}
