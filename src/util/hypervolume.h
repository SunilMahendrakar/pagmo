/*****************************************************************************
 *   Copyright (C) 2004-2013 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
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

#ifndef PAGMO_UTIL_HYPERVOLUME_H
#define PAGMO_UTIL_HYPERVOLUME_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../population.h"
#include "hv_algorithm/base.h"
#include "hv_algorithm/native2d.h"
#include "hv_algorithm/beume3d.h"
#include "hv_algorithm/wfg.h"
#include "hv_algorithm/bf_approx.h"

namespace pagmo { namespace util {

class hypervolume;

/// Alias for the shared pointer to a pagmo::util::hypervolume.
typedef boost::shared_ptr<hypervolume> hypervolume_ptr;

/// Hypervolume class.
/**
 * This class allows for setting up, and solving the hypervolume computation problems.
 * Construction of the problem is either done using the population object, or from a fixed set of points.
 *
 * @author Krzysztof Nowak (kn@kiryx.net)
 */
class __PAGMO_VISIBLE hypervolume
{
	public:
		hypervolume();
		hypervolume(const hypervolume &);
		hypervolume(const boost::shared_ptr<population>, const unsigned int front_idx = 0);
		hypervolume(const std::vector<fitness_vector> &);

		double compute(const fitness_vector &, const hv_algorithm::base_ptr) const;
		double compute(const fitness_vector &) const;

		double exclusive(const unsigned int, const fitness_vector &, const hv_algorithm::base_ptr) const;
		double exclusive(const unsigned int, const fitness_vector &) const;

		unsigned int least_contributor(const fitness_vector &, const hv_algorithm::base_ptr) const;
		unsigned int least_contributor(const fitness_vector &) const;

		static unsigned long long get_expected_operations(const unsigned int n, const unsigned int d);

		fitness_vector get_nadir_point(const double epsilon = 0.0) const;

		hypervolume_ptr clone() const;
		const std::vector<fitness_vector> &get_points() const;

	private:
		// Method returning the best performing algorithm for given computational task
		hv_algorithm::base_ptr get_best_method(const fitness_vector &) const;

		std::vector<fitness_vector> m_points;
		void verify_after_construct() const;
		void verify_before_compute(const fitness_vector &, const hv_algorithm::base_ptr) const;

		friend class boost::serialization::access;
		template <class Archive>
		void serialize(Archive &ar, const unsigned int)
		{
			ar & m_points;
		}
};

}}

BOOST_CLASS_EXPORT_KEY(pagmo::util::hypervolume);

#endif
