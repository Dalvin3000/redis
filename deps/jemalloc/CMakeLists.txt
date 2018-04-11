CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)
PROJECT(jemalloc)

SET(SOURCES
    src/arena.c
    src/background_thread.c
    src/base.c
    src/bitmap.c
    src/ckh.c
    src/ctl.c
    src/extent_dss.c
    src/extent_mmap.c
    src/extent.c
    src/hash.c
    src/hooks.c
    src/jemalloc.c
    src/large.c
    src/malloc_io.c
    src/mutex_pool.c
    src/mutex.c
    src/nstime.c
    src/pages.c
    src/prng.c
    src/prof.c
    src/rtree.c
    src/spin.c
    src/stats.c
    src/sz.c
    src/tcache.c
    src/ticker.c
    src/tsd.c
    src/witness.c
)

IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/jemalloc/jemalloc.h")
        MESSAGE(STATUS "Executing ${CMAKE_CURRENT_SOURCE_DIR}/autogen.sh")

    EXECUTE_PROCESS(
        COMMAND sh -c "./autogen.sh"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        ERROR_VARIABLE ERROR
        RESULT_VARIABLE RESULT
    )
ENDIF()

IF(RESULT)
    MESSAGE(FATAL_ERROR "Jemalloc preconfig script run failed.")
ENDIF()

ADD_LIBRARY(${PROJECT_NAME} ${SOURCES})

TARGET_COMPILE_OPTIONS(${PROJECT_NAME}
    PRIVATE -std=gnu11 -fvisibility=hidden -Wall -Wsign-compare -Wundef -O3 -funroll-loops -c
    PUBLIC -fPIC
)

TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME}
    PUBLIC
        -DPIC
        -D_GNU_SOURCE
        -D_REENTRANT=1
        -DJEMALLOC_NO_PRIVATE_NAMESPACE
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

