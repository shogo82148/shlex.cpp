#include "shlex.h"

static bool contains_unsafe_char(const std::string &s)
{
  for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
  {
    char c = *it;
    if ('0' <= c && c <= '9')
    {
      continue;
    }
    if ('A' <= c && c <= 'Z')
    {
      continue;
    }
    if ('a' <= c && c <= 'z')
    {
      continue;
    }
    if (c == '@' || c == '_' || c == '%' || c == '+' || c == '=' || c == ':' || c == ',' || c == '.' || c == '/' || c == '-' || c == '\'')
    {
      continue;
    }
    return true;
  }

  return false;
}

std::string shlex::quote(const std::string &s)
{
  if (s.empty())
  {
    return "''";
  }
  if (!contains_unsafe_char(s))
  {
    return s;
  }

  // use single quotes, and put single quotes into double quotes
  // the string $'b is then quoted as '$'"'"'b'
  std::string result = "'";
  for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
  {
    char c = *it;
    if (c == '\'')
    {
      result += "'\"'\"'";
    }
    else
    {
      result += c;
    }
  }
  result += "'";
  return result;
}
