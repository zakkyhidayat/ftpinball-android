#!/bin/sh
# Stages your own copy of Full Tilt! Pinball so it is built into the APK.
# Usage: tools/stage_fulltilt.sh /path/to/FULLTILT   (the folder holding CADET, DRAGON and PIRATE)
# The data is copyrighted: app/fulltilt-assets is git-ignored, never commit it or share the APK.
set -e
src="$1"
[ -d "$src" ] || { echo "usage: $0 /path/to/FULLTILT" >&2; exit 1; }
dst="$(dirname "$0")/../app/fulltilt-assets"
rm -rf "$dst"
stage() { # folder-on-disc  dat-name  asset-folder
    d=$(find "$src" -maxdepth 1 -iname "$1" -type d | head -n1)
    [ -n "$d" ] || { echo "skip $3: no $1 folder" >&2; return 0; }
    mkdir -p "$dst/$3"
    find "$d" -maxdepth 1 -iname "$2" -exec cp {} "$dst/$3/$2" \;
    find "$d" -maxdepth 1 -iname "*.BMP" -exec cp {} "$dst/$3/icon.bmp" \;
    s=$(find "$d" -maxdepth 1 -iname SOUND -type d | head -n1)
    [ -n "$s" ] && find "$s" -maxdepth 1 -type f -exec cp {} "$dst/$3/" \;
    echo "staged $3"
}
stage CADET CADET.DAT cadet
stage DRAGON DRAGON.DAT dragon
stage PIRATE PIRATES.DAT pirates
