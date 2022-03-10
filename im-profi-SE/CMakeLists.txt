# CMakeList.txt: проект CMake для im-profi-SE; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("im-profi-SE")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (im-profi-SE "im-profi-SE.cpp" "im-profi-SE.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
