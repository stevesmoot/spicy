.. rubric:: Operators

.. spicy:operator:: generic::Begin <iterator> begin(<container>)

    Returns an iterator to the beginning of the container's content.

.. spicy:operator:: generic::End <iterator> end(<container>)

    Returns an iterator to the end of the container's content.

.. spicy:operator:: generic::New T& new <sp> t:T

    Returns a :ref:`reference <type_reference>` to an instance of a type
    newly allocated on the heap. If ``T`` is a type, a default instance of
    that type will be allocated. If ``T`` is an expression, an instance of
    the expression's type will be allocated and initialized with the value
    of the expression.

.. spicy:operator:: generic::Pack bytes pack <sp> t:tuple

    Packs a value into a binary representation. See :ref:`packing` for
    details.

.. spicy:operator:: generic::Unpack <unpacked~value> unpack <sp> t:type

    Unpacks a value from a binary representation. See :ref:`packing` for
    details.

