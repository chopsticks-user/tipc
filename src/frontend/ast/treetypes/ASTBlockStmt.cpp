#include "ASTBlockStmt.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

ASTBlockStmt::ASTBlockStmt(const std::vector<std::shared_ptr<ASTStmt>>& STMTS) {
  for (auto &stmt : STMTS) {
    const std::shared_ptr<ASTStmt>& s = stmt;
    this->STMTS.push_back(s);
  }
}

std::vector<ASTStmt *> ASTBlockStmt::getStmts() const { return rawRefs(STMTS); }

void ASTBlockStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    for (const auto s : getStmts()) {
      s->accept(visitor);
    }
  }
  visitor->endVisit(this);
}

std::ostream &ASTBlockStmt::print(std::ostream &out) const {
  out << "{ ";
  for (const auto s : getStmts()) {
    out << *s << " ";
  }
  return out << "}";
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTBlockStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.reserve(STMTS.size());
  for (auto &stmt : STMTS) {
    children.push_back(stmt);
  }
  return children;
}
