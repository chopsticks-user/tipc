#pragma once

#include <utility>

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for an output statement.
 */
class ASTOutputStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> ARG;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  explicit ASTOutputStmt(std::shared_ptr<ASTExpr> ARG) : ARG(std::move(ARG)) {}
  [[nodiscard]] ASTExpr *getArg() const noexcept { return ARG.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
