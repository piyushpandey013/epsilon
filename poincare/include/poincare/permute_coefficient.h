#ifndef POINCARE_PERMUTE_COEFFICIENT_H
#define POINCARE_PERMUTE_COEFFICIENT_H

#include <poincare/layout_engine.h>
#include <poincare/static_hierarchy.h>
#include <poincare/complex.h>

namespace Poincare {

class PermuteCoefficient : public StaticHierarchy<2>  {
  using StaticHierarchy<2>::StaticHierarchy;
public:
  Type type() const override;
  Expression * clone() const override;
private:
  constexpr static int k_maxNValue = 100;
  /* Layout */
  ExpressionLayout * privateCreateLayout(FloatDisplayMode floatDisplayMode, ComplexFormat complexFormat) const override {
    return LayoutEngine::createPrefixLayout(this, floatDisplayMode, complexFormat, name());
  }
  int writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits = PrintFloat::k_numberOfStoredSignificantDigits) const override {
    return LayoutEngine::writePrefixExpressionTextInBuffer(this, buffer, bufferSize, numberOfSignificantDigits, name());
  }
  const char * name() const { return "permute"; }
  /* Simplification */
  Expression * shallowReduce(Context& context, AngleUnit angleUnit) override;
  /* Evaluation */
  Expression * privateApproximate(SinglePrecision p, Context& context, AngleUnit angleUnit) const override { return templatedApproximate<float>(context, angleUnit); }
  Expression * privateApproximate(DoublePrecision p, Context& context, AngleUnit angleUnit) const override { return templatedApproximate<double>(context, angleUnit); }
  template<typename T> Complex<T> * templatedApproximate(Context& context, AngleUnit angleUnit) const;
};

}

#endif

