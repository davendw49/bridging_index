cmake_minimum_required(VERSION 3.10.2)
project(BridgeIndex)

set(CMAKE_CXX_STANDARD 17)

add_executable(BridgeIndex main.cpp map.cpp map.h calculate.cpp calculate.h getFileName.cpp getFileName.h dateConverse.cpp dateConverse.h getIDbyNum.cpp getIDbyNum.h)

add_custom_target(clean_all
	COMMAND make clean
	COMMAND rm -rf sample_*
)


