cmake_minimum_required(VERSION 3.11)

set(PROJECT_VERSION "0.1.0")
set(BLOCK_TYPES_BASIC_CPP_VERSION "0.1.0")
set(PROJECT_VERSION_UNDERSCORE "0_1_0")

# Project name and version
project(BlockLibrariesBasicBlocksBasicCpp VERSION ${PROJECT_VERSION})

set(INSTALLED_DYNAMIC_LIB_NAME "BlockLibrariesBasicBlocksBasicCpp-${PROJECT_VERSION}")

set(PLUGIN_INSTALL_DIR lib/pysyslink_plugins/basic_blocks_basic_cpp_${PROJECT_VERSION_UNDERSCORE})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Check if the user has already set CMAKE_INSTALL_PREFIX
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Configure default installation paths based on the platform
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "C:/Program Files" CACHE PATH "Install path" FORCE)
    elseif(APPLE)
        set(CMAKE_INSTALL_PREFIX "/Applications" CACHE PATH "Install path" FORCE)
    else() # Assume Linux or other Unix-like systems
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path" FORCE)
    endif()
endif()

# Print the chosen installation path
message(STATUS "Default install path: ${CMAKE_INSTALL_PREFIX}")

# Locate PySysLinkBase
find_package(BlockTypesBasicCpp ${BLOCK_TYPES_BASIC_CPP_VERSION} REQUIRED)

# Add subdirectories
add_subdirectory(src)
# add_subdirectory(Tests)


# set(PY_SYS_LINK_BASE_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
# set(PY_SYS_LINK_BASE_LIBRARIES "${CMAKE_INSTALL_PREFIX}/lib/libBlockLibrariesBasicBlocksBasicCpp.a")

message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

# Define installation rules for the project
install(DIRECTORY src/                # Install headers
    DESTINATION include/BlockLibraries/BasicBlocksBasicCpp
    FILES_MATCHING PATTERN "*.h"
)

install(TARGETS BlockLibrariesBasicBlocksBasicCpp
    EXPORT BlockLibrariesBasicBlocksBasicCppTargets # Associate this target with the export
    ARCHIVE DESTINATION ${PLUGIN_INSTALL_DIR}
    LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
    RUNTIME DESTINATION bin
)

configure_file(
    ${CMAKE_SOURCE_DIR}/basic_blocks_basic_cpp.pslkp.yaml.in
    ${CMAKE_BINARY_DIR}/basic_blocks_basic_cpp.${PROJECT_VERSION_UNDERSCORE}.pslkp.yaml
    @ONLY
)

install(FILES ${CMAKE_BINARY_DIR}/basic_blocks_basic_cpp.${PROJECT_VERSION_UNDERSCORE}.pslkp.yaml
    DESTINATION ${PLUGIN_INSTALL_DIR}
)


include(CMakePackageConfigHelpers)

# Generate the package configuration file for BlockLibrariesBasicBlocksBasicCpp
install(EXPORT BlockLibrariesBasicBlocksBasicCppTargets
    FILE BlockLibrariesBasicBlocksBasicCppTargets.cmake
    NAMESPACE BlockLibraries::BasicBlocksBasicCpp::
    DESTINATION lib/cmake/BlockLibrariesBasicBlocksBasicCpp
)

# Set the include directories and libraries for the package
set(PACKAGE_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
set(PACKAGE_LIBRARIES "${CMAKE_INSTALL_PREFIX}/${PLUGIN_INSTALL_DIR}")


write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BlockLibrariesBasicBlocksBasicCppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create and install the config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/BlockLibrariesBasicBlocksBasicCppConfig.cmake.in
    ${CMAKE_BINARY_DIR}/BlockLibrariesBasicBlocksBasicCppConfig.cmake
    INSTALL_DESTINATION lib/cmake/BlockLibrariesBasicBlocksBasicCpp
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/BlockLibrariesBasicBlocksBasicCppConfig.cmake
    FILES ${CMAKE_CURRENT_BINARY_DIR}/BlockLibrariesBasicBlocksBasicCppConfigVersion.cmake
    DESTINATION lib/cmake/BlockLibrariesBasicBlocksBasicCpp
)


# Ensure the libraries are installed correctly
install(TARGETS BlockLibrariesBasicBlocksBasicCpp
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)


if(UNIX AND NOT APPLE) # Linux-specific
    install(CODE "execute_process(COMMAND ldconfig)")
endif()
