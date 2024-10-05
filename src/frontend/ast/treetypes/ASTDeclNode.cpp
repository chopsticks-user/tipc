#include "ASTDeclNode.h"
#include "ASTVisitor.h"

void ASTDeclNode::accept(ASTVisitor *visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

std::ostream &ASTDeclNode::print(std::ostream &out) const {
  return out << getName();
} // LCOV_EXCL_LINE
