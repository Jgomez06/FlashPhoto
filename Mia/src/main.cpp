#include "MIAApp.h"
#include "ColorData.h"
#include <iostream>

int main(int argc, char* argv[]) {
  MIAApp *app = new MIAApp(argc, argv, 800, 800, ColorData(1,1,0.95), argc == 1); // Only create window in graphical mode (when arg count is 1)
  delete app;
  exit(0);
}

