//*****************************************************************//
//    Albany 3.0:  Copyright 2016 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef ALBANY_DISTRIBUTED_PARAMETER_HPP
#define ALBANY_DISTRIBUTED_PARAMETER_HPP

#include "Albany_ThyraTypes.hpp"
#include "Albany_CombineAndScatterManager.hpp"

#include "Panzer_DOFManager.hpp"
#include "Teuchos_RCP.hpp"
#include "Teuchos_TestForException.hpp"

#include <string>

namespace Albany {

//! Class for storing distributed parameters
class DistributedParameter {
public:

  //! Constructor
  DistributedParameter(
    const std::string& param_name_,
    const Teuchos::RCP<const Thyra_VectorSpace>& owned_vs_,
    const Teuchos::RCP<const Thyra_VectorSpace>& overlapped_vs_) :
      param_name(param_name_)
  {
    // Sanity checks
    TEUCHOS_TEST_FOR_EXCEPTION(owned_vs_.is_null(), std::runtime_error, "Error! Owned vector space is null.\n");
    TEUCHOS_TEST_FOR_EXCEPTION(overlapped_vs_.is_null(), std::runtime_error, "Error! Overlapped vector space is null.\n");

    owned_vec = Thyra::createMember(owned_vs_);
    overlapped_vec = Thyra::createMember(overlapped_vs_);

    lower_bounds_vec = Thyra::createMember(owned_vs_);
    upper_bounds_vec = Thyra::createMember(owned_vs_);

    cas_manager = createCombineAndScatterManager(owned_vs_, overlapped_vs_);
  }

  //! Destructor
  virtual ~DistributedParameter() {}

  //! Get name
  const std::string& name() const { return param_name; }

  //! Set workset_elem_dofs map
  void set_dof_mgr(const Teuchos::RCP<const panzer::DOFManager>& dof_mgr) {
    m_dof_mgr = dof_mgr;
  }

  //! Access the dof manager for this parameter
  Teuchos::RCP<const panzer::DOFManager> dof_mgr() const { return m_dof_mgr; }

  //! Get vector space 
  virtual Teuchos::RCP<const Thyra_VectorSpace> vector_space() const { return owned_vec->space(); }

  //! Get overlap vector space
  virtual Teuchos::RCP<const Thyra_VectorSpace> overlap_vector_space() const { return overlapped_vec->space(); }

  //! Get vector
  virtual Teuchos::RCP<Thyra_Vector> vector() const { return owned_vec; }

  //! Get overlapped vector
  virtual Teuchos::RCP<Thyra_Vector> overlapped_vector() const { return overlapped_vec; }

  //! Get lower bounds vector
  Teuchos::RCP<Thyra_Vector> lower_bounds_vector() const { return lower_bounds_vec; }

  //! Get upper bounds vector
  Teuchos::RCP<Thyra_Vector> upper_bounds_vector() const { return upper_bounds_vec; }

  //! Fill overlapped vector from owned vector (CombineMode = INSERT)
  void scatter() const {
    cas_manager->scatter(owned_vec, overlapped_vec, CombineMode::INSERT);
  }

  //! Fill owned vector from overlapped vector (CombineMode = ZERO)
  void combine() const {
    // Note: this allows one to fill the overlapped vector (rather than the owned)
    //       during the evaluation phase, and simply copy what's local in the
    //       overlapped_vec into the owned_vec
    cas_manager->combine(overlapped_vec, owned_vec, CombineMode::ZERO);
  }

  //! Get the CombineAndScatterManager for this parameter
  virtual Teuchos::RCP<const CombineAndScatterManager> get_cas_manager () const { return cas_manager; }

protected:

  //! Name of parameter
  std::string param_name;

  //! Owned and repeated vectors
  Teuchos::RCP<Thyra_Vector>        owned_vec;
  Teuchos::RCP<Thyra_Vector>        overlapped_vec;

  //! Lower and upper bounds (they are null if never provided)
  Teuchos::RCP<Thyra_Vector>        lower_bounds_vec;
  Teuchos::RCP<Thyra_Vector>        upper_bounds_vec;

  //! The manager for scatter/combine operation
  Teuchos::RCP<const CombineAndScatterManager> cas_manager;

  // Dof manager
  Teuchos::RCP<const panzer::DOFManager>  m_dof_mgr;
};

} // namespace Albany

#endif // ALBANY_DISTRIBUTED_PARAMETER_HPP
