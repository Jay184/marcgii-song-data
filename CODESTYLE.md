# Code style guides
It is good to write code idiomatically in each language and not bring,
for example, Python experience to JavaScript. The doc describes idiomatic &
widely-used by the languages' communities styles of coding.

## All languages
* Readability counts.
* Be consistent.
* [Don't repeat yourself](http://en.wikipedia.org/wiki/Don't_repeat_yourself).
* Flat is better than nested.
* Beautiful is better than ugly.
* Simple is better than complex.
* Add blank line to the end of every file.
* Limit lines to 80 characters.
* Indentations are done using 4 spaces, no tabs.

## Git
* Keep the repository clean.
* Don't commit big files unless they absolutely require git.
* Structure your commit message like this:
    ```
    One line summary (less than 50 characters)

    Longer description (wrap at 72 characters)
    ```
* Commit summary:
    * Less than 50 characters.
    * What was changed.
    * Imperative present tense (fix, add, change): ("Fix bug 123.", "Add
      'foobar' command.", "Change default timeout to 123.").
      [official git style](http://repo.or.cz/w/git.git?a=blob;f=Documentation/SubmittingPatches;hb=HEAD)
    * End with period.
* Commit description:
    * Wrap at 72 characters.
    * Why, explain intention and implementation approach.
    * Present tense.
* Commit atomicity:
    * Break up logical changes.
    * Make whitespace changes separately.
* Branch naming:
    * Use hyphens as word a separator.

## C++
* Variables, functions and namespaces are written in *snake_case*.
* Classes are written in *PascalCase*.
* Curly brackets go in the same line.
* Prefer `using` over `typedef`.
* Avoid `using namespace` statements.
    - Write `std::string` instead of `string`, for example.
* Try to use `const`, `constexpr`, and references as best as possible to avoid accidental copies and ensure smaller assemblies.
* Avoid macros if not required.
    - Define macro names in *UPPER_SNAKE_CASE*
    - Place the definition at the top near the include statements.
    - Give macros a prefix e.g. `WIN_MAX(a, b)` instead of `MAX(a, b)`.
* Try to avoid global variables, and if used, give them a default value.
* When commenting, put a space after the commenting slashes, unless it is code:
    ```cpp
    // This is a comment
    //if(code) { no_space }
    ```
* If-statements with only one statement still have their curly brackets.
    - Both of the following are okay:
        ```cpp
        if (condition) { statement; }
        if (condition) {
            statement;
        }
        ```
* Only use `auto` if:
    1. It infers the correct variable.
    (certain compilers struggle with references, so use `auto&`).
    2. The real type is too long (over 20 characters)
    3. The variable name hints at the type.
* Resolve old-style Windows macros to their final construct if possible.
    - Do not use `NULL`, prefer `nullptr` or simply `0`.
    - Instead of `BOOL`, use `int`.
* Use the following include guard in your header files:header files:
    ```cpp
    // folder/file.hpp
    #ifndef FOLDER_FILE_HPP_INCLUDED
    #define FOLDER_FILE_HPP_INCLUDED
    #pragma once

    // Implementation here

    #endif // FOLDER_FILE_HPP_INCLUDED
    ```
* Only include what is required.
* Use `<>` for external includes, `""` for internal files.
* Order includes:
    - std
    - external
    - internal
* Use parenthesis around logical expressions when the order of operations is unclear:
    ```cpp
    if (A || (B && C)) { statement; }
    if ((A() + 1) == 0xFF || (B << (C ^ D))) { statement; }
    ```
* When dealing with many parameters or arguments, write one per line:
    - When doing this for functions, indent the parameters by one level
        ```cpp
        const int calculate(
                int a,
                int b,
                int c,
                int d,
                int e,
                int f) {
            return a + b + c + d + e + f;
        }
        ```
