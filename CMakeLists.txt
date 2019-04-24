#CMAKE_MINIMUM_REQUIRED(version 2.8)
	set(LIBFLOWCATCH_LIST
		flowcatch.cpp
		eyedetect.cpp
		facedetect.cpp
		readsenior.cpp 
		)
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/LIB_OPENCV/share/OpenCV)
	
	set(CMAKE_BUILD_TYPE "Debug")
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
	
	#detect if it supports c++11 compiler option	
	include(CheckCXXCompilerFlag)  
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)	
	
	#set(CMAKE_EXE_LINKER_FLAGS "-lpthread -lrt")
	#Use C++11
	if(COMPILER_SUPPORTS_CXX11)  
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")  
	elseif(COMPILER_SUPPORTS_CXX0X)  
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
	else()  
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
	endif()  

	#set the output 路径
	#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)	

	#using OpenCV 3.1.0
	#set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/lib/LIB_OPENCV/share/OpenCV)
	
	#Find DLIB lib path
	FIND_LIBRARY(DLIB_LIB libdlib.so ${PROJECT_SOURCE_DIR}/lib NO_DEFAULT_PATH)


	#Find OpenCV lib path
	find_package(OpenCV REQUIRED)	
	MESSAGE(STATUS "Libs: "${Opencv_LIBS})
	#	INCLUDE_DIRECTORIES(/usr/local/include
	#						${project_source_dir}
	#						/usr/include/)
	#	link_directories(
	#		/usr/local/lib
	#		)
	#ADD_LIBRARY(flowcatch SHARED ${LIBFLOWCATCH_LIST})
	#ADD_LIBRARY(flowcatch_static STATIC ${LIBFLOWCATCH_LIST})
	ADD_EXECUTABLE(main ${LIBFLOWCATCH_LIST})
	TARGET_LINK_LIBRARIES(main ${DLIB_LIB} ${OpenCV_LIBS})

	#	TARGET_LINK_LIBRARIES(flowcatch ${DLIB_LIB} ${OpenCV_LIBS})
	#	TARGET_LINK_LIBRARIES(flowcatch_static ${DLIB_LIB} ${OpenCV_LIBS})
	#	
	#	#this version=1.0
	#	SET_TARGET_PROPERTIES(flowcatch PROPERTIES VERSION 1.0 SOVERSION 1)
	#	SET_TARGET_PROPERTIES(flowcatch_static PROPERTIES OUTPUT_NAME "flowcatch" VERSION 1.0 SOVERSION 1)
	#
	#	SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../prework)
	#	INSTALL(TARGETS flowcatch flowcatch_static 
	#			LIBRARY DESTINATION lib
	#			ARCHIVE DESTINATION lib)
	#	INSTALL(FILES victor.h DESTINATION include)
	
