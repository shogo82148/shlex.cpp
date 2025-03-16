#include "shlex.h"

// Implementation is based on Python's shlex module.
// https://github.com/python/cpython/blob/10cbd1fe88d1095a03cce24fb126d479668a67c3/Lib/shlex.py#L253

shlex::optional<std::string> shlex::shlex::get_token()
{
  while (pos_ < s_.size() && s_[pos_] == ' ')
  {
    ++pos_;
  }
  if (pos_ == s_.size())
  {
    return optional<std::string>::nullopt;
  }
  std::string::size_type start = pos_;
  if (s_[pos_] == '\'')
  {
    ++pos_;
    while (pos_ < s_.size() && s_[pos_] != '\'')
    {
      ++pos_;
    }
    if (pos_ == s_.size())
    {
      throw std::runtime_error("unterminated single quote");
    }
    ++pos_;
  }
  else
  {
    while (pos_ < s_.size() && s_[pos_] != ' ')
    {
      ++pos_;
    }
  }
  return s_.substr(start, pos_ - start);
}

std::vector<std::string> shlex::split(const std::string &s)
{
  std::vector<std::string> result;
  shlex lex(s);
  while (true)
  {
    optional<std::string> token = lex.get_token();
    if (!token)
    {
      break;
    }
    result.push_back(*token);
  }
  return result;
}

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
