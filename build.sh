#!/usr/bin/env bash

###
 # @Author: modnarshen
 # @Date: 2022.11.25 10:53:58
 # @Note: Copyrights (c) 2022 modnarshen. All rights reserved.
### 

build_dir="./.build/"

rm -fr ${build_dir}
mkdir -p ${build_dir} && cd ${build_dir}
cmake .. && make -j10