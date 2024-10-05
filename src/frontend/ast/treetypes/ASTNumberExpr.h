#pragma once

#include "ASTExpr.h"

/*! \brief Class for numeric literals.
 */
class ASTNumberExpr : public ASTExpr {
  int VAL;

public:
  explicit ASTNumberExpr(int VAL) : VAL(VAL) {}
  [[nodiscard]] int getValue() const noexcept { return VAL; }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
