#include "ASTDeRefExpr.h"
#include "ASTVisitor.h"

void ASTDeRefExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getPtr()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTDeRefExpr::print(std::ostream &out) const {
  return out << "(*" << *getPtr() << ")";
}

std::vector<std::shared_ptr<ASTNode>> ASTDeRefExpr::getChildren() {
  return {PTR};
}
