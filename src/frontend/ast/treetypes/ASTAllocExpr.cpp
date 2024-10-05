#include "ASTAllocExpr.h"
#include "ASTVisitor.h"

void ASTAllocExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getInitializer()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTAllocExpr::print(std::ostream &out) const {
  return out << "alloc " << *getInitializer();
}

std::vector<std::shared_ptr<ASTNode>> ASTAllocExpr::getChildren() {
  return {INIT};
}
