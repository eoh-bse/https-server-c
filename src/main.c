#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>

#include "modules/common.h"
#include "modules/server.h"

int main(void) {
  if (run_server() == ERROR)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
