cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(FaceDetection)
add_subdirectory(FaceAlignment)
add_subdirectory(FaceIdentification)


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

if (WIN32)
message(STATUS "execute_process(COMMAND ${CMAKE_SOURCE_DIR}/tools/rar x -ep seeta_fr_v1.0.part1.rar seeta_fr_v1.0.bin)")
execute_process(COMMAND "${CMAKE_SOURCE_DIR}/tools/rar" x -ep seeta_fr_v1.0.part1.rar seeta_fr_v1.0.bin
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/FaceIdentification/model")
message(STATUS "rename ${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin ${CMAKE_BINARY_DIR}/model/seeta_fr_v1.0.bin")
file(RENAME "${CMAKE_SOURCE_DIR}/FaceIdentification/model/seeta_fr_v1.0.bin" "${CMAKE_BINARY_DIR}/model/seeta_fr_v1.0.bin")
endif()

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

