// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#pragma once

#include <hilti/ast/types/unknown.h>

#include <spicy/ast/aliases.h>
#include <spicy/ast/engine.h>
#include <spicy/ast/types/unit-item.h>
#include <spicy/ast/types/unit.h>

namespace spicy::type::unit::item {

/**
 * AST node for a unit field with its type determined by a not yet resolved
 * ID. The ID may refer to either a type or an ctor.
 */
class UnresolvedField : public hilti::NodeBase, public spicy::trait::isUnitItem {
public:
    UnresolvedField(const std::optional<ID>& id, Type type, Engine e, const std::vector<Expression>& args,
                    std::optional<Expression> repeat, const std::vector<Expression>& sinks,
                    std::optional<AttributeSet> attrs = {}, std::optional<Expression> cond = {},
                    std::vector<Hook> hooks = {}, Meta m = Meta())

        : NodeBase(nodes(std::move(type), id, std::move(repeat), std::move(attrs), std::move(cond), args, sinks,
                         std::move(hooks)),
                   std::move(m)),
          _engine(e),
          _args_start(5),
          _args_end(_args_start + static_cast<int>(args.size())),
          _sinks_start(_args_end),
          _sinks_end(_sinks_start + static_cast<int>(sinks.size())) {}

    UnresolvedField(const std::optional<ID>& id, Ctor ctor, Engine e, const std::vector<Expression>& args,
                    std::optional<Expression> repeat, const std::vector<Expression>& sinks,
                    std::optional<AttributeSet> attrs = {}, std::optional<Expression> cond = {},
                    std::vector<Hook> hooks = {}, Meta m = Meta())

        : NodeBase(nodes(std::move(ctor), id, std::move(repeat), std::move(attrs), std::move(cond), args, sinks,
                         std::move(hooks)),
                   std::move(m)),
          _engine(e),
          _args_start(5),
          _args_end(_args_start + static_cast<int>(args.size())),
          _sinks_start(_args_end),
          _sinks_end(_sinks_start + static_cast<int>(sinks.size())) {}

    UnresolvedField(const std::optional<ID>& id, Item item, Engine e, const std::vector<Expression>& args,
                    std::optional<Expression> repeat, const std::vector<Expression>& sinks,
                    std::optional<AttributeSet> attrs = {}, std::optional<Expression> cond = {},
                    std::vector<Hook> hooks = {}, Meta m = Meta())

        : NodeBase(nodes(std::move(item), id, std::move(repeat), std::move(attrs), std::move(cond), args, sinks,
                         std::move(hooks)),
                   std::move(m)),
          _engine(e),
          _args_start(5),
          _args_end(_args_start + static_cast<int>(args.size())),
          _sinks_start(_args_end),
          _sinks_end(_sinks_start + static_cast<int>(sinks.size())) {}

    UnresolvedField(std::optional<ID> id, ID unresolved_id, Engine e, const std::vector<Expression>& args,
                    std::optional<Expression> repeat, const std::vector<Expression>& sinks,
                    std::optional<AttributeSet> attrs = {}, std::optional<Expression> cond = {},
                    std::vector<Hook> hooks = {}, Meta m = Meta())
        : NodeBase(nodes(std::move(unresolved_id), std::move(id), std::move(repeat), std::move(attrs), std::move(cond),
                         args, sinks, std::move(hooks)),
                   std::move(m)),
          _engine(e),
          _args_start(5),
          _args_end(_args_start + static_cast<int>(args.size())),
          _sinks_start(_args_end),
          _sinks_end(_sinks_start + static_cast<int>(sinks.size())) {}

    auto fieldID() const { return childs()[1].tryAs<ID>(); }

    // Only one of these will have return value.
    auto unresolvedID() const { return childs()[0].tryAs<ID>(); }
    auto type() const { return childs()[0].tryAs<Type>(); }
    auto ctor() const { return childs()[0].tryAs<Ctor>(); }
    auto item() const { return childs()[0].tryAs<Item>(); }

    auto repeatCount() const { return childs()[2].tryAs<Expression>(); }
    auto attributes() const { return childs()[3].tryAs<AttributeSet>(); }
    auto condition() const { return childs()[4].tryAs<Expression>(); }
    auto arguments() const { return childs<Expression>(_args_start, _args_end); }
    auto sinks() const { return childs<Expression>(_sinks_start, _sinks_end); }
    auto hooks() const { return childs<Hook>(_sinks_end, -1); }
    Engine engine() const { return _engine; }

    bool operator==(const UnresolvedField& other) const {
        return _engine == other._engine && unresolvedID() == other.unresolvedID() && fieldID() == other.fieldID() &&
               attributes() == other.attributes() && arguments() == other.arguments() && sinks() == other.sinks() &&
               condition() == other.condition() && hooks() == other.hooks();
    }

    // Unit item interface
    Type itemType() const { return hilti::type::unknown; }
    auto isEqual(const Item& other) const { return node::isEqual(this, other); }

    // Node interface.
    auto properties() const { return node::Properties{{"engine", to_string(_engine)}}; }

private:
    Engine _engine;
    const int _args_start;
    const int _args_end;
    const int _sinks_start;
    const int _sinks_end;
};

} // namespace spicy::type::unit::item
