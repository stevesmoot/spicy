// Copyright (c) 2023 by the Zeek Project. See LICENSE for details.

#include <spicy/ast/all.h>
#include <spicy/ast/visitor-dispatcher.h>

using namespace hilti;

SPICY_NODE_IMPLEMENTATION_0(spicy, declaration::Hook)
SPICY_NODE_IMPLEMENTATION_0(spicy, type::unit::item::switch_::Case)
SPICY_NODE_IMPLEMENTATION_1(spicy, ctor::Unit, Ctor)
SPICY_NODE_IMPLEMENTATION_1(spicy, declaration::UnitHook, Declaration)
SPICY_NODE_IMPLEMENTATION_1(spicy, operator_::unit::MemberCall, ResolvedOperator)
SPICY_NODE_IMPLEMENTATION_1(spicy, statement::Confirm, Statement)
SPICY_NODE_IMPLEMENTATION_1(spicy, statement::Print, Statement)
SPICY_NODE_IMPLEMENTATION_1(spicy, statement::Reject, Statement)
SPICY_NODE_IMPLEMENTATION_1(spicy, statement::Stop, Statement)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::Sink, UnqualifiedType)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::Unit, UnqualifiedType)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::Item, hilti::Declaration)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::Field, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::Property, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::Sink, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::Switch, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::UnitHook, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::UnresolvedField, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_1(spicy, type::unit::item::Variable, type::unit::Item)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Close, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Connect, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::ConnectFilter, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::ConnectMIMETypeBytes, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::ConnectMIMETypeString, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Gap, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SequenceNumber, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SetAutoTrim, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SetInitialSequenceNumber, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SetPolicy, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SizeReference, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::SizeValue, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Skip, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Trim, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::sink::Write, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Backtrack, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::ConnectFilter, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::ContextConst, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::ContextNonConst, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Find, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Forward, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::ForwardEod, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::HasMember, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Input, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::MemberConst, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::MemberNonConst, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Offset, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Position, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::SetInput, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::TryMember, ResolvedOperator, Expression)
SPICY_NODE_IMPLEMENTATION_2(spicy, operator_::unit::Unset, ResolvedOperator, Expression)