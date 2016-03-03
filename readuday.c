#include <string.h>
#include <stdio.h>

int PANE; 				//number of panes
int HEADER = 126;		//size of .bmp header
int SPACE = 180098;		//total pixels in pane - size of header. Amount of data that can be stored in a single pane in bits.

int howfar() {
  int dist;

  dist = PANE*SPACE;

  return dist;
}

void basecopy() {	//copies file header
  FILE *base, *test;

  base = fopen("base.bmp", "rb");
  test = fopen("gilgamesh.bmp", "wb");

  char buf[126];
  fread(buf, 126, 1, base);
  fwrite(buf, sizeof(char), 126, test);
}

void datacopy() {	//copies data, places under header
  FILE *file, *copy;
  char writebuf[SPACE];
  int panename = PANE + 1;

  printf("mr\n");
  
  file = fopen("gilgamesh.txt", "rb");

  char bmpname[4];
  snprintf(bmpname, sizeof(bmpname), "%d.bmp", panename);
  copy = fopen(bmpname, "wb");

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  fseek(file, 0, SEEK_SET);		//find size of file

  char fullbuf[size];

  fseek(file, HEADER, SEEK_SET);

  if (sizeof(file) >= SPACE) {
	char smallbuf[size];
	fread(fullbuf, size, 1, file);
	fseek(copy, HEADER, SEEK_SET);

	strncpy(smallbuf, fullbuf, SPACE);

	printf("skeltal\n");
  }

  else {

  fread(fullbuf, size, 1, file);	//put entire file into buffer
  fseek(file, HEADER, SEEK_SET);	//place fseek 126 bits in

  strncpy(writebuf, &fullbuf[howfar()], SPACE);	 //puts 180098 bits into new buffer

  fwrite(writebuf, sizeof(char), SPACE, file);

  printf("doot\n");
  }
}

int main() {
  
  basecopy();
  
  datacopy();

  return 0;
}
