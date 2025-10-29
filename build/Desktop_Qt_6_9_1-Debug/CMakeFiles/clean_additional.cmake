# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appnovelist_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appnovelist_autogen.dir/ParseCache.txt"
  "appnovelist_autogen"
  "libai/CMakeFiles/libai_autogen.dir/AutogenUsed.txt"
  "libai/CMakeFiles/libai_autogen.dir/ParseCache.txt"
  "libai/CMakeFiles/libaiplugin_autogen.dir/AutogenUsed.txt"
  "libai/CMakeFiles/libaiplugin_autogen.dir/ParseCache.txt"
  "libai/CMakeFiles/libaiplugin_init_autogen.dir/AutogenUsed.txt"
  "libai/CMakeFiles/libaiplugin_init_autogen.dir/ParseCache.txt"
  "libai/libai_autogen"
  "libai/libaiplugin_autogen"
  "libai/libaiplugin_init_autogen"
  "libnovelist/CMakeFiles/libnovelist_autogen.dir/AutogenUsed.txt"
  "libnovelist/CMakeFiles/libnovelist_autogen.dir/ParseCache.txt"
  "libnovelist/CMakeFiles/libnovelistplugin_autogen.dir/AutogenUsed.txt"
  "libnovelist/CMakeFiles/libnovelistplugin_autogen.dir/ParseCache.txt"
  "libnovelist/CMakeFiles/libnovelistplugin_init_autogen.dir/AutogenUsed.txt"
  "libnovelist/CMakeFiles/libnovelistplugin_init_autogen.dir/ParseCache.txt"
  "libnovelist/libnovelist_autogen"
  "libnovelist/libnovelistplugin_autogen"
  "libnovelist/libnovelistplugin_init_autogen"
  )
endif()
