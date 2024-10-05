#include "ASTAccessExpr.h"
#include "ASTVisitor.h"

void ASTAccessExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getRecord()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTAccessExpr::print(std::ostream &out) const {
  return out << "(" << *getRecord() << "." << getField() << ")";
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTAccessExpr::getChildren() {
  return {RECORD};
}
