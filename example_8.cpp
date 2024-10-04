// Пример 8: Простой редактор текста
#include <pdcurses.h>
#include <fstream>
#include <string>

#define MAX_ROWS 20
#define MAX_COLS 50

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char buffer[MAX_ROWS][MAX_COLS] = {0}; // Буфер для хранения текста
    int x = 0, y = 0;                     // Текущие координаты курсора
    int ch;

    // Инструкция для пользователя
    mvprintw(0, 0, "Simple Text Editor (Press F2 to save and quit)");
    refresh();

    move(1, 0); // Устанавливаем курсор на позицию (1,0)
    while ((ch = getch()) != KEY_F(2)) {  // Завершение по нажатию F2
        switch (ch) {
            case KEY_LEFT:
                if (x > 0) x--;
                break;
            case KEY_RIGHT:
                if (x < MAX_COLS - 1) x++;
                break;
            case KEY_UP:
                if (y > 0) y--;
                break;
            case KEY_DOWN:
                if (y < MAX_ROWS - 1) y++;
                break;
            case KEY_BACKSPACE:
            case 127:
                if (x > 0) {
                    x--;
                    buffer[y][x] = ' ';  // Удаление символа
                }
                break;
            case 10: // Enter key
                y++;
                x = 0;
                break;
            default:
                buffer[y][x] = ch;       // Запись символа в буфер
                x++;
                break;
        }
        clear();                         // Очистка экрана для отображения обновлений
        mvprintw(0, 0, "Simple Text Editor (Press F2 to save and quit)");
        for (int i = 0; i < MAX_ROWS; i++) { // Вывод буфера
            mvprintw(1 + i, 0, buffer[i]);
        }
        move(1 + y, x);                  // Перемещение курсора на новую позицию
        refresh();
    }

    // Сохранение текста в файл
    std::ofstream file("output.txt");
    for (int i = 0; i < MAX_ROWS; i++) {
        file << buffer[i] << std::endl;
    }
    file.close();

    endwin();
    return 0;
}
