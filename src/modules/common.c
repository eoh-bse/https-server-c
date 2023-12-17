#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "modules/common.h"

#define MAX_ERR_SIZE 1024

void handle_error(const char *msg) {
  int errnum = errno;
  char err[MAX_ERR_SIZE];
  if (strerror_r(errnum, err, sizeof(err)) == ERROR) {
    fprintf(stderr, "Error while loggin error\n");
    return;
  }

  fprintf(stderr, "%s: %s\n", msg, err);
}
