// Пример 7: Множественные окна и взаимодействие с ними
#include <pdcurses.h>

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);          // Включение режима работы с клавишами
    curs_set(0);                   // Скрываем курсор

    // Создаем два окна размером 10x30 с разными позициями
    WINDOW* win1 = newwin(10, 30, 5, 5);
    WINDOW* win2 = newwin(10, 30, 5, 40);

    box(win1, 0, 0);               // Рисуем рамку в первом окне
    box(win2, 0, 0);               // Рисуем рамку во втором окне
    mvwprintw(win1, 1, 1, "Window 1 Active"); // Текст для первого окна
    mvwprintw(win2, 1, 1, "Window 2");        // Текст для второго окна
    wrefresh(win1);                // Обновляем оба окна
    wrefresh(win2);

    WINDOW* active_win = win1;     // Начально активное окно — win1
    int ch;
    while ((ch = getch()) != 'q') { // Завершение по нажатию 'q'
        if (ch == 9) {             // Если нажата клавиша TAB
            if (active_win == win1) {
                active_win = win2; // Переключение на второе окно
                mvwprintw(win1, 1, 1, "Window 1");
                mvwprintw(win2, 1, 1, "Window 2 Active");
            } else {
                active_win = win1; // Переключение на первое окно
                mvwprintw(win1, 1, 1, "Window 1 Active");
                mvwprintw(win2, 1, 1, "Window 2");
            }
        }
        // Обновляем оба окна после изменения текста
        wrefresh(win1);
        wrefresh(win2);
    }

    // Завершение работы с окнами и PDCurses
    delwin(win1);
    delwin(win2);
    endwin();
    return 0;
}
