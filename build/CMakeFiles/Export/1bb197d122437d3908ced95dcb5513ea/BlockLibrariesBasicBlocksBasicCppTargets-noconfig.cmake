#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BlockLibraries::BasicBlocksBasicCpp::BlockLibrariesBasicBlocksBasicCpp" for configuration ""
set_property(TARGET BlockLibraries::BasicBlocksBasicCpp::BlockLibrariesBasicBlocksBasicCpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(BlockLibraries::BasicBlocksBasicCpp::BlockLibrariesBasicBlocksBasicCpp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libBlockLibrariesBasicBlocksBasicCpp.so"
  IMPORTED_SONAME_NOCONFIG "libBlockLibrariesBasicBlocksBasicCpp.so"
  )

list(APPEND _cmake_import_check_targets BlockLibraries::BasicBlocksBasicCpp::BlockLibrariesBasicBlocksBasicCpp )
list(APPEND _cmake_import_check_files_for_BlockLibraries::BasicBlocksBasicCpp::BlockLibrariesBasicBlocksBasicCpp "${_IMPORT_PREFIX}/lib/libBlockLibrariesBasicBlocksBasicCpp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
