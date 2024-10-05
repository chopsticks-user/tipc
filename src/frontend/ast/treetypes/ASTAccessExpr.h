#pragma once

#include <utility>

#include "ASTExpr.h"

/*! \brief Class for a record field access
 */
class ASTAccessExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> RECORD;
  std::string FIELD;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTAccessExpr(std::shared_ptr<ASTExpr> RECORD, std::string FIELD)
      : RECORD(std::move(RECORD)), FIELD(std::move(FIELD)) {}
  [[nodiscard]] std::string getField() const { return FIELD; }
  [[nodiscard]] ASTExpr *getRecord() const noexcept { return RECORD.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
