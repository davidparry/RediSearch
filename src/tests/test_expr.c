#include "test_util.h"
#include "time_sample.h"
#include <aggregate/expr/expression.h>

int testExpr() {

  RSExpr *l = RS_NewNumberLiteral(2);
  RSExpr *r = RS_NewNumberLiteral(4);

  RSExpr *op = RS_NewOp('+', l, r);
  RSValue val;
  char *err;
  int rc = RSExpr_Eval(NULL, op, &val, &err);
  ASSERT_EQUAL(EXPR_EVAL_OK, rc);
  ASSERT_EQUAL(RSValue_Number, val.t);
  ASSERT_EQUAL(6, val.numval);

  RETURN_TEST_SUCCESS;
}

int testParser() {
  char *e = "(((2 + 2) * (3 / 4) + 2 % 3 - 0.43) ^ -3)";

  char *err = NULL;
  RSExpr *root = RSExpr_Parse(e, strlen(e), &err);
  if (err != NULL) {
    FAIL("Error parsing expression: %s", err);
  }
  ASSERT(root != NULL);
  RSExpr_Print(root);
  printf("\n");

  RSValue val;
  int rc = RSExpr_Eval(NULL, root, &val, &err);
  ASSERT_EQUAL(EXPR_EVAL_OK, rc);
  ASSERT_EQUAL(RSValue_Number, val.t);
  RSValue_Print(&val);
  RETURN_TEST_SUCCESS;
}
TEST_MAIN({
  TESTFUNC(testExpr);
  TESTFUNC(testParser);
});