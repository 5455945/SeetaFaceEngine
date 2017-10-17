cmake_minimum_required(VERSION 2.8.4)

project(SeetaFaceEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(FaceDetection)
add_subdirectory(FaceAlignment)
add_subdirectory(FaceIdentification)
option(BUILD_SFMFCTEST "Building SFMFCTest Project" OFF)
if (MSVC AND BUILD_SFMFCTEST)
  add_subdirectory(SFMFCTest)
endif()

message(STATUS "copying ${CMAKE_SOURCE_DIR}/FaceDetection/data DESTINATION ${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/FaceDetection/data" DESTINATION "${CMAKE_BINARY_DIR}")
message(STATUS "copying ${CMAKE_SOURCE_DIR}/FaceDetection/model DESTINATION ${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/FaceDetection/model" DESTINATION "${CMAKE_BINARY_DIR}")

message(STATUS "copying ${CMAKE_SOURCE_DIR}/FaceAlignment/data DESTINATION ${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/FaceAlignment/data" DESTINATION "${CMAKE_BINARY_DIR}")
message(STATUS "copying ${CMAKE_SOURCE_DIR}/FaceAlignment/model DESTINATION ${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/FaceAlignment/model" DESTINATION "${CMAKE_BINARY_DIR}")

message(STATUS "copying ${CMAKE_SOURCE_DIR}/FaceIdentification/data DESTINATION ${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/FaceIdentification/data" DESTINATION "${CMAKE_BINARY_DIR}")

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin")
    if (WIN32)
	    message(STATUS "execute_process(COMMAND ${CMAKE_SOURCE_DIR}/tools/rar x -ep -y seeta_fr_v1.0.part1.rar seeta_fr_v1.0.part2.rar seeta_fr_v1.0.bin)")
	    execute_process(COMMAND "${CMAKE_SOURCE_DIR}/tools/rar" x -ep -y seeta_fr_v1.0.part1.rar seeta_fr_v1.0.part2.rar seeta_fr_v1.0.bin
			WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/FaceIdentification/model")
	endif()
endif()
	
if (WIN32)
    message(STATUS "COPY ${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin DESTINATION ${CMAKE_BINARY_DIR}/model")
    file(COPY "${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin" DESTINATION "${CMAKE_BINARY_DIR}/model")
endif()

if (BUILD_EXAMPLES)
	if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user")
		file(GENERATE
			OUTPUT "${CMAKE_BINARY_DIR}/ALL_BUILD.vcxproj.user"
			INPUT "${CMAKE_SOURCE_DIR}/cmake/ALL_BUILD.vcxproj.user.in")
	endif()
	if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/FaceAlignment/test_face_alignment.vcxproj.user")
		file(GENERATE
			OUTPUT "${CMAKE_BINARY_DIR}/FaceAlignment/test_face_alignment.vcxproj.user"
			INPUT "${CMAKE_SOURCE_DIR}/cmake/test_face_alignment.vcxproj.user.in")
	endif()
	if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/FaceDetection/test_face_detection.vcxproj.user")
		file(GENERATE
			OUTPUT "${CMAKE_BINARY_DIR}/FaceDetection/test_face_detection.vcxproj.user"
			INPUT "${CMAKE_SOURCE_DIR}/cmake/test_face_detection.vcxproj.user.in")
	endif()
	if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/FaceIdentification/src/test/test_face_recognizer.vcxproj.user")
		file(GENERATE
			OUTPUT "${CMAKE_BINARY_DIR}/FaceIdentification/src/test/test_face_recognizer.vcxproj.user"
			INPUT "${CMAKE_SOURCE_DIR}/cmake/test_face_recognizer.vcxproj.user.in")
	endif()
	if(MSVC AND NOT EXISTS "${CMAKE_BINARY_DIR}/FaceIdentification/src/test/test_face_verification.vcxproj.user")
		file(GENERATE
			OUTPUT "${CMAKE_BINARY_DIR}/FaceIdentification/src/test/test_face_verification.vcxproj.user"
			INPUT "${CMAKE_SOURCE_DIR}/cmake/test_face_verification.vcxproj.user.in")
	endif()
endif()

if(MSVC AND BUILD_SFMFCTEST AND NOT EXISTS "${CMAKE_BINARY_DIR}/SFMFCTest/SFMFCTest.vcxproj.user")
	file(GENERATE
		OUTPUT "${CMAKE_BINARY_DIR}/SFMFCTest/SFMFCTest.vcxproj.user"
		INPUT "${CMAKE_SOURCE_DIR}/cmake/SFMFCTest.vcxproj.user.in")
endif()

option(BUILD_SEETAFACEENGINE "Install Python SeetaFaceEngine" OFF)
if(BUILD_SEETAFACEENGINE)
	if (NOT EXISTS ${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin)
		if (WIN32)
			install(CODE "execute_process(COMMAND \"${CMAKE_SOURCE_DIR}/tools/rar\" x -ep -y seeta_fr_v1.0.part1.rar seeta_fr_v1.0.part2.rar seeta_fr_v1.0.bin
					WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/FaceIdentification/model\")")
		endif()
	endif()
	if (NOT EXISTS ${CMAKE_BINARY_DIR}/model/seeta_fr_v1.0.bin)
	    install(CODE "file(COPY \"${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fd_frontal_v1.0.bin\" DESTINATION \"${CMAKE_BINARY_DIR}/model\")")
	endif()
	
	install(CODE "file(COPY \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${CMAKE_INSTALL_CONFIG_NAME}/seeta_fa_lib.dll\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/bin\")")
	install(CODE "file(COPY \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${CMAKE_INSTALL_CONFIG_NAME}/seeta_facedet_lib.dll\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/bin\")")
	install(CODE "file(COPY \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/\${CMAKE_INSTALL_CONFIG_NAME}/viplnet.dll\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/bin\")")
	install(CODE "file(COPY \"${CMAKE_BINARY_DIR}/model/seeta_fa_v1.1.bin\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/model\")")
	install(CODE "file(COPY \"${CMAKE_BINARY_DIR}/model/seeta_fd_frontal_v1.0.bin\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/model\")")
	install(CODE "file(COPY \"${CMAKE_BINARY_DIR}/model/seeta_fr_v1.0.bin\" DESTINATION \"${CMAKE_SOURCE_DIR}/python/model\")")
	message(STATUS "DIRECTORY \"${CMAKE_SOURCE_DIR}/python\" DESTINATION \"${CMAKE_BINARY_DIR}\"")
	install(DIRECTORY "${CMAKE_SOURCE_DIR}/python" DESTINATION "${CMAKE_INSTALL_PREFIX}")
	
	# 安装到系统python的Lib/site-packages下面
	message(STATUS "execute_process(COMMAND python setup.py install WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/python\")")
	install(CODE "execute_process(COMMAND python setup.py install WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/python\")")
	message(STATUS "file(REMOVE_RECURSE \"${CMAKE_SOURCE_DIR}/python/build\" \"${CMAKE_SOURCE_DIR}/python/dist\" \"${CMAKE_SOURCE_DIR}/python/SeetaFaceEngine.egg-info\")")
	install(CODE "file(REMOVE_RECURSE \"${CMAKE_SOURCE_DIR}/python/build\" 
	    \"${CMAKE_SOURCE_DIR}/python/dist\" 
	    \"${CMAKE_SOURCE_DIR}/python/SeetaFaceEngine.egg-info\"
	    \"${CMAKE_SOURCE_DIR}/python/pyseeta/__pycache__\")")

endif()

