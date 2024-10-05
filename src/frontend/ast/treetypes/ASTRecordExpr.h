#pragma once

#include "ASTExpr.h"
#include "ASTFieldExpr.h"

/*! \brief Class for defining a record.
 */
class ASTRecordExpr : public ASTExpr {
  std::vector<std::shared_ptr<ASTFieldExpr>> FIELDS;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  explicit ASTRecordExpr(const std::vector<std::shared_ptr<ASTFieldExpr>>& FIELDS);
  [[nodiscard]] std::vector<ASTFieldExpr *> getFields() const;
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
