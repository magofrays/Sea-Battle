file(GLOB_RECURSE SRCFILES "*.cpp")
#target_sources(seabattle PRIVATE ${SRCFILES})

set(FILTERED_SOURCE_FILES)
set(IGNORE_FOLDERS)
set(IGNORE_FILES)

foreach(FILE ${SRCFILES})
    get_filename_component(FILE_DIR ${FILE} DIRECTORY)
    get_filename_component(FILE_NAME ${FILE} NAME)
    
    set(IGNORE FALSE)
    foreach(IGNORE_FOLDER ${IGNORE_FOLDERS})
        if(FILE_DIR MATCHES "${IGNORE_FOLDER}")
            set(IGNORE TRUE)
            break()
        endif()
    endforeach()
    foreach(IGNORE_FILE ${IGNORE_FILES})
        if(FILE_NAME MATCHES "${IGNORE_FILE}")
            set(IGNORE TRUE)
            break()
        endif()
    endforeach()

    if(NOT ${IGNORE})
        list(APPEND FILTERED_SOURCE_FILES ${FILE})
    endif()
endforeach()


target_sources(seabattle PRIVATE ${FILTERED_SOURCE_FILES})
