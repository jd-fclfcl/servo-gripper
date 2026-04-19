cmake_minimum_required(VERSION 3.14)
project(usb_serial)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(REAL_ROBOT "Enable Unitree motor SDK" OFF)
option(USE_ROS2 "Force build with ROS2" OFF)
option(USE_ROS1 "Force build with ROS1(catkin)" OFF)

# Eigen
find_package(Eigen3 QUIET)
if(Eigen3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# OpenCV
find_package(OpenCV QUIET)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

# Boost
find_package(Boost QUIET)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Unitree Legged SDK for real robot
if(REAL_ROBOT)
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/include/serialPort/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/include/unitreeMotor/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/include/IOPort
    )

    add_definitions(-DCOMPILE_WITHOUT_GO_M8010)

    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../_motor/lib)
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/lib/libUnitreeMotorSDK_Arm64.so)
    else()
        set(EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../_motor/lib/libUnitreeMotorSDK_Linux64.so)
    endif()
endif()

# 添加项目头文件路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/src
)

# ROS选择
set(BUILD_WITH_ROS2 OFF)
set(BUILD_WITH_ROS1 OFF)

if(USE_ROS2)
    find_package(rclcpp QUIET)
    if(rclcpp_FOUND)
        set(BUILD_WITH_ROS2 ON)
    else()
        message(WARNING "USE_ROS2=ON but ROS2 not found, continue without ROS")
    endif()
elseif(USE_ROS1)
    find_package(catkin QUIET COMPONENTS
        roscpp
        std_msgs
        geometry_msgs
        sensor_msgs
        tf2
        tf2_ros
    )
    if(catkin_FOUND)
        set(BUILD_WITH_ROS1 ON)
        catkin_package()
    else()
        message(WARNING "USE_ROS1=ON but catkin not found, continue without ROS")
    endif()
else()
    find_package(rclcpp QUIET)
    if(rclcpp_FOUND)
        set(BUILD_WITH_ROS2 ON)
    else()
        find_package(catkin QUIET COMPONENTS
            roscpp
            std_msgs
            geometry_msgs
            sensor_msgs
            tf2
            tf2_ros
        )
        if(catkin_FOUND)
            set(BUILD_WITH_ROS1 ON)
            catkin_package()
        endif()
    endif()
endif()

if(BUILD_WITH_ROS2)
    message(STATUS "Building with ROS2")
elseif(BUILD_WITH_ROS1)
    message(STATUS "Building with ROS1")
else()
    message(STATUS "Building without ROS (standalone)")
endif()

# 源文件
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/src/*.cc"
)

if(REAL_ROBOT)
    file(GLOB_RECURSE MOTOR_SRC_LIST CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/../_motor/src/*.cpp"
    )
    list(APPEND SRC_LIST ${MOTOR_SRC_LIST})
endif()

# 可执行文件
add_executable(usb_serial ${SRC_LIST})

# ROS依赖
if(BUILD_WITH_ROS1)
    include_directories(${catkin_INCLUDE_DIRS})
    target_link_libraries(usb_serial ${catkin_LIBRARIES})
endif()

# 链接库
target_link_libraries(usb_serial
    ${EXTRA_LIBS}
    pthread
    ${OpenCV_LIBS}
)

# 安装规则
install(TARGETS usb_serial
    DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_WITH_ROS2)
    find_package(ament_cmake QUIET)
    if(ament_cmake_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/package.xml")
        ament_package()
    endif()
endif()