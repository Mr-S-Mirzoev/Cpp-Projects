set(THIS_DIR ${DIR}/concurency)
set(BIN_ROOT ${DIR}/bin/concurency)

# Find threads package to link with -pthread
find_package( Threads )

list(APPEND  
    EASY_LIST
    "print_in_order"
)
list(APPEND
    MEDIUM_LIST
    "print_foobar"
    "hydrogen"
)

list(APPEND 
     TASK_LIST  
     "EASY_LIST" 
     "MEDIUM_LIST"
)

list(APPEND 
     LEVEL_LIST 
     "easy"
     "medium"
)
list(LENGTH LEVEL_LIST level_count)
math(EXPR list_max_index ${list_count}-1)

message(STATUS "====Building Concurency subproject====")

foreach(i RANGE ${list_max_index})
    list(GET TASK_LIST ${i} CURRENT_LEVEL_LIST_NAME)
    list(GET LEVEL_LIST ${i} LEVEL_NAME)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_ROOT}/${LEVEL_NAME})

    foreach(LETTER ${${CURRENT_LEVEL_LIST_NAME}})
        message(STATUS "Creating executable \"${LETTER}\" from level: \"${LEVEL_NAME}\"")

        # Executable name
        set(TARGET_NAME ${LETTER})

        # All the sources to be linked
        set(SOURCE_FILES 
            ${THIS_DIR}/${LEVEL_NAME}/${TARGET_NAME}.cc
        )

        # Create an executable from the source files
        add_executable(${TARGET_NAME} ${SOURCE_FILES})

        # Link with pthread
        target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})
    endforeach()
endforeach()
