// Пример 3: Простейшая анимация
#include <pdcurses.h>
#include <unistd.h> // Для usleep()

int main() {
    initscr();
    noecho();
    curs_set(FALSE);                 // Скрываем курсор

    int x = 0;                       // Начальная координата по X
    for (int i = 0; i < COLS; ++i) { // Движение по горизонтали
        clear();                     // Очистка экрана
        mvprintw(5, x++, "O");       // Рисуем символ
        refresh();
        usleep(50000);               // Задержка в 50 мс
    }

    getch();
    endwin();
    return 0;
}
