#!/bin/bash

inputPath=$1

echo "There were "$(find "$inputPath" -type d | wc -l)" directories."
echo "There were "$(find "$inputPath" -type f | wc -l)" regular files."