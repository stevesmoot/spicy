// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#pragma once

#include <spicy/ast/types/unit.h>
#include <spicy/compiler/detail/codegen/production.h>

namespace spicy::detail::codegen::production {

/**
 * A production executing as long as a given boolean expression evaluates
 * to true.
 */
class While : public ProductionBase, public spicy::trait::isNonTerminal {
public:
    While(const std::string& symbol, Expression e, Production body, const Location& l = location::None)
        : ProductionBase(symbol, l), _expression(std::move(e)), _body(std::move(body)) {}

    const Expression& expression() const { return _expression; }
    const Production& body() const { return _body; }

    // Production API
    std::vector<std::vector<Production>> rhss() const { return {{_body}}; }
    std::optional<spicy::Type> type() const { return {}; }
    bool nullable() const { return production::nullable(rhss()); }
    bool eodOk() const { return nullable(); }
    bool atomic() const { return false; }
    bool supportsSynchronize() const { return hasSize() || _body.supportsSynchronize(); }
    std::string render() const { return util::fmt("while(%s): %s", _expression, _body.symbol()); }

private:
    Expression _expression;
    Production _body;
};

} // namespace spicy::detail::codegen::production
