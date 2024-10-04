# Установка минимально необходимой версии CMake
cmake_minimum_required(VERSION 3.10)

# Имя вашего проекта
project(pdcurses_project)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указать путь к заголовочным файлам
include_directories("C:/msys64/mingw64/include")

# Указать путь к библиотекам
link_directories("C:/msys64/mingw64/lib")

# Собрать каждый файл как отдельный исполняемый файл
file(GLOB EXAMPLES "example_*.cpp")

foreach(example_file ${EXAMPLES})
    # Извлечь имя файла без расширения и использовать его как имя цели
    get_filename_component(example_name ${example_file} NAME_WE)

    # Создать исполняемый файл
    add_executable(${example_name} ${example_file})

    # Подключить библиотеку PDCurses
    target_link_libraries(${example_name} pdcurses)
endforeach()

