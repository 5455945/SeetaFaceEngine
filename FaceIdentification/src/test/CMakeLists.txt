cmake_minimum_required(VERSION 2.8.4)

aux_source_directory (. SRC_LIST)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /O2 /Ob2 /DNDEBUG")

# add external libraries
find_package(OpenCV REQUIRED)
include_directories(${VIPLNET_INCLUDE_DIR})
include_directories(${VIPLNET_INCLUDE_DIR}/../../FaceAlignment/include)
include_directories(${VIPLNET_INCLUDE_DIR}/../../FaceDetection/include)
enable_testing ()

foreach (f ${SRC_LIST})
  string(REGEX REPLACE "[.]/" "" BIN ${f})
  string(REGEX REPLACE "[.]cpp" "" BIN ${BIN})
  add_executable(${BIN} ${f})
  link_directories(${OpenCV_LIB_PATH})
  target_link_libraries(${BIN} viplnet seeta_fa_lib seeta_facedet_lib ${OpenCV_LIBS})

  install(TARGETS ${BIN}
	RUNTIME DESTINATION bin/\${CMAKE_INSTALL_CONFIG_NAME}
	LIBRARY DESTINATION lib/\${CMAKE_INSTALL_CONFIG_NAME}
	ARCHIVE DESTINATION lib/static/\${CMAKE_INSTALL_CONFIG_NAME})

  install(FILES ${PROJECT_SOURCE_DIR}/src/test/${f} DESTINATION sample)
endforeach ()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data DESTINATION .)

if (NOT EXISTS ${CMAKE_INSTALL_PREFIX}/model/seeta_fr_v1.0.bin)
	if (WIN32)
		install(CODE "execute_process(COMMAND \"${CMAKE_SOURCE_DIR}/tools/rar\" x -ep -y seeta_fr_v1.0.part1.rar seeta_fr_v1.0.part2.rar seeta_fr_v1.0.bin
				WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/FaceIdentification/model\")")
		install(CODE "file(RENAME \"${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin\" \"${CMAKE_INSTALL_PREFIX}/model/seeta_fr_v1.0.bin\")")
	else()
		install(DIRECTORY ${PROJECT_SOURCE_DIR}/model DESTINATION .)
	endif()
endif()