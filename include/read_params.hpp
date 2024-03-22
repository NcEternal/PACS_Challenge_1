#ifndef HH_READ_PARAMETERS_HH
#define HH_READP_ARAMETERS_HH

#include "parameters.hpp"
/*Reads parameters from .pot file

filename	string containing the name of the file;
n_vars		number of variables in the function to minimize;
verbose		true = print the parameters;
numerical	true = use numerical gradient;
*/
params read_parameters(std::string const& filename, unsigned n_vars, bool verbose, bool numerical);

#endif