#ifndef OPENSIM_Delay_H_
#define OPENSIM_Delay_H_
/* -------------------------------------------------------------------------- *
 *                      OpenSim: Delay.h                                      *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2021 Stanford University, TU Delft and the Authors      *
 * Author(s): Ajay Seth, Hjalti Hilmarsson                                    *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied    *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */


//============================================================================
// INCLUDE
//============================================================================
#include "osimDelayDLL.h"
#include "OpenSim/Simulation/Control/Controller.h"
#include "OpenSim/Simulation/Model/Muscle.h"
#include "OpenSim/Common/PiecewiseLinearFunction.h"
#include "OpenSim/Simulation/Model/Model.h"
#include "OpenSim/Simulation/Model/ModelComponent.h"



namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * ToyReflexController is a concrete controller that excites muscles in response
 * to muscle lengthening to simulate a simple stretch reflex. This controller 
 * is meant to serve as an example how to implement a controller in
 * OpenSim. It is intended for demonstration purposes only. 
 *
 * @author  Ajay Seth
 */
class OSIMDELAY_API Delay : public ModelComponent {
OpenSim_DECLARE_CONCRETE_OBJECT(Delay, ModelComponent);

public:
//=============================================================================
// INPUT
//=============================================================================
    // Input the signal from the proprioceptors 
    OpenSim_DECLARE_INPUT(signal, double, SimTK::Stage::Position,
        "The signal from the proprieceptors");
    
//=============================================================================
// PROPERTIES
//=============================================================================
    OpenSim_DECLARE_PROPERTY(delay, double, "The time delay (seconds) between the muscle stretch and the stretch reflex signal");
    
    OpenSim_DECLARE_PROPERTY(defaultControlSignal, double, "the default control signal to send while the signal has not yet gotten their delaied signal");
    
//==============================================================================
// SOCKETS
//==============================================================================
    OpenSim_DECLARE_SOCKET(muscle, Muscle, "The muscle that will have delayed muscle signals");
    
//=============================================================================
// OUTPUTS
//=============================================================================
    // we get our propriceptive afferents
    OpenSim_DECLARE_OUTPUT(controlSignal, double, getSignal, SimTK::Stage::Position);
    //
//=============================================================================
// METHODS
//=============================================================================
    //--------------------------------------------------------------------------
    // CONSTRUCTION AND DESTRUCTION
    //--------------------------------------------------------------------------
    /** Default constructor. */
    Delay();
    Delay(const std::string& name,
          const Muscle& muscle,
          double delay,
          double defaultControlSignal);

    // Uses default (compiler-generated) destructor, copy constructor and copy 
    // assignment operator.
    
//--------------------------------------------------------------------------
// GOLGI TENDON PARAMETER ACCESSORS
//--------------------------------------------------------------------------
    
  // SOCKET get/set
    
    // A reference to the muscle that is having delayed muscle signals
    const Muscle& getMuscle() const;

    void setDelayValue(double delay);
    double getDelayValue() const;
    
    void setDefaultSignal(double defaultControlSignal);
    double getDefaultSignal() const;
          

//--------------------------------------------------------------------------
// GOLGI TENDON STATE DEPENDENT ACCESSORS
//--------------------------------------------------------------------------
/** @name Golgi Tendon State Dependendt Access Methods
    Get quanitites of interest common to all spindles*/
    void setSignal(SimTK::State& s, double controlSignal) const;
    double getSignal(const SimTK::State& s) const;
    
        

private:
    // Connect properties to local pointers.  */
    void constructProperties();
    // ModelComponent interface to connect this component to its model
    void extendConnectToModel(Model& aModel) override;
    // ModelComponent interface to add computational elemetns to the SimTK system
    void addToSystem(SimTK::MultibodySystem& system) const;
    
    mutable PiecewiseLinearFunction muscleHistory;

    
protected:
    //=========================================================================
};  // END of class Delay

}; //namespace
//=============================================================================
//=============================================================================

#endif // OPENSIM_Delay_H_


