set(THIS_DIR ${DIR}/algorithms)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR}/bin/algorithms)

set(MYLIST  "median_of_two_vectors;merge_sorted_lists;"
            "regular_expression_matching;simplify_path;"
            "score_of_parentheses;shortest_unsorted_subarray;"
            "shuffle_an_array;min_stack")
foreach(LETTER ${MYLIST})
    # Executable name
    set(TARGET_NAME ${LETTER})

    # All the sources to be linked
    set(SOURCE_FILES 
        ${THIS_DIR}/${TARGET_NAME}.cpp
    )

    # Create an executable from the source files
    add_executable(${TARGET_NAME} ${SOURCE_FILES})
endforeach()