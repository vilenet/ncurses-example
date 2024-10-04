// Пример 11: Главное меню приложения с подменю
// TODO
#include <pdcurses.h>
#include <string>
#include <vector>

// Функция для отображения меню
void display_menu(WINDOW* menu_win, std::vector<std::string> &menu_items, int highlight) {
    int x = 2, y = 2;  // Положение текста внутри окна
    box(menu_win, 0, 0);
    for (size_t i = 0; i < menu_items.size(); ++i) {
        if (highlight == (int)i) {
            wattron(menu_win, A_REVERSE);  // Включаем выделение для выбранного пункта
            mvwprintw(menu_win, y + i, x, menu_items[i].c_str());
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y + i, x, menu_items[i].c_str());
        }
    }
    wrefresh(menu_win);
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);  // Включение поддержки клавиш, таких как стрелки
    curs_set(0);           // Скрываем курсор

    start_color();  // Включаем поддержку цветов
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Пара цветов для выделенного текста
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Пара цветов для заголовка меню

    // Определяем меню и подменю
    std::vector<std::string> main_menu = { "Start Game", "Settings", "Help", "Exit" };
    std::vector<std::string> settings_menu = { "Graphics", "Sound", "Controls", "Back" };
    
    int highlight = 0;
    int choice;
    bool in_settings = false;  // Флаг для переключения между меню

    // Создаем окно для меню
    WINDOW* menu_win = newwin(10, 30, 5, 5);
    wattron(menu_win, COLOR_PAIR(1));  // Устанавливаем цвет для меню
    wbkgd(menu_win, COLOR_PAIR(1));    // Задание фона окна
    display_menu(menu_win, main_menu, highlight);

    mvprintw(1, 10, "Application Main Menu");
    attron(COLOR_PAIR(2));             // Цвет для заголовка
    mvprintw(3, 10, "Use Arrow Keys to Navigate");
    mvprintw(4, 10, "Press Enter to Select");
    attroff(COLOR_PAIR(2));
    refresh();

    while (true) {
        choice = wgetch(menu_win);  // Чтение нажатой клавиши в окне меню
        switch (choice) {
            case KEY_UP:
                highlight = (highlight > 0) ? highlight - 1 : (in_settings ? settings_menu.size() - 1 : main_menu.size() - 1);
                break;
            case KEY_DOWN:
                highlight = (highlight < (in_settings ? settings_menu.size() - 1 : main_menu.size() - 1)) ? highlight + 1 : 0;
                break;
            case 10:  // Enter
                if (!in_settings) {
                    if (highlight == 0) {
                        // Запуск игры (вывод простой строки)
                        mvprintw(15, 10, "Starting the game...");
                        refresh();
                    } else if (highlight == 1) {
                        // Переход в меню настроек
                        highlight = 0;
                        in_settings = true;
                        display_menu(menu_win, settings_menu, highlight);
                    } else if (highlight == 2) {
                        mvprintw(15, 10, "Help: Use Arrow Keys to Navigate, Enter to Select");
                        refresh();
                    } else if (highlight == 3) {
                        endwin();
                        return 0;
                    }
                } else {
                    if (highlight == 3) {  // Пункт "Back" в меню настроек
                        highlight = 0;
                        in_settings = false;
                        display_menu(menu_win, main_menu, highlight);
                    }
                }
                break;
        }
        display_menu(menu_win, in_settings ? settings_menu : main_menu, highlight);
    }

    delwin(menu_win);
    endwin();
    return 0;
}
