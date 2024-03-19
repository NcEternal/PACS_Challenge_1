# Challenge 1. A gradient method for the minimization of a multivariate function #

Solution to the  $1^{st}$ PACS challenge. This implementation makes use of the GetPot and MuParser libraries.

The makefile produces an executable called `minimize`. <br>
Run from the command line `./minimize -h` to print a list of options.


## Parser Functions ##

The functions already in the `functions/` folder to be used with the parser are:

* `base_function.txt`: $xy + 4x^2 + y^2 + 3x$;

* `1_variable_function.txt`: $(x - 5)e^{x - 5}$;

* `4_variable_function.txt`: $(x + y + z + t - 2)^2 - x(y + \frac{1}{2}z + \frac{3}{2}t) - y(z + \frac{1}{5}t) - zt$;

* `ugly_function.txt`: $\frac{\sin(x + \pi)}{ln(ln(x^2 + 1) + 1) + 1} + \frac{2}{5}ln(1 + e^{5(x + y)}) - x - y - \frac{2}{5}ln(2) + log_{10}(y^2 + 1)$;

The minima to these four functions are provided in the `expected_solutions/` folder.


### Adding Functions ###

To add functions create a `.txt` file containing the function in its first line and put it in the `functions/` folder. <br>
Variables inside the function should be preceded by `$`. <br>
The order in which variables appear in the function matters. As an example, the functions `$x - $y` and `$y - $x` return the same value for the point (1, 2) 
because the first variable to appear in the function is evaluated as 1 and the second as 2, independent of their names.