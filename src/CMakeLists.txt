# Define a library
add_library(BlockLibrariesBasicBlocksBasicCpp SHARED
    RegisterBasicCppFactories.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories(BlockLibrariesBasicBlocksBasicCpp PRIVATE ${CMAKE_SOURCE_DIR}/src)


find_package(BlockTypeSupportsBasicCppSupport REQUIRED)

target_link_libraries(BlockLibrariesBasicBlocksBasicCpp
    PRIVATE
        BlockTypeSupports::BasicCppSupport::BlockTypeSupportsBasicCppSupport
)

# -------------------------------------------------------------------
# Eigen3 (system)
# -------------------------------------------------------------------
find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(BlockLibrariesBasicBlocksBasicCpp PRIVATE Eigen3::Eigen)

set_target_properties(BlockLibrariesBasicBlocksBasicCpp PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    VERSION ${PROJECT_VERSION}
    IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}${INSTALLED_DYNAMIC_LIB_NAME}.so"
    OUTPUT_NAME "${INSTALLED_DYNAMIC_LIB_NAME}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# -------------------------------------------------------------------
# Filesystem
# -------------------------------------------------------------------

# only if GCC version is 8 or lower, we need to link with stdc++fs for filesystem support

IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    EXECUTE_PROCESS(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
        OUTPUT_VARIABLE GCC_VERSION
    )
    if (GCC_VERSION VERSION_LESS 9)
        target_link_libraries(BlockLibrariesBasicBlocksBasicCpp PRIVATE stdc++fs)
    endif()
endif()

# Include directories for header files
target_include_directories(BlockLibrariesBasicBlocksBasicCpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Include path for the build tree
        $<INSTALL_INTERFACE:include>                   # Include path for the installed tree
)

target_link_options(BlockLibrariesBasicBlocksBasicCpp PRIVATE
    -static-libstdc++
    -static-libgcc
)