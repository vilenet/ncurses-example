// Пример 12: Простейшая файловая система с навигацией
#include <pdcurses.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Функция для отображения списка файлов и папок
void display_files(WINDOW* win, std::vector<std::string>& files, int highlight) {
    werase(win);
    box(win, 0, 0);
    for (size_t i = 0; i < files.size(); ++i) {
        if (highlight == (int)i) {
            wattron(win, A_REVERSE);  // Выделяем выбранный элемент
            mvwprintw(win, i + 1, 1, files[i].c_str());
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, i + 1, 1, files[i].c_str());
        }
    }
    wrefresh(win);
}

// Функция для отображения содержимого файла
void display_file_content(WINDOW* content_win, const std::string& file_path) {
    std::ifstream file(file_path);
    werase(content_win);
    box(content_win, 0, 0);
    std::string line;
    int row = 1;
    while (std::getline(file, line) && row < getmaxy(content_win) - 1) {
        mvwprintw(content_win, row++, 1, line.c_str());
    }
    wrefresh(content_win);
}

int main() {
    initscr();                      // Инициализация PDCurses
    cbreak();                       // Немедленная реакция на ввод
    noecho();                       // Отключаем отображение вводимых символов
    keypad(stdscr, TRUE);           // Включаем поддержку клавиш-стрелок
    curs_set(0);                    // Скрываем курсор

    // Создание двух окон для файлов и содержимого
    WINDOW* files_win = newwin(20, 30, 2, 2);      // Левое окно для списка файлов
    WINDOW* content_win = newwin(20, 50, 2, 35);   // Правое окно для содержимого файла

    box(files_win, 0, 0);
    box(content_win, 0, 0);
    wrefresh(files_win);
    wrefresh(content_win);

    DIR* dir;
    struct dirent* ent;
    std::vector<std::string> files;

    // Открываем текущий каталог и считываем его содержимое
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG || ent->d_type == DT_DIR) {  // Только файлы и каталоги
                files.push_back(ent->d_name);
            }
        }
        closedir(dir);
    }

    int highlight = 0;
    display_files(files_win, files, highlight);

    int ch;
    while ((ch = wgetch(files_win)) != 27) {  // Завершение по нажатию Esc (код 27)
        switch (ch) {
            case KEY_UP:
                highlight = (highlight > 0) ? highlight - 1 : files.size() - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight < (int)files.size() - 1) ? highlight + 1 : 0;
                break;
            case 10:  // Enter — отображение содержимого файла
                if (highlight < (int)files.size()) {
                    display_file_content(content_win, files[highlight]);
                }
                break;
        }
        display_files(files_win, files, highlight);
    }

    // Освобождение ресурсов и завершение работы
    delwin(files_win);
    delwin(content_win);
    endwin();
    return 0;
}
