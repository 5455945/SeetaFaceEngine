cmake_minimum_required(VERSION 3.1.0)

project(SFMFCTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_AFXDLL")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

include_directories(include)
include_directories(../FaceAlignment/include)
include_directories(../FaceDetection/include)
include_directories(../FaceIdentification/include)

set(inc_files
    include/stdafx.h
    include/SFMFCTest.h
    include/SFMFCTestDlg.h
	)

set(src_files
    res/SFMFCTest.rc
    src/SFMFCTest.cpp
    src/SFMFCTestDlg.cpp
    )

add_executable(SFMFCTest ${inc_files} ${src_files})

find_package(OpenCV REQUIRED)
if (NOT OpenCV_FOUND)
	message(WARNING "OpenCV not found. Test will not be built.")
else()
	include_directories(${OpenCV_INCLUDE_DIRS})
	link_directories(${OpenCV_LIB_PATH})
	list(APPEND viplnet seeta_fa_lib seeta_facedet_lib  ${OpenCV_LIBS})
	target_link_libraries(SFMFCTest viplnet seeta_fa_lib seeta_facedet_lib ${OpenCV_LIBS})
endif()
