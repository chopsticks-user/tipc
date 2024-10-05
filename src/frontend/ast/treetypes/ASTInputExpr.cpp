#include "ASTInputExpr.h"
#include "ASTVisitor.h"

void ASTInputExpr::accept(ASTVisitor *visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

std::ostream &ASTInputExpr::print(std::ostream &out) const {
  return out << "input";
}
