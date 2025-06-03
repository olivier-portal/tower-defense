cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)

# Spécifie le chemin vers SFML si nécessaire
set(SFML_DIR "C:/msys64/ucrt64/lib/cmake/SFML")

# Trouve SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Ajoute l’exécutable
add_executable(tower-defense main.cpp)

# Lie SFML
target_link_libraries(tower-defense sfml-graphics sfml-window sfml-system)

# Copie les DLLs nécessaires après build (Windows uniquement)
if (WIN32)
    add_custom_command(TARGET tower-defense POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/msys64/ucrt64/bin/libsfml-graphics-2.dll"
            "$<TARGET_FILE_DIR:tower-defense>/libsfml-graphics-2.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/msys64/ucrt64/bin/libsfml-window-2.dll"
            "$<TARGET_FILE_DIR:tower-defense>/libsfml-window-2.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/msys64/ucrt64/bin/libsfml-system-2.dll"
            "$<TARGET_FILE_DIR:tower-defense>/libsfml-system-2.dll"
    )
endif()

