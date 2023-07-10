set(LIB_NAME glad)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME})

set(TARGET_H
    ${HEADER_PATH}/glad.h
)

set(TARGET_C
    glad.c
)

setup_lib(${LIB_NAME})
