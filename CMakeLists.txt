cmake_minimum_required(VERSION 2.6)
project(INDIGO)

# SETTING UP DIRECTORIES

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

if(WIN32)
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/include
  )
  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/lib
  )
endif()
# END DIRECTORY SETUP


# SETTING UP INDIGO ENGINE LIB
add_library(indigo

)
# LINKING NECESSARY DLLs
if(WIN32)
  target_link_libraries(indigo glew32 freeglut libogg libvorbis libvorbisfile openal)
endif()


# SETTING UP EDITOR EXECUTABLE
add_executable(editor
  src/editor/main.cpp
)
# LINKING TO INDIGO ENGINE LIB
target_link_libraries(editor indigo)


