cmake_minimum_required(VERSION 2.8.3)
project(comm_ugv)
##set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
find_package(catkin REQUIRED 
	COMPONENTS 
	roscpp 
	rospy 
	geometry_msgs
	tf)

catkin_package()

#roslaunch_add_file_check(launch)

add_executable(comm_ugv src/comm_ugv.cpp)

add_dependencies(comm_ugv ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(comm_ugv ${catkin_LIBRARIES})

#catkin_install_python(PROGRAMS scripts/stow_ur5 DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY config launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY scripts
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS comm_ugv RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
