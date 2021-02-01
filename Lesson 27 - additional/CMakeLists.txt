cmake_minimum_required(VERSION 3.17)
project(RoguelikeCLion C)

set(CMAKE_C_STANDARD 11)

include_directories (include)

add_executable(RoguelikeCLion  src/main.c src/entities/player.c src/entities/room.c src/entities/level.c
        src/entities/monster.c src/combat.c src/screen.c src/utils/pathFinding.c
        src/entities/items/itemFactory.c)

add_compile_options(RoguelikeCLion PUBLIC -Wall -Wextra -pedantic -Werror)
find_library(PDCURSES pdcurses lib)
target_link_libraries(RoguelikeCLion LINK_PUBLIC ${PDCURSES})
