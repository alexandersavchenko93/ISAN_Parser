cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)

set(This ISANParserTests)

set(Sources 
	main_tests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
	gtest_main
	ISANParser
)

add_test(
	NANE ${This}
	COMMAND ${This}

)
