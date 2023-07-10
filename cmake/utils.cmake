macro(link_lib LIB_NAME)
    target_link_libraries(${LIB_NAME} ${ARGN})
endmacro(link_lib LIB_NAME)


macro(setup_lib LIB_NAME)
    add_library(${LIB_NAME}
        SHARED
        ${TARGET_H}
        ${TARGET_C}
    )

    target_include_directories(${LIB_NAME}
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include
    )

    if(DEPEND_LIBS)
        link_lib(${LIB_NAME} ${DEPEND_LIBS})
    endif()

endmacro(setup_lib LIB_NAME)
