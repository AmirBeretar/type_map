#pragma once

template<int KEY, typename VALUE>
struct key_value { };

template<bool IS_LESS>
struct is_key_less;

template<>
struct is_key_less<true> { };

template<typename... Args>
struct type_map;

template<int KEY1, typename VALUE1, int KEY2, typename VALUE2, typename... Args>
struct type_map<key_value<KEY1, VALUE1>, key_value<KEY2, VALUE2>, Args...> :
          public type_map<key_value<KEY2, VALUE2>, Args...>
        , virtual public is_key_less<KEY1<KEY2>
{
    typedef VALUE1 type_value;
    type_value value;
};

template<int KEY, typename VALUE>
struct type_map<key_value<KEY, VALUE>>
{
    typedef VALUE type_value;
    type_value value;
};

template<bool IS_EQUAL, int KEY_E, class T>
class type_map_element_compare;

template<int KEY_E, int KEY1, typename VALUE1, int KEY2, typename VALUE2, typename... Args>
class type_map_element_compare<false, KEY_E, type_map<key_value<KEY1, VALUE1>, key_value<KEY2, VALUE2>, Args...>> :
        public type_map_element_compare<KEY_E==KEY2, KEY_E, type_map<key_value<KEY2, VALUE2>, Args...>> { };

template<int KEY_E, int KEY1, typename VALUE1, int KEY2, typename VALUE2, typename... Args>
class type_map_element_compare<true, KEY_E, type_map<key_value<KEY1, VALUE1>, key_value<KEY2, VALUE2>, Args...>> :
        public type_map<key_value<KEY1, VALUE1>, key_value<KEY2, VALUE2>, Args...>
{
public:
    typedef type_map<key_value<KEY1, VALUE1>, key_value<KEY2, VALUE2>, Args...> type;
};

template<int KEY_E, int KEY, typename VALUE>
class type_map_element_compare<false, KEY_E, type_map<key_value<KEY, VALUE>>>;

template<int KEY_E, int KEY, typename VALUE>
class type_map_element_compare<true, KEY_E, type_map<key_value<KEY, VALUE>>> :
        public type_map<key_value<KEY, VALUE>>
{
public:
    typedef type_map<key_value<KEY, VALUE>> type;
};

template<int KEY_E, class T>
class type_map_element;

template<int KEY_E, int KEY, typename VALUE, typename... Args>
class type_map_element<KEY_E, type_map<key_value<KEY, VALUE>, Args...>> :
        public type_map_element_compare<KEY_E==KEY, KEY_E, type_map<key_value<KEY, VALUE>, Args...>>{ };

template<int KEY_E, int KEY, typename VALUE>
class type_map_element<KEY_E, type_map<key_value<KEY, VALUE>>> :
        public type_map_element_compare<KEY_E==KEY, KEY_E, type_map<key_value<KEY, VALUE>>>{ };

template<int KEY, class T>
typename type_map_element<KEY, T>::type_value& get(T& map)
{
    return static_cast<typename type_map_element<KEY, T>::type&>(map).value;
}
