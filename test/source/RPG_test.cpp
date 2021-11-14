#include "lib.hpp"

auto main() -> int
{
  library lib;

  return lib.name == "RPG" ? 0 : 1;
}
