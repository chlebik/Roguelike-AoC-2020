cmake_minimum_required(VERSION 3.17)
project(RoguelikeCLion C)

set(CMAKE_C_STANDARD 11)

include_directories (include)

add_executable(RoguelikeCLion  src/main.c  src/player.c src/room.c src/level.c src/monster.c)

find_library(PDCURSES pdcurses lib)
target_link_libraries(RoguelikeCLion LINK_PUBLIC ${PDCURSES})