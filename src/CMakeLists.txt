# Define a library
add_library(BlockLibrariesBasicBlocksBasicCpp SHARED
    Constant.cpp
    Display.cpp
    Adder.cpp 
    BasicCppFactory.cpp
    Accumulator.cpp
    Integrator.cpp
    ContinuousToDiscrete.cpp
    RegisterBasicCppFactories.cpp
    Gain.cpp
)

target_include_directories(BlockLibrariesBasicBlocksBasicCpp PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(BlockLibrariesBasicBlocksBasicCpp PRIVATE BlockTypesBasicCpp)

# Include directories for header files
target_include_directories(BlockLibrariesBasicBlocksBasicCpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # Include path for the build tree
        $<INSTALL_INTERFACE:include>                   # Include path for the installed tree
)
