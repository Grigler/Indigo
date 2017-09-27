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
add_executable(Indigo
  src/indigo/main.cpp

  src/indigo/Environment.cpp
  src/indigo/Scene.cpp
  src/indigo/GameObj.cpp
  src/indigo/Component.cpp
  src/indigo/MessageQueue.cpp
  src/indigo/RenderManager.cpp
  src/indigo/Camera.cpp
  src/indigo/Texture.cpp
  src/indigo/Window.cpp
  src/indigo/Transform.cpp

)
# LINKING NECESSARY DLLs
if(WIN32)
  #UNCOMMENT THINGS WHEN YOU NEED TO START ADDING LIBRARIES BACK IN
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


#indigo colour code in rgb (75, 0, 130)