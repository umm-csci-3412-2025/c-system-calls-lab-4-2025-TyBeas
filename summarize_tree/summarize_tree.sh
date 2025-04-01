#!/bin/bash

dirname=$1

echo "There were `find $dirname -type d | wc -l` directories."
echo "There were `find $dirname -type f | wc -l` regular files."