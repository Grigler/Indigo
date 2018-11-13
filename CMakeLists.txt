#Version 2.8 for policy-CMP0012 compliance - OPENMP_FOUND conditional
cmake_minimum_required(VERSION 2.8)
project(INDIGO)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

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


add_library(AL_AUDIO SHARED
  src/indigo/AL_AUDIO/AudioManager.h
  src/indigo/AL_AUDIO/AudioManager.cpp
)
target_link_libraries(AL_AUDIO openal libogg libvorbis libvorbisfile) 

#I don't like doing this, but it means the header files don't appear in "External Dependencies"
#in Visual Studio and that I don't have to fill up the add_library with .h files
message(STATUS "Rel: ${PROJECT_SOURCE_DIR}/indigo/src")
file(GLOB HEADERS RELATIVE ${PROJECT_SOURCE_DIR} src/indigo/*h)

add_definitions(-DGLEW_STATIC)
add_library(Indigo
  ${HEADERS}

  src/indigo/plank.cpp

  src/indigo/Application.cpp
  src/indigo/Engine.cpp
  src/indigo/Input.cpp
  src/indigo/MemObj.cpp
  src/indigo/GameObject.cpp
  src/indigo/Component.cpp
  src/indigo/Transform.cpp
  src/indigo/Camera.cpp
  src/indigo/Resources.cpp

  src/indigo/AABB.cpp
  src/indigo/PhysicsHandler.cpp
  src/indigo/ContactResolver.cpp
  
  src/indigo/Collider.cpp
  src/indigo/RB.cpp
  
  src/indigo/MeshRenderer.cpp
  src/indigo/MeshResource.cpp
  src/indigo/Mesh.cpp
  src/indigo/tiny_obj_loader.cc
  
  src/indigo/TextureResource.cpp
  src/indigo/Texture.cpp
  src/indigo/lodepng.cpp

  src/indigo/Shader.cpp
  src/indigo/RenderBuffer.cpp
  src/indigo/Light.cpp
  src/indigo/LightSources.cpp

  src/indigo/CharacterController.cpp
)
target_link_libraries(Indigo glew32s freeglut AL_AUDIO)

#Hacky way of using the ${HEADERS} glob and writing it into an API header
# I'm proud of this in a way, but mostly ashamed

#set(INCLUDE_OUT ${PROJECT_SOURCE_DIR}/include/indigo/indigo.h)
#file(REMOVE ${INCLUDE_OUT})
#file(APPEND ${INCLUDE_OUT} "#ifndef __INDIGO__\n#define __INDIGO__\n")
#file(APPEND ${INCLUDE_OUT} "#include \"config.h\"\n\n")
#foreach(CURR_HEADER ${HEADERS})
#  string(REGEX MATCH indigo/.* PATH_FIX ${CURR_HEADER})
#  file(APPEND ${INCLUDE_OUT} "#include \"${PATH_FIX}\"\n")
#endforeach(${CURR_HEADER})

#file(APPEND ${INCLUDE_OUT} "\n#endif\n")


include_directories(
  ${PROJECT_SOURCE_DIR}/include
  )

add_executable(example
  src/example/config.h

  src/example/main.cpp
)
target_link_libraries(example Indigo)
