cmake_minimum_required(VERSION 3.0)
PROJECT(ion)
set(PROJECT_DESCRIPTION "ION Userspace Memory Allocator Library")
set(PROJECT_VERSION 1.0.0)

INCLUDE(GNUInstallDirs)

add_library(ion
	SHARED
		src/libion.c
)

set_target_properties(ion
	PROPERTIES
		VERSION ${PROJECT_VERSION}
		PUBLIC_HEADER include/ion/ion.h
)

target_include_directories(ion
	PUBLIC
		include
		include/kernel-headers/4.19
)

configure_file(libion.pc.in libion.pc @ONLY)

install(TARGETS ion
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ion)

install(DIRECTORY include/kernel-headers/4.19/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN "*.h")

install(FILES ${CMAKE_BINARY_DIR}/libion.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
