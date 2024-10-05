#include "ASTRecordExpr.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

ASTRecordExpr::ASTRecordExpr(
    const std::vector<std::shared_ptr<ASTFieldExpr>>& FIELDS) {
  for (const auto &field : FIELDS) {
    this->FIELDS.push_back(field);
  }
}

std::vector<ASTFieldExpr *> ASTRecordExpr::getFields() const {
  return rawRefs(FIELDS);
}

void ASTRecordExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    for (const auto f : getFields()) {
      f->accept(visitor);
    }
  }
  visitor->endVisit(this);
}

std::ostream &ASTRecordExpr::print(std::ostream &out) const {
  out << "{";
  bool skip = true;
  for (const auto &f : getFields()) {
    if (skip) {
      skip = false;
      out << *f;
      continue;
    }
    out << "," << *f;
  }
  return out << "}";
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTRecordExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.reserve(FIELDS.size());
  for (auto &field : FIELDS) {
    children.push_back(field);
  }
  return children;
}
