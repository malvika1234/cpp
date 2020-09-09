#include <iostream>

class Widget
{
public:
  Widget()
  : width{640}
  , height{480}
  , frame{false}
  , visible{true}
  {
  }

  Widget(int w)
  : width{w}
  , height{getHeight(w)}
  , frame{false}
  , visible{true}
  {
  }

  Widget(int w, int h)
  : width{w}
  , height{h}
  , frame{false}
  , visible{true}
  {
  }

  void show()
  {
    std::cout << std::boolalpha << width << "x"
              << height << ", frame: " << frame
              << ", visible: " << visible << std::endl;
  }

private:
  static int getHeight(int w) { return w * 3 / 4; }
  const int  width;
  const int  height;
  const bool frame;
  const bool visible;
};

int main()
{
  Widget wVGA;
  Widget wSVGA{800};
  Widget wHD{1280, 720};

  wVGA.show();
  wSVGA.show();
  wHD.show();
}
