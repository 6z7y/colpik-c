#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define IMG_PATH "/tmp/colpik_cache.png"

// command for get position
#define SLURP_COMMAND_W "slurp -b '#00000000' -pf '%x %y'"
#define SLOP_COMMAND_X "slop -o > /dev/null && xdotool getmouselocation | awk '{print $1\"\\t\"$2}' | sed 's/x://;s/y://'"

// command for screen shot
#define GRIM_COMMAND_W(buf, x, y, path) snprintf(buf, 256, "grim -g '%d,%d 1x1' %s", x, y, path)
#define MAIM_COMMAND_X(buf, x, y, path) snprintf(buf, 256, "maim -g 1x1+%d+%d %s", x, y, path)

int get_position(int is_wayland, char *buf, size_t bufsz, int *x, int *y)
{
  FILE *pipe_cmd;

  // check display for get right execute
  if (is_wayland) {
    pipe_cmd = popen(SLURP_COMMAND_W, "r");
  }
  else {
    pipe_cmd = popen(SLOP_COMMAND_X, "r");
  }

  if (!pipe_cmd) { perror("popen"); return -1; }

  fgets(buf, bufsz, pipe_cmd); // stored to buffer

  sscanf(buf, "%d %d", x, y);

  pclose(pipe_cmd); // close pipe

  return 0;
}


int main()
{
  int x, y;
  char buf[256];

  //1. check if wayland of x11
  char *display = getenv("XDG_SESSION_TYPE");

  int is_wayland = (!strcmp(display, "wayland")) ? 1 : 0;

  // 2. get position
  if (get_position(is_wayland, buf, sizeof(buf), &x, &y) < 0) {
    perror("Position");
    return 1;
  }

  // 3. take screenshot (with position)
  if (is_wayland) GRIM_COMMAND_W(buf, x, y , IMG_PATH);
  else            MAIM_COMMAND_X(buf, x -2, y -2 , IMG_PATH);

  system(buf); // exec screenshot command

  // 4. load image
  int channels, w, h;
  unsigned char *img = stbi_load(IMG_PATH, &w, &h, &channels, 4);

  if (!img) { fprintf(stderr, "Failed to load Image\n"); return -1; }

  unsigned char r = img[0];
  unsigned char g = img[1];
  unsigned char b = img[2];
  unsigned char a = img[3];

  // 5. convert to hex
  printf("#%02X%02X%02X", r, g, b);

  // 6. remove image cache
  system("rm -r /tmp/colpik_cache.png");
  return 0;
}
