cmake_minimum_required(VERSION 2.6)
project(INDIGO)

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

add_library(Indigo
  src/Indigo/plank.cpp

  src/Indigo/Application.cpp
  src/Indigo/Engine.cpp
  src/Indigo/Input.cpp
  src/Indigo/MemObj.cpp
  src/Indigo/GameObject.cpp
  src/Indigo/Component.cpp
  src/Indigo/Transform.cpp

)

if(WIN32)
  #target_link_libraries(indigo glew32 freeglut libogg libvorbis libvorbisfile openal)
  target_link_libraries(Indigo glew32 freeglut)
endif()


# SETTING UP EDITOR EXECUTABLE
#add_executable(editor
#
#  src/editor/main.cpp
#
#)
# LINKING TO INDIGO ENGINE LIB
#target_link_libraries(editor indigo)

add_executable(example

  src/example/main.cpp

)
target_link_libraries(example Indigo)


#indigo colour code in rgb (75, 0, 130)