cmake_minimum_required (VERSION 3.13)
if (MSVC)
set (CMAKE_SYSTEM_VERSION 10.0.22000.0)
endif (MSVC)
project (Fuel VERSION ${PROMETHEUS_VERSION} DESCRIPTION "Fuel Calculation Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

SET(LOWLEVEL_INCLUDE_DIR "error" CACHE STRING "The path to the includes from HSS LowLevel")
SET(WTIME_INCLUDE_DIR "error" CACHE STRING "The path to the WTime libraries includes")
SET(MULTITHREAD_INCLUDE_DIR "error" CACHE STRING "The path to the includes from HSS Multithread")
SET(MATH_INCLUDE_DIR "error" CACHE STRING "The path to HSS_Math include files")
SET(THIRD_PARTY_INCLUDE_DIR "error" CACHE STRING "The path to third party include files")
SET(BOOST_INCLUDE_DIR "error" CACHE STRING "The path to boost include files")
SET(ERROR_CALC_INCLUDE_DIR "error" CACHE STRING "The path to the error calc include files")
SET(FWI_INCLUDE_DIR "error" CACHE STRING "The path to the FWI include files")
SET(FIREENGINE_INCLUDE_DIR "error" CACHE STRING "The path to the fire engine include files")
SET(GRID_INCLUDE_DIR "error" CACHE STRING "The path to the grid include files")
SET(GDAL_INCLUDE_DIR "error" CACHE STRING "The path to the GDAL include files")
SET(GSL_INCLUDE_DIR "error" CACHE STRING "The path to the GSL include files")
SET(PROTOBUF_INCLUDE_DIR "error" CACHE STRING "The path to the protobuf include files")

find_library(FOUND_MULTITHREAD_LIBRARY_PATH NAMES Multithread REQUIRED PATHS ${LOCAL_LIBRARY_DIR})
find_library(FOUND_LOWLEVEL_LIBRARY_PATH NAMES LowLevel REQUIRED PATHS ${LOCAL_LIBRARY_DIR})
find_library(FOUND_WTIME_LIBRARY_PATH NAMES WTime REQUIRED PATHS ${LOCAL_LIBRARY_DIR})
find_library(FOUND_MATH_LIBRARY_PATH NAMES hssmath REQUIRED PATHS ${LOCAL_LIBRARY_DIR})
find_library(FOUND_PROTOBUF_LIBRARY_PATH NAMES protobuf libprotobuf REQUIRED PATHS ${PROTOBUF_LIBRARY_DIR})
find_library(FOUND_FWI_LIBRARY_PATH NAMES fwi REQUIRED PATHS ${LOCAL_LIBRARY_DIR})

if (MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -DPROTOBUF_USE_DLLS -DBOOST_ALL_DYN_LINK -D_CRT_SECURE_NO_WARNINGS /Zc:__cplusplus")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD -D_AFXDLL")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd -D_AFXDLL /W4")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS atomic REQUIRED PATHS ${BOOST_LIBRARY_DIR})
else ()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(Boost_LIBRARIES "")
endif (MSVC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_NO_MFC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG -DDEBUG")

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

add_library(fuel SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FuelConfig.h
    cpp/accAlpha.pb.cc
    cpp/ccwfgmFuel.pb.cc
    cpp/cfb.pb.cc
    cpp/dbh.pb.cc
    cpp/flame.pb.cc
    cpp/fmc.pb.cc
    cpp/fuelNames.pb.cc
    cpp/isf.pb.cc
    cpp/lb.pb.cc
    cpp/rsi.pb.cc
    cpp/sfc.pb.cc
    cpp/spreadParms.pb.cc
    cpp/tfc.pb.cc
    cpp/AccAlpha.cpp
    cpp/cfb.cpp
    cpp/CWFGM_Fuel_Shared.cpp
    cpp/CWFGM_Fuel.cpp
    cpp/CWFGM_Fuel.Serialize.cpp
    cpp/FBPFuel.cpp
    cpp/flame.cpp
    cpp/fmc.cpp
    cpp/FuelAttribute.cpp
    cpp/ICWFGM_CommonBase.cpp
    cpp/isf.cpp
    cpp/lb.cpp
    cpp/RSI.cpp
    cpp/SFC.cpp
    cpp/SpreadParms.cpp
    cpp/tfc.cpp
)

target_include_directories(fuel
    PUBLIC ${WTIME_INCLUDE_DIR}
    PUBLIC ${PROTOBUF_INCLUDE_DIR}
    PUBLIC ${LOWLEVEL_INCLUDE_DIR}
    PUBLIC ${MULTITHREAD_INCLUDE_DIR}
    PUBLIC ${ERROR_CALC_INCLUDE_DIR}
    PUBLIC ${THIRD_PARTY_INCLUDE_DIR}
    PUBLIC ${MATH_INCLUDE_DIR}
    PUBLIC ${FWI_INCLUDE_DIR}
    PUBLIC ${FIREENGINE_INCLUDE_DIR}
    PUBLIC ${GRID_INCLUDE_DIR}
    PUBLIC ${GDAL_INCLUDE_DIR}
    PUBLIC ${GSL_INCLUDE_DIR}
    PUBLIC ${BOOST_INCLUDE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(fuel PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
set_target_properties(fuel PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
set_target_properties(fuel PROPERTIES DEFINE_SYMBOL "FUEL_EXPORTS")

set_target_properties(fuel PROPERTIES
    PUBLIC_HEADER include/AccAlpha.h
    PUBLIC_HEADER include/accAlpha.pb.h
    PUBLIC_HEADER include/ccwfgmFuel.pb.h
    PUBLIC_HEADER include/cfb.h
    PUBLIC_HEADER include/cfb.pb.h
    PUBLIC_HEADER include/CWFGM_Fuel_Shared.h
    PUBLIC_HEADER include/dbh.pb.h
    PUBLIC_HEADER include/FBPFuel.h
    PUBLIC_HEADER include/flame.h
    PUBLIC_HEADER include/flame.pb.h
    PUBLIC_HEADER include/fmc.h
    PUBLIC_HEADER include/FuelAttribute.h
    PUBLIC_HEADER include/FuelCom_ext.h
    PUBLIC_HEADER include/fuelNames.h
    PUBLIC_HEADER include/ICWFGM_CommonBase.h
    PUBLIC_HEADER include/ICWFGM_FBPFuel.h
    PUBLIC_HEADER include/ICWFGM_Fuel.h
    PUBLIC_HEADER include/ISerializeProto.h
    PUBLIC_HEADER include/isf.h
    PUBLIC_HEADER include/isf.pb.h
    PUBLIC_HEADER include/lb.h
    PUBLIC_HEADER include/lb.pb.h
    PUBLIC_HEADER include/rsi.h
    PUBLIC_HEADER include/sfc.h
    PUBLIC_HEADER include/sfc.pb.h
    PUBLIC_HEADER include/SpreadParams.h
    PUBLIC_HEADER include/spreadParams.pb.h
    PUBLIC_HEADER include/tfc.h
    PUBLIC_HEADER include/tfc.pb.h
)

target_link_libraries(fuel ${Boost_LIBRARIES} ${FOUND_FWI_LIBRARY_PATH} ${FOUND_PROTOBUF_LIBRARY_PATH} ${FOUND_WTIME_LIBRARY_PATH} ${FOUND_LOWLEVEL_LIBRARY_PATH} ${FOUND_MULTITHREAD_LIBRARY_PATH} ${FOUND_MATH_LIBRARY_PATH})
if (MSVC)
else ()
target_link_libraries(fuel -lstdc++fs)
endif (MSVC)
