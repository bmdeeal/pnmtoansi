#include <string>
#include <iostream>

using namespace std;

/*
pnmtoansi -- filter that converts plain format pnm images to 256-color character sequences for display on a terminal
Copyright 2016, 2020 B.M.Deeal

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

This program converts plain ppm immages to 216 color ANSI sequences. It also converts plain pgm images to 24 level ANSI sequences and converts plain pbm images to monochrome ANSI sequences.
See README.txt for more details.

TODO list:
* use the half fg/half bg character to increase vertical image resolution.
* add option to support 24-bit terminals, would be no effort at all (the code is written in a separate branch, and simply needs to be integrated into this version	
*/

char escape = 27; //escape character

//resetDisp: set the colors back to normal
void resetDisp() {
	cout << escape << "[0;m";
}

//round: takes a double, rounds it to an int
int round(double n) {
	int ground = (int)n;
	if (n - ground >= 0.5) { return ground+1; }
	return ground;
}

//pixelColor: convert each image value into the ANSI color code number
int pixelColor(int rr, int gg, int bb, int depth) {
	int dv=round(depth/5.0); //divide value to bring 0-255 down to 0-5
	int r=rr/dv;
	int g=gg/dv;
	int b=bb/dv;
	int result=16+(36*r+6*g+b);
	return result;
}

//parseColor: display ppm images to terminal
void parseColor() {
	//string format;
	int w, h, d;
	int r, g, b;
	int pos=0;
	/*
	//check file format:
	cin >> format;
	if (format != "P3") { cerr << "!format incorrect\nshould be P3 (plain PPM) -- use pnmtoplainpnm to fix\n"; return; }
	*/
	cin >> w;
	cin >> h;
	cin >> d;
	//if (d != 255) { cerr << "!format incorrect\nshould have a maxcol of 255 (8-bit RGB)\n"; return; }
	//read and show file:
	while (!cin.eof() && pos < w*h) {
		cin >> r;
		cin >> g;
		cin >> b;
		cout << escape << "[48;5;" << pixelColor(r,g,b,d) << "m ";
		pos++;
		if (cin.fail()) { cerr << "!format incorrect\nsomething went wrong, there's probably something other than a number in there\n"; return; }
		if (pos % w == 0) { resetDisp(); cout << "\n"; }
	}
}

//pixelGray: convert to 24 level grayscale
int pixelGray(int level, int depth) {
	int dv=round(depth/24.0);
	return 232+level/dv;
}

//parseGray: display pgm images to terminal
void parseGray() {
	int w, h, d;
	int l;
	int pos=0;
	cin >> w;
	cin >> h;
	cin >> d;
	//read and show file:
	while (!cin.eof() && pos < w*h) {
		cin >> l;
		cout << escape << "[48;5;" << pixelGray(l,d) << "m ";
		pos++;
		if (cin.fail()) { cerr << "!format incorrect\nsomething went wrong, there's probably something other than a number in there\n"; return; }
		if (pos % w == 0) { resetDisp(); cout << "\n"; }
	}
}

//pixelBW: convert to 2 level monochrome
//TODO: allow the colors to be selected
int pixelBW(char bit) {
	if (bit == '0') { return 15; }
	return 0;
}

//parseBW: display pbm images to terminal
void parseBW() {
	int w,h;
	char b;
	int pos=0;
	cin >> w;
	cin >> h;
	//read and show file:
	while (!cin.eof() && pos < w*h) {
		cin >> b;
		if (b == ' ' || b == '\t') { continue; }
		cout << escape << "[48;5;" << pixelBW(b) << "m ";
		pos++;
		if (cin.fail()) { cerr << "!format incorrect\nsomething went wrong, there's probably something other than a number in there\n"; return; }
		if (pos % w == 0) { resetDisp(); cout << "\n"; }
	}
}

//main: show intro text and then go parse, also clean up the display
int main() {
	string format;
	cerr << "pnmtoansi -- pipe in a plain pnm file to show it on a 256 color terminal\n";
	cin >> format;
	if (format == "P3") {
		cerr << "loaded color image!\n";
		parseColor();
	} else if (format == "P2") {
		cerr << "loaded gray image!\n";
		parseGray();
	} else if (format == "P1") {
		cerr << "loaded b/w image!\n";
		parseBW();
	} else {
		cerr << "!format unsupported, use plain format PGM/PPM files\n";
	}
	resetDisp();
	cout << endl;
}
