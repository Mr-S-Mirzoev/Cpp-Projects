set(THIS_DIR ${DIR}/algorithms)
set(BIN_ROOT ${DIR}/bin/algorithms)

list(APPEND  
    EASY_LIST
    "average_on_levels"
    "candies"
    "first_bad_version"
    "matching_the_rule"
    "min_stack"
)
list(APPEND
    MEDIUM_LIST
    "count_and_say"
    "minimal_price_in_store"
    "score_of_parentheses"
    "shortest_unsorted_subarray"
    "shuffle_an_array"
    "simplify_path"
    "solve_equation"
)
list(APPEND
    HARD_LIST
    "first_missing_positive"
    "median_of_two_vectors"
    "merge_sorted_lists"
    "palindrome_list"
    "regular_expression_matching" 
    "reverse_nodes_in_k_group"
    "substring_with_concatenation"
    "sudoku"
)

list(APPEND 
     TASK_LIST  
     "EASY_LIST" 
     "MEDIUM_LIST" 
     "HARD_LIST"
)

list(APPEND 
     LEVEL_LIST 
     "easy"
     "medium"
     "hard"
)

list(LENGTH LEVEL_LIST level_count)
math(EXPR list_max_index ${level_count}-1)

message(STATUS "====Building Algorithms subproject====")

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
    endforeach()
endforeach()