# Phoenix-ML
A lightweight machine learning library for small devices

To enable parallel ML training build cmake with flag DPARALLEL=1
cmake DPARALLEL=ON ..

Required to allow boost python 3 transpilation
export CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:/usr/include/python3.6m/"
