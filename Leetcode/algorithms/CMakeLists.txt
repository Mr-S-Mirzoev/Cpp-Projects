set(THIS_DIR ${DIR}/algorithms)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR}/bin/algorithms)

# Executable name
set(TARGET_NAME median_of_two_vectors)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/median_of_two_vectors.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Executable name
set(TARGET_NAME merge_sorted_lists)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/merge_sorted_lists.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Executable name
set(TARGET_NAME regular_expression_matching)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/regular_expression_matching.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Executable name
set(TARGET_NAME simplify_path)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/simplify_path.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Executable name
set(TARGET_NAME score_of_parentheses)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/score_of_parentheses.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})