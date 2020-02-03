pnmtoansi -- filter that converts plain format pnm images to 256-color character sequences for display on a terminal

Copyright 2016, 2020 B.M.Deeal

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

---
* About:
This program converts plain format PPM images to 216 color ANSI sequences.
It also converts plain PGM images to 24 level ANSI sequences and converts plain PGM images to monochrome ANSI sequences.
Grays are poorly represented when converting to 216 color output because  because I don't use the extra 24 grays in the palette.
To use the program in grayscale mode, a PGM format file must be provided. Similarly, to use the program in monochrome mode, a PBM format file must be provided.

This program is a pure filter -- it does not do scaling or dithering, and it does not load anything other than plain PPM/PGM/PBM images.
A command, view-image-term.sh is provided with this program that does the needed pre-processing automatically.
view-image-term.sh requires netpbm and ncurses to be installed.

---
* Installation:
Compiling pnmtoansi is extremely easy:
	$ c++ pnmtoansi.cpp -o pnmtoansi

Installation is similarly easy, just place the program into a directory that is in your $PATH. For example:
	$ cp pnmtoansi view-image-term.sh ~/bin/
