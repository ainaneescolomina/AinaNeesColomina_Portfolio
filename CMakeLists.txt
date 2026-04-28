cmake_minimum_required(VERSION 3.26)
project(Portfolio)

include(FetchContent)

set(TARGET_NAME portfolio)

# =========================
# Executable
# =========================
add_executable(${TARGET_NAME}
  src/engine.cpp
)

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

# =========================
# SDL3 (DESKTOP ONLY)
# =========================
if(NOT EMSCRIPTEN)
  FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(SDL3)

  target_link_libraries(${TARGET_NAME} PRIVATE SDL3::SDL3)
endif()

# =========================
# EMSCRIPTEN BUILD
# =========================
if(EMSCRIPTEN)
  message(STATUS "Building for Web")

set_target_properties(${TARGET_NAME} PROPERTIES
  SUFFIX ".js"
)

target_link_options(${TARGET_NAME} PRIVATE
    "-sALLOW_MEMORY_GROWTH"

    "-sEXPORTED_FUNCTIONS=['_process_command']"
    "-sEXPORTED_RUNTIME_METHODS=['ccall']"

    "--preload-file" "${CMAKE_SOURCE_DIR}/resources@/resources"
)

  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/web
    $<TARGET_FILE_DIR:${TARGET_NAME}>
  )

# =========================
# DESKTOP BUILD
# =========================
else()
  message(STATUS "Building for Desktop")

  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${TARGET_NAME}>/resources
  )
endif()