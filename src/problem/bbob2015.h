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

#ifndef PAGMO_PROBLEM_BBOB2015_H
#define PAGMO_PROBLEM_BBOB2015_H

#include <string>

#include "../serialization.h"
#include "../types.h"
#include "base.h"

extern "C"{
	/* the specific includes for BBOB */
	#include "./bbob_original/bbobStructures.h"
}

namespace pagmo{ namespace problem {
	
   /// The BBOB 2015 problems: Real-Parameter Black-Box Optimization Benchmarking
   /**
    * This class allows to instantiate any of the 54 benchmark functions of 
	* Black-Box Optimization Benchmarking testbed for Real-Parameter
    * Blackbox Optimization at CEC'2015.
	*
    * @see http://coco.gforge.inria.fr/doku.php?id=cec-bbob-2015
    *
    * @author Sunil Kumar Mahendrakar (sunil.mahendrakar19@gmail.com)
    */
class __PAGMO_VISIBLE bbob2015 : public base
{
	public:
		bbob2015(unsigned int  = 1, problem::base::size_type = 30, unsigned int = 1, const std::string = "MY_BBOB_DATA", const std::string = "Algorithm Name", const std::string = "comments");
		base_ptr clone() const;
		std::string get_name() const;
		void finalize();
	protected:
		void objfun_impl(fitness_vector &, const decision_vector &) const;

	private:
		unsigned int m_problem_number;
		double m_precision;
		unsigned int m_dim;
		unsigned int m_trailid;
		unsigned int m_initdone = 0;
};
}}

#endif
