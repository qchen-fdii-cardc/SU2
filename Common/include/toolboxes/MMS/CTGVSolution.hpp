/*!
 * \file CTGVSolution.hpp
 * \brief Header file for the class CTGVSolution.
 *        The implementations are in the <i>CTGVSolution.cpp</i> file.
 * \author T. Economon, E. van der Weide
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

#include <cmath>
#include "CVerificationSolution.hpp"

/*!
 * \class CTGVSolution
 * \brief Class to define the required data for the Taylor Green Vortex.
 * \author E. van der Weide, T. Economon
 */
class CTGVSolution final : public CVerificationSolution {
 protected:
  /*--- TGV specific conditions. ---*/

  su2double tgvLength;   /*!< \brief Taylor-Green length scale. */
  su2double tgvVelocity; /*!< \brief Taylor-Green velocity. */
  su2double tgvDensity;  /*!< \brief Taylor-Green density. */
  su2double tgvPressure; /*!< \brief Taylor-Green pressure. */
  su2double ovGm1;       /*!< \brief 1 over Gamma minus 1 */

 public:
  /*!
   * \brief Constructor of the class.
   */
  CTGVSolution(void);

  /*!
   * \overload
   * \param[in] val_nDim  - Number of dimensions of the problem.
   * \param[in] val_nvar  - Number of variables of the problem.
   * \param[in] val_iMesh - Multigrid level of the solver.
   * \param[in] config    - Configuration of the particular problem.
   */
  CTGVSolution(unsigned short val_nDim, unsigned short val_nvar, unsigned short val_iMesh, CConfig* config);

  /*!
   * \brief Destructor of the class.
   */
  ~CTGVSolution(void) override;

  /*!
   * \brief Get the exact solution at the current position and time.
   * \param[in] val_coords   - Cartesian coordinates of the current position.
   * \param[in] val_t        - Current physical time.
   * \param[in] val_solution - Array where the exact solution is stored.
   */
  void GetSolution(const su2double* val_coords, const su2double val_t, su2double* val_solution) const override;

  /*!
   * \brief Whether or not the exact solution is known for this verification solution.
   * \return  - False, because the exact solution is not known for the TGV case.
   */
  bool ExactSolutionKnown(void) const override;
};
