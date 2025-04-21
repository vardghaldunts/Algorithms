project(BFS)

add_executable(GraphDemo graph_representation.cpp)
add_executable(BFSDemo BFS.cpp)

target_include_directories(GraphDemo PRIVATE ../../Utils/)
target_include_directories(BFSDemo PRIVATE ../../Utils/)


