#!/bin/sh
# view-image-term.sh -- view an image, scaled to the terminal's size, on a 256 color terminal.
# 2020 B.M.Deeal
# requires pnmtoansi (either in the current directory or in the PATH), ncurses and netpbm
# this version of view-image-term.sh was designed for the rather old release of netpbm that has been provided by Debian and Ubuntu for a while now, and thus uses old names for various utilities
# if anytopnm fails to convert an image, uninstall the repository version of netpbm and locate the latest release of the program (available at http://netpbm.sourceforge.net/getting_netpbm.php)

#show usage info if no arguments provided
if [ -z "$1" ]
then
	echo "$0 -- display an image on a 256-color terminal"
	echo "usage:"
	echo "    $0 image-to-view"
	exit 1
fi

#bail if file doesn't exist
if ! [ -f "$1" ]
then
	echo "error: could not find file '$1'!"
	exit 1
fi

#prefer an installed version of pnmtoansi, but use one in the current directory otherwise
conv_command="pnmtoansi"
command -v pnmtoansi >/dev/null 2>&1 || conv_command="./pnmtoansi"

#load, scale, dither, and convert image
anytopnm "$1" |
pnmscale -width $(tput cols) |
pnmscale -yscale 0.5 |
ppmdither -red 6 -green 6 -blue 6 |
pnmtoplainpnm |
"$conv_command"

