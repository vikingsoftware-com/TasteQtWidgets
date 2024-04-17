# Use ccache for faster builds when available
option(ENABLE_CCACHE "Use ccache" ON)

if(ENABLE_CCACHE)
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_FOUND}")
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_FOUND}")
        message(STATUS "Using ccache")
    endif()
else()
    set(CCACHE_FOUND FALSE)
endif()
