set(LIB_NAME render)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include/${LIB_NAME})

set(TARGET_H
    ${HEADER_PATH}/shader.h
    ${HEADER_PATH}/texture.h
    ${HEADER_PATH}/camera.h
    ${HEADER_PATH}/scene.h
    ${HEADER_PATH}/boundingsphere.h
    ${HEADER_PATH}/rendercallback.h
    ${HEADER_PATH}/scene_info.h
)

set(TARGET_C
    shader.c
    texture.c
    camera.c
    scene.c
    boundingsphere.c
)

set(DEPEND_LIBS
    opengl32
    glad
    mpool
    math
)

setup_lib(${LIB_NAME})
