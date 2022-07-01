cmake_minimum_required(VERSION 2.8.3)
project(robot_arm_control)

find_package(catkin_simple REQUIRED)

#uncomment next line to use OpenCV library
#find_package(OpenCV REQUIRED)

#uncomment the next 2 lines to use the point-cloud library
#find_package(PCL 1.7 REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})


#uncomment the following 4 lines to use the Eigen library
#find_package(cmake_modules REQUIRED)
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})
#add_definitions(${EIGEN_DEFINITIONS})
# set(CMAKE_INSTALL_PREFIX /usr/local)
# include_directories(
# # include
#   ${catkin_INCLUDE_DIRS}
#   ${CMAKE_INSTALL_PREFIX}/include
# )

# link_directories(
#   ${CMAKE_INSTALL_PREFIX}/lib
# )

catkin_simple()

# example boost usage
# find_package(Boost REQUIRED COMPONENTS system thread)

# C++0x support - not quite the same as final C++11!
# use carefully;  can interfere with point-cloud library
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Libraries: uncomment the following and edit arguments to create a new library
# cs_add_library(my_lib src/my_lib.cpp)   


# Executables: uncomment the following and edit arguments to compile new nodes
# may add more of these lines for more nodes from the same package

cs_add_executable(ArmControllerServer src/ArmControllerServer.cpp)
cs_add_executable(robot_arm_service src/arm_service_copy.cpp)
cs_add_executable(robot_arm_client src/arm_client_copy.cpp)
cs_add_executable(robot_arm_client_3.0 src/arm_client_3.0.cpp)
cs_add_executable(path_list src/path_planning.cpp)
cs_add_executable(path_actuator src/path_actuator.cpp)
cs_add_executable(move_uno src/move_uno_client.cpp)

#cs_add_executable(path_actuator_servo src/path_actuator_servo.cpp)
#cs_add_executable(servo_sub src/servo_sub.cpp)


######################################
#cs_add_executable(robot_mini_jointController_cxy src/mini_joint_controller.cpp)
#cs_add_executable(robot_mini_jointController src/minimal_joint_controller.cpp)
#the following is required, if desire to link a node in this package with a library created in this same package
# edit the arguments to reference the named node and named library within this package
#target_link_libraries(servo_sub
#    ${catkin_LIBRARIES}
#    cserialport
#    fsuartservo
#)

cs_install()
cs_export()
    
