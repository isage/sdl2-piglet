cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()

project(SDL2-piggy)
include("${DOLCESDK}/share/dolce.cmake" REQUIRED)

set(DOLCE_APP_NAME "SDL2-piggy")
set(DOLCE_TITLEID  "GLES00003")
set(DOLCE_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVITA -D__VITA__ -fno-lto -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__VITA__ -std=c++11")
set(DOLCE_MKSFOEX_FLAGS "${DOLCE_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")


find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})


#include_directories(${CMAKE_SOURCE_DIR}/sdl2/include)

add_executable(${PROJECT_NAME}
  main.c
)

target_link_libraries(${PROJECT_NAME}
#  ${CMAKE_SOURCE_DIR}/sdl2/lib/libSDL2.a
  ${SDL2_LIBRARY}
  pib
  SceSharedFb_stub
  SceDisplay_stub
  SceDisplayUser_stub
  SceCtrl_stub
  SceAppMgr_stub
  SceAppMgrUser_stub
  SceAudio_stub
  SceIofilemgr_stub
  SceSysmodule_stub
  SceGxm_stub
  SceGxmInternalForVsh_stub
  SceCommonDialog_stub
  SceTouch_stub
  SceHid_stub
  m
)

set(DOLCE_ELF_CREATE_FLAGS "${DOLCE_ELF_CREATE_FLAGS} -h 4194304")

dolce_create_self(eboot.bin ${PROJECT_NAME} UNSAFE)

dolce_create_vpk(${PROJECT_NAME}.vpk ${DOLCE_TITLEID} eboot.bin
  VERSION ${DOLCE_VERSION}
  NAME ${DOLCE_APP_NAME}
  FILE piglet.bmp piglet.bmp
)