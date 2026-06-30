file(REMOVE_RECURSE
  "libLuxRegni.a"
  "libLuxRegni.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/LuxRegni.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
