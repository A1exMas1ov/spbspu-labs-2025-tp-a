#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <map>

namespace maslov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  void area(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
  {}

  void max(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
  {}

  void min(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
  {}

  void echo(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
  {}

  void rects(std::ostream & out, const std::vector< Polygon > & polygons)
  {}
}

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR: wrong arguments\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "ERROR: there is no such file\n";
    return 1;
  }

  using maslov::Polygon;
  std::vector< Polygon > polygons;
  while (!file.eof())
  {
    std::copy
    (
      std::istream_iterator< Polygon >(file),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (!file)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void() > > cmds;
  cmds["AREA"] = std::bind(maslov::area, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmds["MAX"] = std::bind(maslov::max, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmds["MIN"] = std::bind(maslov::min, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmds["ECHO"] = std::bind(maslov::echo, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmds["RECTS"] = std::bind(maslov::rects, std::ref(std::cout), std::cref(polygons));
  
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)();
    }
    catch (const std::exception &)
    {
      if (std::cin.fail())
      {
        std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
      }
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
