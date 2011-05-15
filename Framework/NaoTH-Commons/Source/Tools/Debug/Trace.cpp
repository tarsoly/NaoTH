/**
* @file Tools/Debugging/Trace.cpp
*
* A class representing a trace.
* 
* @author Thomas Roefer
*/ 

#include "Trace.h"
#include "NaoTHAssert.h"
#include <sstream>
#include "Tools/SynchronizedFileWriter.h"
#include <string.h>

//static Trace* trace = 0;

Trace::Line::Line(const char* f, int l, const std::string msg)
  : 
  line(l),
  msg(msg)
{
  ASSERT(strlen(f) < MAX_FILE_NAME_LENGHT);
  strcpy(file, f);
}

void Trace::setCurrentLine(const char* file, int line, const std::string& msg) 
{
  buffer.add(Line(file, line, msg));
}//end setCurrentLine

void Trace::dump()
{
  std::stringstream sstream;
  sstream << *this;

  // write to file
  SynchronizedFileWriter::saveStreamToFile(sstream, string("Config/trace.dump"));
}//end dump

 
std::ostream& operator<<(ostream& stream, const Trace& trace) 
{
  stream << trace.buffer.getNumberOfEntries() << endl;
  for(int i = trace.buffer.getNumberOfEntries() - 1; i >= 0; --i)
    stream << trace.buffer[i].file << ":" << trace.buffer[i].line << " " << trace.buffer[i].msg << endl;
  return stream;
}
