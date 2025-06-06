﻿/*!
 * \file species_convection.hpp
 * \brief Declarations of numerics classes for discretization of
 *        convective fluxes in species problems.
 * \author T. Kattmann
 * \version 8.2.0 "Harrier"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2025, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../scalar/scalar_convection.hpp"

/*!
 * \class CUpwSca_Species
 * \brief Class for doing a scalar upwind solver for the species transport equations.
 * \ingroup ConvDiscr
 */
template <class FlowIndices>
class CUpwSca_Species final : public CUpwScalar<FlowIndices> {
 private:
  using Base = CUpwScalar<FlowIndices>;
  using Base::nVar;
  using Base::nDim;
  using Base::V_i;
  using Base::V_j;
  using Base::a0;
  using Base::a1;
  using Base::Flux;
  using Base::Jacobian_i;
  using Base::Jacobian_j;
  using Base::ScalarVar_i;
  using Base::ScalarVar_j;
  using Base::idx;
  using Base::bounded_scalar;

  /*!
   * \brief Adds any extra variables to AD
   */
  void ExtraADPreaccIn() override {}

  /*!
   * \brief Species transport specific steps in the ComputeResidual method
   * \param[in] config - Definition of the particular problem.
   */
  void FinishResidualCalc(const CConfig* config) override {
    for (auto iVar = 0u; iVar < nVar; iVar++) {
      Flux[iVar] = a0 * V_i[idx.Density()] * ScalarVar_i[iVar] + a1 * V_j[idx.Density()] * ScalarVar_j[iVar];

      /*--- Jacobians are taken wrt rho*Y not Y alone in the species solver. ---*/
      /*--- Off-diagonal entries are zero. ---*/
      Jacobian_i[iVar][iVar] = a0;
      Jacobian_j[iVar][iVar] = a1;
    }  // iVar
  }

 public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CUpwSca_Species(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config)
    : CUpwScalar<FlowIndices>(val_nDim, val_nVar, config) { bounded_scalar = config->GetBounded_Species(); }
};
