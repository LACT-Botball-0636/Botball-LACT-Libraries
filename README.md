# Botball LACT Libraries
## Libraries for the Los Altos Community Botball Teams (LACT)

This library is written by LACT, and can be used by any other
Botball team with permission. It only supports the iRobot Create 2.0 and the KIPR
Wallaby. Some of the functions currently do not work and are being updated.

All information about the library and code is in the [Wiki](https://github.com/LACT-Botball-0636/Botball-LACT-Libraries/wiki). 

## Getting Started

1. Copy libary files into project
2. Write code for your robot in a separate Main file (ex. createMain.* and linkMain.*). This allows for cleaner code and easier updates to newer versions of the libraries.
3. Check that all library files are included with `#include`
4. Compile
5. Robot Works

## Todo

* Use gyro for driving
* PWM driving for Create

## Styleguide

* Use two spaces, no indents
* Keep braces on the same line as the procedure or statement:

	```c
	// Wrong:
	while (1)
	{
		printf("Wrong!\n");
	}

	// Right:
	while (1) {
		printf("Right!\n");
	}
	```

* Spaces should be put where possible:
    
    * Around operators
	* Between a keyword and parenthisis: `if (1) {}` vs `if(1) {}`
	* Spaces should be put between a brace and anything else: `}else{` vs `} else {`
	* Spaces should be put between the `//` in a comment and its content.
    * One exception is between the function's name and its arguments in a declaration

* Newlines should be used to separate logical blocks of code.
* Braces should be omitted when a single line is in an if or while loop.

	```c
	// Right:
	while (1)
		printf("right!\n");
	```

*NOTE*: You will have to delete or remove the `createDriveOld.*` files for this to compile correctly.
