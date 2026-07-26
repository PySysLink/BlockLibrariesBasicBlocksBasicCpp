# Define a library
add_library(BlockLibrariesBasicBlocksBasicCpp SHARED
    RegisterBasicCppFactories.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories(BlockLibrariesBasicBlocksBasicCpp PRIVATE ${CMAKE_SOURCE_DIR}/src)

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

# Include directories for header files
target_include_directories(BlockLibrariesBasicBlocksBasicCpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Include path for the build tree
        $<INSTALL_INTERFACE:include>                   # Include path for the installed tree
)
