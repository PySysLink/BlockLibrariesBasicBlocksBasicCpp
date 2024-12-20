
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was BlockLibrariesBasicBlocksBasicCppConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# Specify the include directories and libraries
set_and_check(BLOCK_LIBRARIES_BASIC_BLOCKS_BASIC_CPP_INCLUDE_DIRS "/usr/local/include")
set_and_check(BLOCK_LIBRARIES_BASIC_BLOCKS_BASIC_CPP_LIBRARIES "/usr/local/lib")

# Set include directories for BlockTypeSupportsBasicCppSupport
set(BlockLibrariesBasicBlocksBasicCpp_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
set(BlockLibrariesBasicBlocksBasicCpp_LIBRARIES "/usr/local/lib")
