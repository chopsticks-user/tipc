#pragma once

#include <utility>

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for if-then-else.
 */
class ASTIfStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> COND;
  std::shared_ptr<ASTStmt> THEN, ELSE;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTIfStmt(std::shared_ptr<ASTExpr> COND, std::shared_ptr<ASTStmt> THEN,
            std::shared_ptr<ASTStmt> ELSE)
      : COND(std::move(COND)), THEN(std::move(THEN)), ELSE(std::move(ELSE)) {}
  [[nodiscard]] ASTExpr *getCondition() const noexcept { return COND.get(); }
  [[nodiscard]] ASTStmt *getThen() const { return THEN.get(); }

  /*! \fn getElse
   * \return Else statement if it exists and nullptr otherwise.
   */
  [[nodiscard]] ASTStmt *getElse() const noexcept { return ELSE.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
