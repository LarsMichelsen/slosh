cmake_minimum_required(VERSION 3.7)
project(emulator)

find_package(SDL2 REQUIRED)
include_directories(emulator ${SDL2_INCLUDE_DIRS})

# Directly include the common components into this cmake application
add_library(common
    ../common/Game.h
    ../common/GameState.h
    ../common/Renderer.h
    ../common/Sound.h
    ../common/Entity.h
    ../common/Player.h
    ../common/Enemy.h
    ../common/Spawner.h
    ../common/Exit.h
    ../common/Input.h
    ../common/utils.h
)
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(common PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

add_executable(emulator
    main.cc
    SDLRenderer.cc
    SDLSound.cc
    SDLInput.cc
    ../common/Game.cc
    ../common/GameStateLevel.cc
    ../common/GameStateDead.cc
    ../common/GameStateFinished.cc
    ../common/GameStateSkipped.cc
    ../common/GameStateInit.cc
    ../common/GameStateWon.cc
    ../common/Sound.cc
    ../common/Entity.cc
    ../common/Player.cc
    ../common/Enemy.cc
    ../common/Spawner.cc
    ../common/Exit.cc
    ../common/utils.cc
)

target_link_libraries(emulator common ${SDL2_LIBRARIES})
