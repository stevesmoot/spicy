[...]

namespace hlt_my_http::MyHTTP {
    struct RequestLine : ::hilti::rt::trait::isStruct, ::hilti::rt::Controllable<RequestLine> {
        std::optional<::hilti::rt::Bytes> method{};
        std::optional<::hilti::rt::Bytes> uri{};
        std::optional<::hilti::rt::ValueReference<Version>> version{};
        [...]
    };

    struct Version : ::hilti::rt::trait::isStruct, ::hilti::rt::Controllable<Version> {
        std::optional<::hilti::rt::Bytes> number{};
        [...]
    };

    [...]

    extern auto parse1(::hilti::rt::ValueReference<::hilti::rt::Stream>& data, const std::optional<::hilti::rt::stream::View>& cur, const std::optional<::spicy::rt::UnitContext>& context) -> ::hilti::rt::Resumable;
    extern auto parse2(::hilti::rt::ValueReference<__hlt_my_http::MyHTTP::RequestLine>& unit, ::hilti::rt::ValueReference<::hilti::rt::Stream>& data, const std::optional<::hilti::rt::stream::View>& cur, const std::optional<::spicy::rt::UnitContext>& context) -> ::hilti::rt::Resumable;
    extern auto parse3(::hilti::rt::ValueReference<::spicy::rt::ParsedUnit>& gunit, ::hilti::rt::ValueReference<::hilti::rt::Stream>& data, const std::optional<::hilti::rt::stream::View>& cur, const std::optional<::spicy::rt::UnitContext>& context) -> ::hilti::rt::Resumable;
}

[...]
