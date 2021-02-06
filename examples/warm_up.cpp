/*
 *	This file is part of lcqpOASES.
 *
 *	lcqpOASES -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	lcqpOASES is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	lcqpOASES is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with lcqpOASES; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <iostream>
#include "LCQProblem.hpp"

using namespace lcqpOASES;

int main() {
    std::cout << "Preparing warm up problem...\n";

    /* Setup data of first QP. */
    double H[2*2] = { 2.0, 0.0, 0.0, 2.0 };
    double g[2] = { -2.0, -2.0 };
    double lb[2] = { 0.0, 0.0 };
    double ub[2] = { 10000.0, 10000.0 };
    double S1[1*2] = {1.0, 0.0};
    double S2[1*2] = {0.0, 1.0};

    // Initial guess
    double x0[2] = { 1.0, 1.0 };

    int nV = 2;
    int nC = 0;
    int nComp = 1;

    LCQProblem lcqp( nV, nC, nComp );

	Options options;
    options.initialComplementarityPenalty = 0.5;
    options.complementarityPenaltyUpdate = 2;
    options.printLvl = printLevel::NONE;
	lcqp.setOptions( options );

    // Solve first LCQP
	returnValue retVal = lcqp.solve( H, g, lb, ub, S1, S2, (double*)0, (double*)0, (double*)0, x0);

    if (retVal != SUCCESSFUL_RETURN)
    {
        printf("Termination ended without success.\n");
        return 1;
    }

    // Get solutions
    double* xOpt = new double[2];
	double* yOpt = new double[nV + nC + 2*nComp];
	lcqp.getPrimalSolution( xOpt );
	lcqp.getDualSolution( yOpt );
	printf( "\nxOpt = [ %g, %g ];  yOpt = [ %g, %g, %g, %g ]; \n\n",
			xOpt[0],xOpt[1],yOpt[0],yOpt[1],yOpt[2],yOpt[3] );

    return 0;
}