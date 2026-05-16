cmake_minimum_required(VERSION 3.21)

project(blagger LANGUAGES C)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(${PROJECT_NAME}
    src/blagger.c
    src/globals.c
    src/input.c
    src/level.c
    src/render.c
    src/update.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL2::SDL2main    
        SDL2::SDL2
        SDL2_mixer::SDL2_mixer
)

# Copy assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/data" 
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
    COMMENT "Copying assets..."
)

# Copy required DLLs on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying runtime DLLs..."
    )
endif()