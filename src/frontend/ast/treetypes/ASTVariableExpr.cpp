#include "ASTVariableExpr.h"
#include "ASTVisitor.h"

void ASTVariableExpr::accept(ASTVisitor *visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

std::ostream &ASTVariableExpr::print(std::ostream &out) const {
  return out << getName();
} // LCOV_EXCL_LINE
