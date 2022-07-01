cmake_minimum_required(VERSION 3.0.2)
project(servo_test)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation # Message生成依赖
)


################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
## 这里添加msg文件夹下的msg文件名称
add_message_files(
  FILES
  ServoAngle.msg     # 设置舵机角度
  #SetServoDamping.msg   # 设置舵机为阻尼模式
)

## Generate services in the 'srv' folder
#add_service_files(
  #FILES
  #QueryServoAngle.srv  # 舵机角度查询服务

#)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)


###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES servo_test
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
set(CMAKE_INSTALL_PREFIX /usr/local)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_INSTALL_PREFIX}/include
)

# 设置串口总线舵机链接库的位置
link_directories(
  ${CMAKE_INSTALL_PREFIX}/lib
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
## 定义C++可执行文件
# - 串口总线舵机服务示例节点
add_executable(uservo_demo_node src/servo_demo_sub.cpp)

add_executable(test_set_angle_node src/servo_demo_pub.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(uservo_demo_node
  ${catkin_LIBRARIES}
  cserialport # 轻量级串口通信库
  fsuartservo # FashionStar串口总线舵机SDK (C++)
)

target_link_libraries(test_set_angle_node
  ${catkin_LIBRARIES}
)
