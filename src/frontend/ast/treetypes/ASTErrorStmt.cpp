#include "ASTErrorStmt.h"
#include "ASTVisitor.h"

void ASTErrorStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArg()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTErrorStmt::print(std::ostream &out) const {
  return out << "error " << *getArg() << ";";
}

std::vector<std::shared_ptr<ASTNode>> ASTErrorStmt::getChildren() {
  return {ARG};
}
