#ifndef SHOGO82148_SHLEX_H_
#define SHOGO82148_SHLEX_H_

#include <string>

namespace shlex
{
  // returns a shell-escaped version of the string s
  std::string quote(const std::string &s);
}

#endif // SHOGO82148_SHLEX_H_
