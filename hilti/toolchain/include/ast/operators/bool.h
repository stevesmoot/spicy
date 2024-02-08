// Copyright (c) 2020-2023 by the Zeek Project. See LICENSE for details.

#pragma once

#include <memory>
#include <string>

#include <hilti/ast/operators/common.h>

namespace hilti::operator_ {

HILTI_NODE_OPERATOR(hilti, bool_, Equal)
HILTI_NODE_OPERATOR(hilti, bool_, Unequal)
HILTI_NODE_OPERATOR(hilti, bool_, BitAnd)
HILTI_NODE_OPERATOR(hilti, bool_, BitOr)
HILTI_NODE_OPERATOR(hilti, bool_, BitXor)

} // namespace hilti::operator_
