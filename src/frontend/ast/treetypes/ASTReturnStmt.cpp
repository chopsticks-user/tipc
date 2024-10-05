#include "ASTReturnStmt.h"
#include "ASTVisitor.h"

void ASTReturnStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArg()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTReturnStmt::print(std::ostream &out) const {
  return out << "return " << *getArg() << ";";
}

std::vector<std::shared_ptr<ASTNode>> ASTReturnStmt::getChildren() {
  return {ARG};
}
