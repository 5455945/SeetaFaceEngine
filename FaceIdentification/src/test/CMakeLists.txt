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
endforeach ()

