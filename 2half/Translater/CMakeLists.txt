cmake_minimum_required(VERSION 3.10) # Указываю минимальную версию CMake
project(translater) # Определяю имя проекта

set(CMAKE_C_STANDARD 11) # Устанавливаю стандарт C

add_library(translate STATIC translate.c) # Создаю статическую библиотеку

add_executable(translater main.c) #Создаю исполняющий файл и связываю с библиотекой
target_link_libraries(translater PRIVATE translate)

find_package(CMocka REQUIRED) # Ищю пакет CMocka для юнит тестов
add_executable(test_translate test_translate.c) # Создаю исполняемый текстовый файл
target_link_libraries(test_translate PRIVATE translate cmocka) # Связываю тектстовый файл с библиотекой и CMocka