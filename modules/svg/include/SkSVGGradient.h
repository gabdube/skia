/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGGradient_DEFINED
#define SkSVGGradient_DEFINED

#include "include/core/SkShader.h"
#include "modules/svg/include/SkSVGHiddenContainer.h"
#include "modules/svg/include/SkSVGTypes.h"

class SkMatrix;
class SkSVGRenderContext;
class SkSVGStop;

class SkSVGGradient : public SkSVGHiddenContainer {
public:
    ~SkSVGGradient() override = default;

    void setHref(const SkSVGStringType&);
    void setGradientTransform(const SkSVGTransformType&);
    void setSpreadMethod(const SkSVGSpreadMethod&);
    void setGradientUnits(const SkSVGObjectBoundingBoxUnits&);

protected:
    explicit SkSVGGradient(SkSVGTag t) : INHERITED(t) {}

    void onSetAttribute(SkSVGAttribute, const SkSVGValue&) override;

    bool onAsPaint(const SkSVGRenderContext&, SkPaint*) const final;

    virtual sk_sp<SkShader> onMakeShader(const SkSVGRenderContext&,
                                         const SkColor*, const SkScalar*, int count,
                                         SkTileMode, const SkMatrix& localMatrix) const = 0;

    SkSVGObjectBoundingBoxUnits fGradientUnits =
            SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kObjectBoundingBox);

private:
    using StopPositionArray = SkSTArray<2, SkScalar, true>;
    using    StopColorArray = SkSTArray<2,  SkColor, true>;
    void collectColorStops(const SkSVGRenderContext&, StopPositionArray*, StopColorArray*) const;
    SkColor resolveStopColor(const SkSVGRenderContext&, const SkSVGStop&) const;

    SkSVGStringType    fHref;
    SkSVGTransformType fGradientTransform = SkSVGTransformType(SkMatrix::I());
    SkSVGSpreadMethod  fSpreadMethod = SkSVGSpreadMethod(SkSVGSpreadMethod::Type::kPad);

    using INHERITED = SkSVGHiddenContainer;
};

#endif // SkSVGGradient_DEFINED
