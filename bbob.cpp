/*****************************************************************************
 *   Copyright (C) 2004-2015 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *                                                                           *
 *   https://github.com/esa/pagmo                                            *
 *                                                                           *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <iostream>
#include <iomanip>
#include "src/pagmo.h"
#include <stdio.h>

using namespace pagmo;

// Running algorithms on bbob2015 testbed
int main()
{
	unsigned int dim[6] = {2, 3, 5, 10, 20, 40};
    unsigned int instances[15] = {1, 2, 3, 4, 5, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    unsigned int idx_dim, ifun, idx_instances;

    double maxfunevals, minfunevals;
    /* now the main loop */
    for (idx_dim = 0; idx_dim < 6; idx_dim++)
    {
        /* Function indices are from 1 to 24 (noiseless) or from 101 to 130 (noisy) */
        /* for the noisy functions exchange the for loop with */
        /* for (ifun = 101; ifun <= 130; ifun++) */
        for (ifun = 1; ifun <= 24; ifun++)
        {
            for (idx_instances = 0; idx_instances < 15; idx_instances++)
            {
				
				maxfunevals = 5. * dim[idx_dim];
				
                minfunevals = dim[idx_dim] + 2;  /* PUT MINIMAL USEFUL NUMBER OF FEVALS */
					
				pagmo::problem::bbob2015 prob(ifun, dim[idx_dim], instances[idx_instances], "/Users/Sunil/PSO", "PSO", 
					"gen=500, omega = 0.7298, eta1 = 2.05, eta2 = 2.05, vcoeff = 0.5, variant = 5, neighb_type = 2, neighb_param = 4");
				
				pagmo::algorithm::pso algo(500);
				pagmo::population pop(prob,20);
				algo.evolve(pop);
				
				prob.finalize();
                
            }
		}
		printf("---- dimension %d-D done ----\n", dim[idx_dim]);
	}
	return 0;
}
