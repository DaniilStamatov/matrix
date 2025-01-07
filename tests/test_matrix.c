#include "test_matrix.h"

void run_tests(void) {
  Suite *list_cases[] = {mult_suite(),
                        create_suite(),
                        sub_suite(),
                        mult_by_number_suite(),
                        sum_suite(),transpose_suite(),determinant_suite(),components_suite(), inverse_suite(), NULL};  
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0)
    putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_tests();
  return 0;
}