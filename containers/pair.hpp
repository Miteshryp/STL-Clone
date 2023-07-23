#pragma once

namespace pixel {

template<typename Key_Type,typename Value_Type>
class pair {
    using key_type = Key_Type;
    using key_reference = Key_Type&;

    using value_type = Value_Type;
    using value_reference = Value_Type&;

    using pair_type = pixel::pair<Key_Type, Value_Type>;
    using pair_reference = pixel::pair<Key_Type, Value_Type>&;
    using pair_ptr = pixel::pair<Key_Type, Value_Type>*;
    using const_pair_reference = pixel::pair<Key_Type, Value_Type> const&;

public:
    /**
     * @brief Construct a new pair object
     * @todo implement
     */
    pair();
    pair(const_pair_reference pair);
    pair(pair_type&& pair);

public:
    union {
        Key_Type first;
        Key_Type key;
    };

    union {
        Value_Type second;
        Value_Type value;
    };

};

}