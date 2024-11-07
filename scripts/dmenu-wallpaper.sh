#!/bin/bash

PICTURES_DIR=~/Pictures

# Find all image files in the directory
IMAGE=$(find "$PICTURES_DIR" -type f \( -iname "*.jpg" -o -iname "*.png" -o -iname "*.jpeg" -o -iname "*.bmp" \) | dmenu -i -l 10)

if [ -n "$IMAGE" ]; then
  setbg "$IMAGE"
  echo "Wallpaper set to $IMAGE"
else
  echo "No image selected."
fi

