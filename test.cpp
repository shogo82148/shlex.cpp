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

static void testQuote(void)
{
  ok(shlex::quote("") == "''", "quote empty string");
  ok(shlex::quote("abcdefghijklmnopqrstuvwxyz") == "abcdefghijklmnopqrstuvwxyz", "quote lower case string");
  ok(shlex::quote("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "quote upper case string");
  ok(shlex::quote("0123456789") == "0123456789", "quote number string");
  ok(shlex::quote("@%_-+=:,./") == "@%_-+=:,./", "quote special character string");
  ok(shlex::quote("test file name") == "'test file name'", "quote test file name");

  ok(shlex::quote("test\"name") == "'test\"name'", "quote test\"name");
  ok(shlex::quote("test`name") == "'test`name'", "quote test`name");
  ok(shlex::quote("test$name") == "'test$name'", "quote test$name");
  ok(shlex::quote("test\\name") == "'test\\name'", "quote test\\name");
  ok(shlex::quote("test!name") == "'test!name'", "quote test!name");
  ok(shlex::quote("test\xc3\xa9name") == "'test\xc3\xa9name'", "quote e + acute accent");
  ok(shlex::quote("test\xc3\xa0name") == "'test\xc3\xa0name'", "quote a + grave");
  ok(shlex::quote("test\xc3\x9fname") == "'test\xc3\x9fname'", "quote sharp s");

  ok(shlex::quote("test\"'name'") == "'test\"'\"'\"'name'\"'\"''", "quote test\"'name'");
  ok(shlex::quote("test`'name'") == "'test`'\"'\"'name'\"'\"''", "quote test`'name'");
  ok(shlex::quote("test$'name'") == "'test$'\"'\"'name'\"'\"''", "quote test$'name'");
  ok(shlex::quote("test\\'name'") == "'test\\'\"'\"'name'\"'\"''", "quote test\\'name'");
  ok(shlex::quote("test!'name'") == "'test!'\"'\"'name'\"'\"''", "quote test!'name'");
  ok(shlex::quote("test\xc3\xa9'name'") == "'test\xc3\xa9'\"'\"'name'\"'\"''", "quote e + acute accent + 'name'");
  ok(shlex::quote("test\xc3\xa0'name'") == "'test\xc3\xa0'\"'\"'name'\"'\"''", "quote a + grave + 'name'");
  ok(shlex::quote("test\xc3\x9f'name'") == "'test\xc3\x9f'\"'\"'name'\"'\"''", "quote sharp s + 'name'");
}

int main(void)
{
  testQuote();

  std::cout << "1.." << testCount << std::endl;
  if (ngCount > 0)
  {
    return 1;
  }
  return 0;
}
