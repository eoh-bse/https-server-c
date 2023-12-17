cmake_minimum_required(VERSION 3.26)

if(NOT DEFINED CMAKE_X_STANDARD)
	set(CMAKE_C_STANDARD 17)
	set(CMAKE_C_STANDARD_REQUIRED ON)
	set(CMAKE_C_EXTENSIONS OFF)
endif()

project(https-server-c
	VERSION 0.1.0
	DESCRIPTION "C Template"
	LANGUAGES C)

set(DEBUG_FLAGS "-D_POSIX_C_SOURCE=200809L -g -Wall -Wpedantic -Wextra -Wconversion -pthread -fsanitize=address,undefined")
set(RELEASE_FLAGS "-D_POSIX_C_SOURCE=200809L -O2 -pthread")

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
	message("Using flags: ${DEBUG_FLAGS}")
	set(CMAKE_C_FLAGS ${DEBUG_FLAGS})
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
	message("Using flags: ${RELEASE_FLAGS}")
	set(CMAKE_C_FLAGS ${RELEASE_FLAGS})
else()
	message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

file(GLOB MAIN "${PROJECT_SOURCE_DIR}/src/main.c")
file(GLOB MODULES "${PROJECT_SOURCE_DIR}/src/modules/*.c")
add_executable(${PROJECT_NAME} ${MAIN} ${MODULES})
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

function(add_test_suite TEST_SUITE_NAME)
	file(GLOB TEST_FILES "${PROJECT_SOURCE_DIR}/tests/${TEST_SUITE_NAME}/*.c")
	add_executable(${TEST_SUITE_NAME} ${TEST_FILES} ${MODULES})
	target_include_directories(${TEST_SUITE_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/")
	target_link_libraries(${TEST_SUITE_NAME} PRIVATE unity)
	add_dependencies(${TEST_SUITE_NAME} unity)

	add_test(NAME ${TEST_SUITE_NAME} COMMAND ${TEST_SUITE_NAME})
endfunction()

enable_testing()
add_test_suite(modules)
