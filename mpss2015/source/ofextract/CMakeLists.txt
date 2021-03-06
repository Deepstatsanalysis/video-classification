
set(target ofextract)
message(STATUS "Lib ${target}")


# External libraries

find_package(OpenCV REQUIRED)

add_definitions(-DBOOST_ALL_NO_LIB)
find_package(Boost COMPONENTS system filesystem regex REQUIRED)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/cuda/lib64/)

# Includes

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    /home/mpss2015m_1/poco-1.6.0/Foundation/include
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Libraries

set(libs
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
    /home/mpss2015m_1/poco-1.6.0/lib/Linux/x86_64/libPocoFoundation.so
)


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-D${META_PROJECT_NAME_UPPER}_STATIC")
else()
    add_definitions("-DFIBLIB_EXPORTS")
endif()


# Sources

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(api_includes
    ${include_path}/ofextract_api.h
    ${include_path}/Fibonacci.h
    ${include_path}/BroxOpticalFlow.h
)

set(sources
    ${source_path}/Fibonacci.cpp
    ${source_path}/BroxOpticalFlow.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# Build library

add_library(${target} ${api_includes} ${sources})

target_link_libraries(${target} ${libs})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})


# Deployment

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
