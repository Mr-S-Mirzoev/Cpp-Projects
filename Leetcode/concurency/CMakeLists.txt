set(THIS_DIR ${DIR}/concurency)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR}/bin/concurency)

# Find threads package to link with -pthread
find_package( Threads )

# Executable name
set(TARGET_NAME print_in_order)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/${TARGET_NAME}.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Link with pthread
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} )

# Executable name
set(TARGET_NAME print_foobar)

# All the sources to be linked
set(SOURCE_FILES 
    ${THIS_DIR}/${TARGET_NAME}.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Link with pthread
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} )