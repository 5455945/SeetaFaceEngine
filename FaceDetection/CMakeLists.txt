cmake_minimum_required(VERSION 3.1.0)

project(seeta_facedet_lib)

# Build options
option(BUILD_EXAMPLES  "Set to ON to build examples"  ON)
option(USE_OPENMP      "Set to ON to build use openmp"  ON)
option(USE_SSE         "Set to ON to build use SSE"  ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

# Use SSE
if (USE_SSE)
    add_definitions(-DUSE_SSE)
    message(STATUS "Use SSE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
endif()

# Use OpenMP
if (USE_OPENMP)
    find_package(OpenMP QUIET)
    if (OPENMP_FOUND)
        message(STATUS "Use OpenMP")
        add_definitions(-DUSE_OPENMP)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
endif()

include_directories(include)

set(src_files 
    src/util/nms.cpp
    src/util/image_pyramid.cpp
    src/io/lab_boost_model_reader.cpp
    src/io/surf_mlp_model_reader.cpp
    src/feat/lab_feature_map.cpp
    src/feat/surf_feature_map.cpp
    src/classifier/lab_boosted_classifier.cpp
    src/classifier/mlp.cpp
    src/classifier/surf_mlp.cpp
    src/face_detection.cpp
    src/fust.cpp
    )

# Build shared library
add_library(seeta_facedet_lib SHARED ${src_files})
set(facedet_required_libs seeta_facedet_lib)

install(TARGETS seeta_facedet_lib
        RUNTIME DESTINATION bin/\${CMAKE_INSTALL_CONFIG_NAME}
        LIBRARY DESTINATION lib/\${CMAKE_INSTALL_CONFIG_NAME}
        ARCHIVE DESTINATION lib/static/\${CMAKE_INSTALL_CONFIG_NAME})
install(DIRECTORY include DESTINATION include/FaceDetection)

# Build examples
if (BUILD_EXAMPLES)
    message(STATUS "Build with examples.")
    find_package(OpenCV)
    if (NOT OpenCV_FOUND)
        message(WARNING "OpenCV not found. Test will not be built.")
    else()
        include_directories(${OpenCV_INCLUDE_DIRS})
        list(APPEND facedet_required_libs ${OpenCV_LIBS})
        
        add_executable(test_face_detection src/test/test_face_detection.cpp)
        target_link_libraries(test_face_detection ${facedet_required_libs})

		install(TARGETS test_face_detection
			RUNTIME DESTINATION bin/\${CMAKE_INSTALL_CONFIG_NAME}
			LIBRARY DESTINATION lib/\${CMAKE_INSTALL_CONFIG_NAME}
			ARCHIVE DESTINATION lib/static/\${CMAKE_INSTALL_CONFIG_NAME})
		install(FILES ${PROJECT_SOURCE_DIR}/src/test/test_face_detection.cpp DESTINATION sample)
	    install(DIRECTORY data DESTINATION .)
	    install(DIRECTORY model DESTINATION .)
    endif()
endif()
