// -*- mode: c++ ; -*-
/** \file falaise/snemo/reconstruction/gamma_clustering_module.h
 * Author(s) :    Xavier Garrido <garrido@lal.in2p3.fr>
 * Creation date: 2012-10-07
 * Last modified: 2014-02-28
 *
 * Copyright (C) 2011-2014 Xavier Garrido <garrido@lal.in2p3.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *
 * Description:
 *
 *   Module for gamma clustering
 *
 * History:
 *
 */

#ifndef FALAISE_GAMMA_CLUSTERING_PLUGIN_SNEMO_RECONSTRUCTION_GAMMA_CLUSTERING_MODULE_H
#define FALAISE_GAMMA_CLUSTERING_PLUGIN_SNEMO_RECONSTRUCTION_GAMMA_CLUSTERING_MODULE_H 1

// Third party:
// - Boost:
#include <boost/scoped_ptr.hpp>
// - Bayuex/dpp :
#include <dpp/base_module.h>
// - Bayeux/geomtools:
#include <geomtools/geom_id.h>

// This project:
#include <falaise/snemo/datamodels/calibrated_calorimeter_hit.h>
#include <falaise/snemo/datamodels/calibrated_data.h>

namespace geomtools {
  class manager;
}

namespace snemo {

  namespace datamodel {
    class particle_track_data;
  }

  namespace geometry {
    class locator_plugin;
  }

  namespace reconstruction {

    /// \brief The data processing module for the gamma clustering
    class gamma_clustering_module : public dpp::base_module
    {

    public:

      /// Typedef for calorimeters collection
      typedef std::set<geomtools::geom_id> calo_list_type;

      /// Typedef for gamma dictionnaries
      typedef std::map<int, calo_list_type> gamma_dict_type;

      /// Setting geometry manager
      void set_geometry_manager(const geomtools::manager & gmgr_);

      /// Getting geometry manager
      const geomtools::manager & get_geometry_manager() const;

      /// Constructor
      gamma_clustering_module(datatools::logger::priority = datatools::logger::PRIO_FATAL);

      /// Destructor
      virtual ~gamma_clustering_module();

      /// Initialization
      virtual void initialize(const datatools::properties  & setup_,
                              datatools::service_manager   & service_manager_,
                              dpp::module_handle_dict_type & module_dict_);

      /// Reset
      virtual void reset();

      /// Data record processing
      virtual process_status process(datatools::things & data_);

    protected:

      void _get_new_neighbours(const geomtools::geom_id & gid,
                               const snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & cch,
                               std::vector<geomtools::geom_id>  & ccl,
                               std::vector<geomtools::geom_id>  & a_cluster);

      /// Special method to process and generate trajectory data
      void _process(snemo::datamodel::particle_track_data & ptd_, gamma_dict_type & clustered_gammas_);

      /// Give default values to specific class members.
      void _set_defaults ();

    private:

      const geomtools::manager * _geometry_manager_; //!< The geometry manager
      std::string _PTD_label_;                       //!< The label of the input/output  data bank

      // Locator plugin
      const snemo::geometry::locator_plugin * _locator_plugin_;

      // Macro to automate the registration of the module :
      DPP_MODULE_REGISTRATION_INTERFACE (gamma_clustering_module);
    };

  } // end of namespace reconstruction

} // end of namespace snemo

#include <datatools/ocd_macros.h>

// Declare the OCD interface of the module
DOCD_CLASS_DECLARATION(snemo::reconstruction::gamma_clustering_module)

#endif // FALAISE_GAMMA_CLUSTERING_PLUGIN_SNEMO_RECONSTRUCTION_GAMMA_CLUSTERING_MODULE_H
