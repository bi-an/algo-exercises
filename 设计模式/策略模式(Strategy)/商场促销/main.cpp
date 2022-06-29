#include "CashContext.h"

int main()
{

  CashContextFactory context("满300减100");

  double result = context.GetResult(300);

  return 0;
}