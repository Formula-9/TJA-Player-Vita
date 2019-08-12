cmake_minimum_required(VERSION 2.8)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else ()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif ()
endif ()

project(tjaplayervita)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "TJA Player")
set(VITA_TITLEID "TJAPLVITA")
set(VITA_VERSION "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -g -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -Wpedantic")

add_executable(${PROJECT_NAME}
	src/main.c
	src/Log.c
	src/Game.c
	src/SjisTable.c
	src/SjisToUtf8.c
	src/Genre.c
	src/GenreLinkedList.c
	src/ChartFile.c
	src/ChartLinkedList.c
	src/ChartFinder.c
	src/Title.c
	src/SongSelect.c
)

target_link_libraries(${PROJECT_NAME}
	SDL2_mixer
	SDL2
	vita2d
	freetype
	FLAC
	mikmod
	vorbisfile
	vorbis
	ogg
	mpg123
	png
	z
	m
	SceIofilemgr_stub
	SceDisplay_stub
	SceCtrl_stub
	SceAudio_stub
	SceSysmodule_stub
	SceGxm_stub
	SceCommonDialog_stub
	SceTouch_stub
	SceHid_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
	VERSION ${VITA_VERSION}
	NAME ${VITA_APP_NAME}
	FILE sce_sys/icon0.png sce_sys/icon0.png
	FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
	FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
	FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)
