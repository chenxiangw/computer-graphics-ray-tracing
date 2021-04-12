#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
using std::endl;
using std::ends;

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return false;
  ////////////////////////////////////////////////////////////////////////////
  std::ofstream outfile(filename, std::ios::out | std::ios::trunc);
  if (num_channels == 1)
  {
    outfile << "P2";
  }
  else
  {
    outfile << "P3";
  }
  outfile << endl
          << width << ends << height << endl
          << "255";
  if (num_channels == 1)
  {
    for (size_t i = 0; i < width * height; i++)
    {
      outfile << endl << (int) data[i];
    }
  }else
  {
    for (size_t i = 0; i < width * height; i++)
    {
      outfile << endl << (int) data[i * 3] << ends << (int) data[i * 3 + 1] << ends << (int) data[i * 3 + 2];
    }
  }


  outfile.close();
  return true;
}
