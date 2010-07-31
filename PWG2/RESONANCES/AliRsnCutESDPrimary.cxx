//
// Class AliRsnCutESDPrimary
//
// General implementation of a single cut strategy, which can be:
// - a value contained in a given interval  [--> IsBetween()   ]
// - a value equal to a given reference     [--> MatchesValue()]
//
// In all cases, the reference value(s) is (are) given as data members
// and each kind of cut requires a given value type (Int, UInt, Double),
// but the cut check procedure is then automatized and chosen thanks to
// an enumeration of the implemented cut types.
// At the end, the user (or any other point which uses this object) has
// to use the method IsSelected() to check if this cut has been passed.
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Alberto Pulvirenti (alberto.pulvirenti@ct.infn.it)
//

#include "AliRsnDaughter.h"
#include "AliRsnCutESDPrimary.h"

ClassImp(AliRsnCutESDPrimary)

//_________________________________________________________________________________________________
AliRsnCutESDPrimary::AliRsnCutESDPrimary() :
  AliRsnCut(AliRsnCut::kDaughter),
  fCuts()
{
//
// Default constructor.
//
}

//_________________________________________________________________________________________________
AliRsnCutESDPrimary::AliRsnCutESDPrimary
(const char *name) :
  AliRsnCut(name, AliRsnCut::kDaughter, 0.0, 0.0),
  fCuts()
{
//
// Main constructor.
//
}

//_________________________________________________________________________________________________
Bool_t AliRsnCutESDPrimary::IsSelected(TObject *obj1, TObject* /*obj2*/)
{
//
// Cut checker.
//

  // coherence check
  AliRsnDaughter *daughter = dynamic_cast<AliRsnDaughter*>(obj1);
  if (!daughter) return kFALSE;
  
  // retrieve the TPC signal
  AliESDtrack *esdTrack = daughter->GetRefESDtrack();
  if (!esdTrack) 
  {
    AliError("ESD information unavailable");
    return kTRUE;
  }

  // check cut
  return fCuts.IsSelected(esdTrack);
}
