/****************************************************/
/*File: main.cpp                                    */
/*The main function instantiate a new driver class  */ 
/*And execute input and output                      */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include <iostream>
#include <fstream>
#include "driver.h"

int main (int argc, const char *argv[])
{
  int res = 0;
  driver drv;
  if (argc < 2){
    std::cerr<<"Usage: "<< argv[0] << "-S [-e|-t] [<input>] [-o <output>] [-p] [-s]"
             << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; )
    if (argv[i] == std::string ("-p"))
      {drv.trace_parsing = true; ++i;}
    else if (argv[i] == std::string ("-s"))
      {drv.trace_scanning = true; ++i;}
    else if (argv[i] == std::string ("-S"))
      //Compile it
      { if (argv[i+1] == std::string ("-e"))
        {drv.compile(argv[i+2]); i+=3;}
      }
    else if (argv[i] == std::string("-o"))
      {
        std::ofstream ofs(argv[i+1]);
        drv.Dump_Eeyore(ofs);
        i+=2;
      }
    else
      {res = 1; std::cerr<<"Unknown Parameters!"<<std::endl; break;}
  return res;
}
