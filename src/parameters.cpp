#include "parameters.hpp"

std::ostream& operator<<(std::ostream& os, const params& p) {
    os << "\nPARAMETER VALUES:\n";
    os << "Starting Point: " << p.x0;
    os << "Step Residual Tolerance: " << p.step_tol << "\n";
    os << "Function Residual Tolerance: " << p.res_tol << "\n";
    os << "Step: " << p.step << "\n";
    os << "Maximum Iterations: " << p.max_iter << "\n";
    if (p.algorithm == 1)
        os << "Algorithm: Adam\n";
    else {
        os << "Algorithm: Gradient Descent\n";
        switch (p.strategy) {
        case 1:
            os << "Step Strategy: Exponential Decay\n";
            os << "Step Decay: " << p.step_decay << "\n";
            break;
        case 2:
            os << "Step Strategy: Inverse Decay\n";
            os << "Step Decay: " << p.step_decay << "\n";
            break;
        default:
            os << "Step Strategy: Line Search\n";
            os << "Sigma: " << p.step_decay << "\n";
        }
    }
    if(p.h > 0.)
        os << "Step for Numerical Approximation of Gradient: " << p.h << "\n";
    return os;
}