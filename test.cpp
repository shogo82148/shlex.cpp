#include <iostream>
#include <string>
#include "shlex.h"

static int testCount = 0;
static int ngCount = 0;

static void ok(bool b, const char *msg)
{
  testCount++;
  if (b)
  {
    std::cout << "ok " << testCount << " - " << msg << std::endl;
  }
  else
  {
    ngCount++;
    std::cout << "not ok " << testCount << " - " << msg << std::endl;
  }
}

static void is(const std::string &a, const std::string &b, const char *msg)
{
  testCount++;
  if (a == b)
  {
    std::cout << "ok " << testCount << " - " << msg << std::endl;
  }
  else
  {
    ngCount++;
    std::cout << "not ok " << testCount << " - " << msg << std::endl
              << "# Expected: '" << b << "'" << std::endl
              << "#   Actual: '" << a << "'" << std::endl;
  }
}

static void is(int a, int b, const char *msg)
{
  testCount++;
  if (a == b)
  {
    std::cout << "ok " << testCount << " - " << msg << std::endl;
  }
  else
  {
    ngCount++;
    std::cout << "not ok " << testCount << " - " << msg << std::endl
              << "# Expected: " << b << std::endl
              << "#   Actual: " << a << std::endl;
  }
}

static void testOptional(void)
{
  shlex::optional<int> a;
  ok(!a, "optional<int> default constructor");

  shlex::optional<int> b(shlex::optional<int>::nullopt);
  ok(!b, "optional<int> nullopt constructor");

  shlex::optional<int> c(42);
  ok(c, "optional<int> value constructor");
  is(c.value(), 42, "optional<int> value constructor");
  is(*c, 42, "optional<int> value constructor");

  shlex::optional<int> d(c);
  ok(d, "optional<int> copy constructor");
  is(d.value(), 42, "optional<int> copy constructor");

  shlex::optional<int> e;
  e = c;
  ok(e, "optional<int> copy assignment operator");
  is(e.value(), 42, "optional<int> copy assignment operator");

  shlex::optional<int> f;
  f = shlex::optional<int>::nullopt;
  ok(!f, "optional<int> nullopt assignment operator");

  shlex::optional<int> g;
  g = 42;
  ok(g, "optional<int> value assignment operator");
  is(g.value(), 42, "optional<int> value assignment operator");
}

static void testQuote(void)
{
  is(shlex::quote(""), "''", "quote empty string");
  is(shlex::quote("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz", "quote lower case string");
  is(shlex::quote("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "quote upper case string");
  is(shlex::quote("0123456789"), "0123456789", "quote number string");
  is(shlex::quote("@%_-+=:,./"), "@%_-+=:,./", "quote special character string");
  is(shlex::quote("test file name"), "'test file name'", "quote test file name");

  is(shlex::quote("test\"name"), "'test\"name'", "quote test\"name");
  is(shlex::quote("test`name"), "'test`name'", "quote test`name");
  is(shlex::quote("test$name"), "'test$name'", "quote test$name");
  is(shlex::quote("test\\name"), "'test\\name'", "quote test\\name");
  is(shlex::quote("test!name"), "'test!name'", "quote test!name");
  is(shlex::quote("test\xc3\xa9name"), "'test\xc3\xa9name'", "quote e + acute accent");
  is(shlex::quote("test\xc3\xa0name"), "'test\xc3\xa0name'", "quote a + grave");
  is(shlex::quote("test\xc3\x9fname"), "'test\xc3\x9fname'", "quote sharp s");

  is(shlex::quote("test\"'name'"), "'test\"'\"'\"'name'\"'\"''", "quote test\"'name'");
  is(shlex::quote("test`'name'"), "'test`'\"'\"'name'\"'\"''", "quote test`'name'");
  is(shlex::quote("test$'name'"), "'test$'\"'\"'name'\"'\"''", "quote test$'name'");
  is(shlex::quote("test\\'name'"), "'test\\'\"'\"'name'\"'\"''", "quote test\\'name'");
  is(shlex::quote("test!'name'"), "'test!'\"'\"'name'\"'\"''", "quote test!'name'");
  is(shlex::quote("test\xc3\xa9'name'"), "'test\xc3\xa9'\"'\"'name'\"'\"''", "quote e + acute accent + 'name'");
  is(shlex::quote("test\xc3\xa0'name'"), "'test\xc3\xa0'\"'\"'name'\"'\"''", "quote a + grave + 'name'");
  is(shlex::quote("test\xc3\x9f'name'"), "'test\xc3\x9f'\"'\"'name'\"'\"''", "quote sharp s + 'name'");
}

int main(void)
{
  testOptional();
  testQuote();

  std::cout << "1.." << testCount << std::endl;
  if (ngCount > 0)
  {
    return 1;
  }
  return 0;
}
