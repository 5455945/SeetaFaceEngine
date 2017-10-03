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
	
	install(TARGETS SFMFCTest
	    RUNTIME DESTINATION bin/\${CMAKE_INSTALL_CONFIG_NAME}
	    LIBRARY DESTINATION lib/\${CMAKE_INSTALL_CONFIG_NAME}
	    ARCHIVE DESTINATION lib/static/\${CMAKE_INSTALL_CONFIG_NAME})
	
	if (NOT EXISTS ${CMAKE_INSTALL_PREFIX}/model/seeta_fr_v1.0.bin)
		if (WIN32)
			install(CODE "execute_process(COMMAND \"${CMAKE_SOURCE_DIR}/tools/rar\" x -ep -y seeta_fr_v1.0.part1.rar seeta_fr_v1.0.part2.rar seeta_fr_v1.0.bin
					WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/FaceIdentification/model\")")
			install(CODE "file(RENAME \"${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin\" \"${CMAKE_INSTALL_PREFIX}/model/seeta_fr_v1.0.bin\")")
		else()
			install(DIRECTORY ${PROJECT_SOURCE_DIR}/model DESTINATION .)
		endif()
	endif()
endif()
