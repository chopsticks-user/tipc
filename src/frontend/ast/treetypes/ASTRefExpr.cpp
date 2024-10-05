#include "ASTRefExpr.h"
#include "ASTVisitor.h"

void ASTRefExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getVar()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTRefExpr::print(std::ostream &out) const {
  return out << "&" << *getVar();
}

std::vector<std::shared_ptr<ASTNode>> ASTRefExpr::getChildren() {
  return {VAR};
}
