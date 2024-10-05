#include "ASTBinaryExpr.h"
#include "ASTVisitor.h"

void ASTBinaryExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getLeft()->accept(visitor);
    getRight()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTBinaryExpr::print(std::ostream &out) const {
  return out << "(" << *getLeft() << getOp() << *getRight() << ")";
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTBinaryExpr::getChildren() {
  return {LEFT, RIGHT};
}
