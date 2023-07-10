set(LIB_NAME mpool)
set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME})

set(TARGET_H
    ${HEADER_PATH}/mpool.h
)

set(TARGET_C
    mpool.c
)

setup_lib(${LIB_NAME})
