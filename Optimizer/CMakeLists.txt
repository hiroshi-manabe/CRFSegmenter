add_library(Optimizer OptimizerClass.cpp)
set_property(TARGET Optimizer PROPERTY CXX_STANDARD 11)
target_link_libraries(Optimizer liblbfgs)
