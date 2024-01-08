cmake_minimum_required(VERSION 3.8)

project(hrt-prep VERSION 1.0.0 LANGUAGES CXX)

function(get_repo_root root)
    execute_process(COMMAND git rev-parse --show-cdup
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        OUTPUT_VARIABLE relative_path_to_repository_root)

    get_filename_component(repository_root
        "${CMAKE_CURRENT_LIST_DIR}/${relative_path_to_repository_root}"
        ABSOLUTE)

    string(STRIP ${repository_root} repository_root)

    # This is the correct way to get the variable name passed to the function
    set(${root} ${repository_root} PARENT_SCOPE)
endfunction(get_repo_root)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(BIN_ROOT ${DIR}/bin)

list(APPEND
    TASK_LIST
    "Manhattan"
)

message(STATUS "====Building HRT Preb project====")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_ROOT})

get_repo_root(repo_root)
message(STATUS "===Including Small Test Framework: ${repo_root}/Small-Test-Framework ===")
include_directories(${repo_root}/Small-Test-Framework)

foreach(TASK ${TASK_LIST})
    message(STATUS "Creating executable \"${TASK}\"")
    # Executable name
    set(TARGET_NAME ${TASK})

    # All the sources to be linked
    set(SOURCE_FILES 
        ${DIR}/${TARGET_NAME}/solution.cc
    )

    # Create an executable from the source files
    add_executable(${TARGET_NAME} ${SOURCE_FILES})
endforeach()