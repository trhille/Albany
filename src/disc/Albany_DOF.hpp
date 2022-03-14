#ifndef ALBANY_DOF_HPP
#define ALBANY_DOF_HPP

#include "Albany_ThyraTypes.hpp"

#include <Panzer_DOFManager.hpp>
#include <Teuchos_RCP.hpp>

namespace Albany {

class DOF {
public:
  
private:
  Teuchos::RCP<panzer::DOFManager>        dof_mgr;
  Teuchos::RCP<const Thyra_MultiVector>   vs;
  Teuchos::RCP<const Thyra_MultiVector>   overlapped_vs;
  Teuchos::RCP<const Thyra_MultiVector>   node_vs;
  Teuchos::RCP<const Thyra_MultiVector>   overlapped_node_vs;
};

} // namespace Albany

#endif // ALBANY_DOF_HPP
