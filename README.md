# BCC
Welcome to Bad Calculator Compiler, where we waste millions of CPU cycle on computation that should only take a couple. 



### What it is

Funny name, eh? Does BCC compile calculators, or is it a calculator that is simultaneously a compiler?

Well, as a matter of fact, it's more of a calculator that uses compilers to do evaluation through generating and compiling 
code that would force the compiler to compute some values during compile time through using templates.


### How to use

While I'd like to think this program been made as useless as possible, whenever an integer calculator is being made, is has some use somewhere.
By the end of the day, we may all have a moment where we need to calculate addition, subtraction, and multiplication of two digit numbers, and are too lazy to not use a calculator.
However, given the intention of making this program somewhat useless and silly, proceed to use the program with caution.

#### Dependencies and building
BCC is only tested on Linux (debian testing) so far, dependencies include:
```
G++: of a somewhat recent version
GNU make, or other supported build system. Ninja is tested to work just fine
CMake >= 3.24
Flex: tested on 2.6.4
Bison: tested on 3.8.2
```

Using CMake to build the executable and run it in the build directory should be rather straightforward. 
The `ext_include` files that are copied into the build directory is necessary too, so only copying the compiled executable
to somewhere else would not really work. 


For a basic build process, clone bcc, create a build directory inside, run CMake from within the build directory, and
running

```shell
git clone https://github.com/Extremezhazha/bcc.git
cd bcc
mkdir build
cd build
cmake ..
make
```
Or, with Ninja
```shell
git clone https://github.com/Extremezhazha/bcc.git
cd bcc
mkdir build
cd build
cmake -G Ninja ..
ninja
```

#### Actually using it

Once everything have been built, simply run `bcc`, and start doing some calculatory calculations!

By simply typing 
```python
print(29 - 20 + 30 * 10)
```

The output will be `309`, of course, due to precedence of multiplication being higher than addition and subtraction. 

We can also define a couple of variables
```python
x = 12
print(x)
```

Will simply print out `12`

We can also do some calculations with the defined variables! I mean, what else would these variables be good for? 

```python
x = 12
x = x + 1
y = x + x
print(y)
```

Will in fact print out `26`

Okay. How about lists? We know about lists, they can be nested, concatenated, and multiplied with an integer, right? 

```python
someList = ([1, 2] + [3, 4, [5, 6]]) * 3
print(someList)
```

And this will in fact, print out `[1, 2, 3, 4, [5, 6], 1, 2, 3, 4, [5, 6], 1, 2, 3, 4, [5, 6]]`, as we would expect

And of course, `print(someList[2])` prints `3`, `print(someList[4])` prints out `[5, 6]`.

Alternatively, if an expression is just a value, the result will be printed out even without the print statement. Which 
means all the print statements shown here in the examples are redundant. 
### What it does

Imagine we want to calculate the value of `2 + 3`

In which case, instead of writing 
```c++
std::cout << 2 + 3 + 4 << std::endl;
```

Why don't we first define something like

```c++
template <typename x, typename y>
struct add : public add<typename x::type, typename y::type> {};

template <int x, int y>
struct add<std::integral_constant<int, x>, std::integral_constant<int, y>> {
    using type = std::integral_constant<int, x + y>;
};
```

And simply print out... This monstrosity?

```c++
std::cout << add<add<std::integral_constant<int, 2>, std::integral_constant<int, 3>>, std::integral_constant<int, 4>>::type::value << std::endl;
```

Intrigued? Well, we can surely do more interesting things here.

Say instead of 
```c++
int x = 2;
int y = x + 3;
int z = x + y;
```

Using the `add` defined as above, we can easily write

```c++
using x_t = std::integral_constant<int, 2>;
using y_t = add<x_t, std::integral_constant<int, 3>>;
using z_t = add<x_t, y_t>;
```
And print
```c++
std::cout << z_t::type::value << std::endl; // Will print 7
```

Isn't it beautiful? We are now using types to encapsulate values, and class templates to encapsulate what is essentially function calls. 

But wait... Think about the possibilities, what if instead of writing

```c++
int v = 2;

int addV(int u) {
    return u + v;
}
```

We take a similar approach and write this?

```c++
using v_t = std::integral_constant<int, 2>;

template<typename u_t>
struct addV {
    using type = add<u_t, v_t>;
};

```

And now instead of printing `addV(3)`, we can print

```c++
std::cout << addV<std::integral_constant<int, 3>>::type::value << std::endl; // Will print 5
```

Isn't that pretty neat. Or maybe not. But also, this part is no (yet) implemented in here anyhow...
so too bad if someone was looking forward to this functionality.


On the bright side, lists are implemented already. Lists are essentially defined as 
```c++
template<typename... Types>
struct listOfTypes {};
```
And other templates are built around this to handle the list operations, such as getting the `i`th element from the list 