#pragma once

#include <utility>

#include "ASTExpr.h"

/*! \brief Class for the field of a record
 */
class ASTFieldExpr : public ASTExpr {
  std::string FIELD;
  std::shared_ptr<ASTExpr> INIT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTFieldExpr(std::string FIELD, std::shared_ptr<ASTExpr> INIT)
      : FIELD(std::move(FIELD)), INIT(std::move(INIT)) {}
  [[nodiscard]] std::string getField() const { return FIELD; }
  [[nodiscard]] ASTExpr *getInitializer() const noexcept { return INIT.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
