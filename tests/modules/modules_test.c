#include "modules/modules.h"
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

static void add_should_return_correct_value(void) {
  TEST_ASSERT_EQUAL(30, add(14, 16));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(add_should_return_correct_value);
  return UNITY_END();
}
