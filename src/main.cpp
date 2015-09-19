#include "gorgone.h"

int main()
{
  ofGLFWWindowSettings settings;

  auto window = ofCreateWindow(settings);
  auto app = make_shared<gorgone>();
  ofRunApp(window, app);

  return ofRunMainLoop();
}
