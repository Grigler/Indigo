#Version 2.8 for policy-CMP0012 compliance for OPENMP_FOUND conditional
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

add_definitions(-DGLEW_STATIC)

if(WIN32)
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/include
  )
  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/msvc/lib
  )
endif()

add_library(AL_AUDIO SHARED
  src/Indigo/AudioManager.cpp
)
target_link_libraries(AL_AUDIO openal)


add_library(Indigo
  src/Indigo/plank.cpp

  src/Indigo/Application.cpp
  src/Indigo/Engine.cpp
  src/Indigo/Input.cpp
  src/Indigo/MemObj.cpp
  src/Indigo/GameObject.cpp
  src/Indigo/Component.cpp
  src/Indigo/Transform.cpp
  src/Indigo/Camera.cpp
  src/Indigo/Resources.cpp

  src/Indigo/AABB.cpp

  src/Indigo/MeshRenderer.cpp
  src/Indigo/MeshResource.cpp
  src/Indigo/Mesh.cpp

  src/Indigo/Shader.cpp

  src/Indigo/CharacterController.cpp
)
target_link_libraries(Indigo glew32s freeglut AL_AUDIO)


add_executable(example

  src/example/main.cpp

)
target_link_libraries(example Indigo)