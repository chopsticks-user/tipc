#include "ASTAssignStmt.h"
#include "ASTVisitor.h"

void ASTAssignStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getLHS()->accept(visitor);
    getRHS()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTAssignStmt::print(std::ostream &out) const {
  return out << *getLHS() << " = " << *getRHS() << ";";
}

std::vector<std::shared_ptr<ASTNode>> ASTAssignStmt::getChildren() {
  return {LHS, RHS};
}
