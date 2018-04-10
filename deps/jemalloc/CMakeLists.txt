CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)
PROJECT(jemalloc)

SET(SOURCES
    src/jemalloc.c
    src/arena.c
    src/atomic.c
    src/base.c
    src/bitmap.c
    src/chunk.c
    src/chunk_dss.c
    src/chunk_mmap.c
    src/ckh.c
    src/ctl.c
    src/extent.c
    src/hash.c
    src/huge.c
    src/mb.c
    src/mutex.c
    src/pages.c
    src/prof.c
    src/quarantine.c
    src/rtree.c
    src/stats.c
    src/tcache.c
    src/util.c
    src/tsd.c
)

ADD_LIBRARY(${PROJECT_NAME} ${SOURCES})

TARGET_COMPILE_OPTIONS(${PROJECT_NAME}
    PRIVATE -Wall -Wall -pipe -O3 -funroll-loops  -fvisibility=hidden
    PUBLIC -fPIC -std=gnu99
)

TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME}
    PRIVATE -Denable_valgrind=0
    PUBLIC -DPIC -DCMAKE_JEMALLOC -DJEMALLOC_HAVE_SECURE_GETENV
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

