echo
echo Cleaning...
rm -f -r CMakeFiles
rm -f cmake_install.cmake
rm -f CMakeCache.txt
rm -f OpenPT
echo
echo Generating CMake Project...
echo
cmake CMakeLists.txt
echo
echo Building Project...
echo
cmake --build ./
echo
echo Running Project...
echo
./OpenPT
echo
echo Test Complete!
echo