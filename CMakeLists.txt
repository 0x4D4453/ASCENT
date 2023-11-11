cmake_minimum_required(VERSION 3.16)
project(GOTY LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(GOTY
    src/main.cpp src/Game.cpp src/Being.cpp
    src/Entities/Entity.cpp src/Entities/EntityList.cpp src/Entities/Character.cpp src/Entities/Player.cpp src/Entities/Platform.cpp src/Entities/Obstacle.cpp src/Entities/Projectile.cpp src/Entities/Enemy.cpp src/Entities/Goomba.cpp
    src/Manager/GraphicsManager.cpp src/Manager/CollisionManager.cpp     
    src/Stage/Stage.cpp    
    src/State/State.cpp src/State/StateStack.cpp src/State/GameState.cpp  src/State/OptionsState.cpp src/State/PauseState.cpp src/State/MenuState.cpp
    src/Animation/Animation.cpp src/Animation/PlayerAnimation.cpp
    src/Manager/Event/EventManager src/Manager/Event/EventObserver src/Manager/Event/EventSubject)
target_include_directories(GOTY PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(GOTY PRIVATE sfml-graphics sfml-audio)
target_compile_features(GOTY PRIVATE cxx_std_17)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/assets/)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/saves/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/saves/)

if(WIN32)
    add_custom_command(
        TARGET GOTY
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:GOTY>
        VERBATIM)
endif()

install(TARGETS GOTY)
