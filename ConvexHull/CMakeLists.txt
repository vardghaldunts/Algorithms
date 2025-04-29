project(ConvexHull)

add_executable(ConvexHullDemo convex_hull.cpp)
add_executable(GrahamScanDemo graham_scan.cpp)

target_include_directories(ConvexHullDemo PRIVATE ../../Utils/)
target_include_directories(GrahamScanDemo PRIVATE ../../Utils/)


