cmake_minimum_required(VERSION 3.26)
project(Portfolio)

# Emscripten only
if(NOT EMSCRIPTEN)
  message(FATAL_ERROR "This project is configured for Emscripten only.")
endif()

message("Using Emscripten!")

set(TARGET_NAME portfolio_web)

# =========================
# Portfolio engine library
# =========================
add_library(portfolio_engine STATIC
  src/engine.cpp
)

target_compile_features(portfolio_engine PUBLIC cxx_std_20)

# =========================
# Executable
# =========================
add_executable(${TARGET_NAME}
  web/index.html
)

target_link_libraries(${TARGET_NAME} PRIVATE portfolio_engine)
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

# =========================
# Emscripten settings
# =========================
set(EMSCRIPTEN_COMPILE_FLAGS "-g")
set(EMSCRIPTEN_LINK_FLAGS
  "-sUSE_FREETYPE=1 \
   -sUSE_HARFBUZZ=1 \
   -sALLOW_MEMORY_GROWTH \
   --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" \
   -g"
)

set_target_properties(${TARGET_NAME} PROPERTIES
  COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
  LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
)

# Copy web template files
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
  "${CMAKE_CURRENT_SOURCE_DIR}/web"
  "$<TARGET_FILE_DIR:${TARGET_NAME}>/"
)

# Generate HTML output
set(CMAKE_EXECUTABLE_SUFFIX ".html")