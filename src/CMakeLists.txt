project(laplace-equation-3D)

set(HEADERS
	#	${HEADER_DIR}/*.h
	)


set(SOURCES
		rosenthal.cpp 
	)


add_executable(rosenthal ${SOURCES} ${HEADERS})

target_link_libraries(rosenthal
		${VTK_LIBRARIES}
	)
