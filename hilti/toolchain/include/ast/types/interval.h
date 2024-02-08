// Copyright (c) 2020-2023 by the Zeek Project. See LICENSE for details.

#pragma once

#include <memory>
#include <utility>

#include <hilti/ast/type.h>

namespace hilti::type {

/** AST node for a `interval` type. */
class Interval : public UnqualifiedType {
public:
    std::string_view typeClass() const final { return "interval"; }

    bool isAllocable() const final { return true; }
    bool isSortable() const final { return true; }

    static auto create(ASTContext* ctx, Meta meta = {}) {
        return std::shared_ptr<Interval>(new Interval(ctx, std::move(meta)));
    }

protected:
    Interval(ASTContext* ctx, Meta meta) : UnqualifiedType(ctx, {"interval"}, std::move(meta)) {}

    HILTI_NODE(hilti, Interval)
};

} // namespace hilti::type
