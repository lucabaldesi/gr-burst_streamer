find_package(PkgConfig)

PKG_CHECK_MODULES(PC_BURST_STREAMER burst_streamer)

FIND_PATH(
    BURST_STREAMER_INCLUDE_DIRS
    NAMES burst_streamer/api.h
    HINTS $ENV{BURST_STREAMER_DIR}/include
        ${PC_BURST_STREAMER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    BURST_STREAMER_LIBRARIES
    NAMES gnuradio-burst_streamer
    HINTS $ENV{BURST_STREAMER_DIR}/lib
        ${PC_BURST_STREAMER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/burst_streamerTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BURST_STREAMER DEFAULT_MSG BURST_STREAMER_LIBRARIES BURST_STREAMER_INCLUDE_DIRS)
MARK_AS_ADVANCED(BURST_STREAMER_LIBRARIES BURST_STREAMER_INCLUDE_DIRS)
