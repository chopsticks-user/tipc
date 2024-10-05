#pragma once

#include "ASTNode.h"

/*! \brief Abstract class for all expression subtypes
 */
class ASTExpr : public ASTNode {
public:
  ~ASTExpr() override = default;
  // delegating the obligation to override accept, codegen, and print
};
