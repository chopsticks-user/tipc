#pragma once

#include <utility>

#include "ASTExpr.h"

/*! \brief Class for a binary operator.
 */
class ASTBinaryExpr : public ASTExpr {
  std::string OP;
  std::shared_ptr<ASTExpr> LEFT, RIGHT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTBinaryExpr(std::string OP, std::shared_ptr<ASTExpr> LEFT,
                std::shared_ptr<ASTExpr> RIGHT)
      : OP(std::move(OP)), LEFT(std::move(LEFT)), RIGHT(std::move(RIGHT)) {}
  [[nodiscard]] std::string getOp() const { return OP; }
  [[nodiscard]] ASTExpr *getLeft() const noexcept { return LEFT.get(); }
  [[nodiscard]] ASTExpr *getRight() const noexcept { return RIGHT.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
