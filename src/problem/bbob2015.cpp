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

#include <string>
#include <time.h>
#include "../serialization.h"
#include "../types.h"
#include "base.h"

#include "bbob2015.h"


namespace pagmo{ namespace problem {

bbob2015::bbob2015(unsigned int problem_number, problem::base::size_type dim, unsigned int instance, std::string datapath, std::string algo, std::string comments):base(dim,0,1,0,0.)
{

	m_problem_number=problem_number;
	double m_precision=1e-16;
	unsigned int m_dim=dim;
	unsigned int m_trailid=1;
	unsigned int m_initdone = 0;
	
	ParamStruct params = fgeneric_getDefaultPARAMS();
    
	strcpy(params.dataPath, datapath.c_str());
    strcpy(params.algName, algo.c_str());
    strcpy(params.comments, comments.c_str());

    params.DIM = dim;
    params.funcId = problem_number;
    params.instanceId = instance;
    fgeneric_initialize(params);
}


std::string bbob2015::get_name() const
{
    std::string retval("BBOB2015");
    retval.append(boost::lexical_cast<std::string>(m_problem_number));

    return retval;
}

void bbob2015::objfun_impl(fitness_vector &f, const decision_vector &x) const
{
	std::vector<double>::size_type n = x.size();
	
	double *decision = (double *) malloc(sizeof(double)*n);
	for(int i=0; i<n; i++)
		decision[i] = x[i];
	
	f[0] = fgeneric_evaluate(decision);
	free(decision);
	
	return;
}

void bbob2015::finalize()
{
    printf("  f%d, FEs=%.0f", m_problem_number, fgeneric_evaluations());
    printf(" fbest-ftarget=%.4e\n", fgeneric_best() - fgeneric_ftarget());

    fgeneric_finalize();

}

base_ptr bbob2015::clone() const
{
    return base_ptr(new bbob2015(*this));
}

}}
