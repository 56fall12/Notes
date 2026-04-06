

//2.8 Programs with multiple files
/*
we can use forward declaration to link a function from another file to this one to satisfy the compiler
*/

int add(int x, int y); // this is the forward declaraction that is needed so taht main.cpp knows that add is a function elsewhere


//2.11  Header Files

/*
Forward declarations can be useful but it is very difficult to scale 
We can fix this issue via header files and typically have a .h/.hpp/None extension 
They are used to propagate a bunch of related forward declarations into a code file 
They are like shared communal files that allow us to put declarations in one place and then import them wherever we need.
iostream is an example of a header file where it forward declares cout  and cin
when we include a file, they are included at the line they say include 
when writing a header file we need two things
1. header guard 
2. The actual content of the header file AKA all the forward declarations
then we can add the file with #include "(filename)" 
putting a function or variable definition in a header file will most likely violate the one-definition rule(ODR)
we should include the include header file in their paired header file to catch errors at compile time rather than link process
we should never #include .cpp files 
1. can cause naming collisions 
2. in a larger project, can violate the ODR rule
3. if any changes to a cpp file were to happen, the other cpp files would have to recompile and waste a lot of time
4. Unconventinal
use brackets for header files we didn't write ourselves which will let the preprocessor to search for the header only in the default dictionaries 
use " " when it is a header file we wrote so the preprocesser will first search the current directory
Each file should explicitly #include all the header files it needs to compile and we shouldn't rely on files transitively included from other header files
Best Order to Include
1.The paired header file for this code file (EX. add.cpp should include add.h first)
2.Other headers from the same project
3.3rd party libraries
4.default libraries (iostream)
*/

//5.1 constant variables (named constants)

/*
C++ supports two types of constants
Named constants that are constant values that are associated with an identifier. Can also be called symbolic constants
Literal Constants are constants that are not associated with an identifier
to create a constant variable place "const" next to the datatype (can be before or after) (place const before, easier to read)
can also initalize a constant variable from a normal variable
good practice to make variables constant whenver possible 
1. reduces bugs
2. can allow the compiler to optimize the program mored
3. Reduces overall complexity 
exceptions are by-value function parameters and by-value return types
*/


//6.4 Increment/Decrement Operators, and side effects
/*
++x  : operate on x first, then return it
x++ : copy x , then increment x, then return the copy
same with -
we should prefer the prefix version as it is more performant and less likely to cause surprises
we say something has a side effect when it has some observable effect beyond producing a return value 
side effects can cause order of evaluation issues 
C++ does ont define the order of evaluation for funtion arguements or the operands of operators
dont use a variable that has a side effect applied to it more than once in a given statement, may become an undefined result 

*/

//10.8 Type Deduction for objects using the auto keyword
/*
can use the keyword auto to have c++ deduce the type of the object
type deductions also typically drop the const status 
if you wanna type deduction a string, you have to put a s or sv at the end or it will be a char
benefits is readability
type deduction only works on varaibles that have initalizaers so it can help you prevent errors
guarenteed to have no unintended performance impacting conversions
downsides
it obscures which type it actually is
it can unexpectdly change our type if the type of the initailzer changes 
use type deduction for your variable when the type of the object doesn't matter
favor an explicit type when you require a specific type that differs from the type of the initializer 
Can also be when the object is used in a context where making the type obvious is useful 
*/

//12.1 Intorduction to compound data types
/*
We can use compound data types to solve certain types of problems like needing to use multiple variables
Every data type is eitehr a fundamental type or a compound type
void is an example of a compoundd data type 
a class type is a type that is struct, class or union. 
*/

//12.2 Value categories
/*
The properties of an expression have a type and a value category
The type of an expression is the same as the type of the value that results from the function 
the value of an expression indicates whether an expression resolves to a value, a function or an object of some kind 
lvalue(ell-value) is an expression that evaluates to an identifiable object or function
entities with identities that can be accessed via an identifier, reference, or pointer all typically have a longer lifetime than a single expression or statement
there are two types of lvalues
modifiable can be modified
non-modifiable cannot be modified (const or constexpr)
An lvalue is any expression that refers to a memory location 
rvalue is an expression that is not an lvalue
Rvalue expressions evaluate to a value 
they typically include literals and the return values of functions and operators that return by value
Rvalues aren't identifiable and only exist within the scope of the expression in which they are used 
Lvalues expressions evaluate to an identifiable object
Rvalue expressions evaluate to a value 
Rvalues do not have a stable named memory location
operators expect their operands to be Rvalues 
an assignment operators require the left operand to be a modifiable lvalue expression while the right is an rvalue
An lvalue will implicitly convert to an rvalue which means that an lvalue can be used anywhere an rvalue is used
an rvalue will not implicilty convert to an lvaluei
A rule of thumb to identify lvalue and rvalue expressions:
Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.
*/

//12.3 Lvalue References
/*
a reference is an alias for an existing object 
a reference is esentially identical to the object being referenced
An lvalue refernce acts as an alias fro an existing lvalue 
the type of a reference determines what type of object it can reference 
Lvalue can be identified by use of a single & in the type specifier 
*/

int& //an lvalue reference to an int object
double& //an lvalue reference to a double object
const int& //an lvalue reference to a constant int object

/*
An lvalue reference to a non-const is just an lvalue reference 
an lvalue reference to a const is called a lvalue reference to const or a const lvalue reference
we can use this to create an lvalue reference variable that acts as a reference to a nother lvalue
we just define the varaible with an lvalue reference type
*/

int x {5}; //x is a nomral integer value
int& ref {x}; //ref is an lvalue reference variable that can be used as an alias for variable x

/*
all refernces must be initialized thorough reference initialization
we say it is bound to that object and it is through reference binding 
the object that got bound to is sometimes referred to as the referent 
can only bind lvalue reference to modifiable since we can violate their const if we bind something to it
a refernece will only bind to an object of the same type most of the type 
if we try to bind a reference that doesn't match, the compiler will try to convert the object
references cannot be changed to another object
the lifetime of reference and referent are independent 
a reference can be deleted before the object is
the referent can be deleted before the refernce
when the referent is destroyed before a reference to it, the reference is left as a dangling reference and will lead to undefined behavior 
references are not objects
*/

//12.4 Lvalue refernces to const
/*
Since we cannot bind to a refernce to a constant, we have to use a const variable to declare it 
It is called an lvalue reference to a const value 
we can bind a const reference to a modifiable lvalue but we cannot modify the lvalue through the reference
Favor const references unless we need to modify the object 
if we tried to bind a const lvalue reference to a value of a different type, the compiler will try to create a temporary object of the same reference, initialize, and then bind it
When a const lvalue reference is directly bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference
Lvalue const references can bind to modifiable lvalue, non-modifiable, and rvalues
*/

//12.5 Pass by lvalue reference
/*
class types are expensive to copy and we would want to avoid them whenever possible 
we can avoid this by doing a pass by reference instead of a pass by value 
we do this by declaring a function parameter as a reference type 
pass by references allow us to pass arguements to a function wihtout making copies of those arguments each time the function is called
Passing values by reference to non-const allows us to write functions that modify the value of arguments passed in.
can only accept modifiable lvalues
*/

//12.6 Pass by const lvalue reference
/*
if we use a const lvalue reference for our parameter, we can pass in any type of argument 
Favor passing by const unless we have a specific reason not to 
Since C++ will try to convert and match the type, it will create a copy and remove the reason we do pass by const lvalue in the first place 
pass fundamental types by value and class types by const refernce
we should use string_view by value instead of string& unless the funciton calls other functions that require C-style strings or string parameters
copying a string_view is inexpensive while copying view is expensive 
*/

//14.1 Introduction to object-oriented programming
/*
we can use oop to help with things like inheritance, encapsulation, abstraction, and polymorphism 
*/

//14.2 Introduction to classes
/*
structs provide a convenient package for sorting and moving related data values 
Issue with structs is that they do not document and enforce class invariants 
An invariant is something that must be true while executing 
it must remain in this invariant condition its entire lifetime or it would be in an invalid state
*/

//14.3 Member Functions
/*
Functions that are part of a class type are member functions while those that are not are called non-member function
Member functions must be declared inside the class type function and can be defined inside or outside the class type definition 
The object that a member function is called on is implicitly passed to the member function
member functions can be overloaded
Member functions can be used with both structs and classes.
However, structs should avoid defining constructor member functions, as doing so makes them a non-aggregate.
if we want to create a class with no data members, often overkill so we could just use a namespace instead
*/

//14.4 Const class objects and const member functions
/*
class type objects can also be made const 
we want to make them const generally if we need to ensure they aren't changed after creation
data fields cannot be modified
cannot call non-const member functions 
put const after the function parameter list and it a member function that guarentees it will not modify the object or call any non-const member functions
A const member function may not: modify the implicit object, call non-const member functions.
A const member function may: modify objects that aren’t the implicit object, call const member functions, call non-member functions.
A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both const and non-const objects.
another way to create a const object is pass an object to a function by a const reference 
*/

//14.5 Public and Private members and access specifiers 
/*
Each member of a class type has a property called an access level that determines who can access that member 
There are private, protected, and public 
It will generate a compile error if access is not permitted 
Public members of a class type do not have any restrictions in how they are accessed 
They can be called by people outside the given class type 
Members of a class are private by default 
They can only be accessed by other members of the same class 
Consider naming your private data members starting with an “m_” prefix to help distinguish them from the names of local variables, function parameters, and member functions.
Public members of classes may also follow this convention if desired. However, the public members of structs typically do not use this prefix since structs generally do not have many member functions (if any).
*/

//access attributes are shown doing public: Private:

public: 
	void print()

private: 
	int m_year

/*
Classes should generally make member variables private (or protected), and member functions public.
Structs should generally avoid using access specifiers (all members will default to public).
access levels work on a per class basis so objects of the same class type can pull into other object's class type 
*/

//14.9 Introduction of constructors
/*
Constructors are a special member function that is automically called when a non-aggregate class type object is created(has private data fields)
Once a non-aggregate is defined, the compiler will see if there are any accessible constructors that can match the initialization values 
If an accessible matching constructor is found, memory for the object is allocated, and then the constructor function is called.
If no accessible matching constructor can be found, a compilation error will be generated.
the compiler sets up the memory allocation for the object prior to the constructor call
Although the constructors don't create objects, the lack of a matching constructor will prevent the creation of the object 
Constructors mainly perform initialization of any member variables 
They may perform steup functions such as error checking values or opening a file
After a constructor is finished, we say the object has been "constructed" and is in a usable state 
Have no return types 
Must be the same name as the class
Usually public
*/

#include <iostream>
using namespace;

class Foo
{
private: 
	int m_x {};
	int m_y {};

public:
	Foo(int x, int y) //the constructor that takes in two initializers
	{
		cout << "Foo(" << x << ", " << y << ") constructed" << endl;
	}

	void print() const
	{
		cout << "Foo(" << m_x << ", " << m_y ")" << endl;
	}
};

int main()
{
	Foo foo{ 6, 7};// this calls the Foo constructor
	foo.print();

	return 0;
}

/*
constructors will also implicitely type convert if needed 
should not be const 
*/

//14.10 Constructor member initializer lists
/*
we need a member initializer list 
*/
class Foo
{
private: 
	int m_x {};
	int m_y {};

public:
	Foo (int x, int y)
		: m_x{x}, m_y { y } // member init list 

/*
defined after the constructor parameters and starts with a colon and lists each member to initialize with the initialization values for that variable 
must be initialized in the order they are defined inside the class 
Prefer using the member initializer list to initialize your members over assigning values in the body of the constructor.
when a constructor cannot construct a semantically valid object, we can say it has failed
Throwing an exception is usually the best thing to do when a constructor fails (and cannot recover)
*/

class Ball{
private:
	string color {"none"};
	double radius {0.0};

public:
	Ball (string_view color, int radius) : m_color {color} , m_radius {radius}
};

void print(const Ball& ball)
{
	cout << "thing"
}

//Classer and Header Files
/*
we can sepearte the complexity of the member function definitions by defining the member functions outside the class definition 
utilizies the same method as forward declarations 
we must prefix the member function names with the name of the class type 
when we use a header file for classes, we typically put the full definition of a class rather than just the forward declaratoin 
Prefer to put your class definitions in a header file with the same name as the class. Trivial member functions (such as access functions, constructors with empty bodies, etc…) can be defined inside the class definition.
Prefer to define non-trivial member functions in a source file with the same name as the class.
member functions inside the class definition are inline and they are exempt from the ODR rule 
*/
