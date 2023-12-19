# match-cpp

A basic implementation of "pattern matching" in C++

[Pattern matching](https://en.wikipedia.org/wiki/Pattern_matching) is a beloved feature of typed functional languages, and has been adopted by more and more languages like Rust and Python. It allows for applying code over a union/ADT in a concise and readable way.

Examples from Rust:
```rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}
```

```Rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}
```

Conceptually, I believe pattern matching is made out of two parts:
- branching code based on types in a union
- destructuring members

Specifically for the last one, you can see that
```Rust
Coin::Quarter(state) => {
    println!("State quarter from {:?}!", state);
    25
}
```
in the above pattern matching clause is able to assign the `USState` member to the `state` variable in the match expression very concisely. C++ does have some capability for this, seen from [structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding) but it is currently out of scope for this project.

So this repo will be focusing on branching based on types aspect of pattern matching, not full fledged pattern matching.

## Goals
We will be applying over `std::variant` for pattern matching, which is C++'s implementation of a type-safe discriminated union.

### Exhaustiveness
The match construct should be exhaustive. If a case is missing, for example

```
// rough pseudocode

std::variant<bool, int> var;
...
match var 
  bool -> {
    //blah blah
  }
  // forgot about int!
```

this program should error. And specifically, it should error at compile time.

### Wildcard matching
There should still be an explicit backdoor allowed for this though. For example there should be some construct for, 
```
// rough pseudocode

std::variant<A, B, C, D, E> var;
...
match var 
  A -> {
    //blah blah
  }
  _ -> {
    //blah blah
  }
```
where we specify a code path for `A`, and let all the other types take the wildcard path.

### No implicit conversions
C++ allows for many types to implicitly convert to each other, for example `float` to `double`. It is out of scope whether or not this is a good idea in general, but for pattern matching specifically it should be outlawed.
```
// rough pseudocode

std::variant<float, double> var;
...
match var 
  float -> {
    //blah blah
  }
  // forgot about double!
```
as described above, this example is non-exhaustive, and should error. However, implicit conversions could theothetically make the case that this construct is well-formed, because the `double` can just implicitly convert to `float`, so it remains exhaustive.

However, pattern matching fundamentally is trying to apply specific code paths to specific types. Implicit conversions that allow a type to take the path of another goes against this idea. Therefore they should not apply for pattern matching.
