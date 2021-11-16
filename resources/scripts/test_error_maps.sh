#!/bin/bash
PATH_TO_MAP="resources/error_maps"
make
for i in `ls ${PATH_TO_MAP}` ; 
    do echo $i && ./so_long ${PATH_TO_MAP}/$i ;
done