project(DFS)

add_executable(DFSDemo DFS.cpp)
add_executable(MAZEDemo MazeGeneration.cpp)

target_include_directories(DFSDemo PRIVATE ../../Utils/)
target_include_directories(MAZEDemo PRIVATE ../../Utils/)


