// MIT License

// Copyright (c) 2017 Simon Pettersson

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

#include <stdexcept>

namespace cmap {

/*
  The underlying model for the binary tree
 */
namespace _model {
  /*
    A map is built like a binary tree as illustrated below.

            f1(k)
             / \
            /   \
         f2(k)  f3(k)
                 / \
                /   \
             f4(k)  f5(k)
              
    Each subtree f1,f2,f3,f4,f5 is a function which
    evaluates a key and returns an `outcome` which contains 
    information about whether the subtree contained the key,
    and in that case what the associated value was.

    To construct the tree we utilize two factory functions

    * One called `make_terminal(k,v)` which creates a function that
      evaluates a key and returns an whether it matches a particular
      constant and the associated value.

    * One called `make_branch(left,right)` which creates a branch 
      node, a function that first evaluats and returns the result of 
      evaluating the left subtree if successful. If unsuccessful it 
      evaluates the right subtree and returns the result of the 
      evaluation of the right subtree.

    Example: Construct the tree above

      const auto f5 = make_terminal(5,15);
      const auto f4 = make_terminal(4,14);
      const auto f2 = make_terminal(3,13);
      const auto f3 = make_branch(f4, f5);
      const auto f1 = make_branch(f2, f3);

      // Performing a lookup for the value `5` would
      // produce the stacktrace
      f1(5)
        f2(5) -> {false, 13}
        f3(5)
          f4(5) -> {false, 14}
          f5(5) -> {true, 15}
        ...
      -> {true, 15}
  */
  template<typename V> struct outcome {
    constexpr outcome(bool s, const V v) 
    : success{s}
    , value{v} 
    { }
    
    const bool success;
    const V value;
  };

  template<typename K, typename V>
  constexpr auto make_terminal(const K key, const V value) {
    return [key,value](const auto _key) -> outcome<decltype(value)> {
      return {_key == key, value};
    };
  };

  constexpr auto make_branch(const auto left, const auto right) {
    return [left,right](auto key) -> decltype(left(key)) {
      const auto result = left(key);
      if(result.success) {
        return {true, result.value};
      }
      return right(key);
    };
  }
}

/*
  Functional interface

  Example:
    constexpr auto map = make_map(map(13,43), map(14,44));
    constexpr auto fourty_three = lookup(map, 13);
    constexpr auto fourty_four  = lookup(map, 14);
 */

constexpr auto make_map(const auto node)
{ return node; }

constexpr auto make_map(const auto left, const auto ... rest)
{ return _model::make_branch(left, rest...); }

constexpr auto map(const auto key, const auto value)
{ return _model::make_terminal(key, value); }

constexpr auto lookup(const auto tree, const auto key) {
  const auto result = tree(key);
  return result.success ? result.value : throw std::out_of_range("No such key");
}

/*
  Class interface

  Example:
    constexpr auto map = make_lookup(map(13,43), map(14,44));
    constexpr auto fourty_three = map[13];
    constexpr auto fourty_four  = map[14];
 */

template<typename TLookup>
struct lookup_type {
  constexpr lookup_type(const TLookup m) 
  : map{m} 
  { }

  constexpr auto operator[](const auto key) const 
  { return lookup(map, key); }

  const TLookup map;
};

constexpr auto make_lookup(const lookup_type<auto> ... rest) 
{ return lookup_type{make_map(rest.map...)}; }

constexpr auto make_lookup(const auto ... rest) 
{ return lookup_type{make_map(rest...)}; }

} // namespace cmap
