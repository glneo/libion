cmake_minimum_required(VERSION 2.8)
PROJECT(ion)
set(PROJECT_DESCRIPTION "ION Userspace Memory Allocator Library")
set(PROJECT_VERSION 1.0.0)

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
)

configure_file(libion.pc.in libion.pc @ONLY)

install(TARGETS ion
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/ion)
install(FILES ${CMAKE_BINARY_DIR}/libion.pc
	DESTINATION lib/pkgconfig)
