CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)
PROJECT(hiredis)

SET(SOURCES
    async.c
    dict.c
    hiredis.c
    net.c
    read.c
    sds.c
    test.c
)

ADD_LIBRARY(${PROJECT_NAME} ${SOURCES})

TARGET_COMPILE_OPTIONS(${PROJECT_NAME}
    PRIVATE -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-unused-function
    PUBLIC -fPIC
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

