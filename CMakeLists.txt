CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)
PROJECT(redis)

ADD_SUBDIRECTORY(deps/hiredis hiredis)
ADD_SUBDIRECTORY(deps/lua lua)
ADD_SUBDIRECTORY(deps/jemalloc jemalloc)
ADD_SUBDIRECTORY(deps/linenoise linenoise)

SET(SERVER_SOURCES
    src/adlist.c
    src/ae.c
    src/anet.c
    src/aof.c
    src/bio.c
    src/bitops.c
    src/blocked.c
    src/childinfo.c
    src/cluster.c
    src/config.c
    src/crc16.c
    src/crc64.c
    src/db.c
    src/debug.c
    src/defrag.c
    src/dict.c
    src/endianconv.c
    src/evict.c
    src/expire.c
    src/geo.c
    src/geohash_helper.c
    src/geohash.c
    src/hyperloglog.c
    src/intset.c
    src/latency.c
    src/lazyfree.c
    src/lzf_c.c
    src/lzf_d.c
    src/memtest.c
    src/module.c
    src/multi.c
    src/networking.c
    src/notify.c
    src/object.c
    src/pqsort.c
    src/pubsub.c
    src/quicklist.c
    src/rand.c
    src/rax.c
    src/rdb.c
    src/redis-check-aof.c
    src/redis-check-rdb.c
    src/release.c
    src/replication.c
    src/rio.c
    src/scripting.c
    src/sds.c
    src/sentinel.c
    src/server.c
    src/setproctitle.c
    src/sha1.c
    src/siphash.c
    src/slowlog.c
    src/sort.c
    src/sparkline.c
    src/syncio.c
    src/t_hash.c
    src/t_list.c
    src/t_set.c
    src/t_string.c
    src/t_zset.c
    src/util.c
    src/ziplist.c
    src/zipmap.c
    src/zmalloc.c
)

SET(CLIENT_SOURCES
    src/crc64.c
    src/ae.c
    src/anet.c
    src/adlist.c
    src/release.c
    src/zmalloc.c
    src/redis-cli.c
)

IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/release.h")
    MESSAGE(STATUS "Executing ${CMAKE_CURRENT_SOURCE_DIR}/src/mkreleasehdr.sh")
    EXECUTE_PROCESS(
        COMMAND sh -c "./mkreleasehdr.sh"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src"
        ERROR_VARIABLE ERROR
        RESULT_VARIABLE RESULT
    )
ENDIF()

IF(MSVC)
    SET(SERVER_SOURCES ${SERVER_SOURCES}
        src/platform/getopt.c
    )
ENDIF()

FIND_PACKAGE(Threads REQUIRED)

ADD_EXECUTABLE(redis-server ${SERVER_SOURCES})
ADD_EXECUTABLE(redis-cli ${CLIENT_SOURCES})

IF(MSVC)
    FIND_LIBRARY(PTHREAD_LIB
        NAMES
            pthreadVC2 pthreadVC2.lib
            pthreadVC pthreadVC.lib
            pthread pthread.lib
        PATH_SUFFIXES pthread
        PATHS
            ${CMAKE_SOURCE_DIR}/src/platform
            $ENV{LIB_ROOT}
    )
    IF(NOT PTHREAD_LIB)
        MESSAGE(FATAL_ERROR "pthreads-msvc not found")
    ENDIF()

    GET_FILENAME_COMPONENT(PTHREAD_INCLUDES "${PTHREAD_LIB}" DIRECTORY)
    SET_PROPERTY(TARGET Threads::Threads PROPERTY INTERFACE_LINK_LIBRARIES "${PTHREAD_LIB}")
    SET_PROPERTY(TARGET Threads::Threads PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${PTHREAD_INCLUDES}")

    TARGET_LINK_LIBRARIES(redis-server
        PRIVATE
            winmm
            pthread
            ${LUA_LIBRARIES}
    )
    TARGET_COMPILE_DEFINITIONS(redis-server
        PRIVATE
            /std:c++98
    )

    TARGET_LINK_LIBRARIES(redis-cli
        PRIVATE
            winmm
            pthread
    )
    TARGET_COMPILE_DEFINITIONS(redis-cli
        PRIVATE
            /std:c++98
    )

ELSEIF(CYGWIN)
ELSE()
ENDIF()

TARGET_COMPILE_OPTIONS(redis-server
    PRIVATE
        -std=c99 -pedantic
        -Wall -W -Wno-missing-field-initializers
)
TARGET_COMPILE_DEFINITIONS(redis-server
    PRIVATE
        -DBYTE_ORDER=LITTLE_ENDIAN
        -DUSE_JEMALLOC
)
TARGET_INCLUDE_DIRECTORIES(redis-server
    PRIVATE "${LUA_INCLUDE_DIR}"
)
TARGET_LINK_LIBRARIES(redis-server
    PRIVATE
        Threads::Threads
        hiredis
        lua
        jemalloc
)

TARGET_LINK_LIBRARIES(redis-cli
    PRIVATE
        Threads::Threads
        hiredis
        linenoise
)


