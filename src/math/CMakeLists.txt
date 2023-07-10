set(LIB_NAME math)
set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME})

set(TARGET_H
    ${HEADER_PATH}/vec.h
    ${HEADER_PATH}/mat.h
)

set(TARGET_C
    vec.c
    mat.c
)

setup_lib(${LIB_NAME})
