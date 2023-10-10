cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/GameObjects/GameObject.cpp src/GameObjects/GameObject.h src/GameObjects/Player.cpp src/GameObjects/Player.h src/GameObjects/Enemy.cpp src/GameObjects/Enemy.h "src/Other Logic/Vector.cpp" "src/Other Logic/Vector.h" src/GameObjects/Gem.cpp src/GameObjects/Gem.h src/GameObjects/Platforms.cpp src/GameObjects/Platforms.h "src/Other Logic/TileMap.cpp" "src/Other Logic/TileMap.h" src/Media/Audio.cpp src/Media/Audio.h src/Media/Text.cpp src/Media/Text.h src/GameObjects/Spike.cpp src/GameObjects/Spike.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)