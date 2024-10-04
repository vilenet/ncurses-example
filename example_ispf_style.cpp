#include <pdcurses.h>
#include <string>

void print_centered(int row, const std::string &text, int width, int color_pair) {
    int col = (width - text.length()) / 2;
    attron(COLOR_PAIR(color_pair));
    mvprintw(row, col, text.c_str());
    attroff(COLOR_PAIR(color_pair));
}

void update_command_line(int input_char) {
    // Обновление строки команд: белый номер и красная линия
    attron(COLOR_PAIR(3)); // Белый цвет для номера
    mvprintw(1, 13, "%c", input_char); // Отображение введенного символа (номер меню)
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(6)); // Красный цвет для линии после номера
    mvprintw(1, 14, "____________________________________________________");
    attroff(COLOR_PAIR(6));
    refresh();
}

int main() {
    // Инициализация ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Определение цветовых пар
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);   // Желтый цвет для основной части заголовка
    init_pair(2, COLOR_CYAN, COLOR_BLACK);     // Бирюзовый цвет для пунктов меню
    init_pair(3, COLOR_WHITE, COLOR_BLACK);    // Белый цвет для номеров и команд
    init_pair(4, COLOR_BLUE, COLOR_BLACK);     // Синий цвет для линий и символов "-"
    init_pair(5, COLOR_WHITE, COLOR_BLUE);     // Белый текст на синем фоне
    init_pair(6, COLOR_RED, COLOR_BLACK);      // Красный цвет для линии Command

    // Устанавливаем размеры окна, как у терминала 3270
    resize_term(24, 80); // 24 строки и 80 столбцов

    int height, width;
    getmaxyx(stdscr, height, width);

    // Заголовок окна (желтый текст для основной части и синие линии)
    attron(COLOR_PAIR(4)); // Синий цвет для линий
    mvprintw(0, 10, " -------- ");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(1)); // Желтый цвет для текста
    mvprintw(0, 20, "Test ISPF Panel Main Menu");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4)); // Синий цвет для линий после заголовка
    mvprintw(0, 58, " ---------");
    attroff(COLOR_PAIR(4));

    // "ARY$MAIN" (белый)
    attron(COLOR_PAIR(3));
    mvprintw(0, 0, "TESTMAIN");
    attroff(COLOR_PAIR(3));

    // Командная строка (белый) и красная линия
    attron(COLOR_PAIR(3)); // Белый цвет для текста
    mvprintw(1, 0, "Command ===>");
    attroff(COLOR_PAIR(3));

    // Красная линия после текста "Command ===>"
    attron(COLOR_PAIR(6)); // Красный цвет для линии
    mvprintw(1, 12, "_____________________________________________________");
    attroff(COLOR_PAIR(6));

    // Пункты меню: номера (белый), начнем с более низкой строки (например, строки 8 для терминала 3270)
    int menu_start_row = 8;  // Начальная строка для пунктов меню в стиле терминала 3270
    attron(COLOR_PAIR(3));
    mvprintw(menu_start_row, 5, "0");
    mvprintw(menu_start_row + 2, 5, "1");
    mvprintw(menu_start_row + 4, 5, "2");
    mvprintw(menu_start_row + 6, 5, "3");
    attroff(COLOR_PAIR(3));

    // Пункты меню: названия (бирюзовый)
    attron(COLOR_PAIR(2));
    mvprintw(menu_start_row, 7, "Test Option");
    mvprintw(menu_start_row + 2, 7, "Test Option");
    mvprintw(menu_start_row + 4, 7, "Test Option");
    mvprintw(menu_start_row + 6, 7, "Test Option");
    attroff(COLOR_PAIR(2));

    // Нижняя линия (синий)
    attron(COLOR_PAIR(4));
    print_centered(height - 2, "************************ Bottom of window ************************", width, 4);
    attroff(COLOR_PAIR(4));

    // Отслеживание ввода символов для командной строки
    int input_char;
    while ((input_char = getch()) != 'q') { // Нажатие 'q' завершает программу
        if (input_char >= '0' && input_char <= '3') {
            update_command_line(input_char);
        }
    }

    // Завершение работы с ncurses
    endwin();
    return 0;
}
