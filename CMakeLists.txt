cmake_minimum_required (VERSION 3.10)
project (wxcd_collection)
find_package(wxWidgets REQUIRED net gl core base)
find_package(SDL2 REQUIRED)
include(${wxWidgets_USE_FILE})
include_directories(${SDL2_INCLUDE_DIRS})
# and for each of your dependent executable/library targets:
file(GLOB sources *.cpp *.c *.h *.hpp)
add_compile_options(-fno-PIC -O2)
add_executable(wxcd_collection ${sources})
set_target_properties(wxcd_collection PROPERTIES LINK_FLAGS "-no-pie -s")
target_link_libraries(wxcd_collection ${wxWidgets_LIBRARIES} ${SDL2_LIBRARIES})
install(TARGETS wxcd_collection DESTINATION wxcd_collection)
INSTALL(FILES wxcd_collection.desktop DESTINATION /usr/share/applications)
install(FILES classicmusic.png DESTINATION /usr/share/icons)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Anders J. Andersen")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Small GUI program to edit and play my music collection.")
include(CPack)
