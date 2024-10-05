#pragma once

#include <utility>

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for assignment
 */
class ASTAssignStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> LHS, RHS;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTAssignStmt(std::shared_ptr<ASTExpr> LHS, std::shared_ptr<ASTExpr> RHS)
      : LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  [[nodiscard]] ASTExpr *getLHS() const noexcept { return LHS.get(); }
  [[nodiscard]] ASTExpr *getRHS() const noexcept { return RHS.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
