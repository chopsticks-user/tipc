#include "ASTOutputStmt.h"
#include "ASTVisitor.h"

void ASTOutputStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArg()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTOutputStmt::print(std::ostream &out) const {
  return out << "output " << *getArg() << ";";
}

std::vector<std::shared_ptr<ASTNode>> ASTOutputStmt::getChildren() {
  return {ARG};
}
