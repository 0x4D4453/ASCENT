cmake_minimum_required(VERSION 3.16)
project(GOTY LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(GOTY
    src/main.cpp src/Context.cpp src/Game.cpp src/Being.cpp 
    src/Entities/Entity.cpp src/Entities/EntityList.cpp src/Entities/EntityFactory.cpp
    src/Entities/Characters/Character.cpp src/Entities/Characters/Player.cpp src/Entities/Characters/Enemy.cpp src/Entities/Characters/Goomba.cpp src/Entities/Characters/Fly.cpp
    src/Entities/Characters/Tyrant.cpp src/Entities/Characters/TyrantStates/TyrantState.cpp src/Entities/Characters/TyrantStates/TyrantIdleState.cpp src/Entities/Characters/TyrantStates/TyrantJumpingState.cpp src/Entities/Characters/TyrantStates/TyrantShootingState.cpp 
    src/Entities/Obstacles/Platform.cpp src/Entities/Obstacles/Obstacle.cpp src/Entities/Obstacles/MovingPlatform.cpp src/Entities/Obstacles/Spike.cpp src/Entities/Obstacles/Door.cpp src/Entities/Projectile.cpp
    src/Manager/GraphicsManager.cpp
    src/Manager/Collision/CollisionManager.cpp src/Manager/Collision/CollisionStrategy.cpp src/Manager/Collision/CollisionStrategyFactory.cpp
    src/Manager/Collision/DefaultCollision.cpp src/Manager/Collision/PhaseCollision.cpp src/Manager/Collision/KnockbackCollision.cpp src/Manager/Collision/BounceCollision.cpp
    src/Stage/Stage.cpp src/Stage/StageFactory.cpp src/Stage/Cave.cpp src/Stage/Factory.cpp 
    src/State/State.cpp src/State/StateStack.cpp src/State/GameState.cpp src/State/LoadingState.cpp src/State/OptionsState.cpp src/State/InStageState.cpp src/State/PauseState.cpp src/State/EndStageState.cpp src/State/SaveScoreState.cpp src/State/MenuState.cpp src/State/PlayerSelectState.cpp src/State/StageSelectState.cpp src/State/RankingState.cpp
    src/State/Pause/PauseObserver.cpp src/State/Pause/PauseSubject.cpp
    src/Animation/Animation.cpp src/Animation/PlayerAnimation.cpp src/Animation/EnemyAnimation.cpp src/Animation/TyrantAnimation.cpp
    src/Manager/Event/EventManager.cpp src/Manager/Event/EventObserver.cpp src/Manager/Event/EventSubject.cpp
    src/Utility/CustomVector.cpp src/Utility/HitboxSprite.cpp src/Utility/ViewShake.cpp src/Utility/Threads/Thread.cpp src/Utility/Threads/LoadingThread.cpp
    src/UI/TextInput.cpp src/UI/PlayerHealth.cpp)
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
