#include "read_params.hpp"
#include "GetPot"
#include <fstream>

params read_parameters(std::string const& filename, unsigned n_vars, bool verbose, bool numerical) {
    // Parameter default constructor, fills it with the defaults values
    params defaults;

    // checks if file exixts and is readable
    std::ifstream check(filename);
    if (!check)
    {
        std::cerr << "\nERROR: Parameter file " << filename << " does not exist" << std::endl;
        std::cerr << "Reverting to default values." << std::endl;
        check.close();

        if (defaults.x0.size() != n_vars)
            defaults.x0 = math::vector(n_vars, 0.) + defaults.x0; // make use of the fact that the size of an element wise addition
                                                                  // is determined by the size of the left vector to adjust the size of the starting point
        if (numerical)          // Since the default is not using 
            defaults.h = 0.1;   // numerical gradient, h needs to be adjusted

        if (verbose)
            std::cout << defaults;

        return defaults;

    }
    else
        check.close();

    GetPot ifile(filename.c_str());
    params values;
    // Read parameters from getpot data base
    values.x0 = math::vector(ifile("x0", "0 0"));
    values.step_tol = ifile("step_tol", defaults.step_tol);
    values.res_tol = ifile("res_tol", defaults.res_tol);
    values.step = ifile("step", defaults.step);
    values.step_decay = ifile("step_decay", defaults.step_decay);
    values.max_iter = ifile("max_iter", defaults.max_iter);
    values.algorithm = ifile("algorithm", defaults.algorithm);
    values.strategy = ifile("strategy", defaults.strategy);

    if (values.x0.size() != n_vars)
        values.x0 = math::vector(n_vars, 0.) + values.x0; // make use of the fact that the size of an element wise addition
                                                          // is determined by the size of the left vector to adjust the size of the starting point

    if(numerical)                   // Read h only if the numerical gradient is being used
        values.h = ifile("h", 0.1); // Since the default is not using numerical gradient, we set default value to 0.1 instead of defaults.h
       
    if (verbose)
        std::cout << values;

    return values;

}