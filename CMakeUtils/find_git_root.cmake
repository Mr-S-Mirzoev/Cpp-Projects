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
