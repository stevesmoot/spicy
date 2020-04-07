// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#pragma once

#include <iostream>

#include <hilti/ast/ctor.h>
#include <hilti/ast/node.h>
#include <hilti/ast/type.h>
#include <hilti/base/result.h>

namespace hilti {
class Unit;
} // namespace hilti
namespace hilti::printer {
class Stream;
} // namespace hilti::printer
namespace spicy {
using hilti::Result;
// namespace spicy
} // namespace spicy

namespace spicy::detail {

/** Implements the corresponding functionality for the Spicy compiler plugin. */
void buildScopes(const std::vector<std::pair<ID, NodeRef>>& modules, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
bool resolveIDs(hilti::Node* root, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
bool applyCoercions(hilti::Node* root, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
void preTransformValidateAST(const hilti::Node& root, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
void postTransformValidateAST(const hilti::Node& root, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
void preservedValidateAST(const std::vector<hilti::Node>& nodes, hilti::Unit* unit);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
bool printAST(const hilti::Node& root, hilti::printer::Stream& out); // NOLINT

/** Implements the corresponding functionality for the Spicy compiler plugin. */
std::optional<hilti::Ctor> coerceCtor(hilti::Ctor c, const hilti::Type& dst, bitmask<hilti::CoercionStyle> style);

/** Implements the corresponding functionality for the Spicy compiler plugin. */
std::optional<hilti::Type> coerceType(hilti::Type t, const hilti::Type& dst, bitmask<hilti::CoercionStyle> style);

} // namespace spicy::detail
