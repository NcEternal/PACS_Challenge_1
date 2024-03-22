# Challenge 1. A gradient method for the minimization of a multivariate function #

Solution to the  $1^{st}$ PACS challenge. This implementation makes use of **GetPot** and **MuParser**.

The makefile produces an executable called `minimize`. <br>
Run from the command line `./minimize -h` to print a list of options.


## Parser Functions ##

The functions already in the `src/functions/` folder ready to be used with the parser are:

* `base_function.txt`: $xy + 4x^4 + y^2 + 3x$;

* `1_variable_function.txt`: $(x - 5)e^{x - 5}$;

* `4_variable_function.txt`: $(x + y + z + t - 2)^2 - x(y + \frac{1}{2}z + \frac{3}{2}t) - y(z + \frac{1}{5}t) - zt$;

* `ugly_function.txt`: $\frac{\sin(x + \pi)}{ln(ln(x^2 + 1) + 1) + 1} + \frac{2}{5}ln(1 + e^{5(x + y)}) - x - y - \frac{2}{5}ln(2) + log_{10}(y^2 + 1)$;

The minima to these four functions are provided in the `src/expected_solutions/` folder.


### Adding Functions ###

To add functions, create a `.txt` file containing the function in its first line and put it in the `src/functions/` folder. <br>
Variables inside the function should be preceded by `$`. 

The order in which variables appear in the function matters. As an example, the functions `$x - $y` and `$y - $x` return the same value for the point (1, 2) 
because the first variable to appear in the function is evaluated as 1 and the second as 2, independent of their names.


## Parameters ##

Parameters are grouped in the following format inside of a `.pot` file:

* `x0`: this is the starting point. It's given as a string of doubles separated by spaces (e.g. `'0. -1.'`). 
Defaults to a vector of $2$ zeros when not using the parser. 
If the parser is being used, the default value is a vector of $N$ zeros, where $N$ is the number of variables in the function;

* `step_tol`: this is the tolerance on step length. It's given as a double. Defaults to $10^{-6}$;

* `res_tol`: this is the tolerance on function residual. It's given as a double. Defaults to $10^{-6}$;

* `step`: the step or learning rate to be used by the algorithm. It's given as a double. Defaults to $0.2$;

* `step_decay`: if you're using *Exponential* or *Inverse Decay*, it's the parameter $\mu$ used to reduce the step. 
When using *Line Search*, it's the parameter $\sigma$ that appears in the Armijo rule and is used to check if the step is large enough. 
It's given as a double. Defaults to $0.25$;

* `max_iter`: this is the maximum number of iteration the algorithm can take. It's given as an unsigned integer. Defaults to $5000$;

* `algorithm`: this is the algorithm to be used by the minimizer. Set it to $1$ to use *ADAM*, any other number to use *Gradient Descent*. 
Defaults to *Gradient Descent*;

* `strategy`: this is the strategy to be used by the Gradient Descent algorithm. Set it to $1$ to use *Exponential Decay*,
$2$ to use *Inverse Decay*, and any other number to use *Line Search* with the Armijo rule. Defaults to *Line Search*;

* `h`: this is the step to be used when computing the numerical approximation of the gradient. It's given as a double. Defaults to $0.01$.


### Adding Parameter Presets ###

To add a parameter preset, create a `.pot` file containing the parameters in the format described above and put it in the `src/parameters/` folder. <br>
Missing parameters will be substituted by their default values.