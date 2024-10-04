// Пример 1: Простой вывод текста в центр окна
#include <pdcurses.h>

int main() {
    initscr();                      // Инициализация PDCurses
    int row, col;
    getmaxyx(stdscr, row, col);     // Получаем размер экрана (строки и колонки)

    // Печатаем текст в центре экрана
    mvprintw(row / 2, (col - 20) / 2, "Hello, PDCurses World!");
    refresh();                      // Обновляем экран для отображения текста

    getch();                        // Ожидаем нажатия клавиши
    endwin();                       // Завершаем работу с PDCurses
    return 0;
}
