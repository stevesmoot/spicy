// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#pragma once

#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include <hilti/ast/id.h>
#include <hilti/base/id-base.h>
#include <hilti/base/util.h>
#include <hilti/json.h>

namespace hilti::detail::cxx {

class Formatter;

namespace element {
enum class Type { Expression, Type, Linkage, Attribute };
} // namespace element

/** An element of type `T` in the compiler's intemediary C++ representation. */
template<element::Type T>
class Element {
public:
    Element() = default;
    Element(std::string s) : _s(std::move(s)) {}
    Element(const char* s) : _s(s) {}

    Element& operator=(const std::string& s) {
        _s = s;
        return *this;
    }
    Element& operator=(std::string&& s) {
        _s = std::move(s);
        return *this;
    }
    Element& operator=(const char* s) {
        _s = s;
        return *this;
    }

    bool isMultiLine() const { return _s.find('\n') != std::string::npos; }

    operator std::string() const { return _s; }
    explicit operator bool() const { return ! _s.empty(); }
    bool operator<(const Element& s) const { return _s < s._s; }
    bool operator==(const Element& s) const { return _s == s._s; }

private:
    std::string _s;
};

using Attribute = Element<element::Type::Attribute>;   /**< C++ function attribute */
using Expression = Element<element::Type::Expression>; /**< C++ expression */
using Linkage = Element<element::Type::Linkage>;       /**< C++ linkage specification */
using Type = Element<element::Type::Type>;             /**< C++ type */

extern std::string normalize_id(std::string id);

/** A C++ ID. */
class ID : public detail::IDBase<ID, normalize_id> {
public:
    using Base = detail::IDBase<ID, normalize_id>;
    using Base::IDBase;
    ID() = default;
    explicit ID(const ::hilti::ID& id) : Base(std::string(id)) {}
    ID& operator=(const ::hilti::ID& id) {
        *this = ID(id);
        return *this;
    }

    /** Wrapper to construct an ID from an already normalized string name. */
    static ID fromNormalized(std::string id) { return ID(std::move(id), Base::AlreadyNormalized()); }

private:
    static std::string _normalize(std::string id);
};

extern void to_json(nlohmann::json& j, const cxx::ID& id);   // NOLINT
extern void from_json(const nlohmann::json& j, cxx::ID& id); // NOLINT

namespace declaration {

/** A C++ `@include` specific ation. */
struct IncludeFile {
    std::string file;
    bool operator<(const IncludeFile& o) const { return file < o.file; }
};

/** Declaration of a local C++ variable. */
struct Local {
    cxx::ID id;
    cxx::Type type;
    std::vector<cxx::Expression> args;
    std::optional<cxx::Expression> init;
    Linkage linkage;

    std::string str() const;
    operator std::string() const { return str(); }
};

/** Declaration of a global C++ variable. */
struct Global {
    cxx::ID id;
    cxx::Type type;
    std::vector<cxx::Expression> args;
    std::optional<cxx::Expression> init;
    Linkage linkage;

    bool operator==(const Global& other) const {
        return id == other.id && type == other.type && init == other.init && linkage == other.linkage;
    }

    std::string str() const;
    operator std::string() const { return str(); }
};

/** Declaration of a C++ constant. */
struct Constant {
    cxx::ID id;
    cxx::Type type = Type();
    std::optional<cxx::Expression> init;
    Linkage linkage;
    bool operator<(const Constant& s) const { return id < s.id; }

    bool operator==(const Constant& other) const {
        return id == other.id && type == other.type && init == other.init && linkage == other.linkage;
    }
};

extern void to_json(nlohmann::json& j, const Constant& c);   // NOLINT
extern void from_json(const nlohmann::json& j, Constant& c); // NOLINT

/** Declaration of a C++ type. */
struct Type {
    cxx::ID id;
    cxx::Type type;
    std::string inline_code = "";
    bool forward_decl = false;
    bool forward_decl_prio = false;
    bool no_using = false;

    bool operator==(const Type& other) const {
        return id == other.id && type == other.type && inline_code == other.inline_code &&
               forward_decl == other.forward_decl && forward_decl_prio == other.forward_decl_prio &&
               no_using == other.no_using;
    }
};

extern void to_json(nlohmann::json& j, const Type& t);   // NOLINT
extern void from_json(const nlohmann::json& j, Type& t); // NOLINT

/** Declaration of a C++ function argument. */
struct Argument {
    cxx::ID id;
    cxx::Type type;
    cxx::Type internal_type = "";
    operator std::string() const { return id ? util::fmt("%s %s", type, id) : std::string(type); }

    bool operator==(const Argument& other) const { return type == other.type && id == other.id; }
};

extern void to_json(nlohmann::json& j, const Argument& a);   // NOLINT
extern void from_json(const nlohmann::json& j, Argument& a); // NOLINT

} // namespace declaration

/** A C++ statement block. */
class Block {
public:
    Block() {}
    Block(std::vector<std::string> stmts);

    void addStatement(std::string stmt);
    void addStatementAtFront(std::string stmt);
    void addBlock(Block child);
    void addComment(const std::string& stmt, bool sep_before = true, bool sep_after = false);
    void addLocal(const declaration::Local& v);
    void addTmp(const declaration::Local& v);
    void addReturn(const Expression& expr = Expression());
    void addIf(const Expression& cond, Block true_);
    void addIf(const Expression& init, const Expression& cond, cxx::Block true_);
    void addIf(const Expression& cond, Block true_, Block false_);
    void addIf(const Expression& init, const Expression& cond, Block true_, Block false_);
    void addElseIf(const Expression& cond, Block true_);
    void addElse(Block true_);
    void addFor(const Expression& init, const Expression& cond, const Expression& next, const cxx::Block& body);
    void addForRange(bool const_, const ID& id, const Expression& seq, const cxx::Block& body);
    // void addForRange(const Expression& init, bool const_, const ID& id, const Expression& seq, cxx::Block body); //
    // C++20 ...
    void addWhile(const Expression& cond, const Block& body);
    void addLambda(const std::string& name, const std::string& signature, Block body);
    void addSwitch(const Expression& cond, const std::vector<std::pair<Expression, Block>>& cases_,
                   std::optional<Block> default_ = {});
    void appendFromBlock(Block b);
    void addTry(Block body, std::vector<std::pair<declaration::Argument, Block>> catches);

    bool ensureBracesForBlock() const { return _ensure_braces_for_block; }
    void setEnsureBracesforBlock() { _ensure_braces_for_block = true; }

    size_t size(bool ignore_comments = false) const;

    Block& operator+=(const Block& other);

    operator bool() const { return ! _stmts.empty(); }

    friend ::hilti::detail::cxx::Formatter& operator<<(Formatter& f, const Block& x);

    bool operator==(const Block& other) const { return _stmts == other._stmts; }

private:
    using Flags = unsigned int;
    std::vector<std::tuple<std::string, Block, Flags>> _stmts;
    std::vector<std::string> _tmps;
    bool _ensure_braces_for_block = false;
};

namespace declaration {

/** Declaration of a C++ function. */
struct Function {
    cxx::Type result;
    cxx::ID id;
    std::vector<Argument> args;
    bool const_ = false;
    Linkage linkage = "static";
    Attribute attribute = "";
    std::optional<Block> inline_body; // TODO(robin): Not serialized to JSON yet.

    std::string prototype(bool qualify) const;
    std::string parameters() const;

    bool operator==(const Function& other) const {
        return result == other.result && id == other.id && args == other.args && linkage == other.linkage &&
               attribute == other.attribute && inline_body == other.inline_body;
    }
};

extern void to_json(nlohmann::json& j, const Function& f);   // NOLINT
extern void from_json(const nlohmann::json& j, Function& f); // NOLINT

} // namespace declaration

/** A C++ function. */
struct Function {
    declaration::Function declaration;
    Block body;
    bool default_ = false;

    bool operator==(const Function& other) const { return declaration == other.declaration && body == other.body; }
};

namespace type {
namespace struct_ {

using Member = std::variant<declaration::Local, declaration::Function>;

inline bool operator<(const Member& m1, const Member& m2) {
    auto id = [](auto m) {
        if ( auto x = std::get_if<declaration::Local>(&m) )
            return x->id;
        if ( auto x = std::get_if<declaration::Function>(&m) )
            return x->id;

        throw std::bad_variant_access();
    };

    return id(m1) < id(m2);
}

} // namespace struct_

/** A C++ struct type. */
struct Struct {
    std::vector<declaration::Argument> args;
    std::vector<struct_::Member> members;
    cxx::ID type_name;
    std::optional<cxx::Type> self;
    bool add_ctors = false;
    std::string str() const;
    std::string inlineCode() const;

    operator std::string() const { return str(); }
    operator cxx::Type() const { return str(); }
};

namespace union_ {
using Member = struct_::Member;
} // namespace union_

/** A C++ union type. */
struct Union {
    std::vector<union_::Member> members;
    cxx::ID type_name;
    std::string str() const;
    operator std::string() const { return str(); }
    operator cxx::Type() const { return str(); }
};

namespace enum_ {
using Label = std::pair<cxx::ID, int>;
} // namespace enum_

/** A C++ enum type. */
struct Enum {
    std::vector<enum_::Label> labels;
    cxx::ID type_name;
    std::string str() const;
    operator std::string() const { return str(); }
    operator cxx::Type() const { return str(); }
};

} // namespace type

inline std::ostream& operator<<(std::ostream& o, const ID& i) { return o << std::string(i); }
inline std::ostream& operator<<(std::ostream& o, const Linkage& l) { return o << std::string(l); }
inline std::ostream& operator<<(std::ostream& o, const Type& t) { return o << std::string(t); }
inline std::ostream& operator<<(std::ostream& o, const Attribute& a) { return o << std::string(a); }
inline std::ostream& operator<<(std::ostream& o, const declaration::Argument& t) { return o << std::string(t); }
inline std::ostream& operator<<(std::ostream& o, const Expression& e) { return o << std::string(e); }

extern Formatter& operator<<(Formatter& f, const Block& x);
extern Formatter& operator<<(Formatter& f, const Expression& x);
extern Formatter& operator<<(Formatter& f, const ID& x);
extern Formatter& operator<<(Formatter& f, const Function& x);
extern Formatter& operator<<(Formatter& f, const Type& x);
extern Formatter& operator<<(Formatter& f, const declaration::Type& x);
extern Formatter& operator<<(Formatter& f, const declaration::IncludeFile& x);
extern Formatter& operator<<(Formatter& f, const declaration::Local& x);
extern Formatter& operator<<(Formatter& f, const declaration::Global& x);
extern Formatter& operator<<(Formatter& f, const declaration::Function& x);
extern Formatter& operator<<(Formatter& f, const declaration::Constant& x);

} // namespace hilti::detail::cxx
