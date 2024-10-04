// Пример 10: Интерфейс с двумя окнами — Информационное окно и окно ввода
// TODO
#include <pdcurses.h>
#include <string>
#include <vector>

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Создаем два окна
    WINDOW* info_win = newwin(10, 30, 0, 0);  // Информационное окно
    WINDOW* input_win = newwin(10, 50, 0, 31); // Окно для ввода

    // Рисуем рамки вокруг окон
    box(info_win, 0, 0);
    box(input_win, 0, 0);
    mvwprintw(info_win, 1, 1, "Information Window");
    mvwprintw(input_win, 1, 1, "Input Window");

    wrefresh(info_win);
    wrefresh(input_win);

    std::vector<std::string> messages;        // Вектор для хранения сообщений
    std::string input;                        // Переменная для ввода текста

    int ch;
    while ((ch = wgetch(input_win)) != 27) {  // Завершение программы по нажатию Esc (код 27)
        if (ch == 10) {  // Enter - переносим сообщение в информационное окно
            messages.push_back(input);  // Добавляем введенный текст в вектор сообщений
            werase(input_win);  // Очищаем окно ввода
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "Input Window");
            input.clear();  // Очищаем строку ввода
        } else if (ch == KEY_BACKSPACE || ch == 127) {  // Обработка клавиши Backspace
            if (!input.empty()) {
                input.pop_back();
                werase(input_win);
                box(input_win, 0, 0);
                mvwprintw(input_win, 1, 1, "Input Window");
                mvwprintw(input_win, 2, 1, "%s", input.c_str());
            }
        } else {
            input += ch;  // Добавляем символ в строку ввода
        }

        // Обновление содержимого окна ввода
        mvwprintw(input_win, 2, 1, "%s", input.c_str());
        wrefresh(input_win);

        // Обновление информационного окна
        werase(info_win);
        box(info_win, 0, 0);
        mvwprintw(info_win, 1, 1, "Information Window");
        for (size_t i = 0; i < messages.size(); ++i) {
            mvwprintw(info_win, 2 + i, 1, messages[i].c_str());
        }
        wrefresh(info_win);
    }

    // Удаляем окна и завершаем работу с ncurses
    delwin(info_win);
    delwin(input_win);
    endwin();
    return 0;
}

