# Botball LACT Libraries
## Libraries for the Los Altos Community Botball Teams (LACT)

This library is written by LACT, and can be used by any other
Botball team with permission. It only supports the iRobot Create 2.0 and the KIPR
Wallaby (for more information, see the wiki). Some of the functions currently do not work and are being updated.

## Todo

[] Use gyro for driving
[] Custom speeds for drive functions
[] PWM driving for Create

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

    * Between the function's name and its arguments in a declaration
    * Around operators
	* Between a keyword and parenthisis: `if (1) {}` vs `if(1) {}`
	* Spaces should be put between a brace and anything else: `}else{` vs `} else {`
	* Spaces should be put between the `//` in a comment and its content.

* Newlines should be used to separate logical blocks of code.
* Braces should be omitted when a single line is in an if or while loop, but when you do that, also put the statement inside the block on the same line.

	```c
	// Wrong:
	while (1) {
		printf("Wrong!\n");
	}

	// Right:
	while (1) printf("Right!\n");
	```

*NOTE*: You will have to delete or remove the `createDriveOld.*` files for this to compile correctly.
