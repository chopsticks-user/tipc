#pragma once

#include "ASTFunction.h"
#include <ostream>

class SemanticAnalysis;

/*! \brief Class for a program which is a name and a list of functions.
 *
 */
class ASTProgram : public ASTNode {
  std::string name;
  std::vector<std::shared_ptr<ASTFunction>> FUNCTIONS;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  explicit ASTProgram(const std::vector<std::shared_ptr<ASTFunction>>& FUNCTIONS);
  void setName(std::string n) { name = std::move(n); }
  [[nodiscard]] std::string getName() const { return name; }
  [[nodiscard]] std::vector<ASTFunction *> getFunctions() const;
  ASTFunction *findFunctionByName(const std::string &) const;
  void accept(ASTVisitor *visitor) override;
  std::shared_ptr<llvm::Module> codegen(SemanticAnalysis *st, const std::string& name);

private:
  llvm::Value *codegen() override;

public:
  friend std::ostream &operator<<(std::ostream &os, const ASTProgram &obj) {
    return obj.print(os);
  }

protected:
  std::ostream &print(std::ostream &out) const override;
};
