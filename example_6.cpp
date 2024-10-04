// Пример 6: Простейшее меню
#include <pdcurses.h>

int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);

    const char* options[] = { "Option 1", "Option 2", "Option 3", "Exit" };
    int highlight = 0;                // Индекс выделенного элемента
    int choice;

    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == highlight) {
                attron(A_REVERSE);    // Включаем обратное отображение цвета для выделенного элемента
            }
            mvprintw(2 + i, 10, options[i]); // Печатаем каждую опцию
            attroff(A_REVERSE);
        }
        choice = getch();
        switch (choice) {
            case KEY_UP:
                if (highlight > 0)
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight < 3)
                    ++highlight;
                break;
            case 10: // Enter key
                if (highlight == 3) { // Если выбрана опция "Exit"
                    endwin();
                    return 0;
                }
                break;
        }
    }

    endwin();
    return 0;
}
