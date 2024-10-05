#pragma once

#include <utility>

#include "ASTNode.h"

/*! \brief Class for declaring a name, e.g., function, parameter, variable
 */
class ASTDeclNode : public ASTNode {
  std::string NAME;

public:
  explicit ASTDeclNode(std::string NAME) : NAME(std::move(NAME)) {}
  [[nodiscard]] std::string getName() const { return NAME; }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
