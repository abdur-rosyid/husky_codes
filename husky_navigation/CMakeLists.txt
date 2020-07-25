cmake_minimum_required(VERSION 2.8.3)
project(husky_navigation)

find_package(catkin REQUIRED COMPONENTS roslaunch roscpp geometry_msgs actionlib actionlib_msgs tf)

catkin_package()
catkin_package(CATKIN_DEPENDS roscpp actionlib actionlib_msgs tf)

roslaunch_add_file_check(launch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(map_navigation src/map_navigation.cpp)
add_executable(demoTfListener src/example_tf_listener.cpp)

add_dependencies(map_navigation ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(map_navigation ${catkin_LIBRARIES})
add_dependencies(demoTfListener ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(demoTfListener ${catkin_LIBRARIES})

install(TARGETS map_navigation demoTfListener RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(
  DIRECTORY config launch maps params src
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

