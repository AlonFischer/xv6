/*
 * Tests the functionality of the `dup2` system call. With no arguments we open
 * two files and write out text. In this case we expect the file 'new_dup2' to
 * contain the string 'bar\n'. With one or more arguments we open two files,
 * perform a `dup2` system call and expect string 'bar\n' to expect in
 * 'old_dup2'
 */

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[]) {
  int oldfd, newfd;

  // Dont care if the files dont exist already
  unlink("old_dup2");
  unlink("new_dup2");

  if ((oldfd = open("old_dup2", O_CREATE|O_RDWR)) < 0) {
      printf(1, "Cannot open 'old_dup2'\n");
      exit();
  }
  if ((newfd = open("new_dup2", O_CREATE|O_RDWR)) < 0) {
      printf(1, "Cannot open 'new_dup2'\n");
      exit();
  }

  write(oldfd, "foo", 3);
  write(newfd, "err", 3);

  if (argc > 1) {
    printf(0, "Attempting dup2\n");

    if (dup2(oldfd, newfd) < 0) {
      printf(1, "dup2 error: \n");
    }
  }

  write(newfd, "bar\n", 4);

  exit();
}
