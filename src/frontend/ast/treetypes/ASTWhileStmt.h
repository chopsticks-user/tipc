#pragma once

#include <utility>

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for a while loop.
 */
class ASTWhileStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> COND;
  std::shared_ptr<ASTStmt> BODY;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTWhileStmt(std::shared_ptr<ASTExpr> COND, std::shared_ptr<ASTStmt> BODY)
      : COND(std::move(COND)), BODY(std::move(BODY)) {}
  [[nodiscard]] ASTExpr *getCondition() const noexcept { return COND.get(); }
  [[nodiscard]] ASTStmt *getBody() const noexcept { return BODY.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
