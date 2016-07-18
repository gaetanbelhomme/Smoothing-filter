# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 3.0)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()


# This project is designed to be built outside the Insight source tree.
project(main)

# Find ITK.
find_package(ITK REQUIRED)

# Find the QtWidgets library
#find_package(Qt5Widgets)

include(${ITK_USE_FILE})

#SmoothingFilter.cxx SmoothingFilter.hxx
add_executable(main main.cxx SmoothingFilter.hxx SmoothingFilter.h)

target_link_libraries(main ${ITK_LIBRARIES})
#target_link_libraries(main Qt5::Widgets)
